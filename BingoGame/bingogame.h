#pragma once
/**
 * @file bingogame.h
 * @author Group 5
 * @brief C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#ifdef _WIN32
#include <Winsock2.h>
#include <windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <iostream>


using namespace std;

class BingoGame
{
public:
    // Constructor
    BingoGame();

    // Destructor
    ~BingoGame();

    // Creating the Bingo board.
    bool setBoard(string inputString);

    // Checks if the current number displayed by the system matches a number in the player's bingo board.
    void markBoard();

    // Sets the number of seconds the server will wait between each bingo
    // number re-roll for the rest of the game.
    bool setTime(string inputString);

    // Takes in a string and sets the max number the server will call for the
    // rest of the game.
    bool setMaxNum(string inputString);

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
    bool checkUnique();
    void printBoard();

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
bool BingoGame::setBoard(string inputString)
{
    istringstream stringStream(inputString);
    string token;
    int i = 0;
    while (getline(stringStream, token, ',') && i < boardSize){
        numbers[i] = stoi(token);
        i++;
    }

    if (i != boardSize) {
        return false;
    }
    if (checkUnique()) {
        cout << "Board successfully set!\n";
        printBoard();
        return true;
    }
    cout << "Invalid board setup provided. Please try again.\n";
    return false;
}

/* Helper function to test if all numbers in the board are unique.
 * Returns false if there is a duplicate number, otherwise returns
 * true.
 */
bool BingoGame::checkUnique() {

    for (int i = 0; i < boardSize; i++) {
        if (numbers[i] > maxNum) {
            return false;
        }
        for (int j = 0; j < i; j++) {
            if (numbers[i] == numbers[j]) {
                return false;
            }
        }
    }
    return true;
}

/* Private utility function to print the current state of the board.
 * If a number is marked off, print a star instead of the number.
 */
void BingoGame::printBoard() {

    cout << "|========================| \n";
    for (int i = 0; i < boardSize; i++) {

        if (markedNumbers[i] == 0) {
            if (numbers[i] < 10 && numbers[i] > -10) {
                cout << "| 0" << numbers[i];
            } else {
                cout << "| " << numbers[i];
            }
        } else {
            cout << "|  *";
        }
        if ((i + 1) % 5 == 0) {
            cout << " | \n";
        } else {
            cout << " ";
        }

    }
    cout << "|========================|";
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
void BingoGame::markBoard()
{
    // TODO: Implement server generating random numbers every interval
    //       to update serverNum (temp value until implemented)
    int serverNum = 1;
    bool found = false;

    for (int i = 0; i < boardSize; i++) {
        if (numbers[i] == serverNum) {
            markedNumbers[i] = 1;
            found = true;
            break;
        }
    }
    if (found) {
        printBoard();
    } else {
        cout << "Number called by the server not found in current bingo board.\n";
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
bool BingoGame::setTime(string inputString)
{
    inputDelay = stoi(inputString);
    if (inputDelay <= maxDelay) {
        cout << "Successfully set! The delay between each server call will be " << inputDelay
            << " seconds." << endl;
        return true;
    }
    cout << "The delay provided was invalid. Please enter a new number less than or"
            " equal to " << maxDelay << "." << endl;
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
bool BingoGame::setMaxNum(string inputString)
{
    maxNum = stoi(inputString);
    if (maxNum > boardSize) {
        cout << "Successfully set! The max number that the server will call will be " << maxNum
            << "." << endl;
        return true;
    }
    cout << "The max number provided was invalid. Please enter a new number greater than "
        << boardSize << "." << endl;
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
