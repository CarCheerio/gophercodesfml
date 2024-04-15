#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <fstream>
#include <iostream>

// This class is the game engine

class Game
{
private:
	//Variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode VideoMode;
	sf::Event ev;

	sf::Texture grasstxt;
	sf::Sprite grasssprt;
	/*
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
*/
	//private functions
	void initVariables();
	void initWindow();


public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;


	//Functions
	void pollEvents();
	void update();
	void render();

};