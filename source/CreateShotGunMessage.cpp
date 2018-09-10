//*********************************************************************//
//	File:		CreateKuramaEnergyBall.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make CreateKuramaEnergyBall and set and make variables 
//
//*********************************************************************//

#include "CreateShotGunMessage.h"
#include "Yusuke.h"
#include "MessageID.h"

CreateShotGunMessage::CreateShotGunMessage(Yusuke* _owner) :Message(MessageID::MSG_CREATE_SHOT_GUN)
{
	m_Owner = _owner;
	m_Owner->AddRef();
}


CreateShotGunMessage::~CreateShotGunMessage()
{
	m_Owner->Release();
}
