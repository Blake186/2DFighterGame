//*********************************************************************//
//	File:		Game.h
//	Author:		Blake Bergstrom
//	Course:		Structure of Game Design
//	Purpose:	Game class initializes the SGD Wrappers
//				and runs the game state machine
//*********************************************************************//

#pragma once

#include "../SGD Wrappers/SGD_Geometry.h"
#include "GameplayState.h"

//*********************************************************************//
// Forward class declarations
class BitmapFont;
class IGameState;


//*********************************************************************//
// Game class
//	- handles the SGD wrappers
//	- runs the game state machine
//	- SINGLETON
//		- only ONE instance can be created
//		- global access to THE instance
class Game
{
public:
	//*****************************************************************//
	// SINGLETON!
	//	- static accessor to get the singleton object
	static Game* GetInstance( void );
	static void  DeleteInstance( void );

	
	//*****************************************************************//
	// Setup, Play, Cleanup
	bool	Initialize	( void );
	int		Update		( void );
	void	Terminate	( void );
	void Pause(IGameState* pNextState);
	bool CheckPriveous();
	//*****************************************************************//
	// Screen Accessors
	SGD::Size	GetScreenSize	( void ) const	{	return m_szScreenSize;	}
	
	// Font Accessor (#include "BitmapFont.h" to use!)
	BitmapFont*	GetFont			( void ) const	{	return	m_pFont;		}


	//*****************************************************************//
	// Game State Mutator:
	void	ChangeState( IGameState* pNextState );
	
private:
	//*****************************************************************//
	// SINGLETON!
	//	- static member to hold the singleton object
	//	- prevent access to constructors / destructor / =op
	static Game* s_pInstance;

	Game( void )	= default;					// default constructor
	~Game( void )	= default;					// destructor

	Game( const Game& )				= delete;	// disabled copy constructor
	Game& operator=( const Game& )	= delete;	// disabled assignment operator


	//*****************************************************************//
	// Screen Size
	SGD::Size		m_szScreenSize		= SGD::Size{ 1024,512  };
	
	// Font
	BitmapFont*		m_pFont				= nullptr;


	//*****************************************************************//
	// Active Game State
	IGameState*		m_pCurrState		= nullptr;
	IGameState* Current;
	IGameState* Previous = nullptr;

	//*****************************************************************//
	// Game Time
	unsigned long	m_ulGameTime	= 0;
	bool m_Fullscreen = false;
	
};
