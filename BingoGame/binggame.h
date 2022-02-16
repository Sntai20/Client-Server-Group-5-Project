/**
 * @file BingoGame.h
 * @author Group 5
 * @brief C/C++ program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include <cstdio>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <iterator>
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
    printf("\nFunction setBoard is not implemented yet!");

    // TODO: Implement.
    return true;
}

/**
 * @brief This method is used to mark the board values.
 * 
 */
void BingoGame::markBoard() 
{
    printf("\nFunction markBoard is not implemented yet!");
    
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
    printf("\nFunction setTime is not implemented yet!\n\n");

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
    printf("\nFunction setMaxNum is not implemented yet!");
    
    // TODO: Implement.
    return true;
}