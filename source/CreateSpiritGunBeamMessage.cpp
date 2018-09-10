//*********************************************************************//
//	File:		CreateSpiritGunBeamMessage.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make  CreateSpiritGunBeamMessage and set and make variables 
//
//*********************************************************************//

#include "CreateSpiritGunBeamMessage.h"
#include "Yusuke.h"
#include "MessageID.h"

CreateSpiritGunBeamMessage::CreateSpiritGunBeamMessage(Yusuke* _owner) :Message(MessageID::MSG_CREATE_ENERGYBALL)
{
	m_Owner = _owner;
	m_Owner->AddRef();
}


CreateSpiritGunBeamMessage::~CreateSpiritGunBeamMessage()
{
	m_Owner->Release();
}
