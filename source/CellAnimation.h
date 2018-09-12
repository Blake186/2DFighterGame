
//***********************************************************************
//	File:		CellAnimation.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure of Game Design
//	Purpose:	CellAnimation 
//***********************************************************************
#pragma once



#include "../SGD Wrappers/SGD_Handle.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_Color.h"





class CellAnimation
{
public:
	/**********************************************************/
	// Default Constructor & Destructor
	CellAnimation(unsigned int _firstFrame = 0, SGD::Point _startPt = { 0, 0 }, float delay = 0.125f);
	~CellAnimation( void )	= default;

	CellAnimation(const CellAnimation&) = default;
	/**********************************************************/
	// Initialize & Terminate
	void	Initialize(unsigned int numRows, unsigned int numCols, unsigned int frameWidth,
		unsigned int frameHeight, unsigned int numberOfFrames = 10, float animationSpeed = 1, bool loop = false);	
	void	Terminate	( void );
	void	SetImage	(SGD::HTexture _texture)	{ m_hImage = _texture; }

	SGD::HTexture GetImage(void) const { return m_hImage; }
	int GetCurrentFrame(void) const { return m_nCurrFrame; }
	//*******************************************************************
	// Controls:
	
	void	Update		( float elapsedTime );
	void	Render(SGD::Point position, float scale, SGD::Color color, bool facingForwards = true)	const;

	void	Restart		( bool looping, float speed = 1.0f );
	void	Pause		( bool pause )	{	m_bPlaying = !pause;	}
	//*******************************************************************
	// Accessors:
	bool	IsPlaying	( void ) const	{	return m_bPlaying;		}
	bool	IsFinished	( void ) const	{	return m_bFinished;		}
 	bool	IsLooping	( void ) const	{	return m_bLooping;		}
	void    SetCurrentFrame(int frame);
	void	NextFrame(void) { m_fTimeWaited += 1.f; }
private:
	//*******************************************************************
	// image
	SGD::HTexture	m_hImage		= SGD::INVALID_HANDLE;
	
	SGD::Point		m_ptStart;
	// cell algorithm data
	int				m_nNumRows		= 0;
	int				m_nNumCols		= 0;
	int				m_nFrameWidth	= 0;
	int				m_nFrameHeight	= 0;
	int				m_nFirstFrame	= 0;

	// animation data
	int				m_nCurrFrame	= 0;
	int				m_nNumFrames	= 0;

	float			m_fTimeWaited	= 0.0f;
	float			m_fDuration		= 0.0f;		
	float			m_fSpeed		= 1.0f;		

	bool			m_bPlaying		= false;
	bool			m_bLooping		= false;
	bool			m_bFinished		= false;
};

