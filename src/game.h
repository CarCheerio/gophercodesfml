#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <math.h>
#include <utility>
using namespace std;

#ifndef GAMETILE_H
#define GAMETILE_H
// This class is the game engine

class Game
{
private:
	//Variables
	//window


	sf::RenderWindow window;
	sf::VideoMode VideoMode;
	sf::Event ev;

	sf::Texture gophertxt;
	sf::Sprite gophersprt;
	sf::Texture gopherhittxt;
	sf::Sprite gopherhitsprt;
	sf::Texture steakplctxt;
	sf::Sprite steakplcsprt;
	sf::Texture steaktxt;
	sf::Sprite steaksprt;
	sf::Texture hammertxt;
	sf::Sprite hammersprt;
	sf::Texture lawntxt;
	sf::Sprite lawnsprt;

	sf::Sprite gridSprite;

	int gridCubeWidth, gridCubeHeight;
	sf::Sprite gridPieces[12][12];
	int gridArray[12][12];

	//private functions
	void initVariables();
	void initWindow();
	void initGridPiece();


	//lets get started
	// int goferMover;
	void mainLogic();
	int lawn[12][12];
	void placeStake(int locale[3][2], int array[12][12], int counter);
	bool isSteak(int arrLawn[12][12], int steakRow, int steakColumn);
	pair <int, int> goferMover(int arrLawn[12][12], int goferRow, int goferColumn);


public:



	//void GameTile(std::string, float, float);
	sf::Vector2f pos;// for the grid

	void lawngrid();

	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;


	//Functions
	void pollEvents();
	void update();
	void render();
#endif
};