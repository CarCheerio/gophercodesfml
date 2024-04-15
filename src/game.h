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