//*********************************************************************//
//	File:		MainMenuState.h
//	Author:		Blake Bergstrom
//	Course:		Structure of Game Design 
//	Purpose:	MainMenuState class handles the main menu
//*********************************************************************//

#pragma once

#include "IGameState.h"
#include "../SGD Wrappers/SGD_AudioManager.h"

//*********************************************************************//
// MainMenuState class
//	- runs the main menu
//	- SINGLETON! (Static allocation, not dynamic)
class MainMenuState : public IGameState
{
public:
	//*****************************************************************//
	// Singleton Accessor:
	static MainMenuState* GetInstance( void );

	
	//*****************************************************************//
	// IGameState Interface:
	virtual void Enter	( void )				override;	// load resources / reset data
	virtual void Exit	( void )				override;	// unload resources

	virtual bool Update	( float elapsedTime )	override;	// handle input / update entities
	virtual void Render	( float elapsedTime )	override;	// draw entities / menu

private:
	//*****************************************************************//
	// SINGLETON (not-dynamically allocated)
	//	- Hide the "Quadrilogy-of-Evil" so they cannot be called
	//	  by outside functions
	MainMenuState( void )			= default;	// default constructor
	virtual ~MainMenuState( void )	= default;	// destructor

	MainMenuState( const MainMenuState& )				= delete;	// copy constructor
	MainMenuState& operator= ( const MainMenuState& )	= delete;	// assignment operator


	//*****************************************************************//
	// cursor index / position
	int m_nCursor = 0;
	SGD::HAudio MenuMusic;
	SGD::HAudio MusicVolume;
	SGD::HAudio SFXVolume;
	//SGD::Point Position = { 0, 0 };
	int m_MasterVolume = 0;
	int m_sxfVolume = 0;
};

