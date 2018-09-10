//*********************************************************************//
//	File:		OptionsState.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make OptionsState and set and make variables 
//
//*********************************************************************//
#pragma once
#include "IGameState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_Geometry.h"
class OptionsState : public IGameState
{
public:

public:


	static  OptionsState* GetInstance(void);
	virtual void Enter(void);	// load resources / reset data
	virtual void Exit(void);	// unload resources

	virtual bool Update(float elapsedTime);	// handle input / update entities
	virtual void Render(float elapsedTime);

private:

	int m_MasterVolume = 0;
	int m_sxfVolume = 0;
	OptionsState() = default;
	virtual ~OptionsState() = default;
	int m_cursor = 0;
	SGD::Point Position = { 0, 0 };
	SGD::HAudio MusicVolume;
	SGD::HAudio SFXVolume;
	bool play = true;
	bool play2 = true;
};

