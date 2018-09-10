//*********************************************************************//
//	File:		DestroyEntityMessage.cpp
//	Author:		Blake Bergstrom
//	Course:		Structure Of Game Design
//	Purpose:	To Make DestroyEntityMessage and set and make variables 
//
//*********************************************************************//

#include "DestroyEntityMessage.h"
#include "../SGD Wrappers/SGD_Message.h"
#include "Entity.h"
#include "MessageID.h"


DestroyEntityMessage::DestroyEntityMessage(Entity* _entity) :SGD::Message(MessageID::MSG_DESTROY_ENITY)
{
	EntityMessage = _entity;
	EntityMessage->AddRef();
}



DestroyEntityMessage::~DestroyEntityMessage()
{
	EntityMessage->Release();
}
