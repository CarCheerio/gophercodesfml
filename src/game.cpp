#include "game.h"
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;

//void Game::GameTile(std::string textureName, float x, float y)
//{


//}
/*
void Game::lawngrid()
{
    gridCubeWidth = 16, gridCubeHeight = 16;

    cube.Position.X = round(cube.Position.X / gridCubeWidth) * gridCubeWidth;
    cube.Position.Y = round(cube.Position.Y / gridCubeHeight) * gridCubeHeight;


}
*/

//Provate Functions
void Game::initVariables()
{

    //steak texture code
    steakplctxt.loadFromFile("./steakplaced.png");
    steakplcsprt.setTexture(steakplctxt);
    steakplcsprt.setScale(3.0f, 3.0f);

    //lawn with fencline printed constantly in the window
    lawntxt.loadFromFile("./lawn.png");
    lawnsprt.setTexture(lawntxt);
    lawnsprt.setScale(3.0f, 3.0f);
}

void Game::initWindow()
{
    this->VideoMode.height = 1152;
    this->VideoMode.width = 1152;

    this->window.create(this->VideoMode, "Gopher", sf::Style::Titlebar | sf::Style::Close);

}
//This is creating the grid where the aray will interact with.
void Game::initGridPiece()
{
    //havent figured this part out yet 
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (lawn[i][j] == 1) { steakplcsprt.setPosition(i * 96, j * 96); window.draw(steakplcsprt); }
            //else if (array[i][j] == 0) { grass.setPosition(i * sprite_12, j * sprite_12); window.draw(grass); }
            else if (lawn[i][j] == 2) { gophersprt.setPosition(i * 96, j * 96); window.draw(gophersprt); }
        }
    }

    gridSprite.setPosition((1152.f / 2) - (gridSprite.getGlobalBounds().width / 2), (1152.f / 2) - (gridSprite.getGlobalBounds().height / 2));
    gridPieces;

    for (int x = 0; x < 12; x++)
    {

        for (int y = 0; y < 12; y++)
        {
            gridArray[x][y] = 1;

        }

    }
}

void Game::placeStake(int locale[3][2], int array[12][12], int counter)
{

    //This function places the stakes. It takes in the array of stake locations and the gameboard, as well as a counter to know which stake you are placing. The stake location gets pulled from the stake array, and then the corresponding x, y location on the game board is switched from a 0 to a 1.

    if (counter == 0) {
        // Places the 1st, 4th, 7th, etc stake
        array[locale[0][0]][locale[0][1]] = 1;

    }
    else if (counter == 1) {
        // Places 2nd, 5th, 8th, etc stake
        array[locale[1][0]][locale[1][1]] = 1;

    }
    else if (counter == 2) {
        // Places 3rd, 6th, 9th, etc stake
        array[locale[2][0]][locale[2][1]] = 1;
    }

}

void Game::mainLogic()
{
    // initializes variables for hammer, gofer coorsinates, and continuing the program
    int lawn[12][12] = {
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
    }; // 10 x 10 play area, with a 1 border fence
    int column, row;
    int empty = 0, steak = 1, gofer = 2; // describes the numbers in the array
    pair<int, int> newGoferPosition;
    bool overflow = false;
    int stakes[3][2] = {
    {100, 100}, // 0:{0, 1} set to impossible 12 number
    {100, 100}, // 1:{x, y} to avoid accidently deleting
    {100, 100}  // 2:{x, y} a fence post
    }; //creates 2D array of steaks, 3 stakes and their position
    int totalStakes = 0;

    srand(time(NULL));

    // randomizes the gofer's initial position
    int goferRow = (rand() % 10);
    int goferColumn = (rand() % 10);

    int hammerTime;

    // places the gofer
    lawn[goferRow][goferColumn] = gofer;

    // do-while loop executes until the user decides to stop
    do {
        bool success = true;
        // gets column and row of hammer from user
        /*cout << "\nColumn: ";
        cin >> column;

        cout << "\nRow: ";
        cin >> row;
        */

        // Checking if a stake already exists at input position
        for (int i = 0; i < 3; i++) {
            //if x coordinate = given x coord, check y
            if (stakes[i][0] == row) {
                for (int j = 0; j < 3; j++) {
                    // if y also matches given, stake already exists
                    if (stakes[i][1] == column) {
                        cout << "\nThere is already a stake here!";
                        success = false;
                        break;
                    }
                }
            }
        }

        if (success == false) continue;
        // "moves" hammer to those coordinates
        hammerTime = lawn[row][column];

        if (success == true) {
            if (totalStakes == 0) {
                // Removes the oldest stake
                if (overflow == true) lawn[stakes[0][0]][stakes[0][1]] = 0;

                stakes[0][0] = row;
                stakes[0][1] = column;
                placeStake(stakes, lawn, totalStakes);
            }
            else if (totalStakes == 1) {
                // Removes the middle oldest stake
                if (overflow == true) lawn[stakes[1][0]][stakes[1][1]] = 0;

                stakes[1][0] = row;
                stakes[1][1] = column;
                placeStake(stakes, lawn, totalStakes);
            }
            else if (totalStakes == 2) {
                // Removes the least old stake
                if (overflow == true) lawn[stakes[2][0]][stakes[2][1]] = 0;

                stakes[2][0] = row;
                stakes[2][1] = column;
                placeStake(stakes, lawn, totalStakes);
            }
            //increasing number or stakes on board after placing
            totalStakes++;
            //if three exist, the fourth stake will need to start deleting the oldest
            if (totalStakes == 3) {
                overflow = true;
                totalStakes = 0;
            }
        }

        if (hammerTime == empty || hammerTime == steak) {
            // places steak and removes the ghost gofer value
            lawn[goferRow][goferColumn] = empty;
            // gets the new gofer position coordinates
            newGoferPosition = goferMover(lawn, goferRow, goferColumn);
            // updates the gofer position variables
            goferRow = newGoferPosition.first;
            goferColumn = newGoferPosition.second;
            // updates the gofer postion
            lawn[goferRow][goferColumn] = gofer;
        }
        else if (hammerTime == gofer) {
            // executes win scenario
            cout << "\nBonk!";
            exit(0);
        }

        // outputs the array to be seen
        //showGrid(lawn);
    } while (totalStakes < 3);

    //return 0;
}

void Game::lawngrid()
{

}

/*
void Game::placeStake(int locale[3][2], int array[12][12], int counter)
{
    
    //This function places the stakes. It takes in the array of stake locations and the gameboard, as well as a counter to know which stake you are placing. The stake location gets pulled from the stake array, and then the corresponding x, y location on the game board is switched from a 0 to a 1.
  
    if (counter == 0) {
        // Places the 1st, 4th, 7th, etc stake
        array[locale[0][0]][locale[0][1]] = 1;

    }
    else if (counter == 1) {
        // Places 2nd, 5th, 8th, etc stake
        array[locale[1][0]][locale[1][1]] = 1;

    }
    else if (counter == 2) {
        // Places 3rd, 6th, 9th, etc stake
        array[locale[2][0]][locale[2][1]] = 1;
    }

}*/

bool Game::isSteak(int arrLawn[12][12], int steakRow, int steakColumn)
{

    // checks individual spaces for steaks
    if (arrLawn[steakRow][steakColumn] == 1)
        return true;
    else
        return false;

}

pair <int, int> Game::goferMover(int arrLawn[12][12], int goferRow, int goferColumn)
{
    bool steaksAround[8] = { true };
    int column[8] = { 0 }, row[8] = { 0 };

    // checks the 8 spaces around the gofer for steaks
    for (int i = 0; i < 8; i++) {
        switch (i) {
        case 0:
            // upper left
            steaksAround[0] = isSteak(arrLawn, (goferRow + 1), (goferColumn - 1));
            column[0] = -1;
            row[0] = 1;
            break;

        case 1:
            // left
            steaksAround[1] = isSteak(arrLawn, (goferRow), (goferColumn - 1));
            column[1] = -1;
            break;

        case 2:
            // bottom left
            steaksAround[2] = isSteak(arrLawn, (goferRow - 1), (goferColumn - 1));
            column[2] = -1;
            row[2] = -1;
            break;

        case 3:
            // upper middle
            steaksAround[3] = isSteak(arrLawn, (goferRow + 1), (goferColumn));
            row[3] = 1;
            break;

        case 4:
            // bottom middle
            steaksAround[4] = isSteak(arrLawn, (goferRow - 1), (goferColumn));
            row[4] = -1;
            break;

        case 5:
            // upper right
            steaksAround[5] = isSteak(arrLawn, (goferRow + 1), (goferColumn + 1));
            column[5] = 1;
            row[5] = 1;
            break;

        case 6:
            // right
            steaksAround[6] = isSteak(arrLawn, (goferRow), (goferColumn + 1));
            column[6] = 1;
            break;

        case 7:
            // bottom right
            steaksAround[7] = isSteak(arrLawn, (goferRow - 1), (goferColumn + 1));
            column[7] = 1;
            row[7] = -1;
            break;
        }
    }

    int move = (rand() % 8), area = 0;
    int newColumn, newRow, newSpot;

    for (int j = 0; j < 8; j++) {
        // else if opening, gofer moves to that opening
        if (steaksAround[j] == false) {
            newRow = (goferRow + row[j]);
            newColumn = (goferColumn + column[j]);
            return make_pair(newRow, newColumn);
        }

    }

    // if surrounded gofer pops out a random steak and moves to a random location provided it is steak free
    if (area == 8) {
        steaksAround[move] = false; // pops a random steak

        do {
            // choses a random spot on the lawn for the gofer to move in
            newColumn = (rand() % 10);
            newRow = (rand() % 10);
            // checks if new spot is steak free
            newSpot = isSteak(arrLawn, newRow, newColumn);
        } while (newSpot != false);

        // returns the randomized gofer spot
        return make_pair(newRow, newColumn);
    }
    else { // defaults the gofer to not move
        return make_pair(goferRow, goferColumn);
    }

}

//Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();

}
Game::~Game()
{

}
//accessors
const bool Game::running() const
{
    return this->window.isOpen();
}
//functions
void Game::pollEvents()
{
    //event polling
    while (this->window.pollEvent(this->ev))
    {

        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window.close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window.close();
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


    this->window.clear();

    //draw game objects

    this->window.draw(lawnsprt);
    this->window.draw(steakplcsprt);
    this->window.display();

}
