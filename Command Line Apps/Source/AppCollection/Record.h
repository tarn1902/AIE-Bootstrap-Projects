/*------------------------------------------------
	File Name: Record.h
	Purpose: Holds header information for Record
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#pragma once
struct Record {
	char callNumber[10], title[20], author[20], bookStatus[2], dueDate[10], borrowerName[20];
};
