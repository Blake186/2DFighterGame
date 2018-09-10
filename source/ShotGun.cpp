//*********************************************************************//
//	File:		ShotGun.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke's Shot Gun that he throws
//
//*********************************************************************//

#include "ShotGun.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "DestroyEntityMessage.h"
#include "Yusuke.h"
#include "Game.h"

ShotGun::ShotGun()
{
}


ShotGun::~ShotGun()
{
}
void ShotGun::Render(void)
{
	if (m_Yusuke->GetTurn())
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x, GetPosition().y }, m_fRotation, SGD::Vector{ m_szSize.width, m_szSize.height });
	}
	else if (!m_Yusuke->GetTurn())
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x, GetPosition().y }, m_fRotation / -2, SGD::Vector{ m_szSize.width, m_szSize.height }, {}, SGD::Size{ -1.0, 1.0 });
	//SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 0, 0 });
	//SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x + 90, GetPosition().y }, m_fRotation, SGD::Vector{ m_szSize.width /2, m_szSize.height /2 });
}

void ShotGun::Update(float elapsedTime)
{/*
	if (!m_Yusuke->GetTurn())
	{
		SGD::Vector newVelcoity = { -1, 0 };
		newVelcoity.x *= 200 + m_Yusuke->GetSpeed();
		newVelcoity.y *= 200 + m_Yusuke->GetSpeed();
		SetVelocity(newVelcoity);
	}*/
	Entity::Update(elapsedTime);
	if (m_ptPosition.x < 80)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
	if (m_ptPosition.x > 1024)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
}

SGD::Rectangle ShotGun::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x, GetPosition().y }, SGD::Size{ m_szSize.width, m_szSize.height });
}

void ShotGun::HandleCollision(const IEntity* pOther)
{
	if (GetType() != pOther->GetType())
	{
		SGD::Event* SpiritGunHitEvent = new SGD::Event("ENEMY_HIT2", nullptr, this);
		SpiritGunHitEvent->QueueEvent(pOther);
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}

}

int	ShotGun::GetType(void)	const
{
	return ENT_SHOT_GUN;

}