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
#include "Hiei.h"

Hiei::Hiei()
{
	SGD::IListener::RegisterForEvent("YUSUKE_HIT");
}


Hiei::~Hiei()
{
	for (size_t i = 0; i < 7; i++)
	{
		delete YusukeAnimation[i];
	}
	for (size_t i = 0; i < 7; i++)
	{
		SGD::GraphicsManager::GetInstance()->UnloadTexture(Animation_Image[i]);

	}
}
void Hiei::Update(float elapsedTime)
{
	SGD::Event* HitEvent = new SGD::Event("M_YUSUKE", nullptr, this);
	SGD::EventManager::GetInstance()->QueueEvent(HitEvent, nullptr);

		Entity::Update(elapsedTime);
		StayinWorldCollision();


}

void Hiei::Render(void)
{
	// Yususke Animation Will render Yusuke on the screen right now at 600 X position and 0 Y position 
	// NOT FIXED?
	float temp = (m_Health / 100.0f) * 50.0f;
	float tem2 = (m_SpiritEnergy / 100.0f) * 50.0f;
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::R))
	{
		m_CollisionRectRender = !m_CollisionRectRender;
	}


	if (m_CollisionRectRender)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 0, 0 });
	}

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

void Hiei::InitializeAnimation(void)
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

SGD::Rectangle Hiei::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x, GetPosition().y }, SGD::Size{ 90, 100 });

}

void Hiei::HandleEvent(const SGD::Event* pEvent)
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
		//SGD::AudioManager::GetInstance()->PlayAudio(KuramaWins);
	}
}

int	Hiei::GetType(void) const
{
	return ENT_YUSUKE;
}

void Hiei::StayinWorldCollision(void)
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