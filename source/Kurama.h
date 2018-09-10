//*********************************************************************//
//	File:		Kurama.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke and set and make variables 
//
//*********************************************************************//

#pragma once
#include "Entity.h"
#include "CellAnimation.h"
#include "../SGD Wrappers/SGD_IListener.h"
class Yusuke;
class Kurama : public Entity,public SGD::IListener
{
public:
	void	Update(float elapsedTime);
	void	Render(void);
	SGD::Rectangle GetRect(void)	const;
	void InitializeAnimation(void);
	float GetKuramaHealth(void) const { return m_Health; }
	float GetKuramaSpiritEnergy(void) const { return m_SpiritEnergy; }
	float GetSpeed(void) { return m_speed; }
	float GetAceleration(void) { return m_aceleration; }
	void SetSpeed(float _Speed) { m_speed = _Speed; }
	void SetAcceleration(float _acceleraion) { m_aceleration = _acceleraion; }
	void SetHealth(float _health) { m_Health = _health; }
	void SetSpiritEnergy(float _Spirit) { m_SpiritEnergy = _Spirit; }
	void	HandleEvent(const SGD::Event* pEvent);
	SGD::HAudio GetHurtSound(void) const { return GettingHurt; }
	void SetGettingHurtSound(SGD::HAudio _audio) { GettingHurt = _audio; }
	Yusuke* GetEnemyTarget() { return Target; }
	void SetTarget(Yusuke* _tatget) { Target = _tatget; }
	int		GetType(void)	const;
	bool GetTurn(void) const { return Turn; }
	void StayinWorldCollision(void);
	void SetWin(bool _winlose) { win = _winlose; }
	void SetWn(SGD::HAudio _win) { KuramaWins = _win; }
	SGD::HAudio GetKuramaWin(void) { return KuramaWins; }
	Kurama();
	~Kurama();

protected:
	CellAnimation* KuramaAnimation[5];
	float m_Health = 100.0f;
	float m_SpiritEnergy = 100.0f;
	float m_speed = 100.0f;
	float m_aceleration = 60.0f;
	int CurrentAnimation = 0;
	bool Turn = false;
	Yusuke* Target = nullptr;
	SGD::HTexture Animation_Image[8];
	SGD::HAudio GettingHurt;
	SGD::HAudio KuramaWins;
	float Timer = 0.0f;
	bool win = false;


};

