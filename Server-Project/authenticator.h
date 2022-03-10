#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class Authenticator
{
public:
    Authenticator(const string &fileName);
    ~Authenticator();

    bool authenticate(const string &username, const string &password);
private:
    unordered_map<string, string> m_users;
    void readFile(const string &filename, char delim = ',');

};


Authenticator::Authenticator(const string &fileName)
{
    // populate username and passwords with data from a file
    readFile(fileName);
}
Authenticator::~Authenticator() = default;

bool Authenticator::authenticate(const string &username, const string &password)
{
    // First check if the user exists
    unordered_map<string, string>::const_iterator mapIterator = m_users.find(username);
    cout << username << "\n" << endl;
    cout << password << "\n" << endl;
    cout << m_users[username] << endl;
    // If the user doesn't exist, return false
    if (mapIterator == m_users.end())
        return false;

    // Check that the password matches the record for this username
    if (m_users[username] == password)
        return true;

    // Otherwise, return false
    return false;
}

void Authenticator::readFile(const string &filename, char delim)
{

    // open the file
    ifstream infile(filename);
    cout << "I have the file " << filename << endl;

    // Make sure the file opened successfully
    if(infile.is_open()) {

        string line; // This will hold each line of the file
        while(getline(infile, line)) {

            // Parse each line for username and password
            string username, password;
            stringstream strStrm(line);
            cout << "I found this line: " << line << endl;

            // Assume the first two delimited values of the line
            // are username and password, respectively
            getline(strStrm, username, delim);
            getline(strStrm, password, delim);

            // Store extracted username and password in the map attribute
            m_users[username] = password;
        }
    }

}