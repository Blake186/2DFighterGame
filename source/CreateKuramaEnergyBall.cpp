//*********************************************************************//
//	File:		CreateKuramaEnergyBall.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make CreateKuramaEnergyBall and set and make variables 
//
//*********************************************************************//
#include "CreateKuramaEnergyBall.h"
#include "MessageID.h"
#include "Kurama.h"

CreateKuramaEnergyBall::CreateKuramaEnergyBall(Kurama*_owner) :Message(MessageID::KURAMA_ENERGY_BALL)
{
	m_Owner = _owner;
	m_Owner->AddRef();
}


CreateKuramaEnergyBall::~CreateKuramaEnergyBall()
{
	m_Owner->Release();
}
