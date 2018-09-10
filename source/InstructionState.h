//*********************************************************************//
//	File:		InstructionState.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make InstructionState  and set and make variables 
//
//*********************************************************************//
#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "CellAnimation.h"

class InstructionState : public IGameState
{
public:

	static  InstructionState* GetInstance(void);
	virtual void Enter(void);	// load resources / reset data
	virtual void Exit(void);	// unload resources

	virtual bool Update(float elapsedTime);	// handle input / update entities
	virtual void Render(float elapsedTime);
	void InitializeAnimation(void);

private:

	InstructionState() = default;
	virtual ~InstructionState() = default;
	CellAnimation* YusukeAnimation[4];
	CellAnimation* KuramaAnimation[1];
	int CurrentAnimation = 0;
	int KuramaCurrentAnimation = 0;
	SGD::HTexture Animation_Image[5];
	SGD::HTexture Keys[4];
	unsigned long	m_ulGameTime = 0;
	int m_pressed = 255;
	int m_pressed1 = 255;
	int m_pressed2 = 255;
	int m_pressed3 = 255;
	bool Turn = true;
};

