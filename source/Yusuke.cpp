//*********************************************************************//
//	File:		Yusuke.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke Urimeshi
//*
//*********************************************************************//

#include "Yusuke.h"
#include "CellAnimation.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "CreateSpiritGunBeamMessage.h"
#include "CreateShotGunMessage.h"
#include "../SGD Wrappers/SGD_IListener.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "../SGD Wrappers/SGD_IListener.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "Kurama.h"

Yusuke::Yusuke()
{
	SGD::IListener::RegisterForEvent("YUSUKE_HIT");
}


Yusuke::~Yusuke()
{
	for (size_t i = 0; i < 7; i++)
	{
		delete YusukeAnimation[i];
	}
	for (size_t i = 0; i < 7; i++)
	{
		SGD::GraphicsManager::GetInstance()->UnloadTexture(Animation_Image[i]);

	}
	SGD::AudioManager::GetInstance()->UnloadAudio(KuramaWins);

}
void Yusuke::Update(float elapsedTime)
{
	SGD::Event* HitEvent = new SGD::Event("M_YUSUKE", nullptr, this);
	SGD::EventManager::GetInstance()->QueueEvent(HitEvent, nullptr);

	if (YusukeAnimation[CurrentAnimation]->IsLooping() == false && YusukeAnimation[CurrentAnimation]->IsFinished() == false)
	{
		YusukeAnimation[CurrentAnimation]->Update(elapsedTime);
		m_vtVelocity.x = 0;

	}
	else
	{
		CurrentAnimation = 0;
	}
	if (WinLose)
	{

	}
	else
	{
		if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::Control) && SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::Shift) && SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::A))
		{
			CheatOn = true;
		}
		// What his else if is doing is When the C Key is pressed Yusuke runs to the Left facing the Left.
		if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::C) || SGD::InputManager::GetInstance()->IsDPadDown(0, SGD::DPad::Right))
		{

			if (CurrentAnimation != 1)
			{
				// ************************NEEDS TO BE WORKED ON FOR THE MOVEMENT RIGHT NOW IT WORKS BUT IT WILL NOT WORK LATER********************
				// switch the Animation to Yusuke Runing 
				CurrentAnimation = 1;

				//m_speed += m_aceleration + elapsedTime;
				m_vtVelocity.x += 0.2f;
				Turn = true;
			}

		}
		// What his else if is doing is When the Z Key is pressed Yusuke runs to the right facing the right. 
		else if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::Z) || SGD::InputManager::GetInstance()->IsDPadDown(0, SGD::DPad::Left))
		{
			if (CurrentAnimation != 1)
			{
				CurrentAnimation = 1;
				//m_speed += m_aceleration + elapsedTime;
				m_vtVelocity.x -= 0.2f;
				Turn = false;
			}
		}
		else if (SGD::InputManager::GetInstance()->IsKeyDown(SGD::Key::X))
		{
			CurrentAnimation = 5;
			if (m_SpiritEnergy < 100)
			{
				m_SpiritEnergy += 5;
			}
			//m_speed += m_aceleration + elapsedTime;
			YusukeAnimation[CurrentAnimation]->Restart(false, 5.0);
		}

		// What this else if Does when The Keys C or Z are released Yusuke Will go back to his Idle animation 
		else if (SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::C) || SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::Z) || SGD::InputManager::GetInstance()->IsDPadReleased(0, SGD::DPad::Left) || SGD::InputManager::GetInstance()->IsDPadReleased(0, SGD::DPad::Right) || SGD::InputManager::GetInstance()->IsKeyReleased(SGD::Key::X))
		{
			CurrentAnimation = 0;
			m_vtVelocity.x = 0;
		}
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::V) && m_SpiritEnergy > 25 && Timer <= 0 || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && m_SpiritEnergy > 25 && Timer <= 0.0f)
		{

			if (CurrentAnimation != 2)
			{
				CurrentAnimation = 2;
				SGD::AudioManager::GetInstance()->PlayAudio(SpiritGun);
				if (m_SpiritEnergy < 25)
					return;
				else
					m_SpiritEnergy -= 25;
			}
			YusukeAnimation[CurrentAnimation]->Restart(false, 5.0);
		}

		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::B) && m_SpiritEnergy > 25 && TimerShotGun <= 0.0f || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && m_SpiritEnergy > 25 && TimerShotGun <= 0.0f)
		{
			if (CurrentAnimation != 3)
			{
				CurrentAnimation = 3;
				SGD::AudioManager::GetInstance()->PlayAudio(ShotGunAudio);
				if (m_SpiritEnergy < 25)
					return;
				else
					m_SpiritEnergy -= 25;
			}
			YusukeAnimation[CurrentAnimation]->Restart(false, 5.0);

		}
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Spacebar))
		{
			if (CurrentAnimation != 4)
			{
				CurrentAnimation = 4;

			}
			YusukeAnimation[CurrentAnimation]->Restart(false, 5.0);

		}

		// What this is doing is everytime an animation is set it will update the animation and it will play it, in it entirty

		if (YusukeAnimation[2]->GetCurrentFrame() == 8 && Timer <= 0.0f)
		{


			CreateSpiritGunBeamMessage* Eneryball = new CreateSpiritGunBeamMessage(this);
			SGD::MessageManager::GetInstance()->QueueMessage(Eneryball);
			Eneryball = nullptr;
			Timer = 2.0f;

		}
		if (YusukeAnimation[3]->GetCurrentFrame() == 9 && TimerShotGun <= 0.0f)
		{
			CreateShotGunMessage* EnergyBall = new CreateShotGunMessage(this);
			SGD::MessageManager::GetInstance()->QueueMessage(EnergyBall);
			TimerShotGun = 3.0f;

		}
		/*if (YusukeAnimation[4]->GetCurrentFrame() == 3)
		{
		m_ptPosition.y -= 0.4f;
		}
		else if (YusukeAnimation[4]->GetCurrentFrame() == 5)
		{
		m_ptPosition.y += 0.2f;
		}*/
		// What this is doing is going to the Parents Update function and updating it position
		if (m_SpiritEnergy < 100)
		{
			m_SpiritEnergy += elapsedTime;
		}
		if (Timer > 0)
			Timer -= elapsedTime;
		if (TimerShotGun > 0)
			TimerShotGun -= elapsedTime;

		YusukeAnimation[CurrentAnimation]->Update(elapsedTime);
		Entity::Update(elapsedTime);
		StayinWorldCollision();

	}
}

void Yusuke::Render(void)
{
	// Yususke Animation Will render Yusuke on the screen right now at 600 X position and 0 Y position 
	// NOT FIXED?
	float temp = (m_Health / 100.0f) * 50.0f;
	float tem2 = (m_SpiritEnergy / 100.0f) * 50.0f;


	YusukeAnimation[CurrentAnimation]->Render(SGD::Point{ GetPosition().x, GetPosition().y }, 2, {}, Turn);
	if (Turn)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x + 20, GetPosition().y - 40 }, SGD::Size{ temp, 10 }), SGD::Color{ 255, 255, 0, 0 }, SGD::Color{ 0, 0, 0, 0 }, 2);
		SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x + 20, GetPosition().y - 30 }, SGD::Size{ tem2, 10 }), SGD::Color{ 255, 0, 0, 255 }, SGD::Color{ 0, 0, 0, 0 }, 2);
		//SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 0, 0, 0, 0 }, { 255, 255, 0, 0 }, 2);
	}
	else
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x - 20, GetPosition().y - 40 }, SGD::Size{ temp, 10 }), SGD::Color{ 255, 255, 0, 0 }, SGD::Color{ 0, 0, 0, 0 }, 2);
		SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x - 20, GetPosition().y - 30 }, SGD::Size{ tem2, 10 }), SGD::Color{ 255, 0, 0, 255 }, SGD::Color{ 0, 0, 0, 0 }, 2);
	}

}

void Yusuke::InitializeAnimation(void)
{
	// Getting an Htexture so that we can see Yusuke on the screen 
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

	Animation_Image[4] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeJumping_strip6.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[4] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[4]->SetImage(Animation_Image[4]);
	YusukeAnimation[4]->Initialize(0, 6, 45, 70, 6, 8.0, false);

	Animation_Image[5] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeCharge_strip8.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[5] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[5]->SetImage(Animation_Image[5]);
	YusukeAnimation[5]->Initialize(0, 8, 75, 70, 8, 8.0, false);


	Animation_Image[6] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Yusuke/Bab_YusukeGettingHurt_strip16.png");

	// Setting the HTexture Image to the CellAnimation SetImage
	YusukeAnimation[6] = new CellAnimation(0, {}, 1.0);
	YusukeAnimation[6]->SetImage(Animation_Image[6]);
	YusukeAnimation[6]->Initialize(0, 14, 50, 70, 14, 8.0, false);
	CurrentAnimation = 0;
}

SGD::Rectangle Yusuke::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x, GetPosition().y }, SGD::Size{ 90, 100 });

}

void  Yusuke::HandleEvent(const SGD::Event* pEvent)
{
	if (CheatOn)
	{

	}
	else
	{
		if (pEvent->GetEventID() == "YUSUKE_HIT")
		{
			CurrentAnimation = 6;
			SGD::AudioManager::GetInstance()->PlayAudio(GetHurt, false);
			YusukeAnimation[CurrentAnimation]->Restart(false, 5.0);
			m_Health -= 20.0f;


		}
	}

	if (m_Health <= 0)
	{
		SetHealth(1);
		WinLose = true;
		reinterpret_cast<Kurama*>(pEvent->GetSender())->SetWin(true);
		SGD::AudioManager::GetInstance()->PlayAudio(KuramaWins);
	}
}

int	Yusuke::GetType(void) const
{
	return ENT_YUSUKE;
}

void Yusuke::StayinWorldCollision(void)
{
	if (m_ptPosition.x < 30)
	{
		m_ptPosition.x = 30;
	}
	if (m_ptPosition.x > 950)
	{
		m_ptPosition.x = 950;
	}


}