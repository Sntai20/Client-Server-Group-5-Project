# Client-Server-Group-5-Project [![CMake](https://github.com/Sntai20/Client-Server-Group-5-Project/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Sntai20/Client-Server-Group-5-Project/actions/workflows/cmake.yml)

Group 5 is designing a bingo simulator project for milestone 1 and 2. To play the game, the user will need to designate if they want a solo or 2-player experience. Then, the user would supply a comma separated list of 25 numbers between a certain range X (for example, 0 to 50) to "build" a bingo board. The numbers will be checked to see if they are in the correct range. The server will then randomly generate up to X unique numbers in a certain range (same as the range above). If the game is solo player, the server might generate 30-35 numbers. If the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo. the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo.

When the server generates a random number, it will show on the screen/console for the client. To make the game more interactive, users must send a trigger input, such as an "X” to indicate that they wish to mark off a number on their board. If they do not type the trigger within a certain time frame (such as 5 seconds), they will lose the chance to mark that number from their board and not be allowed to cross off the specific number. For 2-player mode, the users will share one client screen, and sending a trigger will attempt to mark a number from both the player’s boards. Players will not be penalized for attempting to mark off a number that is not on their board.
The bingo simulator will have the following Remote Procedure Calls (RPCs):

- setBoard
- markBoard
- setTime
- setMaxNum
- Connect
- Disconnect

## Release 1.0.0

The server listens on port 10320.
The client connects to the server.

## Features

- Connect RPC.
- Disconnect RPC.
- Simple Exception Handling
- Multi-threaded Server

## Coming Soon

- Working unit tests for the socket class
- Authentication for multiple users
- setBoard
- markBoard
- setTime
- setMaxNum

## Build

To build, navigate to the `./Client-Server-Group-5-Project/`

`cmake -S . -B build`

`cmake --build build`

## Run the Code

To run the code use the Server-Project and Client-Project Folders. Start the server first, then the client.

To run the server `./build/server 127.0.0.1 10320`

To run the client `./build/client 127.0.0.1 10320`

### Visual Studio Code Extensions

- <https://code.visualstudio.com/docs/languages/cpp>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools>
- <https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-themes>
- <https://marketplace.visualstudio.com/items?itemName=docsmsft.docs-markdown>
