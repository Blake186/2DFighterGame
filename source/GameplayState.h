//*********************************************************************//
//	File:		GameplayState.h
//	Author:		Blake Bergstrom
//	Course:		Structure of Game Design
//	Purpose:	GameplayState class initializes & runs the game logic
//*********************************************************************//

#pragma once

#include "IGameState.h"							// uses IGameState
#include "../SGD Wrappers/SGD_Handle.h"			// uses HTexture & HAudio
#include "../SGD Wrappers/SGD_Declarations.h"	// uses Message


//*********************************************************************//
// Forward class declaration
//	- tells the compiler that the type exists
//	- can make pointers or references to the type
//	- MUST include their headers in the .cpp to dereference
class Entity;
class EntityManager;
class Yusuke;
class Kurama;

//*********************************************************************//
// GameplayState class
//	- runs the game logic
//	- SINGLETON! (Static allocation, not dynamic)
class GameplayState : public IGameState
{
public:
	//*****************************************************************//
	// Singleton Accessor:
	static GameplayState* GetInstance( void );

	
	//*****************************************************************//
	// IGameState Interface:
	virtual void	Enter	( void )				override;	// load resources / reset data
	virtual void	Exit	( void )				override;	// unload resources
													
	virtual bool	Update	( float elapsedTime )	override;	// handle input & update game entities
	virtual void	Render	( float elapsedTime )	override;	// render game entities / menus
	void RenderPause();
	void Pause();
private:
	//*****************************************************************//
	// SINGLETON (not-dynamically allocated)
	GameplayState( void )			= default;	// default constructor
	virtual ~GameplayState( void )	= default;	// destructor

	GameplayState( const GameplayState& )				= delete;	// copy constructor
	GameplayState& operator= ( const GameplayState& )	= delete;	// assignment operator
		
	
	//*****************************************************************//
	// Game Entities
	EntityManager*	m_pEntities			= nullptr;
	Entity* Kurma;
	Entity* m_Yusuke;
	Entity* CreateYusuke(void);
	Entity* CreateKurama(void);
	Entity* CreateEnergyBall(Yusuke*);
	Entity* CreateEnergyBeamBall(Yusuke*);
	Entity* CreatKuramaEnergyBall(Kurama*);
	// HTextures to be used for the backround and energybeams

	SGD::HTexture EnergyBeam;
	SGD::HTexture BigEnergyBall;
	SGD::HTexture KuramaAttack;
	SGD::HTexture m_backround;
	SGD::HTexture YusukeUrimeshi;
	SGD::HTexture YokoKurama;
	SGD::HAudio SpiritGunAudio;
	SGD::HAudio ShotGunAudio;
	SGD::HAudio GettingHurt;
	SGD::HAudio GettingHurt2;
	SGD::HAudio MainMusic;
	SGD::HAudio YusukeWins;
	//SGD::HAudio KuramaWins;
	//*****************************************************************//
	// Message Callback Procedure
	static void MessageProc( const SGD::Message* pMsg );
	float timer = 0.0f;
	bool win = false;
	bool lose = false;
	GameplayState* Save;
	int m_cursor;
	bool  m_Pause = false;
	int Wins = 0;
};
