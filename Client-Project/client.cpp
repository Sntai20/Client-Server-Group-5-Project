/**
 * @file client.cpp
 * @author Group 5
 * @brief Client side C++ 17 program to demonstrate Socket programming for Bingo game.
 * @version 0.1
 * @date 2022-02-11
 */  
#include "client.h"

bool Client::validateInteger(string input)
{
    for (int i = 0; i < input.size(); i++) {
        //check if string input contain int
        if (!isdigit(input[i])) {
            return false;
        }
        else {
            //convert string to int
            int tmp = stoi(input);
            //check if out of range
            if (tmp > 9 || tmp < 0)
            {
                return false;
            }
        }
    }
    return true;
}

void Client::userInterface()
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
        cout << "         Bingo Game            " << endl;
        cout << "1. Calculator" << endl;
        cout << "2. Statistics" << endl;
        cout << "3. Conversion (Binary/Decimal/Hexadecimal)" << endl;
        cout << "4. Quit" << endl << endl;

        //Validate the user selection input, refrain from empty/invalid input
        do {
            cout << "Enter selection: ";
            getline(cin, userInput);
        } while (!validateInteger(userInput));

        //Takes user's choice and perform desired calculation
        switch (stoi(userInput))
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
    } while (stoi(userInput) != quitProgram && stoi(userInput) > 0);
}

void Client::processCalcExpression()
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

    if (result[1] == "0")
    {
        printf("Result : %s\n", result[0].c_str());
    }
    else
    {
        printf("%s\n", "Invalid expression.");
    }
}

void Client::processCalcStats()
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
    if (result[result.size() - 1] == "0")
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

void Client::processConversion() {
    string expr;
    string choice;
    vector<string> result;
    string calcConversion;

    //Present menu options for conversion
    do {
        calcConversion = CALC_CONV + ";";
        cout << endl;
        cout << "************     Conversion Menu     ************" << endl;
        cout << "1. Convert Binary to Decimal" << endl;
        cout << "2. Convert Decimal to Binary" << endl;
        cout << "3. Convert Binary to Hexadecimal" << endl;
        cout << "4. Convert Hexadecimal to Binary " << endl;
        cout << "5. Convert Decimal to Hexadecimal " << endl;
        cout << "6. Convert Hexadecimal to Decimal " << endl;
        cout << "7. Return to main menu" << endl;

        //Validate the user selection input, refrain from empty/invalid input
        do {
            cout << "\nEnter Selection: ";
            getline(cin, choice);
        } while (!validateInteger(choice));

        //Direct user's choice and call conversion methods
        switch (stoi(choice)) {
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

        if (result[1] == "0")
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
    } while (stoi(choice) <= 6 && stoi(choice) > 0);
}

string Client::getCredentials()
{
    //Create terminal interface that is provided to control asynchronous communications ports
    struct termios orig_termios;

    string username, password;
    //Take in username and password
    cout << "\nPlease enter your username: ";
    getline(cin, username);
    cout << "Please enter your password: ";

    //Modify console settings to mask password
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    //Store user input
    getline(cin, password);

    //Restore the terminal settings to start echoing again
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);

    //Return
    return username + ";" + password;
}

void Client::ParseTokens(char* buffer, std::vector<std::string>& a)
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

bool Client::ConnectToServer(const char* serverAddress, int port, int& sock)
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

    // Connect to server
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return false;
    }

    return true;
}