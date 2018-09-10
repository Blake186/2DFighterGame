//*********************************************************************//
//	File:		DestroyEntityMessage.h
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make DestroyEntityMessage and set and make variables 
//
//*********************************************************************//
#pragma once
#include "../SGD Wrappers/SGD_Message.h"
class Entity;
class DestroyEntityMessage : public SGD::Message
{
public:
	DestroyEntityMessage(Entity* Destroy);
	virtual ~DestroyEntityMessage();
	Entity* GetEntityMessage()const { return EntityMessage; }
private:
	Entity* EntityMessage;
};

