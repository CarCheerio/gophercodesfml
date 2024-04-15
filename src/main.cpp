
#include "game.h"
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
// init game engine
    Game game;

   
    //game loop
    while (game.running())
    {
        //update 
        game.update();

        //render
        game.render();
    }

    return 0;
}