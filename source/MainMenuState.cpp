//*********************************************************************//
//	File:		MainMenuState.cpp
//	Author:		Blake Bergstrom
//	Course:		Strucutre of Game Design
//	Purpose:	MainMenuState class handles the main menu
//*********************************************************************//

#include "MainMenuState.h"

#include "../SGD Wrappers/SGD_InputManager.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "BitmapFont.h"
#include "CreditsState.h"
#include "OptionsState.h"
#include "GameplayState.h"
#include "../resource/TinyXML/tinyxml.h"
#include "InstructionState.h"


//*********************************************************************//
// GetInstance
//	- create & return THE singleton object
/*static*/ MainMenuState* MainMenuState::GetInstance(void)
{
	static MainMenuState s_Instance;

	return &s_Instance;
}


//*********************************************************************//
// Enter
//	- called EACH time the screen is shown/switched to
//	- load resources / reset data
/*virtual*/ void MainMenuState::Enter(void)		/*override*/
{
	MusicVolume = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Yu-yu Hakusho Battle Music.wav");
	SFXVolume = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Yu_Yu_Hakusho_OP_1_English_Full_Smile_Bomb_.xwm");
	TiXmlDocument doc;
	if (doc.LoadFile("Volume") == false)
		return;
	TiXmlElement* Root = doc.RootElement();
	Root->Attribute("MasterVolume", &m_sxfVolume);
	Root->Attribute("SFXVolume", &m_MasterVolume);
	SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects, m_sxfVolume);
	//
	//SGD::AudioManager::GetInstance()->PlayAudio(MusicVolume);
	SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music,m_MasterVolume);
	//SGD::AudioManager::GetInstance()->PlayAudio(SFXVolume);
	//MenuMusic = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Yu_Yu_Hakusho_OP_1_English_Full_Smile_Bomb_.wav");
	//SGD::AudioManager::GetInstance()->PlayAudio(MenuMusic, true);
	// Reset the cursor to the top
	// (commented out to keep the last cursor position)
	//m_nCursor = 0;
}

//*********************************************************************//
// Exit
//	- called EACH time the screen is hidden/switched from
//	- unload resources
/*virtual*/ void MainMenuState::Exit(void)		/*override*/
{
	//SGD::AudioManager::GetInstance()->StopAudio(MenuMusic);
	//SGD::AudioManager::GetInstance()->UnloadAudio(MenuMusic);
	SGD::AudioManager::GetInstance()->UnloadAudio(MusicVolume);
	SGD::AudioManager::GetInstance()->UnloadAudio(SFXVolume);
}


//*********************************************************************//
// Update
//	- called EVERY FRAME
//	- handle input & update
/*virtual*/ bool MainMenuState::Update(float elapsedTime)	/*override*/
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true || SGD::InputManager::GetInstance()->IsButtonPressed(0,2))
		m_nCursor = 4;


	// Move the cursor?
	if (pInput->IsKeyPressed(SGD::Key::Down) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Down))
	{
		// next option
		m_nCursor++;

		// wrap around
		if (m_nCursor > 4)
			m_nCursor = 0;
	}
	else if (pInput->IsKeyPressed(SGD::Key::Up) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Up))
	{
		// prev option
		m_nCursor--;

		// wrap around
		if (m_nCursor < 0)
			m_nCursor = 4;
	}


	// Select an option?
	if (pInput->IsKeyPressed(SGD::Key::Enter) == true && !pInput->IsKeyDown(SGD::Key::Alt) || SGD::InputManager::GetInstance()->IsButtonPressed(0, 1) && pInput->IsKeyDown(SGD::Key::Alt) == false)
	{
		// Which option is chosen?
		if (m_nCursor == 0)
		{
			// ChangeState is VERY VOLATILE!!!
			//	- can only be safely called by a game state's`
			//	 Update or Render methods!
			Game::GetInstance()->ChangeState(GameplayState::GetInstance());
						// Exit this state immediately
			return true;	// keep playing in the new state
		}
		else if (m_nCursor == 1) //m_nCursor == 1
		{
			Game::GetInstance()->ChangeState(InstructionState::GetInstance());
		}
		else if (m_nCursor == 2)
		{
			Game::GetInstance()->ChangeState(CreditsState::GetInstance());
		}
		else if (m_nCursor == 3)
		{
			Game::GetInstance()->ChangeState(OptionsState::GetInstance());
		}
		else
		{
			return false;
		}
	}


	return true;	// keep playing
}

//*********************************************************************//
// Render
//	- called EVERY FRAME
//	- draw menus / entities
/*virtual*/ void MainMenuState::Render(float elapsedTime)		/*override*/
{
	// Access the bitmap font
	BitmapFont* pFont = Game::GetInstance()->GetFont();


	// Align text based on window width
	float width = Game::GetInstance()->GetScreenSize().width;


	// Display the game title centered at 4x scale
	pFont->Draw("\t Yu Yu Hakusho \n Battle Between Friends", { (width - (6 * 32 * 4.0f)) / 2, 20 },
		1.0f, { 0, 220, 0 });

	// Display the menu options centered at 1x scale
	pFont->Draw("Play", { (width - (4 * 30)) / 2, 130 },
		1.0f, { 255, 255, 255,  });
	pFont->Draw("How To Play", { (width - (4 * 80)) / 2, 180 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Credits", { (width - (4 * 50)) / 2, 230 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Options", { (width - (4 * 50)) / 2, 280 },
		1.0f, { 255, 255, 255, });
	pFont->Draw("Exit", { (width - (4 * 32)) / 2, 320 },
		1.0f, { 255, 255, 255, });

	// Display the cursor next to the option
	pFont->Draw("\t=", { (width - (7 * 100)) / 2, 130.0f + 50 * m_nCursor },
		1.0f, { 0, 255, 0 });
}
