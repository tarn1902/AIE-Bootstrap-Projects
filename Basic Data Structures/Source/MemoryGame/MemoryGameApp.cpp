/*----------------------------------------
File Name: MemoryGameApp.cpp
Purpose: Holds each method for MemoeryGameApp.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "MemoryGameApp.h"
//-----------------------------------------------------------
// Constructs Application
//-----------------------------------------------------------
MemoryGameApp::MemoryGameApp() {}

MemoryGameApp::~MemoryGameApp() {}

//-----------------------------------------------------------
// Creates pointers to created objects for application
//	replayerTurn (bool): replayerTurns true if method is run correctly
//-----------------------------------------------------------
bool MemoryGameApp::startup() {
	m_font = new aie::Font("../../../../bin/font/consolas.ttf", 32);
	titleFont = new aie::Font("../../../../bin/font/consolas_bold.ttf", 64);

	players.CreateArray(2);
	buttonGroup.CreateArray(2);
	
	m_2dRenderer = new aie::Renderer2D();

	Player* player1 = new Player();
	Player* player2 = new Player();

	Button* play = new Button("Play", m_font);
	Button* option = new Button("Option", m_font);
	Button* exit = new Button("Exit", m_font);

	players.AddToEnd(player1);
	players.AddToEnd(player2);

	buttonGroup.AddToEnd(play);
	buttonGroup.AddToEnd(option);
	buttonGroup.AddToEnd(exit);

	CreateDeck();
	return true;
}

//-----------------------------------------------------------
// Deletes pointers of created objects
//-----------------------------------------------------------
void MemoryGameApp::shutdown() {
	revealed1 = -1;
	delete m_font;
	delete titleFont;
	delete m_2dRenderer;
	if (deck.data != nullptr)
	{
		delete[] deck.data;
		deck.data = nullptr;
	}
	if (players.data != nullptr)
	{
		delete[] players.data;
		players.data = nullptr;
	}
	if (buttonGroup.data != nullptr)
	{
		delete[] buttonGroup.data;
		buttonGroup.data = nullptr;
	}
}

//-----------------------------------------------------------
// Checks any updates related to inputs
//	deltaTime (float): what time was it called?
//-----------------------------------------------------------
void MemoryGameApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	//Inputs for when game is running
	if (gameStart)
	{
		if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
		{
			cardHighlight++;
			if (cardHighlight > deck.usedElements-1)
			{
				cardHighlight--;
			}
			if (cardHighlight < 0)
			{
				cardHighlight--;
			}
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
		{
			cardHighlight--;
			if (cardHighlight > deck.usedElements-1)
			{
				cardHighlight++;
			}
			if (cardHighlight < 0)
			{
				cardHighlight++;
			}
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		{

			cardHighlight += 6;
			if (cardHighlight > deck.usedElements-1)
			{
				cardHighlight -= 6;
			}
			if (cardHighlight < 0)
			{
				cardHighlight -= 6;
			}

		}
		if (input->wasKeyPressed(aie::INPUT_KEY_UP))
		{

			cardHighlight -= 6;
			if (cardHighlight > deck.usedElements-1)
			{
				cardHighlight += 6;
			}
			if (cardHighlight < 0)
			{
				cardHighlight += 6;
			}
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
		{
			if (revealed1 == -1 && deck.data[cardHighlight]->GetOut() == false)
			{
				revealed1 = cardHighlight;
			}
			else if (revealed2 == -1 && cardHighlight != revealed1 && deck.data[cardHighlight]->GetOut() == false)
			{
				revealed2 = cardHighlight;
			}
		}
	}
	//Inputs for when in options menu
	else
	{
		//If want to change deck size
		if (inOptions)
		{
			ImGui::Begin("Deck size option", (bool*)0, 0);
			static int pairs = 18;
			ImGui::InputInt("Value", &pairs);
			if (pairs > 18)
			{
				pairs = 18;
			}
			if (ImGui::Button("Accept", ImVec2(50, 0)))
			{
				if (pairs % 2 != 0)
				{
					pairs++;
				}
				if (pairs == 0)
				{
					pairs = 2;
				}
				maxCardPairs = pairs;
				inOptions = false;
			}
			ImGui::End();
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_DOWN))
		{
			buttonHighlight++;
			if (buttonHighlight == 3)
			{
				buttonHighlight--;
			}
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_UP))
		{
			buttonHighlight--;
			if (buttonHighlight == -1)
			{
				buttonHighlight++;
			}
		}
		if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
		{
			switch (buttonHighlight)
			{
			case 0:
			{
				gameStart = true;
				for (int i = 0; i < 10; i++)
				{
					ShuffleDeck();
				}
				break;
			}
			case 1:
			{
				inOptions = true;
				break;
			}
			case 2:
			{
				quit();
				break;
			}
			}
		}
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		buttonHighlight = 0;
		Reset();
		gameStart = false;
	}
}

//-----------------------------------------------------------
// Draws text or objects to window
//-----------------------------------------------------------
void MemoryGameApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	if (gameStart)
	{
		PlaceCards();
		PlaceUI();
		PlaceResults();
	}
	else
	{
		PlaceMenu();
	}
	// done drawing sprites
	m_2dRenderer->end();
}

//-----------------------------------------------------------
// Places cards on game screen
//-----------------------------------------------------------
void MemoryGameApp::PlaceCards()
{
	float size = maxCardPairs*2;
	float spliter = 0;
	if (maxCardPairs > 12.5)
	{
		spliter = 6;
	}
	else if (maxCardPairs > 8)
	{
		spliter = 5;
	}
	else if (maxCardPairs > 4.5)
	{
		spliter = 4;
	}
	else if(maxCardPairs > 2)
	{
		spliter = 3;
	}
	else if (maxCardPairs > 1)
	{
		spliter = 2;
	}
	spliter++;
	float xPos = 1280 / spliter;
	float yPos = 720 - 720 / spliter;

	//Goes through each row placing cards
	for (int i = 0; i < size; i++)
	{
		//Checks if a card was revealed
		if (i == revealed1 || i == revealed2)
		{
			if (i == cardHighlight)
			{
				deck.data[i]->DrawCard(m_2dRenderer, xPos, yPos, 40, 60, true, true, playerTurn);
			}
			else
			{
				deck.data[i]->DrawCard(m_2dRenderer, xPos, yPos, 40, 60, false, true, playerTurn);
			}
		}
		else
		{
			if (i == cardHighlight)
			{
				deck.data[i]->DrawCard(m_2dRenderer, xPos, yPos, 40, 60, true, false, playerTurn);
			}
			else
			{
				deck.data[i]->DrawCard(m_2dRenderer, xPos, yPos, 40, 60, false, false, playerTurn);
			}
		}
		//goes not next column
		xPos += 1280 / spliter;
		//goes to next row after column is completed
		if (xPos >= 1200)
		{
			xPos = 1280 / spliter;
			yPos -= 720 / spliter;
		}
		//Checks if two cards have been selected
		if (revealed1 != -1 && revealed2 != -1)
		{
			//Timer
			if (delayReveal != 0)
			{
				delayReveal--;
			}
			//triggers when timer is zero
			else
			{
				if (deck.data[revealed1]->picture == deck.data[revealed2]->picture)
				{
					//Checks which player gets point
					if (playerTurn)
					{
						players.data[0]->SetPoints(players.data[0]->GetPoints() + 1);
					}
					else
					{
						players.data[1]->SetPoints(players.data[1]->GetPoints() + 1);
					}
					deck.data[revealed1]->SetOut(true);
					deck.data[revealed2]->SetOut(true);
					cardsRemain -= 2;
				}
				//Changes players turn
				else
				{
					playerTurn = !playerTurn;
				}
				delayReveal = 500; //resets timer
				revealed1 = -1;
				revealed2 = -1;
			}
		}
	}
}

//-----------------------------------------------------------
// Places UI on screen
//-----------------------------------------------------------
void MemoryGameApp::PlaceUI()
{
	char player1Points[64];
	char player2Points[64];
	sprintf_s(player1Points, "%i", players.data[0]->GetPoints());
	sprintf_s(player2Points, "%i", players.data[1]->GetPoints());
	m_2dRenderer->setRenderColour(1, 0, 0);
	m_2dRenderer->drawBox(40, 40, 80, 80);
	m_2dRenderer->setRenderColour(1, 1, 1);
	m_2dRenderer->drawText(m_font, player1Points, 40, 40);
	m_2dRenderer->setRenderColour(0, 0, 1);
	m_2dRenderer->drawBox(1240, 40, 80, 80);
	m_2dRenderer->setRenderColour(1, 1, 1);
	m_2dRenderer->drawText(m_font, player2Points, 1240, 40);
}

//-----------------------------------------------------------
// Places results after game finished
//-----------------------------------------------------------
void MemoryGameApp::PlaceResults()
{
	if (cardsRemain == 0)
	{
		if (players.data[0]->GetPoints() > players.data[1]->GetPoints())
		{
			m_2dRenderer->drawText(m_font, "Red Wins", 1280 / 2 - 50, 680);
			m_2dRenderer->drawText(m_font, "Press Escape to exit to menu", 1280 / 2 - 250, 0 + 10);
			
		}
		else if (players.data[0]->GetPoints() < players.data[1]->GetPoints())
		{
			m_2dRenderer->drawText(m_font, "Blue Wins", 1280 / 2 - 50, 680);
			m_2dRenderer->drawText(m_font, "Press Escape to exit to menu", 1280 / 2 - 250, 0 + 10);
		}
		else
		{
			m_2dRenderer->drawText(m_font, "Draw", 1280 / 2 - 50, 680);
			m_2dRenderer->drawText(m_font, "Press Escape to exit to menu", 1280 / 2 - 250, 0+10);
		}
	}
}

//-----------------------------------------------------------
// Places menu when not in game
//-----------------------------------------------------------
void MemoryGameApp::PlaceMenu()
{
	m_2dRenderer->drawText(titleFont, "Memory Game", 1280 / 2 - 200, 720 / 2 + 250);
	m_2dRenderer->drawText(m_font, "Tarn Cooper", 1280 - 200, 0+15);
	if (textureError)
	{
		m_2dRenderer->drawText(m_font, "Missing textures detected", 0 + 15, 0 + 15);
	}

	//Tests which ubtton needs to be highlighted
	switch (buttonHighlight)
	{
	case 0:
	{
		buttonGroup.data[0]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 + 100, 160, 80, true);
		buttonGroup.data[1]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2, 160, 80, false);
		buttonGroup.data[2]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 - 100, 160, 80, false);
		break;
	}
	case 1:
	{
		buttonGroup.data[0]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 + 100, 160, 80, false);
		buttonGroup.data[1]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2, 160, 80, true);
		buttonGroup.data[2]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 - 100, 160, 80, false);
		break;
	}
	case 2:
	{
		buttonGroup.data[0]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 + 100, 160, 80, false);
		buttonGroup.data[1]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2, 160, 80, false);
		buttonGroup.data[2]->DrawButton(m_2dRenderer, 1280 / 2, 720 / 2 - 100, 160, 80, true);
		break;
	}
	}
}

//-----------------------------------------------------------
// randomly shuffles array of cards
//-----------------------------------------------------------
void MemoryGameApp::ShuffleDeck()
{
	DynamicArray<Card*> shuffleDeck;
	shuffleDeck.CreateArray(deck.usedElements);
	for (int i = 0; i < deck.usedElements; i++)
	{
		switch (rand()%3)
		{
		case 0:
		{
			shuffleDeck.AddToEnd(deck.data[i]);
			break;
		}
		case 1:
		{
			shuffleDeck.AddToMid(deck.data[i]);
			break;
		}
		case 2:
		{
			shuffleDeck.AddToStart(deck.data[i]);
			break;
		}
		}
	}
	for (int i = 0; i < deck.usedElements; i++)
	{
		deck.data[i] = shuffleDeck.data[i];
	}
}

//-----------------------------------------------------------
// Resets game to be played again
//-----------------------------------------------------------
void MemoryGameApp::Reset()
{
	for (int i = 0; i < deck.usedElements; i++)
	{
		if (players.usedElements > i)
		{
			players.data[i]->SetPoints(0);
		}
		deck.data[i]->SetOut(false);
	}
	cardsRemain = deck.usedElements;
}

//-----------------------------------------------------------
// Creates deck to be placed on game screen
//-----------------------------------------------------------
void MemoryGameApp::CreateDeck()
{
	deck.CreateArray(36);
	//Tests if all textures are in bin
	try
	{
		aie::Texture* error = new aie::Texture(" "); //For error testing
		aie::Texture* textureArray[] = {

			new aie::Texture("../../../../bin/textures/car.png"),
			new aie::Texture("../../../../bin/textures/rock_Large.png"),
			new aie::Texture("../../../../bin/textures/rock_medium.png"),
			new aie::Texture("../../../../bin/textures/rock_small.png"),
			new aie::Texture("../../../../bin/textures/ship.png"),
			new aie::Texture("../../../../bin/textures/ball.png"),
			new aie::Texture("../../../../bin/textures/barrelBeige.png"),
			new aie::Texture("../../../../bin/textures/barrelBlue.png"),
			new aie::Texture("../../../../bin/textures/barrelGreen.png"),
			new aie::Texture("../../../../bin/textures/barrelRed.png"),
			new aie::Texture("../../../../bin/textures/cake.png"),
			new aie::Texture("../../../../bin/textures/grass.png"),
			new aie::Texture("../../../../bin/textures/tankBeige.png"),
			new aie::Texture("../../../../bin/textures/tankBlue.png"),
			new aie::Texture("../../../../bin/textures/tankGreen.png"),
			new aie::Texture("../../../../bin/textures/tankRed.png"),
			new aie::Texture("../../../../bin/textures/numbered_grid.tga"),
			new aie::Texture("../../../../bin/textures/croissant.png"),

		};
		//Adds two of each into deck array
		for (int i = 0; i < maxCardPairs; i++)
		{
			deck.AddToEnd(new Card(textureArray[i]));
			deck.AddToEnd(new Card(textureArray[i]));
		}
		deck.ReduceSpace();

		//Tests each texture
		for (int i = 0; i < maxCardPairs; i++)
		{
			if (textureArray[i]->getFilename() == error->getFilename())
			{
				throw(textureArray[i]);
			}
		}
		delete error;
	}
	//Displays error on console
	catch (aie::Texture* e)
	{
		std::cout << "Missing texture: " << e << std::endl;
		textureError = true;
	}
	cardsRemain = deck.usedElements;
}