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
    if (currentX == origin[0] + dataPointer[2] && currentY == origin[1] + dataPointer[3] && dataPointer[5] == 1) {
        return 1;
	}
	else {
		return 0;
    }
}

//Prints the UI
void printUI(int board[9][3], int scoreboard[], int player, int* gameState) {
    //UI elements syntax
    //* => 2D Data
    //$ => 1D Data
    //n => New Line
    //'>' => End Format
    int screenLength = 57, screenHeight = 20;
    int boardDataPointer[6] = {0, 0, 0, 0, 0, 1}; //In order, dataPointerX{0}, dataPointerY{1}, screenPointerX{2}, screenPointerY{3}, formatPointer{4}, isEnabled{5}

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

    int playerTurnDataPointer[6] = { 0, 0, 0, 0, 0, 1 };
    int playerTurnTextOrigin[2] = { 22, 16 };
    char playerTurnText[] = "PLAYER # TURN>";
    
    int playerMessageDataPointer[6] = { 0, 0, 0, 0, 0, 1 };
    int playerMessageOrigin[2] = { 14, 17 };
    char playerMessageText[] = "ENTER COLUMN AND ROW (E.G, 0 1)>";

    int playerOneDataPointer[6] = { 0, 0, 0, 0, 0, 1 };
    int playerOneScoreOrigin[2] = { 5, 5 };
    char playerOneScoreFormat[] = "+----------+n"
								"| PLAYER 1 |n"
								"| SCORE: # |n"
								"+----------+>";

    int playerTwoDataPointer[6] = { 0, 0, 0, 0, 0, 1 };
    int playerTwoScoreOrigin[2] = { 40, 5 };
    char playerTwoScoreFormat[] = "+----------+n"
                                "| PLAYER 2 |n"
                                "| SCORE: # |n"
                                "+----------+>";

    int victoryDataPointer[6] = { 0, 0, 0, 0, 0, 0 };
    int victoryOrigin[2] = { 15, 10 };
    char victoryFormat[] = "+-------------------------+n"
                            "| P L A Y E R  #  W O N ! |n"
                            "+-------------------------+>";

    int tryAgainDataPointer[6] = { 0, 0, 0, 0, 0, 0 };
    int tryAgainOrigin[2] = { 12, 15 };
    char tryAgainFormat[] = "+-------------------------------+n"
                            "| T R Y  A G A I N ?  ( Y / N ) |n"
                            "+-------------------------------+>";

    int titleDataPointer[6] = { 0, 0, 0, 0, 0, 1 };
    int titleOrigin[2] = { 16, 1 };
    char titleFormat[] = "+ T I C - T A C - T O E +>";

    int configDataPointer[6] = { 0, 0, 0, 0, 0, 0 };
    int configOrigin[2] = { 1, 1 };
    char configFormat[] = "+-----------------------------+n"
                          "| E N T E R  N U M B E R  O F  |n"
                          "|   R O U N D S  T O  W I N    |n"
                          "+------------------------------+>";

    int endMessageDataPointer[6] = { 0, 0, 0, 0, 0, 0 };
    int endMessageOrigin[2] = { 1, 1 };
    char endMessageFormat[] = "+------------------------------------+n"
                              "| T H A N K S  F O R  P L A Y I N G  |n"
                              "|    additioNal message              |n"
                              "+------------------------------------+>";


    switch (*gameState) {
    case 0:
        boardDataPointer[5] = 0;
        playerMessageDataPointer[5] = 0;
        victoryDataPointer[5] = 0;
        playerTurnDataPointer[5] = 0;
        tryAgainDataPointer[5] = 0;
        playerOneDataPointer[5] = 0;
        playerTwoDataPointer[5] = 0;
        titleDataPointer[5] = 0;
        configDataPointer[5] = 1;

        screenHeight = 6;
        screenLength = 34;
        break;
    case 2: //Winner Screen; sets board to 0, displays winning message and prompts user to play again
        boardDataPointer[5] = 0;
        playerMessageDataPointer[5] = 0;
        victoryDataPointer[5] = 1;
        playerTurnDataPointer[5] = 0;
        tryAgainDataPointer[5] = 1;

        playerOneScoreOrigin[0] = 15;
        playerOneScoreOrigin[1] = 5;

        playerTwoScoreOrigin[0] = 30;
        playerTwoScoreOrigin[1] = 5;
        break;
    case 3:
        boardDataPointer[5] = 0;
        playerMessageDataPointer[5] = 0;
        victoryDataPointer[5] = 0;
        playerTurnDataPointer[5] = 0;
        tryAgainDataPointer[5] = 0;
        playerOneDataPointer[5] = 0;
        playerTwoDataPointer[5] = 0;
        titleDataPointer[5] = 0;
        configDataPointer[5] = 0;
        endMessageDataPointer[5] = 1;

        screenHeight = 6;
        screenLength = 40;
        break;
    default:
        break;
    }
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
            if (isOrigin(victoryOrigin, victoryDataPointer, x, y) == 1) {
                printFormat(scoreboard[2], NULL, board, victoryFormat, victoryDataPointer);
                continue;
            }
            if (isOrigin(tryAgainOrigin, tryAgainDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, tryAgainFormat, tryAgainDataPointer);
                continue;
            }
            if (isOrigin(titleOrigin, titleDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, titleFormat, titleDataPointer);
                continue;
            }
            if (isOrigin(configOrigin, configDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, configFormat, configDataPointer);
                continue;
            }
            if (isOrigin(endMessageOrigin, endMessageDataPointer, x, y) == 1) {
                printFormat(NULL, NULL, board, endMessageFormat, endMessageDataPointer);
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
void resetBoard(int board[9][3]) {
    for (int i = 0; i < 9; i++) {
		board[i][2] = 0;
	}
}

//Resets the scores of the players, including the winner player index
void resetScore(int scoreboard[]) {
    for (int i = 0; i < 3; i++) {
		scoreboard[i] = 0;
	}
}

//Update the data of a specific cell in the board
void updateData(int board[9][3], int x, int y, int n) {
    for (int k = 0; k < 9; k++) {
        if (board[k][0] == x && board[k][1] == y) {
            board[k][2] = n;
            break;
        }
    }
}
//To be optimized
int checkForWinner(int board[9][3], int scoreboard[]) {
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
void playerInput(int board[9][3], int scoreboard[], int player, int* gameState){
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
					printUI(board, scoreboard, player, &gameState);
					printf("{Invalid Coordinate Input: Please enter a number between 1-3 (inclusive)}");
                    break;
                }
            }
        }

        //Checks if the coordinate is already taken, if taken, it will prompt the user to enter a new coordinate
        if (board[findIndex(board, playerInput[0]-1, playerInput[1]-1)][2] != 0) {
            valid = 0;
            playerInput[0] = 0;
            playerInput[1] = 0;
            system("cls");
            printUI(board, scoreboard, player, &gameState);
            printf("{Invalid Input: Please enter a coordinate with a free space}");
        }
    }
    updateData(board, playerInput[0]-1, playerInput[1]-1, player);
}

int main()
{
    //0 = CONFIG, 1 = Game Running, 2 = Winner Screen, 3 = Game Over Screen 
    int gameState = 0;
    int isRunning = 0;
    int winningScore = 0;
    int valid = 0;
    char optionTry = ' ';
    int board[][3] = { {0, 0, 1}, {1, 0, 1}, {2, 0, 0},
                    {0, 1, 0}, {1, 1, 0}, {2, 1, 0},
                    {0, 2, 0}, {1, 2, 0}, {2, 2, 0} };
    int scoreboard[] = {0, 0, 0};
    int isWinner = 0;
    while (isRunning == 0) {
        valid = 0;
        if (gameState == 0) {
            printUI(board, scoreboard, 0, &gameState);
            while (valid == 0) {
                scanf("%d", &winningScore);
                if (winningScore > 0) {
                    valid = 1;
                    system("cls");
                    gameState = 1;
                }
                else {
                    while ((getchar()) != '\n'); //Clears input buffer
                    system("cls");
					printUI(board, scoreboard, 0, &gameState);
					printf("{Invalid Input: Please enter a number greater than 0}\n");
                }
            }

        }
        else if (gameState == 1) {
            for (int i = 1; i < 3; i++) {
                printUI(board, scoreboard, i, &gameState);
                playerInput(board, scoreboard, i, &gameState);
                system("cls"); //Remember to change the console clear command according to the compiler
                isWinner = checkForWinner(board, scoreboard);
                if (isWinner != 0) {
                    resetBoard(board);
                    i = 1;
                    if (scoreboard[i - 1] >= winningScore) { gameState = 2; scoreboard[2] = i; break; }
                }
            }
        }
        else if (gameState == 2) {
            printUI(board, scoreboard, 0, &gameState);
            while (valid == 0) {
                while ((getchar()) != '\n'); //Clears input buffer
                scanf("%c", &optionTry);
                switch (optionTry) {
                    case 'Y':
						valid = 1;
						gameState = 1;
                        resetScore(scoreboard);
                        system("cls");
						break;
                    case 'N':
                        system("cls");
                        gameState = 3;
                        printUI(board, scoreboard, 0, &gameState);
                        return;
                    default:
                        system("cls");    
                        printUI(board, scoreboard, 0, &gameState);
                        printf("{Invalid Input: Please enter either Y or N}\n");
						break;
                }
            }
        }
    }
    return 0;
}
