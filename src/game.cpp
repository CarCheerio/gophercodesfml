#include "game.h"
#include <iomanip>
#include <fstream>
#include <iostream>
//Provate Functions
void Game::initVariables()
{
    this->window = nullptr;
    
    this->grasstxt.loadFromFile("./grass.png");
    this->grasssprt.setTexture(grasstxt);
    grasssprt.setScale(4.0f, 4.0f);

}

void Game::initWindow()
{
    this->VideoMode.height = 600;
    this->VideoMode.width = 600;

    this->window = new sf::RenderWindow(this->VideoMode, "Gopher", sf::Style::Titlebar | sf::Style::Close);

}
//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();

}
Game::~Game()
{
    delete this->window;

}
//accessors
const bool Game::running() const
{
    return this->window->isOpen();
}
//functions
void Game::pollEvents()
{
    //event polling
    while (this->window->pollEvent(this->ev))
    {

        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }

    }

}

void Game::update()
{
    this->pollEvents();

}

void Game::render()
{
    /*
           renders the game objects
    */


    this->window->clear();

      //draw game objects
    this->window->draw(grasssprt);
    
    
    this->window->display();

}
