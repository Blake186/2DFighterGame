//*********************************************************************//
//	File:		KuramaEnergyBeam.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Kurama's Energy Beam And Set and make all Functions an Variables 
//*
//*********************************************************************//
#pragma once
#include "Entity.h"
#include "Kurama.h"
class KuramaEnergyBeam : public Entity
{
public:
	// What this is going to do is Render the Energy ball when it is created.
	void	Render(void);
	// what this will do is Update the the Energyball 
	void	Update(float elapsedTime);
	SGD::Rectangle GetRect(void) const;
	void	HandleCollision(const IEntity* pOther);
	int		GetType(void)	const;
	Kurama* GetKurama(void) const { return m_Kurama; }
	void SetKurama(Kurama* _yuyu) { m_Kurama = _yuyu; }
	KuramaEnergyBeam();
	~KuramaEnergyBeam();

private:
	Kurama* m_Kurama;
};

