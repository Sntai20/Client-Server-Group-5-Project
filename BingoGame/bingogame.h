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
    BingoGame(/* args */);

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
    /* data */
};

BingoGame::BingoGame(/* args */)
{
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
bool BingoGame::setBoard(string inputString) 
{
    cout << "\nFunction setBoard is not implemented yet!" << endl;

    // TODO: Implement.
    return true;
}

/**
 * @brief This method is used to mark the board values.
 * 
 */
void BingoGame::markBoard() 
{
    cout << "\nFunction markBoard is not implemented yet!" << endl;
    
    // TODO: Implement.
}

/**
 * @brief This method is used to set the time.
 * 
 * @param inputString 
 * @return true 
 * @return false 
 */
bool BingoGame::setTime(string inputString) 
{
    cout << "\nFunction setTime is not implemented yet!\n\n" << endl;

    // TODO: Implement.
    return true;
}

/**
 * @brief This method is used to set the maximum number.
 * 
 * @param inputString 
 * @return true 
 * @return false 
 */
bool BingoGame::setMaxNum(string inputString) 
{
    cout << "\nFunction setMaxNum is not implemented yet!" << endl;
    
    // TODO: Implement.
    return true;
}
