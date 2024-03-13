#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


//TODO
//Implement try again
//Maybe a main menu
//Implement player 1 and player 2 scores

//Converts the integer value of the board to a letter
char convertToLetter(int n) {
	switch (n) {
	case 1:
        return 'X';
	case 2:
        return 'O';
	default:
        return ' ';
	}
}

//Finds the index of a specific cell in the 2D array using its x and y coordinates
int findIndex(int board[9][3], int x, int y) {
    for (int n = 0; n < 9; n++) {
        if (board[n][0] == x && board[n][1] == y) {
            return n;
        }
    }

}

//Prints the UI elements based on a given format
void printFormat(int singleData, int onedArray[], int board[9][3],  char boardFormat[], int dataPointer[]) {
    switch (boardFormat[dataPointer[4]]) {
        case '*':
            printf("%c", convertToLetter(board[findIndex(board, dataPointer[0], dataPointer[1])][2]));
            if (board[findIndex(board, dataPointer[0], dataPointer[1])][0] == 2) { dataPointer[1]++; }
            dataPointer[0]++;
            dataPointer[2]++;
            break;
        case '$':
            printf("%d", onedArray[dataPointer[0]]);
            dataPointer[0]++;
            dataPointer[2]++;
            break;
        case '#':
            printf("%d", singleData);
            dataPointer[2]++;
            break;
        case 'n':
            printf(".");
            dataPointer[0] = 0;
            dataPointer[2] = 0;
            dataPointer[3]++;
            break;
        case '>':
            printf(".");
            for (int i = 0; i < 5; i++) { dataPointer[i] = 0; }
            return;
        default:
            printf("%c", boardFormat[dataPointer[4]]);
            dataPointer[2]++;
            break;
    }
    dataPointer[4]++;
}

//Checks if the current position is within the bounds of the UI element relative to its origin
int isOrigin(int origin[], int dataPointer[], int currentX, int currentY) {
    if (currentX == origin[0] + dataPointer[2] && currentY == origin[1] + dataPointer[3]) {
        return 1;
	}
	else {
		return 0;
    }
}

//Prints the UI
void printUI(int board[9][3], int scoreboard[], int player) {
    //UI elements syntax
    //* => 2D Data
    //$ => 1D Data
    //n => New Line
    //'>' => End Format
    int screenLength = 57, screenHeight = 20;
    int boardDataPointer[5] = {0, 0, 0, 0, 0}; //In order, dataPointerX{0}, dataPointerY{1}, screenPointerX{2}, screenPointerY{3}, formatPointer{4}

    int boardOrigin[2] = { 20, 5 };
    char boardFormat[] = "    +   +   +   +n"
                        "      1   2   3  n"
                        "+   +---+---+---+n"
                        "  1 | * | * | * |n"
                        "+   +---+---+---+n"
                        "  2 | * | * | * |n"
                        "+   +---+---+---+n"
                        "  3 | * | * | * |n"
                        "+   +---+---+---+>";

    int playerTurnDataPointer[5] = { 0, 0, 0, 0, 0 };
    int playerTurnTextOrigin[2] = { 22, 16 };
    char playerTurnText[] = "PLAYER # TURN>";
    
    int playerMessageDataPointer[5] = { 0, 0, 0, 0, 0 };
    int playerMessageOrigin[2] = { 14, 17 };
    char playerMessageText[] = "ENTER COLUMN AND ROW (E.G, 0 1)>";

    int playerOneDataPointer[5] = { 0, 0, 0, 0, 0 };
    int playerOneScoreOrigin[2] = { 5, 5 };
    char playerOneScoreFormat[] = "+----------+n"
								"| PLAYER 1 |n"
								"| SCORE: # |n"
								"+----------+>";

    int playerTwoDataPointer[5] = { 0, 0, 0, 0, 0 };
    int playerTwoScoreOrigin[2] = { 40, 5 };
    char playerTwoScoreFormat[] = "+----------+n"
                                "| PLAYER 2 |n"
                                "| SCORE: # |n"
                                "+----------+>";
    //UI Rendering
    //There will be a reference to the origin of the UI element and the dataPointer will be used to keep track of the current position of the data being printed
    //There would be three types of data pointers: 2D data pointer, 1D data pointer and text data pointer
    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenLength; x++) { 
            if (isOrigin(boardOrigin, boardDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, boardFormat, boardDataPointer);
                continue;
            }
            if (isOrigin(playerTurnTextOrigin, playerTurnDataPointer, x, y) == 1) {
                printFormat(player, NULL, board, playerTurnText, playerTurnDataPointer);
                continue;
            }
            if (isOrigin(playerMessageOrigin, playerMessageDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, playerMessageText, playerMessageDataPointer);
                continue;
            }
            if (isOrigin(playerOneScoreOrigin, playerOneDataPointer, x, y) == 1) {
                printFormat(scoreboard[0], NULL, board, playerOneScoreFormat, playerOneDataPointer);
                continue;
            }
            if (isOrigin(playerTwoScoreOrigin, playerTwoDataPointer, x, y) == 1) {
                printFormat(scoreboard[1], NULL, board, playerTwoScoreFormat, playerTwoDataPointer);
                continue;
            }
            if (x == 0 || y == 0 || x == screenLength - 1 || y == screenHeight - 1) {
                printf(".");
            } else { printf("."); }
        }
        printf("\n");
    }
}

//Resets the data of the board and the scoreboard
void resetData(int board[9][3]) {
    for (int i = 0; i < 9; i++) {
		board[i][2] = 0;
	}
}

void updateData(int board[9][3], int x, int y, int n) {
    for (int k = 0; k < 9; k++) {
        if (board[k][0] == x && board[k][1] == y) {
            board[k][2] = n;
            break;
        }
    }
}
//To be optimized
int checkForWinner(int board[9][3], int* gameOver, int scoreboard[]) {
    //Horizontal
    int playerOneCount = 0;
    int playerTwoCount = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            for (int i = 0; i < 9; i++) {
                if (board[i][0] == x && board[i][1] == y) {
                    if (board[i][2] == 1) {
                        playerOneCount++;
                        if (playerOneCount >= 3) {
                            scoreboard[0]++;
                            return 1;
                        }
                    }
                    else if (board[i][2] == 2) {
                        playerTwoCount++;
                        if (playerTwoCount >= 3) {
                            scoreboard[1]++;
                            return 2;
                        }
                    }
                }
            }
        }
        playerOneCount = 0;
        playerTwoCount = 0;
    }

    //Vertical
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int i = 0; i < 9; i++) {
                if (board[i][0] == x && board[i][1] == y) {
                    if (board[i][2] == 1) {
                        playerOneCount++;
                        if (playerOneCount >= 3) {
                            scoreboard[0]++;
                            return 1;
                        }
                    }
                    else if (board[i][2] == 2) {
                        playerTwoCount++;
                        if (playerTwoCount >= 3) {
                            scoreboard[1]++;
                            return 2;
                        }
                    }
                }
            }
        }
        playerOneCount = 0;
        playerTwoCount = 0;
    }

    //Diagonal
    for (int n = 0; n < 9; n++) {
        for (int i = 0; i < 3; i++) {
            if (board[n][0] == i && board[n][1] == i) {
                if (board[n][2] == 1) {
                    playerOneCount += 1;
                    if (playerOneCount >= 3) {
                        scoreboard[0]++;
                        return 1;
                    }
                }
                else if (board[n][2] == 2) {
                    playerTwoCount += 1;
                    if (playerTwoCount >= 3) {
                        scoreboard[1]++;
                        return 2;
                    }
                }
            }
        }
    }
    playerOneCount = 0;
    playerTwoCount = 0;

    int count = 0;
    for (int x = 2; x >= 0; x--) {
        for (int i = 0; i < 9; i++) {
            if (board[i][0] == x && board[i][1] == count) {
                if (board[i][2] == 1) {
                    playerOneCount += 1;
                    if (playerOneCount >= 3) {
                        scoreboard[0]++;
                        return 1;
                    }
                }
                else if (board[i][2] == 2) {
                    playerTwoCount += 1;
                    if (playerTwoCount >= 3) {
                        scoreboard[1]++;
                        return 2;
                    }
                }
            }
        }
        count++;
    }

    //Draw
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 3; i++) {
            for (int n = 0; n < 9; n++) {
				if (board[n][0] == i && board[n][1] == j) {
					if (board[n][2] == 1 || board[n][2] == 2) {
						if (n == 8) {
                            scoreboard[0]++;
                            scoreboard[1]++;
							return 3;
						}
					}
					else {
						return 0;
					}
				}
			}
        }
    }



    return 0;
}
void playerInput(int board[9][3], int scoreboard[], int player){
    //player input array where index 0 is column and index 1 is row
    int playerInput[2] = { 0 };
    int valid = 0;
    while (valid == 0) {
        valid = 1;
        while (playerInput[0] < 1 || playerInput[0] > 3 || playerInput[1] < 1 || playerInput[1] > 3) {
            printf("\n");
            for (int i = 0; i < 2; i++) {
                scanf("%d", &playerInput[i]);
                if (playerInput[i] < 1 || playerInput[i] > 3) {
                    for (int j = 0; j < 2; j++) { playerInput[j] = 0; }
					while ((getchar()) != '\n'); //Clears input buffer if the user enters a non-integer value, otherwise it would cause an infinite loop
					system("cls");
					printUI(board, scoreboard, player);
					printf("{Invalid Coordinate Input: Please enter a number between 1-3 (inclusive)}");
                    break;
                }
            }
            //if (playerInput[0] < 1 || playerInput[0] > 3 || playerInput[1] < 1 || playerInput[1] > 3) {
            //    for (int i = 0; i < 2; i++) { playerInput[i] = 0; }
            //    while ((getchar()) != '\n'); //Clears input buffer if the user enters a non-integer value, otherwise it would cause an infinite loop
            //    system("cls");
            //    printUI(board, scoreboard, player);
            //    printf("{Invalid Coordinate Input: Please enter a number between 1-3 (inclusive)}");
            //}
        }

        //Checks if the coordinate is already taken, if taken, it will prompt the user to enter a new coordinate
        if (board[findIndex(board, playerInput[0]-1, playerInput[1]-1)][2] != player && board[findIndex(board, playerInput[0]-1, playerInput[1]-1)][2] != 0) {
            valid = 0;
            playerInput[0] = 0;
            playerInput[1] = 0;
            system("cls");
            printUI(board, scoreboard, player);
            printf("{Invalid Input: Please enter a coordinate with a free space}");
        }
    }
    updateData(board, playerInput[0]-1, playerInput[1]-1, player);
}

int main()
{
    int isGameOver = 0;
    int board[][3] = { {0, 0, 0}, {1, 0, 0}, {2, 0, 0},
                    {0, 1, 0}, {1, 1, 0}, {2, 1, 0},
                    {0, 2, 0}, {1, 2, 0}, {2, 2, 0} };
    int scoreboard[] = {0, 0};
    int isWinner = 0;
    while (isGameOver == 0) {
        for (int i = 1; i < 3; i++) {
            printUI(board, scoreboard, i);
            playerInput(board, scoreboard, i);
            system("cls"); //Remember to change the console clear command according to the compiler
            isWinner = checkForWinner(board, &isGameOver, scoreboard);
            if (isWinner != 0) {
                resetData(board);
                i = 1;
            }
        }
    }
    return 0;
}