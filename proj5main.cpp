/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 11/06/17
 *
 * Author: Ross Swanson
 *
 */

#include "proj5.h"

bool debugMode;

bool dbgOn(int numArgs, char** args){
    int i = 0;
    bool dbgMode = false;
    char cmpStr[] = "-d";

    if(numArgs > 1){
        for(i=0; i<numArgs; i++){
            if(strcmp(args[i], cmpStr) != 0){
                dbgMode = false;
            }
            else if(strcmp(args[i], cmpStr) == 0){
                dbgMode = true;
                break;
            }
        }
    }
    return dbgMode;
}

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */

    debugMode = dbgOn(argc, argv);

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
        /* check first Token on Line of input */
        if(inputToken.equalsType(HELP))
        {
            printCommands();
            tr.clearToEoln();
        }
        else if(inputToken.equalsType(ERROR))
        {
            printf ("Invalid Input - For a list of valid commands, type ?\n");
            tr.clearToEoln();
        }
        else if(inputToken.equalsType(EOLN))
        {
            printf ("Blank Line - Do Nothing\n");
            /* blank line - do nothing */
        }
        else
        {
            processExpression(inputToken, &tr);
        }

        printf ("\nEnter Expression: ");
        inputToken = tr.getNextToken ();
    }

    printf ("Quitting Program\n");
    return 1;
}

void processExpression (Token inputToken, TokenReader *tr)
{
    /**********************************************/
    valStack vals1;     //declares value stack
    int valTop;
    int valNext;        //Variables for evaluating the exression
    int valAns;

    opStack ops1;       //declares operator stack
    char opTop;         //Location for calls to topPop() to return to

    /* Loop until the expression reaches its End */
    while (inputToken.equalsType(EOLN) == false)
    {
        /* The expression contain a VALUE */
        if (inputToken.equalsType(VALUE))
        {
            if (debugMode == true)
                printf ("Val: %d, ", inputToken.getValue() );

            // If token is a value, push onto the stack
            vals1.push(inputToken.getValue());
        }

        /* The expression contains an OPERATOR */
        else if (inputToken.equalsType(OPERATOR))
        {
            if (debugMode == true)
                printf ("OP: %c, ", inputToken.getOperator() );

            // If Token == (, push onto the stack
            if(inputToken.getOperator() == '('){
                ops1.push(inputToken.getOperator());
            }

            //If the token is + or -, perform operations on the stack
            else if ((inputToken.getOperator() == '+') || (inputToken.getOperator() == '-')){
                opTop = ops1.topPop();
                while((ops1.isEmpty() == false) && (opTop == '+' || opTop == '-' || opTop == '*' || opTop == '/'))
                    {
                        //POPANDEVAL

                        //Set value on top of the stack to valTop
                        valTop = vals1.topPop();
                        if(debugMode == true)
                            printf("Val top = %d\n", valTop);

                        //Set next value on the stack to valNext
                        valNext = vals1.topPop();
                        if(debugMode == true)
                            printf("Val top = %d\n", valNext);

                        //Code adds valNext and valTop
                        if(opTop == '+')
                        {
                            valAns = valNext + valTop;
                            opTop = ops1.topPop();
                        }

                        //Code subtracts valTop from valNext
                        else if(opTop == '-')
                        {
                            valAns = valNext - valTop;
                            opTop = ops1.topPop();
                        }

                        ////Code multiplies valNext and valTop
                        else if(opTop == '*')
                        {
                            valAns = valNext*valTop;
                            opTop = ops1.topPop();
                        }

                        //Code divies valNext by valTop, if valTop is not 0
                        else if (opTop == '/')
                        {
                            if(valTop != 0){
                                valAns = valNext/valTop;
                                opTop = ops1.topPop();
                            }
                            else
                                printf("ERROR: Can't divide by 0\n");
                        }
                        if(debugMode == true)
                            printf("Val ans = %d\n", valAns);

                        vals1.push(valAns);

                    }
                ops1.push(opTop);
                ops1.push(inputToken.getOperator());
                }
            else if ((inputToken.getOperator() == '*') || (inputToken.getOperator() == '/'))
            {
                opTop = ops1.topPop();
                while(ops1.isEmpty() == false && (opTop == '*' || opTop == '/' ))
                {
                    //POPANDEVAL
                    valTop = vals1.topPop();

                    valNext = vals1.topPop();

                    if(opTop == '*')
                    {
                        valAns = valNext*valTop;
                        opTop = ops1.topPop();
                    }
                    else if (opTop == '/')
                    {
                        if(valTop != 0){
                            valAns = valNext/valTop;
                            opTop = ops1.topPop();
                        }
                        else
                            printf("ERROR: Can't divide by 0\n");
                    }

                    vals1.push(valAns);
                }
                ops1.push(opTop);
                ops1.push(inputToken.getOperator());
            }
            else if(inputToken.getOperator() == ')')
            {
                opTop = ops1.topPop();
                while((ops1.isEmpty() == false) && (opTop != '('))
                {
                    //POPANDEVAL
                    valTop = vals1.topPop();
                    if (debugMode == true)
                        printf("v2: %d\n", valTop);

                    valNext = vals1.topPop();
                    if (debugMode == true)
                        printf("v1: %d\n", valNext);

                    if(opTop == '+'){
                        valAns = valNext + valTop;
                        opTop = ops1.topPop();
                    }
                    else if(opTop == '-')
                    {
                        valAns = valNext - valTop;
                        opTop = ops1.topPop();
                    }
                    else if(opTop == '*')
                    {
                        valAns = valNext*valTop;
                        opTop = ops1.topPop();
                    }
                    else if (opTop == '/')
                    {
                        valAns = valNext/valTop;
                        opTop = ops1.topPop();
                    }

                    vals1.push(valAns);
                    ops1.push(opTop);
                }

                if(ops1.isEmpty() == true)
                {
                    printf("ERROR: missing open parenthesis\n");
                }
                else
                {
                    opTop = ops1.topPop();
                }
                if(debugMode == true)
                    printf("parens val = %d ", valAns);

            }
            }

        /* get next token from input */
        inputToken = tr->getNextToken ();
    }

    /* The expression has reached its end */
    while(ops1.isEmpty() == false) //THIS SEEMS LIKE THE ISSUE
    {
        //POPANDEVAL
        opTop = ops1.topPop();

        valTop = vals1.topPop();

        valNext = vals1.topPop();

        if(opTop == '+'){
            valAns = valNext + valTop;
        }
        else if(opTop == '-')
        {
            valAns = valNext - valTop;
        }
        else if(opTop == '*')
        {
            valAns = valNext*valTop;
        }
        else if (opTop == '/')
        {
            if(valTop != 0){
                valAns = valNext/valTop;
            }
            else
                printf("ERROR: Cannot divide by 0");
        }

        vals1.push(valAns);
    }

    printf("Aswer: %d\n", vals1.topPop());

    valNext = vals1.topPop();
    if (vals1.isEmpty() == false)
    {
        printf("ERROR: val stack not clear. Top val is: %d\n", vals1.topPop());
    }


    printf ("\n");
    vals1.reset();
    ops1.reset();
}
