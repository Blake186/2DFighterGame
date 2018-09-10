//*********************************************************************//
//	File:		CreditsState.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make CreditsState and set and make variables 
//
//*********************************************************************//

#include "CreditsState.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_Utilities.h"
#include "BitmapFont.h"
#include "GameplayState.h"
#include "MainMenuState.h"


CreditsState* CreditsState::GetInstance(void)
{
	static CreditsState m_Credits;

	return &m_Credits;

}
void  CreditsState::Enter(void)
{
	Developer = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Bab_Blake.png");

}
void  CreditsState::Exit(void)
 {
	SGD::GraphicsManager::GetInstance()->UnloadTexture(Developer);
	Posiiton.y = 550;
 }


bool  CreditsState::Update(float elapsedTime)
 {
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) == true &&  Game::GetInstance()->CheckPriveous() == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == true)
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
	}
	else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) == true && Game::GetInstance()->CheckPriveous() == false || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == false)
	{
		Game::GetInstance()->Pause(GameplayState::GetInstance());
	}
	(float)Posiiton.y -= (float)0.05;
	if (Posiiton.y < -730)
		Posiiton.y = 500;
	return true;
 }

void  CreditsState::Render(float elapsedTime)
{
	BitmapFont* pFont = Game::GetInstance()->GetFont();
	pFont->Draw("Yu Yu Hakusho Battle of Friends the Game is", SGD::Point{ 0, Posiiton.y }, 0.6f);
	pFont->Draw("Made By Full Sail Student Blake Bergstrom.", SGD::Point{ 0, Posiiton.y + 30 }, 0.6f);
	pFont->Draw("Yu Yu hakusho was made by Toshihero Tagashi.", SGD::Point{ 0, Posiiton.y + 60 }, 0.6f);
	pFont->Draw("Main Menu Song Was performed by Matsuko Mawatari.", SGD::Point{ 0, Posiiton.y + 90 }, 0.6f);
	pFont->Draw("All Sprites Came From Sprite DataBase as well as SFX", SGD::Point{ 0, Posiiton.y + 120 }, 0.6f);
	pFont->Draw("This is Blake Bergstrom the Game Developer", SGD::Point{ 0, Posiiton.y + 140 }, 0.6f);
	SGD::GraphicsManager::GetInstance()->DrawTexture(Developer, SGD::Point{ 0, Posiiton.y + 160 });
}
