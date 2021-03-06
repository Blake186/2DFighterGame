//*********************************************************************//
//	File:		KuramaEnergyBeam.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Kurama's Energy Beam that he throws
//*
//*********************************************************************//
#include "KuramaEnergyBeam.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_EventManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "DestroyEntityMessage.h"
#include "Game.h"

KuramaEnergyBeam::KuramaEnergyBeam()
{
}


KuramaEnergyBeam::~KuramaEnergyBeam()
{
}

void KuramaEnergyBeam::Render(void)
{
	if (m_Kurama->GetTurn())
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x + 90, GetPosition().y }, m_fRotation, SGD::Vector{ m_szSize.width, m_szSize.height });
	}
	else if (!m_Kurama->GetTurn())
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x - 10, GetPosition().y }, m_fRotation / -2, SGD::Vector{ m_szSize.width, m_szSize.height }, {}, SGD::Size{ -1.0, 1.0 });
}
// what this will do is Update the the Energyball 
void KuramaEnergyBeam::Update(float elapsedTime)
{
	if (!m_Kurama->GetTurn())
	{
		SGD::Vector newVelcoity = { -1, 0 };
		newVelcoity.x *= 200 + m_Kurama->GetSpeed();
		newVelcoity.y *= 200 + m_Kurama->GetSpeed();
		SetVelocity(newVelcoity);
	}
	Entity::Update(elapsedTime);
	if (m_ptPosition.x < 10)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
	if (m_ptPosition.x > 820)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
}

SGD::Rectangle KuramaEnergyBeam::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x + 90, GetPosition().y }, SGD::Size{ m_szSize.width, m_szSize.height });
}
void KuramaEnergyBeam::HandleCollision(const IEntity* pOther)
{
	if (GetType() == pOther->GetType())
	{
		return;
	}
	if (GetType() != pOther->GetType() && pOther->GetType() == ENT_YUSUKE)
	{
		SGD::Event* SpiritGunHitEvent = new SGD::Event("YUSUKE_HIT", nullptr, this);
		SpiritGunHitEvent->QueueEvent(pOther);
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}

}

int	KuramaEnergyBeam::GetType(void)	const
{
	return ENT_KURAMA_ENERGY_BALL;
}