# Client-Server-Group-5-Project
Group 5 is designing a bingo simulator project for milestone 1 and 2. To play the game, the user will need to designate if they want a solo or 2-player experience. Then, the user would supply a comma separated list of 25 numbers between a certain range X (for example, 0 to 50) to "build" a bingo board. The numbers will be checked to see if they are in the correct range. The server will then randomly generate up to X unique numbers in a certain range (same as the range above). If the game is solo player, the server might generate 30-35 numbers. If the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo. the game is 2-player, the server might generate up to 50 numbers and the game will end when one player reaches a bingo.

When the server generates a random number, it will show on the screen/console for the client. To make the game more interactive, users must send a trigger input, such as an "X” to indicate that they wish to mark off a number on their board. If they do not type the trigger within a certain time frame (such as 5 seconds), they will lose the chance to mark that number from their board and not be allowed to cross off the specific number. For 2-player mode, the users will share one client screen, and sending a trigger will attempt to mark a number from both the player’s boards. Players will not be penalized for attempting to mark off a number that is not on their board.
The bingo simulator will have the following Remote Procedure Calls (RPCs):
•	setBoard
•	markBoard
•	setTime
•	setMaxNum
•	Connect
•	Disconnect

## Run the Code 
To run the code provided by the professor use the Server and Client Folders. Start the server first, then the client.

To run the server './server 127.0.0.1 10320'

To run the client './client 127.0.0.1 10320'

## Release 1.0.0
The server listens on port 10320.
The client connects to the server. 

# Features
- Connect RPC.
- Disconnect RPC.

## Coming Soon
- Working unit tests for the socket class.
- Authentication
- setBoard
- markBoard
- setTime
- setMaxNum