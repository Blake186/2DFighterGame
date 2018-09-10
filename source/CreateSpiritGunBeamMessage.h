//*********************************************************************//
//	File:		CreateSpiritGunBeamMessage.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make  CreateSpiritGunBeamMessage and set and make variables 
//
//*********************************************************************//

#pragma once
#include "../SGD Wrappers/SGD_Message.h"
class Yusuke;
class CreateSpiritGunBeamMessage : public SGD::Message
{
public:
	CreateSpiritGunBeamMessage(Yusuke*);
	~CreateSpiritGunBeamMessage();
	Yusuke* GetYusukeOwner(void) const { return m_Owner; }

private:
	Yusuke* m_Owner;
};

