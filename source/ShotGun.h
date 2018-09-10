//*********************************************************************//
//	File:		ShotGun.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke's Shot Gun that he throws
//*
//*********************************************************************//
#pragma once
#include "Entity.h"
#include "Yusuke.h"
class ShotGun : public Entity
{
public:
	// What this is going to do is Render the Energy ball when it is created.
	void	Render(void);
	// what this will do is Update the the Energyball 
	void	Update(float elapsedTime);
	void	HandleCollision(const IEntity* pOther);
	SGD::Rectangle GetRect(void) const;
	int		GetType(void)	const;
	Yusuke* GetYusuke(void) const { return m_Yusuke; }
	void SetYusuke(Yusuke* _yuyu) { m_Yusuke = _yuyu; }
	ShotGun();
	~ShotGun();

private:
	Yusuke* m_Yusuke;
};

