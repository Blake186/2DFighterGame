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
	SGD::GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 0, 0 });
	if (m_vtVelocity.x > 0)
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x , GetPosition().y }, m_fRotation, SGD::Vector{ m_szSize.width /3, m_szSize.height /3 });
	}
	else
	{
		SGD::GraphicsManager::GetInstance()->DrawTexture(m_hImage, SGD::Point{ GetPosition().x, GetPosition().y }, m_fRotation / -2, SGD::Vector{ m_szSize.width / 3, m_szSize.height / 3 });

	}
}
// what this will do is Update the the Energyball 
void KuramaEnergyBeam::Update(float elapsedTime)
{
	/*if (!m_Kurama->GetTurn())
	{
		SGD::Vector newVelcoity = { -1, 0 };
		newVelcoity.x *= 200 + m_Kurama->GetSpeed();
		newVelcoity.y *= 200 + m_Kurama->GetSpeed();
		SetVelocity(newVelcoity);
	}*/
	//Entity::Update(elapsedTime);
	if (m_ptPosition.x < 0)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
	if (m_ptPosition.x > 1500)
	{
		DestroyEntityMessage* destroy = new DestroyEntityMessage{ this };
		destroy->QueueMessage();
		destroy = nullptr;
	}
}

SGD::Rectangle KuramaEnergyBeam::GetRect(void) const
{
	return SGD::Rectangle(SGD::Point{ GetPosition().x, GetPosition().y }, SGD::Size{ m_szSize.width / 3, m_szSize.height / 3 });
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