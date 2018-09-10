//*********************************************************************//
//	File:		Creditsstate.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Credits and set and make variables 
//
//*********************************************************************//

#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
class CreditsState : public IGameState
{
public:


	static  CreditsState* GetInstance(void);
	  virtual void Enter(void);	// load resources / reset data
	  virtual void Exit(void);	// unload resources

	  virtual bool Update(float elapsedTime);	// handle input / update entities
	  virtual void Render(float elapsedTime);
	  
private:

	CreditsState() = default;
	virtual ~CreditsState() = default;
	SGD::Point Posiiton = { 200, 500 };
	SGD::HTexture Developer;
};

