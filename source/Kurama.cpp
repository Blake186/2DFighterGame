//*********************************************************************//
//	File:		Kurama.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Kurama Functions 
//
//*********************************************************************//


#include "Kurama.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "CreateSpiritGunBeamMessage.h"
#include "CreateShotGunMessage.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "CreateKuramaEnergyBall.h"
#include "GameplayState.h"
#include "Yusuke.h"
#include "BitmapFont.h"
#include "CreditsState.h"
#include "Game.h"
#include "CellAnimation.h"

Kurama::Kurama()
{
	SGD::IListener::RegisterForEvent("ENEMY_HIT");
	SGD::IListener::RegisterForEvent("ENEMY_HIT2");
	SGD::IListener::RegisterForEvent("M_YUSUKE");
}


Kurama::~Kurama()
{
	for (size_t i = 0; i < 5; i++)
	{
		delete KuramaAnimation[i];
	}
	for (size_t i = 0; i < 5; i++)
	{
		SGD::GraphicsManager::GetInstance()->UnloadTexture(Animation_Image[i]);

	}
}

void Kurama::Update(float elapsedTime)
{

	if (Target != nullptr)
	{

		SGD::Vector EnemyDistance = GetEnemyTarget()->GetPosition() - this->m_ptPosition;
		if (KuramaAnimation[CurrentAnimation]->IsLooping() == false && KuramaAnimation[CurrentAnimation]->IsFinished() == false)
		{
			KuramaAnimation[CurrentAnimation]->Update(elapsedTime);
			//EnemyDistance.x = 0;

		}
		else
		{
			CurrentAnimation = 0;
			EnemyDistance.x = 0;
		}
		if (win)
		{

		}
		else
		{

			if (EnemyDistance.ComputeLength() > 300)
			{
				if (CurrentAnimation != 1)
				{
					if (Target->GetPosition().x > GetPosition().x)
					{
						Turn = true;
					}
					else
					{
						Turn = false;
					}
					// ************************NEEDS TO BE WORKED ON FOR THE MOVEMENT RIGHT NOW IT WORKS BUT IT WILL NOT WORK LATER********************
					// switch the Animation to Yusuke Runing 
					CurrentAnimation = 1;

					KuramaAnimation[CurrentAnimation]->Restart(false, 5.0);
					EnemyDistance.x += 0.2f;
					SetVelocity(EnemyDistance);
					//Entity::Update(elapsedTime);
				}
				//EnemyDistance.x = 0.0f;
			}


			if (EnemyDistance.ComputeLength() < 300 && m_SpiritEnergy > 25 && Timer <= 0.0f)
			{
				m_vtVelocity.x = 2.0f;
				if (CurrentAnimation != 3)
				{
					m_vtVelocity.x = 0.0f;
					EnemyDistance.x = 0;
					// ************************NEEDS TO BE WORKED ON FOR THE MOVEMENT RIGHT NOW IT WORKS BUT IT WILL NOT WORK LATER********************
					// switch the Animation to Yusuke Runing 
					CurrentAnimation = 3;
					KuramaAnimation[CurrentAnimation]->Restart(false, 5.0);

					m_SpiritEnergy -= 25.0f;

				}
				//Timer = 3.0f;
			}

			SetVelocity(EnemyDistance);
			Entity::Update(elapsedTime);
			StayinWorldCollision();
			KuramaAnimation[CurrentAnimation]->Update(elapsedTime);
			if (KuramaAnimation[3]->GetCurrentFrame() == 1 && Timer <= 0.0f)
			{


				CreateKuramaEnergyBall* Eneryball = new CreateKuramaEnergyBall(this);
				SGD::MessageManager::GetInstance()->QueueMessage(Eneryball);
				Eneryball = nullptr;
				Timer = 3.0f;

			}
		}
		if (Timer > 0)
		{
			Timer -= elapsedTime;
		}
		if (m_Health <= 0)
		{
			Game::GetInstance()->ChangeState(CreditsState::GetInstance());
		}
		m_SpiritEnergy += elapsedTime;
		//KuramaAnimation[CurrentAnimation]->Update(elapsedTime);

	}
}
void Kurama::Render(void)
{
	
	
		float temp = (m_Health / 150.0f) * 50.0f;
		float tem2 = (m_SpiritEnergy / 150.0f) * 50.0f;


		KuramaAnimation[CurrentAnimation]->Render(SGD::Point{ GetPosition().x, GetPosition().y }, 2, {}, Turn);
		if (Turn)
		{
			SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x + 20, GetPosition().y - 50 }, SGD::Size{ temp, 10 }), SGD::Color{ 255, 255, 0, 0 }, SGD::Color{ 0, 0, 0, 0 }, 2);
			SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x + 20, GetPosition().y - 40 }, SGD::Size{ tem2, 10 }), SGD::Color{ 255, 0, 0, 255 }, SGD::Color{ 0, 0, 0, 0 }, 2);
			//SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 0, 0, 0, 0 }, { 255, 255, 0, 0 }, 2);
		}
		else
		{
			SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x - 20, GetPosition().y - 60 }, SGD::Size{ temp, 10 }), SGD::Color{ 255, 255, 0, 0 }, SGD::Color{ 0, 0, 0, 0 }, 2);
			SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(SGD::Point{ GetPosition().x - 20, GetPosition().y - 50 }, SGD::Size{ tem2, 10 }), SGD::Color{ 255, 0, 0, 255 }, SGD::Color{ 0, 0, 0, 0 }, 2);
		}
	


}
SGD::Rectangle Kurama::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x, GetPosition().y }, SGD::Size{ 90, 100 });

}

void  Kurama::InitializeAnimation(void)
{
	Animation_Image[0] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_KuramaIdle_strip4.png");

	KuramaAnimation[0] = new CellAnimation(0, {}, 1.0);
	KuramaAnimation[0]->SetImage(Animation_Image[0]);
	KuramaAnimation[0]->Initialize(1, 4, 30, 70, 4, 8.0, true);


	Animation_Image[1] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_KuramaRunning_strip8.png");

	KuramaAnimation[1] = new CellAnimation(0, {}, 1.0);
	KuramaAnimation[1]->SetImage(Animation_Image[1]);
	KuramaAnimation[1]->Initialize(1, 8, 45, 70, 8, 8.0, true);


	Animation_Image[2] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_KuramaFall_strip11.png");

	KuramaAnimation[2] = new CellAnimation(0, {}, 1.0);
	KuramaAnimation[2]->SetImage(Animation_Image[2]);
	KuramaAnimation[2]->Initialize(1, 8, 50, 70, 8, 8.0, true);

	Animation_Image[3] = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Kurama/Bab_KuramaAttack_strip4.png");

	KuramaAnimation[3] = new CellAnimation(0, {}, 1.0);
	KuramaAnimation[3]->SetImage(Animation_Image[3]);
	KuramaAnimation[3]->Initialize(1, 4, 40, 70, 4, 5.0, true);

	CurrentAnimation = 0;

}

void Kurama::HandleEvent(const SGD::Event* pEvent)
{
	if (pEvent->GetEventID() == "ENEMY_HIT")
	{
		CurrentAnimation = 2;
		KuramaAnimation[CurrentAnimation]->Restart(false, 5.0);
		SGD::AudioManager::GetInstance()->PlayAudio(GettingHurt, false);
		if (m_Health > 0)
		{
			m_Health -= 25.0f;
			int temp = Target->GetScore() + 10;
			Target->SetScore(temp);
		}
		if (m_Health <= 0)
		{
			SetHealth(1);
			int temp = Target->GetScore() + 100;
			Target->SetScore(temp);
			//win = true;
			//	SGD::AudioManager::GetInstance()->SetAudioVolume(Target->GetWinAudio(), 100);
			SGD::AudioManager::GetInstance()->PlayAudio(Target->GetWinAudio(), false);
			win = true;
			Target->SetWinlose(true);
		}



	}
	else if (pEvent->GetEventID() == "ENEMY_HIT2")
	{
		CurrentAnimation = 2;

		KuramaAnimation[CurrentAnimation]->Restart(false, 5.0);
		SGD::AudioManager::GetInstance()->PlayAudio(GettingHurt, false);
		m_Health -= 10.0f;
		pEvent->GetSender();
		if (m_Health <= 0)
		{
			SetHealth(1);
			int temp = Target->GetScore() + 100;
			Target->SetScore(temp);
			//win = true;
			//	SGD::AudioManager::GetInstance()->SetAudioVolume(Target->GetWinAudio(), 100);
			SGD::AudioManager::GetInstance()->PlayAudio(Target->GetWinAudio(), false);
			win = true;
			Target->SetWinlose(true);
		}
	}

	if (pEvent->GetEventID() == "M_YUSUKE")
	{
		SetTarget(reinterpret_cast<Yusuke*>(pEvent->GetSender()));
	}

}
int	Kurama::GetType(void) const
{
	return ENT_KURAMA;
}

void Kurama::StayinWorldCollision(void)
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