/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include <cstdio>
#include <cstring>
#include <cctype>

// Enumarated Type specifying all of the Tokens
enum TokenType{
    ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

//Class for tokens
class Token
{
private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

public:
    Token();
    Token (TokenType t);
    void setToType(TokenType t);
    void setToOperator(char c);
    void setToValue(int v);
    bool equalsType(TokenType t);
    bool equalsOperator(char c);
    char getOperator ();
    int getValue();
};

//Class for token reader
class TokenReader
{
private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;

public:
    TokenReader();
    void clearToEoln();
    Token getNextToken();
};



//Class for values
class valStack
{
private:
    int size;
    int* vals;

public:
    int stackTop;
    valStack();
    bool isEmpty();
    void push(int val);
    int topPop();
    void reset();

};

class opStack
{
private:
    int size;
    char* vals;


public:
    int stackTop;
    opStack();
    bool isEmpty();
    void push(char val);
    int topPop();
    void reset();

};

//Outside of class function declarations
void processExpression (Token inputToken, TokenReader *tr);
bool dbgOn(int numArgs, char** args);
void printCommands();
