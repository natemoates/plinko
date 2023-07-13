/* Nathaniel Oates
 * CPSC 1071: Section 002
 * Project Name: Plinko!
 * Description: This program allows a user to play Plinko! This program uses a menu based system.
 * The user may simulate bidding on prizes, they may play Plinko! and select what slot they would like to drop 
 * their plinko chip in. The chip will randomly move left or right as it goes down the plinko board. 
 * The user will win various amounts of money depending on the slot the plinko chip lands in at the bottom of 
 * the Plinko board. This program also allows the user to view the board and see the path the plinko chip takes
 * through the board. The user may also quit playing Plinko from the menu when they are done playing.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

// prototypes
void runGame(void);
char runMenu(int, int);
int bidOnPrizes(void);
int playPlinko(char[12][17], int, int);
int puckDirection(int, int);
void displayBoard(char[12][17], int, int);
void resetBoard(char[12][17], int, int);

// main function
int main(){
	runGame();
}

// runGame function
void runGame(){

	// variable declarations
	int chips, bonusChips, totalWinnings, roundWinnings;
	char menuChoice;
	bool running = true;
	bool alreadyBid = false;
	char plinkoBoard[12][17];
	int seed = time(0);

	// initializes values for chips and total winnings
	chips = 1;
	totalWinnings = 0;
	
	// creates the board and starts the random number generator
	resetBoard(plinkoBoard, 12, 17);
	srand(seed);
	
	cout<<"Welcome to the CPSC 1070 Plinko!!!"<<endl;
	
	do{
		// calls the menu function and sets menuChoice to the returned value: the  user's menu selection
		menuChoice = runMenu(chips, totalWinnings);
		// executes different functions of the program dependant on the user's menu selection
		switch(menuChoice){
			case '1':
				bonusChips = bidOnPrizes();
				if(!alreadyBid){
					cout<<"You have won "<<bonusChips<<" chips!"<<endl;
					chips += bonusChips;
					alreadyBid = true;
				}
				else{
					cout<<"You've already bid on prizes!"<<endl;
				}
				break;
			case '2':
				if(chips > 0){
					chips--;
					roundWinnings = 0;
					roundWinnings = playPlinko(plinkoBoard, 12, 17);
					totalWinnings += roundWinnings;
					cout<<"You have won $"<<roundWinnings<<"!"<<endl;
				}
				else{
					cout<<"Sorry, you don't have anymore chips!"<<endl;
				}
				break;
			case '3':
				displayBoard(plinkoBoard, 12, 17);  break;
			default:
				running = false; break;

		}
	}while(running);


}

// creates the menu, takes user input, performs input validation, and returns an approproate user menu selection
char runMenu(int chips, int winnings){
	// local variable declarations
	char menuChoice;
	string menuInput;
	bool notValid = true;
	// menu output
	cout<<endl;
	cout<<"---- CPSC 1070 Plinko Menu ----\n"<<endl;
	cout<<" You have "<<chips<<" Plinko chips to use"<<endl;
	cout<<" Total Winnings $"<<winnings<<"!\n"<<endl;
	cout<<" [1] to bid on items to earn chips"<<endl;
	cout<<" [2] to play PLINKO!"<<endl;
	cout<<" [3] to print out the current board"<<endl;
	cout<<" [Q] to quit\n"<<endl;
	cout<<"Your choice?: ";
	// user input
	cin>>menuInput;
	while(menuInput.length() !=  1){
		cout<<"You did not enter a valid response!"<<endl;
		cout<<"Enter another choice?: ";
		cin>>menuInput;
	}
	menuChoice = menuInput[0];

	cout<<endl;
	// performs input validation
	do{
		switch(menuChoice){
			case '1':
			case '2':
			case '3':
			case 'q':
			case 'Q':
				notValid = false; break;
			default: 
				cout<<"You did not enter a valid response!"<<endl;
				cout<<"Enter another choice?: ";
				cin>>menuChoice;
		} 
	} while (notValid);
	return menuChoice;
}

// function that simulates a user bidding on prizes and returns the plinko chips won
int bidOnPrizes(){
	int bonusChips = 0;
	for(int i = 0; i < 4; i++){
		bonusChips += static_cast<int>(rand()%2);
	}
	return bonusChips;
}

// function that allows the user to play Plinko
int playPlinko(char plinkoBoard[12][17], int rows, int cols){
	resetBoard(plinkoBoard, rows, cols);
	int slot;
	int curIndex;
	// performs input validation on the users slot selection
	do{
		cout<<"Which slot do you want to drop your puck down (1-9)?: ";
		cin>>slot;
		if(slot > 9 || slot < 1){
			cout<<"Invalid Input. Please try again."<<endl;
		}
	}while(slot > 9 || slot < 1);
	curIndex = (slot-1)*2;
	// charts the plinko chip's path down through each row
	for(int r = 0; r < rows; r++){
		// calls puckDirection and moves the plinko chip into the column to the left or right depending on the returned value 
		curIndex += puckDirection(r, curIndex);
		// marks each location that the plinko chip has been on the board
		plinkoBoard[r][curIndex] = '*';
	}
	// returns the value associated with the final slot the plinko chip lands in
	switch(curIndex){
		case 0:
		case 16:
			return 50;
		case 2:
		case 14:
			return 200;
		case 4:
		case 12:
			return 500;
		case 6:
		case 10:
			return 0;
		default:
			return 1000;
	}
}

// function that randomly  determines the direction the plinko chip will move
int puckDirection(int currentRow, int currentColumn){
	int randResult = static_cast<int>(rand()%2);
	if(randResult == 1){
		if(currentColumn < 16){
			return 1;
		}
		return -1;
	}
	else{
		if(currentColumn > 0){
			return -1;
		}
		return 1;
	}
}

// outputs the plinkoBoard 2D array in a viewable format
void displayBoard(char plinkoBoard[12][17], int numRows, int numCols){
	for(int i = 0; i < 9; i++){
		cout<<i+1;
		cout<<"             ";
	}
	cout<<endl;
	for(int r = 0; r < numRows; r++){
		for(int c = 0; c < numCols; c++){
			cout<<plinkoBoard[r][c];
				cout<<"      ";
		}
		cout<<endl;
	}
	cout<<"$50         $200          $500           $0          $1,000          $0           $500          $200           $50   "<<endl;
}

// clears the plinkoBoard to the state it was before playPlinko() was called
void resetBoard(char plinkoBoard[12][17], int numRows, int numCols){
	for(int r = 0; r < numRows; r++){
		for(int c = 0; c < numCols; c++){
			if(c%2 == r%2){
				plinkoBoard[r][c] = '|';
			}
			else{
				plinkoBoard[r][c] = ' ';
			}
		}
	}

}
