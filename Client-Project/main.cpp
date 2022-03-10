/**
 * @file main.cpp
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
//Author  : Group#2
//Date    : 02/07/2022
//Version : 1.0
//Filename: ClientCS.cpp

#include <cstdio>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <iterator>
#include <iostream>
#include <cstring>
// #include <termio.h>

using namespace std;

/******************************************************************************/
/**************************** Function Prototypes *****************************/
/******************************************************************************/

/**
 * Prompts the user to enter credentials via keyboard, then returns the
 * credentials in a format ready for RPC
 * @return A string containing user credentials
 *
 */
string getCredentials();

/**
 * Parse RPC buffer into tokens using delimiter ";"
 * @param buffer A char array pointer containing the buffer to be parsed
 * @param a A vector of strings containing the parsed RPC parameters
 *
 */
void ParseTokens(char* buffer, std::vector<std::string>& a);

/**
 * ConnectToServer will connect to the Server based on command line
 * @param serverAddress A pointer to a char array containing the IP address
 *                      of the server
 * @param port An int containing the port on the server for the connection
 * @param sock An int containing the socket number
 * @return A bool indicating if the connection was successful or not
 *
 */
bool ConnectToServer(const char *serverAddress, int port, int & sock);

/**
 * Prompt user to enter the options we have given:
 * 1. basic calculator
 * 2. Statistic
 * 3. Conversion
 * 4. Quit program
 *
 */
void userInterface();

/**
 * Helper function to validate user's input for menu, refrain from entering
 * invalid/empty input
 * @param input An integer for inputting menu options
 * @return true if the input is valid
 */
bool validateInteger(string input);

/**
 * Function to process basic calculator
 *
 */
void processCalcExpression();

/**
 * Function to process five number summary for statistic analysis, and if the
 * input contains more than 2 numbers, extra analysis (standard deviation
 * and variance) will be displayed
 *
 */
void processCalcStats();

/**
 * Function to process conversion among binary, decimal, hexadecimal expression
 *
 */
void processConversion();

/******************************************************************************/
/********************** End of Function Prototypes ****************************/
/******************************************************************************/

//Initialize data
int sock = 0;
struct sockaddr_in serv_addr;

//Global variables for supported RPCs calls from client
const string CONNECT = "connect",
        DISCONNECT = "disconnect",
        CALC_EXPR = "calculateExpression",
        CALC_STAT = "calculateStats",
        CALC_CONV = "conversion";
const char* logoffRPC = "disconnect;";
char buffer[1024] = { 0 };
char connected;
char disconnected;
const int SLEEP_TIME = 10;
bool bConnect = false;

int main(int argc, char const* argv[])
{
    //Welcome the user
    cout << "*************************************************" << endl;
    cout << "*   Welcome to the Group 2 Client Application   *" << endl;
    cout << "*************************************************" << endl;

    //Check if user entered correct # of Command Line args for IP and Port
    if (argc < 3)
    {
        //If insufficient number of args, print error and exit program.
        cout << "\nMissing IP Address or Port number.\n";
        cout << "Exiting Client Application...\n";
        return -1;
    }

    const char *serverAddress = argv[1];
    const int port = atoi(argv[2]);

    bConnect = ConnectToServer(serverAddress, port, sock);

    //If we fail to connect to server, exit the program
    if(!bConnect){
        cout << "Fail to connect to server, exiting program.." << endl;
        return -1;
    }

    string connectRPC;

    //Start plugging in interface
    //testing if client connect to server
    //keep asking for user input, successfully connected.
    do
    {
        //Reset buffers
        memset(buffer, 0 , 1024);
        connectRPC = CONNECT + ";";

        //Get credentials from user
        connectRPC = connectRPC + getCredentials() + ";";

        //Copy the created the RPC string to the buffer
        strcpy(buffer, &connectRPC[0]);

        //Add a null terminator
        int nlen = strlen(buffer);
        buffer[nlen] = 0;

        //Send the created RPC buffer to server
        send(sock, buffer, strlen(buffer) + 1, 0);

        //Read from server
        read(sock, buffer, 1024);
        connected = buffer[0];

        //Check if successfully connected
        if (connected == '0')
        {
            cout << "\nLogin successful!" << endl;
        }
        else
        {
            cout << "\nInvalid login!" << endl;
        }
    } while (connected != '0');

    //Implement user interface
    userInterface();

    //Do a Disconnect message
    cout << "Disconnecting from Server" << endl;

    //Reset buffers
    memset(buffer, 0 , 1024);

    //Create the buffer to be sent via RPC
    strcpy(buffer, logoffRPC);
    int nlen = strlen(buffer);
    buffer[nlen] = 0;   // Put the null terminator

    //Send buffer
    send(sock, buffer, strlen(buffer) + 1, 0);

    //Get RPC response from server
    read(sock, buffer, 1024);
    disconnected = buffer[0];

    //check if buffer equal to disconnect
    if (disconnected == '0')
    {
        cout << "Disconnected successfully" << endl;
    }
    else {
        cout << "Failed to disconnect successfully" << endl;
    }

    //Terminate connection
    close(sock);

    return 0;
}

bool validateInteger(string input)
{
    for(int i = 0; i < input.size(); i++){
        //check if string input contain int
        if(!isdigit(input[i])){
            return false;
        }
        else{
            //convert string to int
            int tmp = stoi(input);
            //check if out of range
            if(tmp > 9 || tmp < 0)
            {
                return false;
            }
        }
    }
    return true;
}

void userInterface()
{
    //Initiate user input and menu option variables
    string userInput;
    const int CalcExpression = 1,
              CalcStats = 2,
              CalcConversion = 3,
              quitProgram = 4;

    //Prompt user to choose the functions presented on the menu, each menu
    //option will direct the calculation towards to designated methods
    do
    {
        cout << endl;
        cout << "*************************************************" << endl;
        cout << "***********            Menu            **********" << endl;
        cout << "*************************************************" << endl;
        cout <<  "1. Calculator" << endl;
        cout <<  "2. Statistics" << endl;
        cout <<  "3. Conversion (Binary/Decimal/Hexadecimal)" << endl;
        cout <<  "4. Quit" << endl << endl;

        //Validate the user selection input, refrain from empty/invalid input
        do{
            cout << "Enter selection: ";
            getline(cin, userInput);
        }while(!validateInteger(userInput));

        //Takes user's choice and perform desired calculation
        switch(stoi(userInput))
        {
            case CalcExpression:
                processCalcExpression();
                break;
            case CalcStats:
                processCalcStats();
                break;
            case CalcConversion:
                processConversion();
                break;
            default:
                break;
        }
    }while(stoi(userInput) != quitProgram && stoi(userInput) > 0);
}

void processCalcExpression()
{
    string expr;
    string calcExpRPC = CALC_EXPR + ";";
    vector<string> result;

    cout << "Enter expression: ";
    getline(cin, expr);
    calcExpRPC = calcExpRPC + expr + ";";
    strcpy(buffer, &calcExpRPC[0]);

    //Add a null terminator
    int nlen = strlen(buffer);
    buffer[nlen] = 0;

    //Send the created RPC buffer to server
    send(sock, buffer, strlen(buffer) + 1, 0);

    //Read from server
    read(sock, buffer, 1024);
    ParseTokens(buffer, result);

    if(result[1] == "0")
    {
        printf("Result : %s\n", result[0].c_str());
    }
    else
    {
        printf("%s\n", "Invalid expression.");
    }
}

void processCalcStats()
{
    string expr;
    string calcStats = CALC_STAT + ";";
    vector<string> result;
    bzero(buffer, 1024);

    cout << "Enter at least two numbers separated by space: ";
    getline(cin, expr);
    calcStats = calcStats + expr + ";";
    strcpy(buffer, &calcStats[0]);

    //Add a null terminator
    int nlen = strlen(buffer);
    buffer[nlen] = 0;

    //Send the created RPC buffer to server
    send(sock, buffer, strlen(buffer) + 1, 0);

    //Read from server
    read(sock, buffer, 1024);
    ParseTokens(buffer, result);
    string printString;

    //Print
    if(result[result.size() - 1] == "0")
    {
        printString = "Min        " + result[0] + "\n" +
                      "1st Qu.    " + result[1] + "\n" +
                      "Median     " + result[2] + "\n" +
                      "Mean       " + result[3] + "\n" +
                      "3rd Qu.    " + result[4] + "\n" +
                      "Max        " + result[5] + "\n";

        if (result.size() > 8)
        {
            printString = printString + "Std. Dev   " + result[6] + "\n" +
                                        "Variance   " + result[7] + "\n";
        }
        printf("%s\n", printString.c_str());
    }
    else
    {
        printf("%s\n", "Invalid expression.");
    }
}

void processConversion() {
    string expr;
    string choice;
    vector<string> result;
    string calcConversion;

    //Present menu options for conversion
    do{
        calcConversion = CALC_CONV + ";";
        cout << endl;
        cout << "************     Conversion Menu     ************" << endl;
        cout<<"1. Convert Binary to Decimal"<<endl;
        cout<<"2. Convert Decimal to Binary"<<endl;
        cout<<"3. Convert Binary to Hexadecimal"<<endl;
        cout<<"4. Convert Hexadecimal to Binary "<<endl;
        cout<<"5. Convert Decimal to Hexadecimal "<<endl;
        cout<<"6. Convert Hexadecimal to Decimal "<<endl;
        cout<<"7. Return to main menu"<<endl;

        //Validate the user selection input, refrain from empty/invalid input
        do{
            cout << "\nEnter Selection: ";
            getline(cin, choice);
        }while(!validateInteger(choice));

        //Direct user's choice and call conversion methods
        switch(stoi(choice)){
            case 1:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            case 2:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            case 3:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            case 4:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            case 5:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            case 6:
                cout << "Enter number to be converted: ";
                getline(cin, expr);
                break;
            default:
                return;
        }
        //Append user's conversion string, menu choice, and the original
        //input to the buffer
        calcConversion = calcConversion + choice + ";" + expr + ";";
        strcpy(buffer, &calcConversion[0]);
        //Add a null terminator
        int nlen = strlen(buffer);
        buffer[nlen] = 0;

        //Send the created RPC buffer to server
        send(sock, buffer, strlen(buffer) + 1, 0);

        //Read from server
        read(sock, buffer, 1024);
        ParseTokens(buffer, result);

        if(result[1] == "0")
        {
            printf("Result : %s\n", result[0].c_str());
        }
        else
        {
            printf("%s\n", "Invalid expression.");
        }
        //Reset result, so it won't carry the old one
        result.clear();
        sleep(1);
    }
    while(stoi(choice) <= 6 && stoi(choice) > 0);
}

string getCredentials()
{
    //Create terminal interface that is provided to control asynchronous
    //communications ports
    // struct termios orig_termios;

    string username, password;
    //Take in username and password
    cout << "\nPlease enter your username: ";
    getline(cin, username);
    cout << "Please enter your password: ";

    //Modify console settings to mask password
    // tcgetattr(STDIN_FILENO, &orig_termios);
    // struct termios new_termios = orig_termios;
    // new_termios.c_lflag &= ~ECHO;
    // tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    //Store user input
    getline(cin, password);

    //Restore the terminal settings to start echoing again
    // tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);

    //Return
    return username + ";" + password;
}


void ParseTokens(char* buffer, std::vector<std::string>& a)
{
    //Declare variables to facilitate the parsing of input buffer
    char* token;
    char* rest = (char*)buffer;

    //Loop through the input buffer, and extract strings using the ';' delimiter
    while ((token = strtok_r(rest, ";", &rest)))
    {
        a.push_back(token);
    }

    return;
}


bool ConnectToServer(const char *serverAddress, int port, int & sock)
{
    //Create socket
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return false;
    }
    //Debuging
    else
    {
        printf("Socket: %d", sock);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverAddress, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    //Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return false;
    }

    return true;
}

