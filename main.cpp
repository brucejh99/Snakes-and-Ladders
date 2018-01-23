#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <ctime>

using namespace std;

// Helper Functions
int diceRoll(){
    srand(time(NULL));
    int rolledNum = (rand() % 6 + 1);

  return rolledNum;
}

// Main Function
int main()
{
// Defining Players
struct Players{
  string playerName;
  int playerSpace;
};

// Defining Spaces
struct Space{
  int spaceNum;
  int changeSpace;
  bool isSnake;
};

// Defining Playing Board
Space board[100];
for(int i=0; i<100; i++){
  board[i] = {i+1, 0, false};
}
board[3] = {4, 10, false};
board[8] = {9, 22, false};
board[16] = {17, 10, true};
board[19] = {20, 18, false};
board[27] = {28, 56, false};
board[32] = {33, 12, true};
board[39] = {40, 19, false};
board[53] = {54, 20, true};
board[62] = {63, 18, false};
board[63] = {64, 14, true};
board[70] = {71, 20, false};
board[86] = {87, 63, true};
board[90] = {91, 55, true};
board[92] = {93, 20, true};
board[94] = {95, 20, true};
board[98] = {99, 21, true};

// Game Operation
cout << "How many players are there?" << endl;
int playerNum;
cin >> playerNum;

Players list[playerNum];

for(int i=0; i<playerNum; i++){
  cout << "What is the name of player " << i+1 << "?" << '\n';
  string name;
  cin >> name;

  list[i] = Players{name, 1};
}

cout << "You all begin the game in space 1. The first person to reach space 100 wins. " << '\n';
cin.ignore(100, '\n');

int i = 0;
while(true){
  Players currentPlayer = list[i%playerNum];

  cout << '\n' << "It is " << currentPlayer.playerName
       << "'s turn. Press enter to roll the first dice. ";
  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

  int d1 = diceRoll();
  cout << "You rolled a " << d1 << "!" << '\n';

  cout << "Press enter to roll the second dice. ";
  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

  int d2 = diceRoll();
  cout << "You rolled a " << d2 << "!" << '\n';

  int rolledNum = d1+d2;
  cout << '\n' << "You moved forward " << rolledNum << " spaces! " << '\n';

  int addedSpace = currentPlayer.playerSpace + rolledNum;

  if(addedSpace>=100){
    cout << "Congrats! " << currentPlayer.playerName << " is the winner!";
    break;
  }

  else if(board[addedSpace].isSnake){
    int newSpace = addedSpace-board[addedSpace].changeSpace;
    list[i%playerNum] = {currentPlayer.playerName, newSpace};
    cout << "Uh-oh, " << currentPlayer.playerName << " landed on a snake on space " << addedSpace << " and slid down to space " << newSpace    << "!" << '\n';
  }

  else if(board[addedSpace].changeSpace!=0){
    int newSpace = addedSpace+board[addedSpace].changeSpace;
    list[i%playerNum] = {currentPlayer.playerName, newSpace};
    cout << "Wow! " << currentPlayer.playerName <<" found a ladder on space " << addedSpace
         << ", you climbed up to space " << newSpace << "!" << '\n';
  }

  else{
    list[i%playerNum] = {currentPlayer.playerName, addedSpace};
    cout << currentPlayer.playerName << " landed on space " << addedSpace << "." << '\n';
  }

  i++;
}

return 0;
}

