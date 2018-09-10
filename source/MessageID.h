//*********************************************************************//
//	File:		MessageID.h
//	Author:		
//	Course:		
//	Purpose:	MessageID enum class defines the message types
//*********************************************************************//

#pragma once


//*********************************************************************//
// MessageID enum class
//	- unique identifiers for messages sent to Game::MessageProc
enum class MessageID	
{
	MSG_UNKNOWN = 0,
	MSG_CREATE_ENERGYBALL,
	MSG_CREATE_SHOT_GUN, MSG_DESTROY_ENITY, KURAMA_ENERGY_BALL,
};
