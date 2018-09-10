//*********************************************************************//
//	File:		EnergyBall.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke's Spirit Gun that he throws And set and make Variables
//
//*********************************************************************//
#pragma once
#include "Entity.h"
#include "Yusuke.h"
class EnergyBall : public Entity
{
public:
	// What this is going to do is Render the Energy ball when it is created.
	void	Render(void);
	// what this will do is Update the the Energyball 
	void	Update(float elapsedTime);
	SGD::Rectangle GetRect(void) const;
	void	HandleCollision(const IEntity* pOther);
	int		GetType(void)	const;
	Yusuke* GetYusuke(void) const {return m_Yusuke; }
	void SetYusuke(Yusuke* _yuyu) { m_Yusuke = _yuyu; }
	EnergyBall();
	~EnergyBall();
private:
	Yusuke* m_Yusuke;
	bool m_CollisionRectRender = false;
};

