//*********************************************************************//
//	File:		CreateKuramaEnergyBall.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make CreateKuramaEnergyBall and set and make variables 
//
//*********************************************************************//
#pragma once
#include "../SGD Wrappers/SGD_Message.h"
class Kurama;

class CreateKuramaEnergyBall: public SGD::Message
{
public:
	CreateKuramaEnergyBall(Kurama*);
	~CreateKuramaEnergyBall();
	Kurama* GetKuramaOwner(void) const { return m_Owner; }
private:
	Kurama* m_Owner;

};

