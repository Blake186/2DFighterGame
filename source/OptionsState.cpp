//*********************************************************************//
//	File:		OptionsState.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make OptionsState and set and make variables 
//
//*********************************************************************//

#include "OptionsState.h"

#include "../resource/TinyXML/tinyxml.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"
#include "../SGD Wrappers/SGD_Utilities.h"
#include "MainMenuState.h"
#include "BitmapFont.h"
#include "Game.h"


OptionsState* OptionsState::GetInstance(void)
{
	static OptionsState m_options;

	return &m_options;

}
void OptionsState::Enter(void)
{
	SFXVolume = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_YusukeWins.wav");
	MusicVolume = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Yu_Yu_Hakusho_OP_1_English_Full_Smile_Bomb_.xwm");
	TiXmlDocument doc;
	if (doc.LoadFile("Volume") == false)
		return;
	TiXmlElement* Root = doc.RootElement();
	Root->Attribute("MasterVolume", &m_sxfVolume);
	Root->Attribute("SFXVolume", &m_MasterVolume);
	SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music,m_MasterVolume );
	SGD::AudioManager::GetInstance()->PlayAudio(SFXVolume,true);
	SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects,m_sxfVolume );
	SGD::AudioManager::GetInstance()->PlayAudio(MusicVolume);






}
void OptionsState::Exit(void)
{
	SGD::AudioManager::GetInstance()->UnloadAudio(MusicVolume);
	TiXmlDocument Doc;
	TiXmlDeclaration* Declare = new TiXmlDeclaration{ "1.0", "utf - 8", "" };
	Doc.LinkEndChild(Declare);
	TiXmlElement* Root = new TiXmlElement{ "Volume.xml" };
	Doc.LinkEndChild(Root);
	Root->SetAttribute("SFXVolume", m_sxfVolume);
	Root->SetDoubleAttribute("MasterVolume", m_MasterVolume);
	Doc.SaveFile("Volume");
	//SGD::AudioManager::GetInstance()->StopAudio(MusicVolume);
	SGD::AudioManager::GetInstance()->UnloadAudio(MusicVolume);
	//SGD::AudioManager::GetInstance()->StopAudio(SFXVolume);
	SGD::AudioManager::GetInstance()->UnloadAudio(SFXVolume);
}

bool OptionsState::Update(float elapsedTime)
{
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) == true && Game::GetInstance()->CheckPriveous() == true || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == true)
	{
		Game::GetInstance()->ChangeState(MainMenuState::GetInstance());
	}
	else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Escape) == true && Game::GetInstance()->CheckPriveous() == false || SGD::InputManager::GetInstance()->IsButtonPressed(0, 0) && Game::GetInstance()->CheckPriveous() == false)
	{
		Game::GetInstance()->Pause(GameplayState::GetInstance());
	}
	if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Down) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Down))
	{
		// next option
		m_cursor++;
		
		//SGD::AudioManager::GetInstance()->PlayAudio(MusicVolume);
		//SGD::AudioManager::GetInstance()->StopAudio(SFXVolume);
		// wrap around
		if (m_cursor > 1)
		{
			m_cursor = 0;



		}

	}
	else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Up) == true || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Up))
	{
		// prev option
		
		m_cursor--;

		// wrap around
		if (m_cursor < 0)
			//Position = SGD::Point{ 0, 350 };
			m_cursor = 1;
		

	}

	if (m_cursor == 0)
	{
		//SGD::AudioManager::GetInstance()->
		
	
		SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects, m_sxfVolume);
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music, 0);
			//SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects,m_MasterVolume);
		
			if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Right) && m_sxfVolume != 100 || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Right) && m_sxfVolume != 100)
		{
			m_sxfVolume += 10;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects, m_sxfVolume);
			//SGD::AudioManager::GetInstance()->PlayAudio(SFXVolume);


		}
			else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Left) && m_sxfVolume != 0 || SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Left) && m_sxfVolume !=  0)
		{
			m_sxfVolume -= 10;
			SGD::AudioManager::GetInstance()->SetAudioVolume(SFXVolume, m_sxfVolume);
			//SGD::AudioManager::GetInstance()->PlayAudio(SFXVolume);
		}
	}

	if (m_cursor == 1)
	{
		
			//SGD::AudioManager::GetInstance()->SetAudioVolume(MusicVolume, 0);
		SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::SoundEffects, 0);
		SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music, m_MasterVolume);
			
		
		if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Left) && m_MasterVolume != 100 || SGD::InputManager::GetInstance()->IsDPadPressed(0,SGD::DPad::Right) && m_MasterVolume != 100)
		{
			m_MasterVolume += 10;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music, m_MasterVolume);


		}
		else if (SGD::InputManager::GetInstance()->IsKeyPressed(SGD::Key::Right) && m_MasterVolume != 0 ||  SGD::InputManager::GetInstance()->IsDPadPressed(0, SGD::DPad::Left) && m_MasterVolume != 0)
		{
			m_MasterVolume -= 10;
			SGD::AudioManager::GetInstance()->SetMasterVolume(SGD::AudioGroup::Music, m_MasterVolume);

		}
	}
	return true;
}
void OptionsState::Render(float elapsedTime)
{
	SGD::Rectangle Rect;
	Rect.top = 100;
	Rect.left = 30;
	Rect.right = ((470.f * (m_sxfVolume / 100.f)) + Rect.left);
	Rect.bottom = 130;
	BitmapFont* pFont = Game::GetInstance()->GetFont();
	pFont->Draw("  SFX Volume:", SGD::Point{ 0, 0 });
	pFont->Draw("0", SGD::Point{ 0, 100 });
	pFont->Draw("100", SGD::Point{ 500, 100 });
	if (m_sxfVolume > 0)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle(Rect, SGD::Color{ 255, 255, 255, 255 }, SGD::Color{ 0, 255, 255, 255 }, 3);
		SGD::OStringStream output;
		output << m_sxfVolume;
		pFont->Draw(output.str().c_str(), SGD::Point{ Rect.right, 130 });
	}
	//SGD::GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(125,105,Rect,130), SGD::Color{ 255, 255, 255, 255 }, SGD::Color{ 0, 255, 255, 255 }, 3);

	float width = Game::GetInstance()->GetScreenSize().width;
	SGD::Rectangle rect;
	rect.top = 350;
	rect.left = 30;
	rect.right = ((470.f * (m_MasterVolume / 100.f)) + Rect.left);
	rect.bottom = 380;

	pFont->Draw("  Master Volume:", SGD::Point{ 0, 300 });
	pFont->Draw("0", SGD::Point{ 0, 350 });
	pFont->Draw("100", SGD::Point{ 500, 350 });
	if (m_MasterVolume > 0)
	{
		SGD::GraphicsManager::GetInstance()->DrawRectangle(rect, SGD::Color{ 255, 255, 255, 255 }, SGD::Color{ 0, 255, 255, 255 }, 3);
		SGD::OStringStream output;
		output << m_MasterVolume;
		pFont->Draw(output.str().c_str(), SGD::Point{ rect.right, 380 });
	}

	pFont->Draw("=", { (width - (10 * 100)) / 2, 0.0f + 300 * m_cursor },
		1.0f, { 0, 255, 0 });
}