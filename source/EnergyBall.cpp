//*********************************************************************//
//	File:		EnergyBall.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke's Spirit Gun that he throws
//
//*********************************************************************//
#include "EnergyBall.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyEntityMessage.h"
#include "Game.h"
EnergyBall::EnergyBall()
{
}


EnergyBall::~EnergyBall()
{
}

void EnergyBall::Render(void)
{
	SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 0, 0 });
	if (m_vtVelocity.x > 0)
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x, GetPosition().y }, m_fRotation, SGD::Vector{ m_szSize.width, m_szSize.height });
	}
	else
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x  + m_szSize.width, GetPosition().y }, m_fRotation / -2, SGD::Vector{ m_szSize.width, m_szSize.height }, {}, SGD::Size{ -1.0, 1.0 });

	}
}
		
void EnergyBall::Update(float elapsedTime)
{
	/*if (!m_Yusuke->GetTurn())
	{
		SGD::Vector newVelcoity = { -1, 0 };
		newVelcoity.x *= 200 + m_Yusuke->GetSpeed();
		newVelcoity.y *= 200 + m_Yusuke->GetSpeed();
		SetVelocity(newVelcoity);
	}*/
	Entity::Update(elapsedTime);
	if (m_ptPosition.x < 0)
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


SGD::Rectangle  EnergyBall::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x , GetPosition().y }, SGD::Size{ m_szSize.width, m_szSize.height });
}


void  EnergyBall::HandleCollision(const IEntity* pOther)
{
	if (GetType() == pOther->GetType() )
	{
		return;
	}
	if(GetType() != pOther->GetType() && pOther->GetType() == ENT_KURAMA && GetRect().IsIntersecting(pOther->GetRect()))
	{
		SGD::Event* SpiritGunHitEvent = new SGD::Event("ENEMY_HIT", nullptr, this);
		SpiritGunHitEvent->QueueEvent(pOther);
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}


}

int	EnergyBall::GetType(void)	const
{

	return ENT_SPIRIT_GUN;
}

