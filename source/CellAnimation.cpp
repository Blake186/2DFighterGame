//*********************************************************************//
//	File:		Cell Animation
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Cell Animation and set and make variables 
//
//*********************************************************************//
#include "CellAnimation.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_Utilities.h"
#include <cassert>


CellAnimation::CellAnimation(unsigned int _firstFrame, SGD::Point _startPt, float delay)
{
	m_nFirstFrame = _firstFrame;
	m_fDuration = delay;
	m_ptStart = _startPt;
}


void CellAnimation::Initialize(unsigned int rows, unsigned int cols, unsigned int width,
	unsigned int height, unsigned int numberOfFrames, float speed, bool loop)
{
	m_nNumRows = rows;
	m_nNumCols = cols;
	m_nFrameWidth = width;
	m_nFrameHeight = height;

	m_nCurrFrame = 0;
	m_nNumFrames = numberOfFrames;		// indices 0 -> 9

	m_fTimeWaited = 0.0f;
	m_fSpeed = speed;

	m_bPlaying = false;
	m_bLooping = loop;
	m_bFinished = false;
}


void CellAnimation::Terminate(void)
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hImage);
}



void CellAnimation::Update(float elapsedTime)
{
	// Is the animation paused?
	//	if( m_bPlaying == false )
	//	return;


	// Increase the timer
	m_fTimeWaited += elapsedTime * m_fSpeed;

	// Is it time to move to the next frame?
	if (m_fTimeWaited >= m_fDuration)
	{
		m_fTimeWaited = 0.0f;
		++m_nCurrFrame;


		// Has it reached the end?
		if (m_nCurrFrame == m_nNumFrames )
		{
			// Should the animation loop from the beginning?
			if (m_bLooping == true)
				m_nCurrFrame = 0;
			else
			{
				// Stop on the last valid frame
				--m_nCurrFrame;
				m_bPlaying = false;
				m_bFinished = true;
			}
		}
	}
}


/**************************************************************/
// Render
//	- draw the current frame at the given position
void CellAnimation::Render(SGD::Point position, float scale, SGD::Color color, bool forwards) const
{
	// Validate the image
	assert(m_hImage != SGD::INVALID_HANDLE
		&& "CellAnimation::Render - image was not initialized!");

	float scaleX = scale, scaleY = scale;

	// Is the color invisible? Or is the scale invisible?
	if (color.alpha == 0 || scale == 0.0f)
		return;

	if (!forwards)
		scaleX *= -1;

	unsigned int index = m_nCurrFrame + m_nFirstFrame;

	// Calculate the source rect for the current frame
	SGD::Rectangle frame;

	//set the top left
	frame.left = float((index % m_nNumCols) * m_nFrameWidth);
	frame.top = float((index / m_nNumCols) * m_nFrameHeight);
	//adjust according to the beginning of the cell
	frame.left += m_ptStart.x;
	frame.top += m_ptStart.y;
	//calculate the bottom right
	frame.right = frame.left + m_nFrameWidth;
	frame.bottom = frame.top + m_nFrameHeight;

	// Draw
	if (forwards)
	{
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, position, frame,
			0.0f, {},
			color, { scaleX, scaleY });
	}
	else
	{
		SGD::Point  pos = SGD::Point(position.x + m_nFrameWidth, position.y);
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(
			m_hImage, pos, frame,
			0.0f, SGD::Vector(position.x + m_nFrameWidth*0.5f, position.y + m_nFrameHeight),
			color, { scaleX, scaleY });
	}
}


/**************************************************************/
// Restart
//	- start the animation over from frame 0
void CellAnimation::Restart(bool looping, float speed)
{
	// Store the parameters
	m_bLooping = looping;
	m_fSpeed = speed;

	// Reset animation
	m_nCurrFrame = 0;
	m_fTimeWaited = 0.0f;
	m_bPlaying = true;
	m_bFinished = false;
}

void CellAnimation::SetCurrentFrame(int frame)
{

	m_nCurrFrame = frame;

}