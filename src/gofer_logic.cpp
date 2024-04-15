/* Just to get all its logic right. I’m thinking of updating the same array, giving empty spaces a value of 0, steaks a value of 1, and the gofer a value of 2 with some math to make it logic good. */
#include <iostream>
#include <random>
using namespace std;

//CONSTANTS
const int SIZE = 12;

//FUNCTIONS
//displays play area
void showGrid(int array[SIZE][SIZE]) {
  /*
    Shows valid play area, loops through the square array and 
    outputs a # if there is a stake (incl. fence) noted by a 1 and ouputs a .
    if the area doesn't contain a stake noted by a 0.
  */
  cout << "\n";
  //prints column number followed by . for 0 and # for 1.
  for(int i = 0; i < SIZE; i++){
    cout << "\t" << i << "\t";
    for(int j = 0; j < SIZE; j++){
      if(array[i][j] == 1) cout << "#";
      else if (array[i][j] == 0) cout << ".";
      else if (array[i][j] == 2) cout << "@";
    }
    cout << "\n";
  }
}

//places stake onto play area.
void placeStake(int locale[3][2], int array[SIZE][SIZE], int counter){ 
  /*
    This function places the stakes. It takes in the array of stake locations and the gameboard, as well as a counter to know which stake you are placing. The stake location gets pulled from the stake array, and then the corresponding x, y location on the game board is switched from a 0 to a 1.
  */
  if(counter == 0){
    // Places the 1st, 4th, 7th, etc stake
    array[locale[0][0]][locale[0][1]] = 1;  

  } else if(counter == 1) {
    // Places 2nd, 5th, 8th, etc stake
     array[locale[1][0]][locale[1][1]] = 1;

  } else if(counter == 2){
    // Places 3rd, 6th, 9th, etc stake
    array[locale[2][0]][locale[2][1]] = 1;
  }
}

// cheaks if there is a steak at the given coordinates
bool isSteak(int arrLawn[SIZE][SIZE], int steakRow, int steakColumn) {
// checks individual spaces for steaks
  if (arrLawn[steakRow][steakColumn] == 1)
    return true;
  else
    return false;
}

// moves the gofer and calls the isSteak function to check for steaks in each of 8 directions
// that the gofer could possibly move in
pair <int, int> goferMover(int arrLawn[SIZE][SIZE], int goferRow, int goferColumn) {
  bool steaksAround[8] = {true};
  int column[8] = {0}, row[8] = {0};
  
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
    
    do{
      // choses a random spot on the lawn for the gofer to move in
      newColumn = (rand() % 10);
      newRow = (rand() % 10);
      // checks if new spot is steak free
      newSpot = isSteak(arrLawn, newRow, newColumn);
    } while(newSpot != false);

    // returns the randomized gofer spot
    return make_pair(newRow, newColumn);
  }
  else { // defaults the gofer to not move
    return make_pair(goferRow, goferColumn);
  }
}


int main() {
  // initializes variables for hammer, gofer coorsinates, and continuing the program
  int lawn[SIZE][SIZE] = {
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
  {100, 100}, // 0:{0, 1} set to impossible size number
  {100, 100}, // 1:{x, y} to avoid accidently deleting
  {100, 100}  // 2:{x, y} a fence post
  }; //creates 2D array of steaks, 3 stakes and their position
  int totalStakes = 0;

  srand(time (NULL));

  // randomizes the gofer's initial position
  int goferRow = (rand() % 10);
  int goferColumn = (rand() % 10);

  int hammerTime;

  // places the gofer
  lawn[goferRow][goferColumn] = gofer;

  // do-while loop executes until the user decides to stop
  do{
    bool success = true;
    // gets column and row of hammer from user
    cout << "\nColumn: ";
    cin >> column;

    cout << "\nRow: ";
    cin >> row;

    // Checking if a stake already exists at input position
    for(int i = 0; i < 3; i++){
      //if x coordinate = given x coord, check y
      if(stakes[i][0] == row){
        for(int j = 0; j < 3; j++){
          // if y also matches given, stake already exists
          if(stakes[i][1] == column){
            cout << "\nThere is already a stake here!";
            success = false;
            break;
          } 
        }
      }
    }    

    if(success == false) continue;
    // "moves" hammer to those coordinates
    hammerTime = lawn[row][column];

    if(success == true) {
      if(totalStakes == 0){
        // Removes the oldest stake
        if(overflow == true) lawn[stakes[0][0]][stakes[0][1]] = 0; 

        stakes[0][0] = row;
        stakes[0][1] = column;
        placeStake(stakes, lawn, totalStakes);
      }
      else if(totalStakes == 1){
        // Removes the middle oldest stake
        if(overflow == true) lawn[stakes[1][0]][stakes[1][1]] = 0; 

        stakes[1][0] = row;
        stakes[1][1] = column;
        placeStake(stakes, lawn, totalStakes);
      }
      else if(totalStakes == 2){
        // Removes the least old stake
        if(overflow == true) lawn[stakes[2][0]][stakes[2][1]] = 0; 

        stakes[2][0] = row;
        stakes[2][1] = column;
        placeStake(stakes, lawn, totalStakes);
      }
      //increasing number or stakes on board after placing
      totalStakes++;
      //if three exist, the fourth stake will need to start deleting the oldest
      if(totalStakes == 3){
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
    showGrid(lawn);
  } while(totalStakes < 3);
  
  return 0;
}




