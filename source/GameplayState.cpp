//*********************************************************************//
//	File:		GameplayState.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure of Game Design
//	Purpose:	GameplayState class initializes & runs the game logic
//*********************************************************************//

#include "GameplayState.h"

#include "Game.h"
#include "MainMenuState.h"
#include "CreditsState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_Utilities.h"
#include "InstructionState.h"
#include "OptionsState.h"
#include "CreditsState.h"

#include "../SGD Wrappers/SGD_EventManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyEntityMessage.h"
#include "CreateKuramaEnergyBall.h"
#include "Yusuke.h"
#include "Kurama.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"
#include "EnergyBall.h"
#include "BitmapFont.h"
#include "ShotGun.h"
#include "EntityManager.h"
#include "Entity.h"
#include "KuramaEnergyBeam.h"
#include "CreateSpiritGunBeamMessage.h"
#include "CreateShotGunMessage.h"
#include "CreateSpiritGunBeamMessage.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdlib>
#include <cassert>


//*********************************************************************//
// GetInstance
//	- allocate static global instance
//	- return THE instance
/*static*/ GameplayState* GameplayState::GetInstance(void)
{
	static GameplayState s_Instance;	// stored in global memory once
	return &s_Instance;
}


//*********************************************************************//
// Enter
//	- reset game
//	- load resources / assets
//	- allocate & initialize game entities
/*virtual*/ void GameplayState::Enter(void)	/*override*/
{
	// Initialize the Event & Message Managers
	SGD::EventManager::GetInstance()->Initialize();
	SGD::MessageManager::GetInstance()->Initialize(&GameplayState::MessageProc);

	EnergyBeam = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Weapons/Bab_SpiritEnergy.png");
	//EnergyBeam = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/YusukeUrimeshi.png");
	m_backround = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Backrounds/Bab_YuyuStage.png");
	
	//m_backround = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Backrounds/YuyuStage.png");
	GettingHurt = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Damage 00.wav");
	BigEnergyBall = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Weapons/Bab_EnergyBall.png");
	YusukeUrimeshi = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeUrimeshi.png");
	YokoKurama = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_YokoKurama.png");
	KuramaAttack = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Weapons/Bab_KuramaEnergyBall.png");
	SpiritGunAudio = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_JinVsYusuke.wav");
	ShotGunAudio = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_ShotGun.wav");
	MainMusic = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Yu-yu Hakusho Battle Music.xwm");
	
		//MainMusic = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/You Shall Not Pass.wav");
	GettingHurt2 = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Damage Yell 02.wav");
	YusukeWins = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_YusukeWins.wav");
	//	KuramaWins = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Kurama Wins.wav");
	SGD::AudioManager::GetInstance()->PlayAudio(MainMusic, true);
	SGD::AudioManager::GetInstance()->SetAudioVolume(MainMusic, 30);
	// Allocate the Entity Manager
	m_pEntities = new EntityManager;
	m_Yusuke = CreateYusuke();
	m_pEntities->AddEntity(m_Yusuke, 0);
	//m_Yusuke->Release();

	Kurma = CreateKurama();
	m_pEntities->AddEntity(Kurma, 0);
	//Kurma->Release();




}


//*********************************************************************//
// Exit
//	- deallocate entities
//	- unload resources / assets
/*virtual*/ void GameplayState::Exit(void)	/*override*/
{
	m_Pause = false;
	m_Yusuke->Release();
	Kurma->Release();

	win = false;
	lose = false;
	timer = 0.0f;
	// Release game entities
	if (m_pEntities != nullptr)
	{
		m_pEntities->RemoveAll();
		delete m_pEntities;
		m_pEntities = nullptr;
	}

	SGD::AudioManager::GetInstance()->UnloadAudio(YusukeWins);
	SGD::AudioManager::GetInstance()->UnloadAudio(MainMusic);
	SGD::AudioManager::GetInstance()->UnloadAudio(GettingHurt);
	SGD::AudioManager::GetInstance()->UnloadAudio(SpiritGunAudio);
	SGD::AudioManager::GetInstance()->UnloadAudio(ShotGunAudio);
	SGD::AudioManager::GetInstance()->UnloadAudio(GettingHurt2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_backround);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(EnergyBeam);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(BigEnergyBall);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(YusukeUrimeshi);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(YokoKurama);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(KuramaAttack);

	// Terminate & deallocate the SGD wrappers
	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::DeleteInstance();

	SGD::EventManager::GetInstance()->Terminate();
	SGD::EventManager::DeleteInstance();
}


//*********************************************************************//
// Update
//	- handle input & update entities
/*virtual*/ bool GameplayState::Update(float elapsedTime)	/*override*/
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	// Press Escape to return to MainMenuState
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 2))
	{
		// ChangeState is VERY VOLATILE!!!
		//	- can only be safely called by a game state's
		//	  Update or Render methods!
		if (!m_Pause)
		{
			m_Pause = true;
		}
		else
		{
			m_Pause = false;
		}


		// Exit this state immediately
		// keep playing in the new state
	}



	SGD::GraphicsManager::GetInstance()->DrawTexture(m_backround, SGD::Point{ 0, 0 });
	// Update the entities]

	if (m_Pause)
	{
		Pause();
	}
	// Process the Message Manager
	//	- all the messages will be sent to our MessageProc
	else
	{


		m_pEntities->UpdateAll(elapsedTime);
		SGD::MessageManager::GetInstance()->Update();
		SGD::EventManager::GetInstance()->Update();
		m_pEntities->CheckCollisions(0, 1);
		if (dynamic_cast<Kurama*>(Kurma)->GetKuramaHealth() <= 1 || dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesHealth() <= 1)
		{

			if (dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesHealth() <= 1)
			{
				lose = true;
			}
			else if (dynamic_cast<Kurama*>(Kurma)->GetKuramaHealth() <= 1)
			{
				win = true;
				Wins++;
			}
			//m_Yusuke->Release();
			//Kurma->Release();
			if (timer == 0.0f)
			{
				timer = 8.0f;
				//SGD::AudioManager::GetInstance()->PlayAudio(YusukeWins);
			}

		}

		if (timer > 0)
		{
			timer -= elapsedTime;
		}
		if (dynamic_cast<Kurama*>(Kurma)->GetKuramaHealth() <= 1 && timer <= 0.0f)
		{

			//Kurma->Release();
			//m_Yusuke->Release();
			Game::GetInstance()->ChangeState(CreditsState::GetInstance());
		}
		else if (dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesHealth() <= 1 && timer <= 0.0f)
		{
			Game::GetInstance()->ChangeState(CreditsState::GetInstance());
		}



	}
	return true;
	// keep playing
}


//*********************************************************************//
// Render
//	- render the game entities
/*virtual*/ void GameplayState::Render(float elapsedTime)	/*override*/
{
	if (m_Pause)
	{
		
		BitmapFont* pFont = Game::GetInstance()->GetFont();
		SGD::GraphicsManager::GetInstance()->DrawTexture(YusukeUrimeshi, SGD::Point{ 0, 0 });
		SGD::OStringStream output;
		SGD::OStringStream output1;
		SGD::OStringStream output2;
		SGD::OStringStream output3;
		SGD::OStringStream output4;
		SGD::OStringStream output5;
		SGD::OStringStream output6;
		output << "Points: " << dynamic_cast<Yusuke*>(m_Yusuke)->GetScore();
		output1 << "Health:" << dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesHealth();
		output2 << "Health:" << dynamic_cast<Kurama*>(Kurma)->GetKuramaHealth();
		output3 << "Spirit Energy" << dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesSpiritEnergy();
		output4 << "Spirit Energy" << dynamic_cast<Kurama*>(Kurma)->GetKuramaSpiritEnergy();
		output6 << "Wins:" << Wins;
		output5 << timer;
		pFont->Draw("Yusuke", SGD::Point{ 60, 0 });
		pFont->Draw(output.str().c_str(), SGD::Point{ 60, 30 }, 0.5);
		pFont->Draw(output1.str().c_str(), SGD::Point{ 60, 45 }, 0.5);
		pFont->Draw(output3.str().c_str(), SGD::Point{ 60, 58 }, 0.5);
		pFont->Draw(output6.str().c_str(), SGD::Point{ 60, 68 }, 0.5);
		pFont->Draw("FIght To the Death", SGD::Point{ 380, 80 }, 0.5);
		pFont->Draw("VS", SGD::Point{ 480, 0 });
		pFont->Draw("Kurama", SGD::Point{ 770, 0 });
		pFont->Draw(output2.str().c_str(), SGD::Point{ 770, 30 }, 0.5);
		pFont->Draw(output4.str().c_str(), SGD::Point{ 680, 48 }, 0.5);
		SGD::GraphicsManager::GetInstance()->DrawTexture(YokoKurama, SGD::Point{ 960, 0 });
		m_pEntities->RenderAll();
		RenderPause();
	}
	else
	{


		BitmapFont* pFont = Game::GetInstance()->GetFont();
		SGD::GraphicsManager::GetInstance()->DrawTexture(YusukeUrimeshi, SGD::Point{ 0, 0 });
		SGD::OStringStream output;
		SGD::OStringStream output1;
		SGD::OStringStream output2;
		SGD::OStringStream output3;
		SGD::OStringStream output4;
		SGD::OStringStream output5;
		SGD::OStringStream output6;
		output << "Points: " << dynamic_cast<Yusuke*>(m_Yusuke)->GetScore();
		output1 << "Health:" << dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesHealth();
		output2 << "Health:" << dynamic_cast<Kurama*>(Kurma)->GetKuramaHealth();
		output3 << "Spirit Energy" << dynamic_cast<Yusuke*>(m_Yusuke)->GetYusukesSpiritEnergy();
		output4 << "Spirit Energy" << dynamic_cast<Kurama*>(Kurma)->GetKuramaSpiritEnergy();
		output6 << "Wins:" << Wins;
		output5 << timer;
		pFont->Draw("Yusuke", SGD::Point{ 60, 0 });
		pFont->Draw(output.str().c_str(), SGD::Point{ 60, 30 }, 0.5);
		pFont->Draw(output1.str().c_str(), SGD::Point{ 60, 45 }, 0.5);
		pFont->Draw(output3.str().c_str(), SGD::Point{ 60, 58 }, 0.5);
		pFont->Draw(output6.str().c_str(), SGD::Point{ 60, 68 }, 0.5);
		pFont->Draw("FIght To the Death", SGD::Point{ 380, 80 }, 0.5);
		pFont->Draw("VS", SGD::Point{ 480, 0 });
		pFont->Draw("Kurama", SGD::Point{ 770, 0 });
		pFont->Draw(output2.str().c_str(), SGD::Point{ 770, 30 }, 0.5);
		pFont->Draw(output4.str().c_str(), SGD::Point{ 680, 48 }, 0.5);
		SGD::GraphicsManager::GetInstance()->DrawTexture(YokoKurama, SGD::Point{ 960, 0 });
		if (win)
		{
			pFont->Draw("You Win", SGD::Point{ 570, 200 });
			pFont->Draw(output.str().c_str(), SGD::Point{ 570, 240 }, 0.5);
			pFont->Draw(output5.str().c_str(), SGD::Point{ 300, 0 }, 0.5);
			//SGD::AudioManager::GetInstance()->PlayAudio(YusukeWins);
		}
		else if (lose)
		{
			pFont->Draw("You Lose", SGD::Point{ 570, 200 });
			pFont->Draw(output.str().c_str(), SGD::Point{ 570, 240 }, 0.5);
			pFont->Draw(output5.str().c_str(), SGD::Point{ 300, 0 }, 0.5);
		}

		// Render the entities
		m_pEntities->RenderAll();
	}
	
}


//*********************************************************************//
// MessageProc
//	- process messages queued in the MessageManager
//	- STATIC METHOD!!!
//		- no invoking object!
//		- MUST USE THE SINGLETON
/*static*/ void GameplayState::MessageProc(const SGD::Message* pMsg)
{
	/* Show warning when a Message ID enumerator is not handled */
#pragma warning( push )
#pragma warning( 1 : 4061 )


	// What type of message?
	switch (pMsg->GetMessageID())
	{
	case MessageID::MSG_CREATE_ENERGYBALL:
	{
											 const CreateSpiritGunBeamMessage* CreateBeamMessage = dynamic_cast<const CreateSpiritGunBeamMessage*>(pMsg);
											 Entity* EneryBall = (GameplayState::GetInstance()->CreateEnergyBall(CreateBeamMessage->GetYusukeOwner()));
											 GameplayState::GetInstance()->m_pEntities->AddEntity(EneryBall, 1);
											 EneryBall->Release();
											 EneryBall = nullptr;

											 break;



	}
	case MessageID::MSG_CREATE_SHOT_GUN:
	{
										   const CreateShotGunMessage* CreateShotGun = dynamic_cast<const CreateShotGunMessage*>(pMsg);
										   Entity* EnergyBall = (GameplayState::GetInstance()->CreateEnergyBeamBall(CreateShotGun->GetYusukeOwner()));
										   GameplayState::GetInstance()->m_pEntities->AddEntity(EnergyBall, 1);
										   EnergyBall->Release();
										   EnergyBall = nullptr;
										   break;
	}
	case MessageID::MSG_DESTROY_ENITY:
	{

										 const DestroyEntityMessage* DestroyMsg = dynamic_cast<const DestroyEntityMessage*>(pMsg);

										 // Access the entity attached to the child message
										 Entity* pEntity = DestroyMsg->GetEntityMessage();

										 // Use the game singleton!
										 GameplayState::GetInstance()->m_pEntities->RemoveEntity(pEntity);
										 break;
	}
	case MessageID::KURAMA_ENERGY_BALL:
	{

										  const CreateKuramaEnergyBall* kurama = dynamic_cast<const CreateKuramaEnergyBall*>(pMsg);
										  Entity* EnergyBall = (GameplayState::GetInstance()->CreatKuramaEnergyBall(kurama->GetKuramaOwner()));
										  GameplayState::GetInstance()->m_pEntities->AddEntity(EnergyBall, 1);
										  EnergyBall->Release();
										  EnergyBall = nullptr;
										  break;

	}

	default:
	case MessageID::MSG_UNKNOWN:
		SGD_PRINT(L"GameplayState::MessageProc - unknown message id\n");
		break;
	}


	/* Restore previous warning levels */
#pragma warning( pop )
}

Entity* GameplayState::CreateYusuke(void)
{
	Yusuke* Urimeshi = new Yusuke;
	Urimeshi->SetSpiritEnergy(100.0f);
	Urimeshi->InitializeAnimation();
	Urimeshi->SetHealth(100.0f);
	Urimeshi->SetSpiritGun(SpiritGunAudio);
	Urimeshi->SetShotGunAudio(ShotGunAudio);
	Urimeshi->SetPosition(SGD::Point{ 70, 400 });
	Urimeshi->SetAcceleration(50.0f);
	Urimeshi->SetSpeed(100.0f);
	Urimeshi->SetGetHurtAudio(GettingHurt2);
	Urimeshi->SetGetWinAudio(YusukeWins);
	//	Urimeshi->SetTarget(dynamic_cast<Kurama*>(Kurma));
	return Urimeshi;
}

Entity*  GameplayState::CreateEnergyBall(Yusuke* _energy)
{
	EnergyBall* temp = new EnergyBall;
	temp->SetImage(EnergyBeam);
	
	SGD::Vector newVelcoity = { 1, 0 };
	temp->SetSize(SGD::Size{ 128, 128 });
	if (_energy->GetTurn())
	{
		newVelcoity.x *= 200 + _energy->GetSpeed();
		temp->SetPosition(_energy->GetPosition() + SGD::Vector{90,0});
	//newVelcoity.y *= 200 + _energy->GetSpeed();
	}
	else
	{
		newVelcoity.x *= -(200 + _energy->GetSpeed());
		temp->SetPosition(_energy->GetPosition() + SGD::Vector{ -90, 0 });
	}

	temp->SetVelocity(newVelcoity);
	temp->SetYusuke(_energy);
	return temp;

}

Entity*  GameplayState::CreateEnergyBeamBall(Yusuke* _energy)
{
	ShotGun* temp = new ShotGun;
	temp->SetImage(BigEnergyBall);
	//temp->SetPosition(_energy->GetPosition());
	SGD::Vector newVelcoity = { 1, 0 };
	temp->SetSize(SGD::Size{ 120, 80 });
	if (_energy->GetTurn())
	{
		newVelcoity.x *= 200 + _energy->GetSpeed();
		temp->SetPosition(_energy->GetPosition() + SGD::Vector{ 90, 0 });
		//newVelcoity.y *= 200 + _energy->GetSpeed();
	}
	else
	{
		newVelcoity.x *= -(200 + _energy->GetSpeed());
		temp->SetPosition(_energy->GetPosition() + SGD::Vector{ -90, 0 });
	}
	
	temp->SetVelocity(newVelcoity);
	temp->SetYusuke(_energy);
	return temp;

}

Entity* GameplayState::CreateKurama(void)
{
	Kurama* Temp = new Kurama;
	Temp->SetPosition(SGD::Point{ Game::GetInstance()->GetScreenSize().width - 32, Game::GetInstance()->GetScreenSize().height - 130 });
	Temp->SetHealth(150.0f);
	Temp->InitializeAnimation();
	Temp->SetSpiritEnergy(150.0f);
	Temp->SetSpeed(100.0f);
	Temp->SetGettingHurtSound(GettingHurt);
	//Temp->SetWn(KuramaWins);
	return Temp;



}
Entity* GameplayState::CreatKuramaEnergyBall(Kurama* _energy)
{
	KuramaEnergyBeam* temp = new KuramaEnergyBeam;
	temp->SetImage(KuramaAttack);
	temp->SetPosition(_energy->GetPosition());
	SGD::Vector newVelcoity = { 1, 0 };
	temp->SetSize(SGD::Size{ 128, 128 });
	newVelcoity.x *= 200 + _energy->GetSpeed();
	newVelcoity.y *= 200 + _energy->GetSpeed();
	temp->SetVelocity(newVelcoity);
	temp->SetKurama(_energy);
	return temp;

}
void GameplayState::Pause()
{

	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Down) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Down))
	{
		// next option
		m_cursor++;

		// wrap around
		if (m_cursor > 4)
			m_cursor = 0;
	}
	else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Up) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Up))
	{
		// prev option
		m_cursor--;

		// wrap around
		if (m_cursor < 0)
			m_cursor = 4;
	}

	if (m_cursor == 0 && SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Enter) == true) //m_nCursor == 1
	{
		m_Pause = false;
	}
	else if (m_cursor == 1 && SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Enter) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && m_cursor == 1  )
	{
		Game::GetInstance()->Pause(InstructionState::GetInstance());
	}
	else if (m_cursor == 2 && SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Enter) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && m_cursor == 2 )
	{
		Game::GetInstance()->Pause(CreditsState::GetInstance());

	}
	else if (m_cursor == 3 && SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Enter) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && m_cursor == 3 )
	{
		Game::GetInstance()->Pause(OptionsState::GetInstance());

	}
	else if (m_cursor == 4 && SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Enter) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && m_cursor == 4 )
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
	}






}
void  GameplayState::RenderPause()
{

	// Access the bitmap font
	BitmapFont* pFont = Game::GetInstance()->GetFont();


	// Align text based on window width
	float width = Game::GetInstance()->GetScreenSize().width;

	pFont->Draw("Resume", { (width - (4 * 30)) / 2, 130 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("How To Play", { (width - (4 * 80)) / 2, 180 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Credits", { (width - (4 * 50)) / 2, 230 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Options", { (width - (4 * 50)) / 2, 280 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Exit", { (width - (4 * 32)) / 2, 320 },
		1.0f, { 255, 255, 255, });

	// Display the cursor next to the option
	pFont->Draw("\t=", { (width - (7 * 100)) / 2, 130.0f + 50 * m_cursor },
		1.0f, { 0, 255, 0 });
}
