//*********************************************************************//
//	File:		Yusuke.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make Yusuke and set and make variables 
//
//*********************************************************************//
#pragma once
#include "Entity.h"
#include "../SGD Wrappers/SGD_IListener.h"
#include "../SGD Wrappers/SGD_AudioManager.h"
#include "Kurama.h"
class CellAnimation;
class Yusuke : public Entity, public SGD::IListener
{
public:

	Yusuke();
	~Yusuke();
	// Update and Render will Show and Mover Yusuke on the screen
	void Update(float elapsedTime);
	void	Render(void);

	// Mutators for Yusukes Health And Spirit Energy
	void SetHealth(float _health) { m_Health = _health; }
	void SetSpiritEnergy(float _Spirit) { m_SpiritEnergy = _Spirit; }

	// Mutator for Yusukes speed and Acceleration
	void SetSpeed(float _Speed) { m_speed = _Speed; }
	void SetAcceleration(float _acceleraion) { m_aceleration = _acceleraion; }
	void SetSpiritGun(SGD::HAudio _audio) { SpiritGun = _audio; }
	void SetShotGunAudio(SGD::HAudio _audio) { ShotGunAudio = _audio; }
	void HandleEvent(const SGD::Event* pEvent);
	// Acsessors for Yusukes Speed and Acceleration
	float GetSpeed(void) { return m_speed; }
	float GetAceleration(void) { return m_aceleration; }

	// Accsessors for Yusukes Health and SpiritEnergy
	float GetYusukesHealth(void) const { return m_Health; }
	float GetYusukesSpiritEnergy(void) const { return m_SpiritEnergy; }
	SGD::HAudio GetSpiritGun(void) { return SpiritGun; }
	SGD::HAudio GetShotGunAudio(void) { return ShotGunAudio; }
	int GetScore() { return m_score; }
	void SetScore(int _score) { m_score = _score; }
	bool GetTurn(void) const { return Turn; }
	void StayinWorldCollision(void);
	void SetWinlose(bool _windLose) { WinLose = _windLose; }
	//SGD::HAudio GetHurt(void) { return SpiritGun; }
	SGD::HAudio GetHurtAudio(void) { return GetHurt; }
	SGD::HAudio GetWinAudio(void) { return YusukeWins; }
	void SetGetHurtAudio(SGD::HAudio _audio) { GetHurt = _audio; }
	void SetGetWinAudio(SGD::HAudio _audio ) { YusukeWins = _audio; }
	// InitializeAnimation Will set all of yusukes Animations at run time
	void InitializeAnimation(void);

	// Get rect is gong to be used for collision rectangle.
	SGD::Rectangle GetRect(void)	const;

	int		GetType(void)	const;
protected:
	// What this is is Yusukes Health it will be displayed on the screen right above his head 
	float m_Health = 100.0f;
	// What this is is Yusukes Health it will be displayed on the screen right above his head But below his health 
	float m_SpiritEnergy = 100.0f;
	// what this is, is the speed that yusuke will be walking with
	float m_speed = 100.0f;
	// what this is, is what yusuke's exceration would be when fireing a Spirit gun 
	float m_aceleration = 60.0f;
	// this is a CellAnimation Array that holds all of Yusukes Animations 
	CellAnimation* YusukeAnimation[10];
	// this will determine what animation you will be on at a gvin time.
	int CurrentAnimation = 0;
	// this variable is used to turn Yusuke's Position
	bool Turn = true;
	float Timer = 0.0f;
	int m_score = 0;
	float TimerShotGun = 0.0f;
	bool m_CollisionRectRender = false;
	SGD::HTexture Animation_Image[8];
	SGD::HAudio SpiritGun;
	SGD::HAudio ShotGunAudio;
	SGD::HAudio GetHurt;
	SGD::HAudio YusukeWins;
	bool WinLose = false;
	SGD::HAudio KuramaWins = SGD::AudioManager::GetInstance()->LoadAudio(L"resource/audio/Bab_Kurama Wins.wav");
	bool CheatOn = false;
};

