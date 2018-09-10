//*********************************************************************//
//	File:		CreateShotGunMessage.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make CreateShotGunMessage and set and make variables 
//
//*********************************************************************//
#pragma once
#include "../SGD Wrappers/SGD_Message.h"
class Yusuke;
class CreateShotGunMessage: public SGD::Message
{
public:
	CreateShotGunMessage(Yusuke*);
	~CreateShotGunMessage();
	Yusuke* GetYusukeOwner(void) const { return m_Owner; }

private:
	Yusuke* m_Owner;
};

