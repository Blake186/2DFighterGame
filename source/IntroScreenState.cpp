//*********************************************************************//
//	File:		IntroScreenState.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make IntroScreenState and set and make variables 
//
//*********************************************************************//

#include "IntroScreenState.h"
#include "../resource/TinyXML/tinyxml.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "Game.h"
#include "../SGD Wrappers/SGD_Utilities.h"
#include "MainMenuState.h"
#include "BitmapFont.h"

IntroScreenState* IntroScreenState::GetInstance(void)
{
	static IntroScreenState s_Instance;

	return &s_Instance;

}


void IntroScreenState::Enter(void)
{
	IntroSpeach = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_YusukeSpeach.wav");
	SGD::AudioManager::GetInstance()->PlayAudio(IntroSpeach);



}
void IntroScreenState::Exit(void)
{

	SGD::AudioManager::GetInstance()->UnloadAudio(IntroSpeach);

}

bool IntroScreenState::Update(float elapsedTime)
{

	if (SGD::InputManager::GetInstance()->IsAnyKeyPressed() || SGD::InputManager::GetInstance()->IsButtonPressed(0,1))
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
	}
	return true;
}
void IntroScreenState::Render(float elapsedTime)
{

	BitmapFont* pFont = Game::GetInstance()->GetFont();

	pFont->Draw("\t\t\t   Welcome to \n Yu-Yu Hakusho Battle Between Friends\n \t\t\t I hope you Enjoy ", SGD::Point{ 0, 0 },float(0.8));
	pFont->Draw("\t Press Any Key To Continue", SGD::Point{ 100, 400 }, float(0.8));

}