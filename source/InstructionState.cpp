//*********************************************************************//
//	File:		InstructionState.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make InstructionState and set and make variables 
//
//*********************************************************************//

#include "InstructionState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "BitmapFont.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include <ctime>
#include <cstdlib>
#include <cassert>
#include "CellAnimation.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>



InstructionState* InstructionState::GetInstance()
{
	static InstructionState m_Instance;

	return &m_Instance;
}

void InstructionState::Enter()
{
	InitializeAnimation();
	m_ulGameTime = GetTickCount();
	Keys[0] = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Bab_CKey.png");
	Keys[1] = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Bab_ZKey.png");
	Keys[2] = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Bab_VKey.png");
	Keys[3] = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Bab_BKey.png");
}

void InstructionState::Exit()
{

	for (unsigned int i = 0; i < 4; i++)
	{
		delete YusukeAnimation[i];
	}
	for (unsigned int i = 0; i < 5; i++)
	{
		SGD::GraphicsManager::GetInstance()->UnloadTexture(Animation_Image[i]);

	}
	for (unsigned int i = 0; i < 4; i++)
	{
		SGD::GraphicsManager::GetInstance()->UnloadTexture(Keys[i]);

	}
	for ( unsigned int i = 0; i < 1; i++)
	{
		delete KuramaAnimation[i];
	}

}

bool InstructionState::Update(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	unsigned long now = GetTickCount();
	float ElapsedTime = (now - m_ulGameTime) / 1000.0f;
	m_ulGameTime = now;
	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true && Game::GetInstance()->CheckPriveous() == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == true)
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
	}
	else if (pInput->IsKeyPressed(SGD::Key::Escape) == true && Game::GetInstance()->CheckPriveous() == false || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == false)
	{
		Game::GetInstance()->Pause(GameplayState::GetInstance());
	}
	else
	{


		if (KuramaAnimation[KuramaCurrentAnimation]->IsLooping() == true && KuramaAnimation[KuramaCurrentAnimation]->IsFinished() == false)
		{
			KuramaAnimation[KuramaCurrentAnimation]->Update(elapsedTime);


		}
		else
		{
			KuramaCurrentAnimation = 0;

		}

		if (YusukeAnimation[CurrentAnimation]->IsLooping() == false && YusukeAnimation[CurrentAnimation]->IsFinished() == false)
		{
			YusukeAnimation[CurrentAnimation]->Update(elapsedTime);


		}
		else
		{
			CurrentAnimation = 0;
			m_pressed2 = 255;
			m_pressed3 = 255;
		}

		if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::C) || SGD::InputManager::GetInstance()->IsDPadDown(0,SGD::DPad::Right))
		{

			if (CurrentAnimation != 1)
			{
				CurrentAnimation = 1;
				m_pressed = 0;
				Turn = true;
			}

		}
		else if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::Z) || SGD::InputManager::GetInstance()->IsDPadDown(0, SGD::DPad::Left))
		{
			if (CurrentAnimation != 1)
			{
				CurrentAnimation = 1;
				m_pressed1 = 0;
				Turn = false;
			}
		}
		else if (SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::C) || SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::Z) || SGD::InputManager::GetInstance()->IsDPadReleased(0, SGD::DPad::Left) || SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::Z) || SGD::InputManager::GetInstance()->IsDPadReleased(0, SGD::DPad::Left) || SGD::InputManager::GetInstance()->IsDPadReleased(0, SGD::DPad::Right))
		{
			CurrentAnimation = 0;
			m_pressed = 255;
			m_pressed1 = 255;
		}
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::V) || SGD::InputManager::GetInstance()->IsButtonPressed(0,1))
		{

			if (CurrentAnimation != 2)
			{
				CurrentAnimation = 2;

				m_pressed2 = 0;
			}
			YusukeAnimation[CurrentAnimation]->Restart(false, 9.0);
		}

		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::B) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 2))
		{
			if (CurrentAnimation != 3)
			{
				CurrentAnimation = 3;
				m_pressed3 = 0;
			}
			YusukeAnimation[CurrentAnimation]->Restart(false, 9.0);

		}
		YusukeAnimation[CurrentAnimation]->Update(elapsedTime);
		KuramaAnimation[KuramaCurrentAnimation]->Restart(true, 5.0);
		KuramaAnimation[KuramaCurrentAnimation]->Update(elapsedTime);


	}
	
	return true;
}

void  InstructionState::Render(float elapsedTime)
{
	BitmapFont* pFont = Game::GetInstance()->GetFont();

	pFont->Draw("How To Play", SGD::Point{ 300, 0 },1.0);
	pFont->Draw("This Is Yusuke", SGD::Point{ 0, 100 },0.5);
	pFont->Draw("This Is Kurama", SGD::Point{ 800, 100 }, 0.5);
	pFont->Draw("He is Your Enemy", SGD::Point{ 770, 220 }, 0.5);
	pFont->Draw("Bring Kuramas Health to zero by shoting projectiles at him", SGD::Point{ 50, 40 },0.5);
	YusukeAnimation[CurrentAnimation]->Render(SGD::Point{40, 120 }, 2, {}, Turn);
	pFont->Draw("Movement Press To See", SGD::Point{ 0, 220 }, 0.5);
	SGD::GraphicsManager::GetInstance()->DrawTexture(Keys[0], SGD::Point{ 100, 250 }, {}, {}, SGD::Color{ 255, 255, (unsigned char)(m_pressed), });
	SGD::GraphicsManager::GetInstance()->DrawTexture(Keys[1], SGD::Point{ 0, 250 }, {}, {}, SGD::Color{ 255, 255, (unsigned char)(m_pressed1), });
	pFont->Draw("How to Shoot Press to See", SGD::Point{ 0, 320 }, 0.5);
	pFont->Draw("Spirit Gun", SGD::Point{ 0, 350 }, 0.5);
	SGD::GraphicsManager::GetInstance()->DrawTexture(Keys[2], SGD::Point{ 0, 370 }, {}, {}, SGD::Color{ 255, 255, (unsigned char)(m_pressed2), });
	pFont->Draw("Shot Gun", SGD::Point{ 210, 350 }, 0.5, SGD::Color{ 255, 255, 255, 0 });
	SGD::GraphicsManager::GetInstance()->DrawTexture(Keys[3], SGD::Point{ 210, 370 }, {}, {}, SGD::Color{ 255, 255, (unsigned char)(m_pressed3), });
	KuramaAnimation[KuramaCurrentAnimation]->Render(SGD::Point{ 1000, 110 }, 2, {}, false);
	pFont->Draw(" You Will have to bring his health to Zero \n \n Before he makes your Health zero \n \n You will Also have a Spirirt EnergyBar \n \n in blue That will determine if  \n \n you can shoot or not \n \n Every Shot Will Take Away \n \n Twenty Five out of One Hundered \n\n Spirit Energy", SGD::Point{ 470, 260 }, float(0.4), SGD::Color{255,0,255,255});
}

void InstructionState::InitializeAnimation(void)
{
	Animation_Image[0] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeIdle_strip4.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[0] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[0]->SetImage(Animation_Image[0]);
	YusukeAnimation[0]->Initialize(0, 4, 40, 55, 4, 8.0, true);

	Animation_Image[1] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeRunning_strip8.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[1] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[1]->SetImage(Animation_Image[1]);
	YusukeAnimation[1]->Initialize(0, 8, 50, 60, 8, 8.0, true);

	Animation_Image[2] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeSpiritGun1_strip10.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[2] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[2]->SetImage(Animation_Image[2]);
	YusukeAnimation[2]->Initialize(0, 14, 55, 70, 14, 8.0, false);

	Animation_Image[3] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeShotGun_strip13.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[3] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[3]->SetImage(Animation_Image[3]);
	YusukeAnimation[3]->Initialize(0, 13, 65, 70, 13, 8.0, false);


	Animation_Image[4] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_KuramaIdle_strip4.png");

	KuramaAnimation[0] = new CellAnimation(0, {}, 1.0);
	KuramaAnimation[0]->SetImage(Animation_Image[4]);
	KuramaAnimation[0]->Initialize(0, 4, 30, 70, 4, 8.0, true);

	CurrentAnimation = 0;
	KuramaCurrentAnimation = 0;
}
