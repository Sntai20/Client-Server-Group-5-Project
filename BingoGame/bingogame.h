#pragma once
/**
 * @file bingogame.h
 * @author Group 5
 * @brief C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

class BingoGame
{
public:
    // Constructor
    BingoGame();

    // Destructor
    ~BingoGame();

    // Creating the Bingo board.
    bool setBoard(std::string inputString);

    // Checks if the current number displayed by the system matches a number in the player's bingo board.
    bool markBoard();

    // Sets the number of seconds the server will wait between each bingo
    // number re-roll for the rest of the game.
    bool setTime(std::string inputString);

    // Takes in a string and sets the max number the server will call for the
    // rest of the game.
    bool setMaxNum(std::string inputString);

    // Checks if there is a bingo in the current board
    bool checkBingo();
    char* printDelimiterBoard(char returnString[],int row);
    bool checkUnique(std::string inputString);
    
    void setNum(int newNumber);
    int getMaxNum();
    int getTime();


private:
    // size of a 5x5 bingo board
    static const int boardSize = 25;
    // max time allowed between server calls
    static const int maxDelay = 10;
    // encapsulated array of board numbers
    int numbers[boardSize];
    // encapsulated array representing marked off numbers
    int markedNumbers[boardSize];
    // max number the server will call
    int maxNum = 0;
    // delay between each server call
    int inputDelay = 0;
    // number displayed by the server
    int serverNumber = 1;
    // number of rows in a printed bingo board
    static const int numRows = 7;
    // number of bingo squares per row
    static const int numPerRow = 5;
    void printBoard();
    char* getBingoString(char returnString[],int row);
};

// Constructor zeroes out board numbers
BingoGame::BingoGame()
{
    for (int i = 0; i < boardSize; i++) {
        numbers[i] = 0;
        markedNumbers[i] = 0;
    }
}

BingoGame::~BingoGame()
{
    
}
// Function for server to update encapsulated value sent to client
void BingoGame::setNum(int newNumber) {
    serverNumber = newNumber;
}
// Function for server to return encapsulated value
int BingoGame::getMaxNum() {
    return maxNum;
}
// Function for server to return encapsulated value
int BingoGame::getTime() {
    return inputDelay;
}

/**
 * @brief This method is used to set the board values.
 *
 * @param inputString
 * @return true
 * @return false
 */

/* This function can only be used before a bingo game. It will take in a string and
 * use a comma as a delimiter to separate out each number in an array. The input string
 * must not include spaces after the comma. It will then check to make sure each number
 * is unique and in the valid range of numbers provided by the server and add the first
 * 25 numbers provided to a global array variable. A virtual bingo board will be printed
 * through calling a private function on successful setup (see markBoard bingo board).
 *
 */
bool BingoGame::setBoard(std::string inputString)
{
    std::istringstream stringStream(inputString);
    std::string token;
    bool isBoardSet = true;
    int i = 0;

    while (getline(stringStream, token, ',') && i < boardSize)
    {
        numbers[i] = stoi(token);
        i++;
    }

    if (i != boardSize) 
    {
        isBoardSet = false;
    }
    if (!checkUnique(inputString)) 
    {
        std::cout << "Invalid board setup provided. Please try again.\n" << std::endl;
        isBoardSet = false;
    } else {
        std::cout << "Board successfully set!\n" << std::endl;
        printBoard();
        isBoardSet = true;
    }
    
    return isBoardSet;
}

/* Helper function to test if all numbers in the board are unique.
 * Returns false if there is a duplicate number, otherwise returns
 * true.
 */
bool BingoGame::checkUnique(std::string inputString) 
{
    std::istringstream stringStream(inputString);
    std::string token;
    int i = 0;

    while (getline(stringStream, token, ',') && i < boardSize)
    {
        numbers[i] = stoi(token);
        i++;
    }

    for (int i = 0; i < boardSize; i++) 
    {
        // This might be a bug.
        // if (numbers[i] > maxNum) 
        // {
        //     return false;
        // }
        for (int j = 0; j < i; j++) 
        {
            if (numbers[i] == numbers[j]) 
            {
                return false;
            }
        }
    }
    return true;
}


/* Public utility function to print the current state of the board.
 * If a number is marked off, print a star instead of the number.
 * Used by the server to send bingo board to client.
 */
char* BingoGame::printDelimiterBoard(char returnString[], int row) {

    if (row == 0 || row == numRows - 1) {
        strcpy(returnString, (char*)"|========================|\r\n");
    } else if (row < numRows - 1) {

        for (int i = 1; i < numRows; i++) {
            if (i == row) {
                char* functionString = getBingoString(returnString, row);

                strcpy(returnString, functionString);
            }
        }
    }
    return returnString;
}

char* BingoGame::getBingoString(char returnString[], int row) 
{

    for (int i = (row * numPerRow) - numPerRow; i < row * numPerRow; i++) 
    {
        std::string s = std::to_string(numbers[i]);
        char const *number = s.c_str();
        if (markedNumbers[i] == 0) {

            if (numbers[i] < 10 && numbers[i] > -10) {
                strcat(returnString, (char*)"| 0");
                strcat(returnString, number);

            } else {
                strcat(returnString, (char*)"| ");
                strcat(returnString, number);
            }
        } else {
            strcat(returnString, (char*)"|  *");
        }
        if ((i + 1) % numPerRow == 0) {
            strcat(returnString, (char*)" | \r\n");
        } else {
            strcat(returnString, (char*)" ");
        }
    }

    return returnString;
}

/* Private utility function to print the current state of the board.
 * If a number is marked off, print a star instead of the number.
 */
void BingoGame::printBoard() 
{

    std::cout << "|========================| \n";
    for (int i = 0; i < boardSize; i++) {

        if (markedNumbers[i] == 0) {
            if (numbers[i] < 10 && numbers[i] > -10) 
            {
                std::cout << "| 0" << numbers[i];
            } else 
            {
                std::cout << "| " << numbers[i];
            }
        } 
        else 
        {
            std::cout << "|  *";
        }
        if ((i + 1) % 5 == 0) {
            std::cout << " | \n";
        } else 
        {
            std::cout << " ";
        }

    }
    std::cout << "|========================|";
}

/**
 * @brief This method is used to mark the board values.
 *
 */
/* This function can only be used during a bingo game. It will check
 * if the current number displayed by the system matches a number in
 * the player's bingo board. If it matches, the virtual board will be
 * updated to cross off the number. If it does not match, output a
 * string to the client saying that the server number is not on the player's
 * board. A new bingo board is printed if a number was successfully marked.
 */
bool BingoGame::markBoard()
{

    bool found = false;

    for (int i = 0; i < boardSize; i++) {
        if (numbers[i] == serverNumber) {
            markedNumbers[i] = 1;
            found = true;
            break;
        }
    }
    if (found) {
        printBoard();
        return true;
    } else {
        std::cout << "Number called by the server not found in current bingo board.\n";
        return false;
    }

}

/**
 * @brief This method is used to set the time.
 *
 * @param inputString
 * @return true
 * @return false
 */
/* This function can only be used before a bingo game. It takes in a string
 * and sets the number of seconds the server will wait between each bingo
 * number reroll for the rest of the game. A message is sent to the client
 * to confirm changes or to inform the user that the input value was invalid,
 * and no changes were made. The time set must be 10 seconds or less.
 */
bool BingoGame::setTime(std::string inputString)
{
    inputDelay = stoi(inputString);
    if (inputDelay <= maxDelay) 
    {
        std::cout << "Successfully set! The delay between each server call will be " << inputDelay
             << " seconds." << std::endl;
        return true;
    }
    std::cout << "The delay provided was invalid. Please enter a new number less than or"
            " equal to " << maxDelay << "." << std::endl;
    return false;
}

/**
 * @brief This method is used to set the maximum number.
 *
 * @param inputString
 * @return true
 * @return false
 */
/* This function can only be used before a bingo game. It takes in a string
 * and sets the max number the server will call for the rest of the game.
 * A message is sent to the client to confirm changes or to inform the user
 * that the input value was invalid, and no changes were made. The provided
 * number must be at least 25, the size of a bingo board.
 */
bool BingoGame::setMaxNum(std::string inputString)
{
    maxNum = stoi(inputString);
    if (maxNum > boardSize) 
    {
        std::cout << "Successfully set! The max number that the server will call will be " << maxNum
             << "." << std::endl;
        return true;
    }
    std::cout << "The max number provided was invalid. Please enter a new number greater than "
         << boardSize << "." << std::endl;
    return false;
}

/* This function can only be used during a bingo game. It will check the current
 * board for horizontal, vertical, and diagonal bingos. It will return true if at
 * least one bingo was detected, otherwise it will return false.
 * The function takes in no parameters.
 */
bool BingoGame::checkBingo() {

    // check horizontal bingos
    for (int i = 0; i < boardSize; i+=5) {
        if (markedNumbers[i] == 1) {
            if (markedNumbers[i] == markedNumbers[i + 1] &&
                markedNumbers[i] == markedNumbers[i + 2] &&
                markedNumbers[i] == markedNumbers[i + 3] &&
                markedNumbers[i] == markedNumbers[i + 4]) {
                return true;
            }
        }
    }

    // check vertical bingos
    for (int i = 0; i < 5; i++) {
        if (markedNumbers[i] == 1) {
            if (markedNumbers[i] == markedNumbers[i + 5] &&
                markedNumbers[i] == markedNumbers[i + 10] &&
                markedNumbers[i] == markedNumbers[i + 15] &&
                markedNumbers[i] == markedNumbers[i + 20]) {
                return true;
            }
        }
    }

    // check diagonal bingo (left to right)
    if (markedNumbers[0] == 1 &&
        markedNumbers[0] == markedNumbers[6] &&
        markedNumbers[0] == markedNumbers[12] &&
        markedNumbers[0] == markedNumbers[18] &&
        markedNumbers[0] == markedNumbers[24]){
        return true;
    }
    // check diagonal bingo (right to left)
    if (markedNumbers[4] == 1 &&
        markedNumbers[4] == markedNumbers[8] &&
        markedNumbers[4] == markedNumbers[12] &&
        markedNumbers[4] == markedNumbers[16] &&
        markedNumbers[4] == markedNumbers[20]){
        return true;
    }
    return false;
}
