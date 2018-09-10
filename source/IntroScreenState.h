//*********************************************************************//
//	File:		IntroScreenState.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make IntroScreenState and set and make variables 
//
//*********************************************************************//

#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
class IntroScreenState : public IGameState
{
public:

	static IntroScreenState* GetInstance(void);


	void Enter(void);
	 void Exit(void);

	bool Update(float elapsedTime);	
	void Render(float elapsedTime);

private:
	IntroScreenState() = default;
	virtual ~IntroScreenState() = default;
	SGD::HAudio IntroSpeach;
};

