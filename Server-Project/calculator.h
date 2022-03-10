
#include <cstring>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm> // for sort function
#include <stdexcept>
#include <regex>

using namespace std;

class Calculator 
{
public:

    /**
     * Calculates an algebraic expression
     * Valid operators: '+', '-', '*', '/', '^'
     * @param inExpr Expression to be evaluated
     * @return Result of the algebraic expression
     */
    string calculateExpression(string inExpr);

    /**
     * Converts numeric value to a different base
     * @param choice
     *          0- Binary to Decimal
     *          1- Decimal to Binary
     *          2- Binary to Hexadecimal
     *          3- Hexadecimal to Binary
     *          4- Decimal to Hexadecimal
     *          5- Hexadecimal to decimal
     *
     * @param inValue Value to be converted
     * @return Result of conversion
     */
    string convertor(const string &choice, string inValue);

    /**
     * Calculate Statistical data on a vector of numbers
     */
    string summary(const string &inValue);

private:
    /**
     * Parses the input expression using operands or spaces as delimiters,
     * and inserts the output into a vector
     * @param inExpression Input algebraic expression
     * @return A vector containing the operands and operators in order entered
     */
    vector<string> expTokenize(string &inExpression);

    /**
     * Converts order of a vector of operands and operators into RPN order
     * @param expTokens Vector containing the original expression tokens
     * @return A vector containing the operands and operators in RPN ordering
     */
    vector<string> convertToRPN(vector<string> &expTokens);


    /**
     * Calculates an expression in RPN notation. Expression passed in as a
     * vector of strings containing the operations and operators in RPN notation
     * @param rpnStack Vector containing the expression in RPN notation
     * @return The result of the calculation
     */
    double calculateRPN(vector<string> &rpnStack);

    /**
     * Helper function to validate input strings
     * @param inExpression String to be validated
     * @param validChars Set of valid char values (e.g. {'1', '2', '*', '.'})
     * @return True if all string characters are found in set, otherwise false.
     */
    bool validateInputString(const string &inExpression, set<char> validChars);

    //*************************************
    // Conversion functions
    //*************************************

    /**
     * Helper function to convert binary to hex
     * @param input Binary number
     * @return Hex representation of the binary number
     */
    string binToHex(string &input);

    /**
     * Helper function to convert hex to binary
     * @param input Hexadecimal number
     * @return Binary representation of the hex number
     */
    string hexToBin(string &input);

    /**
     * Helper function to convert decimal to bin
     * @param input Decimal number
     * @return Binary representation of the decimal number
     */
    string decToBin(string &input);

    /**
     * Helper function to convert binary to decimal
     * @param input Binary number
     * @return Decimal representation of the binary number
     */
    string binToDec(string &input);

    /**
     * Helper function to convert hex to decimal
     * @param input Hexadecimal number
     * @return Decimal representation of the hex number
     */
    string hexToDec(string &input);

    /**
     * Helper function to convert decimal to hex
     * @param input Decimal number
     * @return Hex representation of the decimal number
     */
    string decToHex(string &input);

    //*************************************
    // Stats functions
    //*************************************
    // Calculate the mean of a set of numbers
    float mean(vector<float>);

    // Calculate the median of a set of numbers
    float median(vector<float>);

    // Calculate the sample variance (meaning it uses n-1 in the denominator)
    float var(const vector<float> &vec);

    // calculate the sample standard deviation (meaning it uses n-1 in the denomicator).
    float sd(vector<float>);

    // Caclulate quantiles
    vector<float> quantiles(vector<float> data, float quantCuts);

    // Calculate the value representing the nth percentile (where 0 <= n <= 1)
    float percentile(vector<float> vec, float nth);


    //Unordered map containing the supported operators for calculateRPN
    // function, and their precedence order
    unordered_map<string, int> precedenceMap = {
            {"^", 3},
            {"*", 2},
            {"/", 2},
            {"+", 1},
            {"-", 1},
            {"(", -1},
            {")", -1},
    };

    //Exception Strings
    const string INVALID_EXPRESSION = "Invalid expression entered.",
                 INVALID_OPERATOR = "Invalid operator entered.",
                 INVALID_ARG = "Invalid argument entered.";

    //Sets containing valid char values for different numeric basis
    const set<char> BIN_CHAR = {'0', '1'};
    const set<char> DEC_CHAR = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9'};
    const set<char> FLOAT_CHAR = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', '.', ' ', ',', '-'};

    const set<char> HEX_CHAR = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    const set<char> EXP_CHAR = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', ',', '.', '+', '-', '*', '/', '^', '(',
                                ')', ' '};
};


string Calculator::calculateExpression(string inExpr)
{
   //Validate input expression (i.e. containing valid characters)
   if (validateInputString(inExpr, EXP_CHAR))
   {

      //Parse input expression into tokens using spaces and operators as delimiters
      vector<string> expTokens = expTokenize(inExpr);

      //Convert the tokens into RPN notation
      expTokens = convertToRPN(expTokens);

      //Calculate and return the expression
      return to_string(calculateRPN(expTokens));
   }
   else
   {
      throw invalid_argument(INVALID_EXPRESSION);
   }
}

string Calculator::convertor(const string& choice, string inValue)
{

    //If input is blank, throw an exception
    if (choice.empty())
        throw invalid_argument(INVALID_ARG);

    string result;
    int c = stoi(choice) - 1;
    switch(c){
        case 0:
            if(validateInputString(inValue, BIN_CHAR)){
                result = binToDec(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        case 1:
            if(validateInputString(inValue, DEC_CHAR)){
                result = decToBin(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        case 2:
            if(validateInputString(inValue, BIN_CHAR)){
                result = binToHex(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        case 3:
            if (inValue.substr(0, 2) == "0x")
            {
                inValue = inValue.substr(2);
            }
            if(validateInputString(inValue, HEX_CHAR)){
                result = hexToBin(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        case 4:
            if(validateInputString(inValue, DEC_CHAR)){
                result = decToHex(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        case 5:
            if (inValue.substr(0, 2) == "0x")
            {
                inValue = inValue.substr(2);
            }
            if(validateInputString(inValue, HEX_CHAR)){
                result = hexToDec(inValue);
                break;
            }
            else
            {
                throw invalid_argument(INVALID_ARG);
            }
        default:
            throw invalid_argument(INVALID_EXPRESSION);
    }
    return result;
}

float Calculator::mean(vector<float> vec) 
{
    // Check that vector is not empty
    if (vec.empty())
        throw invalid_argument("Dataset in vec must have size > 0.");
  
    float elementSum = 0.0; // this will store the sum of elements

    // Sum the elements of the vector
    for (float elm : vec) 
        elementSum += elm;

    // calculate the mean and return
    float mean = elementSum / ((float) vec.size());

    return mean;

}

float Calculator::median(vector<float> vec)
{
    // Check that vector is not empty
    if (vec.empty())
        throw invalid_argument("Dataset in vec must have size > 0.");   

    // Then median is the .5 quantile
    return quantiles(vec, .5)[0];
}

float Calculator::percentile(vector<float> vec, float nth) {

    // Check that vector is not empty
    if (vec.empty())
        throw invalid_argument("Dataset in vec must have size > 0.");

    // Check to see if the vector is sorted - if not, sort it. 
    if (!is_sorted(vec.begin(), vec.end()))
	sort(vec.begin(), vec.end());
	
    
    // Get the index of the quantile. There may be two if n is even, so 
    float index = (vec.size() - 1) * nth;

    // If n is odd, indexLow and indexHigh will be the same
    int indexLow = floor(index);
    int indexHigh = ceil(index);

    float qs = vec[indexLow];
    float h = index - indexLow;
    return (1-h) * qs + h * vec[indexHigh];
}

vector<float> Calculator::quantiles(vector<float> vec, float quantCut)
{
    float initQuantCut = quantCut;
    
    // Check that vector is not empty
    if (vec.empty())
        throw invalid_argument("Dataset in vec must have size > 0.");

    vector<float> quants; // this will hold the calculated quantiles

    // Sort the vector if it isn't already
    // Check to see if the vector is sorted - if not, sort it. 
    if (!is_sorted(vec.begin(), vec.end()))
	sort(vec.begin(), vec.end());

    
    while (quantCut < 1.0) {
        if ((quantCut > 1.0) | (quantCut < 0.0))
            throw invalid_argument("Quantile cuts must be between 0.0 and 1.0");


	quants.push_back(percentile(vec, quantCut));
        quantCut += initQuantCut;
    }

    return quants;
}

float Calculator::var(const vector<float> &vec)
{

    // Check that vector is not empty
    if (vec.size() < 2)
        throw invalid_argument("Dataset in vec must have size > 1.");

    // Meed the mean the calculation
    float vecMean = mean(vec);
    // This will hold the accumulated numerator calculations
    float variance = 0.0;
    // Use a for loop for the sums
    for (auto elm : vec) 
    {
        variance += pow((elm - vecMean), 2);
    }

    // returned the unbiased variance
    return variance / (vec.size() - 1);
}

float Calculator::sd(vector<float> vec)
{
    // Check that vector is not empty
    if (vec.size() < 2)
        throw invalid_argument("Dataset in vec must have size > 1.");

    // unbiased sd is just the square root of the unbiased variance
    return sqrt(var(vec));
}

string Calculator::summary(const string &inValue)
{
    vector<float> vec;

    // For now, assume someone typed in mean followed by numbers separated by
    // spaces make a whitespace regex
    auto const re = regex{R"(\s+)"};

    //Check that all the input characters are valid
    if (!validateInputString(inValue, FLOAT_CHAR))
        throw invalid_argument(INVALID_ARG);

    auto const vecString =
            vector<string>(sregex_token_iterator{begin(inValue),
                                                 end(inValue), re, -1},
                           sregex_token_iterator{});

    // put results into single string
    string resultString;

    for (string str : vecString)
    {
        try {
            vec.push_back(stof(str));
        }
        catch(const invalid_argument& is)
        {
            throw invalid_argument(INVALID_ARG);
        }
    }
    // Check that vector is not empty
    if (vec.empty())
        throw invalid_argument(INVALID_ARG);
    
    // This will hold the results of the calculations and be returned
    vector<float> summaryOut;
    
    auto min = *min_element(vec.begin(), vec.end());
    auto max = *max_element(vec.begin(), vec.end());
    auto quartiles = quantiles(vec, .25);
    auto avg = mean(vec);
    auto med = median(vec);
     
    summaryOut.push_back(min);
    summaryOut.push_back(quartiles[0]);
    summaryOut.push_back(quartiles[1]);
    summaryOut.push_back(avg);
    summaryOut.push_back(quartiles[2]);
    summaryOut.push_back(max);
    if (vec.size() > 1)
    {
        auto stdDev = sd(vec);
        auto variance = var(vec);
        summaryOut.push_back(stdDev);
        summaryOut.push_back(variance);
    }


        resultString = to_string(summaryOut[0]) + ";" +
                        to_string(summaryOut[1]) + ";" +
                        to_string(summaryOut[2]) + ";" +
                        to_string(summaryOut[3]) + ";" +
                        to_string(summaryOut[4]) + ";" +
                        to_string(summaryOut[5]);

    if (vec.size() > 1)
    {
        resultString = resultString + + ";" + to_string(summaryOut[6]) + ";" +
                                                to_string(summaryOut[7]);
    }
    return resultString;
}

vector<string> Calculator::expTokenize(string &inExpression)
{
    //Create a vector to store the tokens
    vector<string> tokens = {};

    string temp = ""; //temporary string for storage
    int bracketRefCount = 0;

    //Loop through input string and populate the vector
    for(char c : inExpression)
    {
        //If char is a space, then do nothing
        if( c == ' ')
            continue;

        //if char is an open bracket, flush temp and add multiply
        else if (c == '(')
        {
            bracketRefCount++;
            if (!temp.empty())
            {
                tokens.push_back(temp);
                temp.clear();
                tokens.push_back("*");
            }
            else if (!tokens.empty() && tokens.back() == ")")
            {
                tokens.push_back("*");
            }

          tokens.push_back(string(1, c));
        }

        //if char is an operator and not a negative/minus sign
        else if (precedenceMap.find(string(1, c)) != precedenceMap.end() &&
                    c != '-')
        {
            //Throw an exception if we do have b2b operators (invalid expression)
            if(!tokens.empty() &&
                !isdigit(tokens.back()[tokens.back().length()- 1]) &&
                (tokens.back() != ")") &&
                temp.empty())
            {
                throw invalid_argument(INVALID_EXPRESSION);
            }
            //Throw an exception if the first char in expression is an operator
            else if (tokens.empty() && temp.empty())
            {
                throw invalid_argument(INVALID_EXPRESSION);
            }

            //if temp storage had a number in it
            if(!temp.empty())
                //add the number to the vector first
                tokens.push_back(temp);

            //reset temp storage
            temp.clear();

            if (c == ')' && bracketRefCount <= 0)
            {
                continue;
            }
            else if (c == ')' && bracketRefCount > 0)
            {
                bracketRefCount --;
            }

            //add operator to the vector
            tokens.push_back(string(1, c));


        }

        //if char is a negative/minus sign
        else if (c == '-')
        {
            // if previous token is a number or a closing bracket or previous
            // character is a number, then treat as a minus sign
            if (!temp.empty() ||
                (!tokens.empty() &&
                    (isdigit((tokens.back()[tokens.back().length()-1])) ||
                    tokens.back()[tokens.back().length() - 1] == ')')))
            {
                //if temp storage has a number in it
                if(!temp.empty())
                {
                    //add the number to the vector first
                    tokens.push_back(temp);
                }
                //reset temp storage
                temp.clear();

                //add operator to the vector
                tokens.push_back(string(1, c));
            }

            //else treat as a negative sign
            else
            {
                temp += c;
            }
        }

        //else if the char is a number, add to the temp storage (until a
        // delimiter is reach)
        else
            temp += c;
    }

    //add the last number to the stack
    if(!temp.empty())
    {
        if (!tokens.empty() && tokens.back() == ")")
            tokens.push_back("*");
        tokens.push_back(temp);
    }
    
    // for (bracketRefCount; bracketRefCount > 0; bracketRefCount--)
    // {
    //     tokens.push_back(string(1, ')'));
    //     cout << bracketRefCount << endl;
    // }

    //return the tokens vector
    return tokens;
}

vector<string> Calculator::convertToRPN(vector<string>& expTokens)
{
   //Create a vector to store the result
   vector<string> rpnStack = {};

   //Create a temp storage for operations within parenthesis
   vector<string> temp = {"("};
   expTokens.push_back(")");
   for(string token : expTokens)
   {
      //if the token is a number, add it to the rpnStack
      if(precedenceMap.find(token) == precedenceMap.end()) // oparand
         rpnStack.push_back(token);

      //if token is an opening parenthesis, add it to the temp stack
      else if( token == "(")
         temp.push_back(token);

      //if token is a closing parenthesis, then process the temp stack and
      // add its contents to the rpn stack
      else if (token == ")")
      {
         //while the temp stack has tokens, push them in reverse order into
         // rpnStack
         while(!temp.empty() && temp.back() != "(")
         {
            rpnStack.push_back(temp.back());
            temp.pop_back();
         }

         if (!temp.empty())
            temp.pop_back();
      }

      //if token is an operator
      else
      {
         //while temp vector is not empty and the token has higher precedence
         // than this token, add the temp token to the stack
         while(!temp.empty() &&
               precedenceMap[token] <= precedenceMap[temp.back()])
         {
            rpnStack.push_back(temp.back());
            temp.pop_back();
         }

         //add operator to the temp stack
         temp.push_back(token);
      }
   }

   //return the rpn stack
   return rpnStack;
}

double Calculator::calculateRPN(vector<string>& rpnStack)
{
   //Create a vector to store the operands
   vector<double> operandStack = {};

   if (rpnStack.size() < 3)
   {
       throw invalid_argument(INVALID_EXPRESSION);
   }

   //Loop through each token and perform necessary calculations
   for(string token : rpnStack)
   {
      //if token is an operator, perform the calculation
      if(precedenceMap.find(token) != precedenceMap.end())
      {
         //get the operands
         double operand1 = operandStack[operandStack.size() - 1];
         double operand2 = operandStack[operandStack.size() - 2];

         //perform the calculation
         switch(token[0])
         {
            case '^':
               operand2 = pow(operand2, operand1);
               break;
            case '+':
               operand2 = operand2 + operand1;
               break;
            case '-':
               operand2 = operand2 - operand1;
               break;
            case '*':
               operand2 = operand2 * operand1;
               break;
            case '/':
               operand2 = operand2 / operand1;
               break;
            default:
               throw invalid_argument(INVALID_OPERATOR);
         }

         //remove the operands from the stack, and add result to the stack
         operandStack.pop_back();
         operandStack.pop_back();
         operandStack.push_back(operand2);
      }

      //if token is a number, add to the operand stack
      else
      {
         operandStack.push_back(atof(token.c_str()));
      }
   }

   //return the result
   return operandStack[0];
}

string Calculator::binToHex(string &input)
{
    //pad input
    while (input.size() % 4 != 0)
    {
        input = "0" + input;
    }
    string result, bits;
    vector<string> container;

    for(unsigned long i = 0; i < input.size()-3; i+=4) {
        bits = input.substr(i, 4);
        if(bits == "0000")
            result += '0';
        else if(bits == "0001")
            result += '1';
        else if(bits == "0010")
            result += '2';
        else if(bits == "0011")
            result += '3';
        else if(bits == "0100")
            result += '4';
        else if(bits == "0101")
            result += '5';
        else if(bits == "0110")
            result += '6';
        else if(bits == "0111")
            result += '7';
        else if(bits == "1000")
            result += '8';
        else if(bits == "1001")
            result += '9';
        else if(bits == "1010")
            result += 'A';
        else if(bits == "1011")
            result += 'B';
        else if(bits == "1100")
            result += 'C';
        else if(bits == "1101")
            result += 'D';
        else if(bits == "1110")
            result += 'E';
        else if(bits == "1111")
            result += 'F';
        else
            throw invalid_argument(INVALID_EXPRESSION);
    }

    // Removes leading zeroes, output '0' if all zeroes

    result = regex_replace(result, regex("^0+(?!$)"), "");
    return "0x" + result;
}

string Calculator::hexToBin(string& input)
{
    //String to store results
    string result;

    //Convert each char to its binary representation
    for(unsigned long i = 0; i < input.size(); i++)
    {
        switch(toupper(input[i]))
        {
            case '0':
                result += "0000";
                break;
            case '1':
                result += "0001";
                break;
            case '2':
                result += "0010";
                break;
            case '3':
                result += "0011";
                break;
            case '4':
                result += "0100";
                break;
            case '5':
                result += "0101";
                break;
            case '6':
                result += "0110";
                break;
            case '7':
                result += "0111";
                break;
            case '8':
                result += "1000";
                break;
            case '9':
                result += "1001";
                break;
            case 'A':
                result += "1010";
                break;
            case 'B':
                result += "1011";
                break;
            case 'C':
                result += "1100";
                break;
            case 'D':
                result += "1101";
                break;
            case 'E':
                result += "1110";
                break;
            case 'F':
                result += "1111";
                break;
            default:
                throw invalid_argument(INVALID_EXPRESSION);
        }
    }

    return result;
}
string Calculator::decToBin(string& input)
{

    //convert strinint
    int num = stoi(input);
    vector<unsigned int> tempResult;
    stringstream temp;

    // storing remainder in tempResult
    while (num > 0) {
        tempResult.push_back(num % 2) ;
        num = num / 2;
    }

    //make a binary format ex. 0001
    while(tempResult.size()%4 != 0){
        tempResult.push_back(0);
    }

    //reverse order and convert
    while(!tempResult.empty()){
        temp<<tempResult.back();
        tempResult.pop_back();
    }
    return temp.str();
}

string Calculator::binToDec(string &input) {
    unsigned long result = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    for (int i = input.size() - 1; i >= 0; i--) {
        int tmp = stoi(to_string(input[i])) - '0';

        //int tmp = input[i] - '0';
        result = result + tmp * base;
        base = base * 2;
    }

    return to_string(result);
}

string Calculator::hexToDec(string &input)
{
    string result;
    result = hexToBin(input);
    result = binToDec(result);

    return result;
}

string Calculator::decToHex(string &input)
{
    string result;
    result = decToBin(input);
    result = binToHex(result);

    return result;
}

bool Calculator::validateInputString(const string &inExpression,
                                     set<char>validChars)
{
    //if input value is empty, return false
    if (validChars.empty())
        return false;

    //For each character in the string
    for (char c : inExpression)
    {
        //if character not in valid set, return false
        if (validChars.find(toupper(c)) == validChars.end())
            return false;
    }

    //if all characters passed test, return true
    return true;
}
