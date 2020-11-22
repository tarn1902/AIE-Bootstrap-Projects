/*----------------------------------------
File Name: GameMessages.h
Purpose: Holds game messages for both 
 server and client.
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <MessageIdentifiers.h>

//Enumerator of game messages
enum GameMessages
{
	ID_SERVER_TEXT_MESSAGE = ID_USER_PACKET_ENUM + 1,
	ID_SERVER_SET_CLIENT_ID,
	ID_CLIENT_CLIENT_DATA,
	ID_CLIENT_CLIENT_DATA_X,
	ID_CLIENT_CLIENT_DATA_Y,
	ID_CLIENT_UPDATE_DATA,
};
