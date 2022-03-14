# Client-Server-Group-5-Project [![CMake](https://github.com/Sntai20/Client-Server-Group-5-Project/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Sntai20/Client-Server-Group-5-Project/actions/workflows/cmake.yml)

Group 5 is designing a bingo simulator project for milestone 1 and 2. To play the game, the user will need to designate if they want a solo or 2-player experience. Then, the user would supply a comma separated list of 25 numbers between a certain range X (for example, 0 to 50) to "build" a bingo board. The numbers will be checked to see if they are in the correct range. The server will then randomly generate up to X unique numbers in a certain range (same as the range above). If the game is solo player, the server might generate 30-35 numbers. If the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo. the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo.

When the server generates a random number, it will show on the screen/console for the client. To make the game more interactive, users must send a trigger input, such as an "X” to indicate that they wish to mark off a number on their board. If they do not type the trigger within a certain time frame (such as 5 seconds), they will lose the chance to mark that number from their board and not be allowed to cross off the specific number. For 2-player mode, the users will share one client screen, and sending a trigger will attempt to mark a number from both the player’s boards. Players will not be penalized for attempting to mark off a number that is not on their board.
The bingo simulator will have the following Remote Procedure Calls (RPCs):

- setBoard
- markBoard
- checkBingo
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
- Working unit tests
- Authentication

## Build

To build, navigate to the `~/Client-Server-Group-5-Project/`

`cmake --preset macos-default`

Available configure presets:

- "linux-default"   - Use this preset for Linux Debug
- "macos-default"   - Use this preset for macOS Debug
- "windows-default" - Use this preset for Windows x64 Debug

## Run the Code

To run the code, navigate to the build Project Folder `~/Client-Server-Group-5-Project/out/build/macos-default/`. To run the code use the Server-Project and Client-Project Folders. Start the server first, then the client.

To run the server `./server`

To run the client `./client localhost`

## TODO

- [x] Update README.MD
- [ ] generate random numbers on the server on each interval and send them to the client
- [ ] update markBoard RPC to use this random number instead of a hard-coded value
- [ ] create global context class/struct with mutexes
- [x] clean up code
- [x] either allow client to restart game after a bingo is detected or end client connection
- [ ] screenshot of 4+ clients connected and running RPCs at the same time testing that output is correct for multiple clients connecting at the same time (for example, clients with different setTime calls should get numbers at different intervals)
- [ ] update final PDF to reflect global context and include additional features
- [ ] optional things to do to get the "exceeds expectations" grade (based on what we have already):
- [ ] update google tests/CMake/github site to work for the windows version
- [x] include compatibility for max/linux
- [ ] restrict RPC calls setMaxNum, setTime, and setBoard to only before the game starts
- [ ] restrict RPC calls checkBingo, markBoard to only during a game

### Visual Studio Code Extensions

- <https://code.visualstudio.com/docs/languages/cpp>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools>
- <https://marketplace.visualstudio.com/items?itemName=matepek.vscode-catch2-test-adapter>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack>
- <https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-themes>
- <https://marketplace.visualstudio.com/items?itemName=docsmsft.docs-markdown>
