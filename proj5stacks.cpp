/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 11/06/17
 *
 * Author: Ross Swanson
 *
 */

#include "proj5.h"


//Stack function declarations for the value stack
valStack::valStack()    //constructor creates an instance of the stack
{
    size = 2;
    vals = new int[size];
    stackTop = 0;
}

bool valStack::isEmpty() //Functions checks if the stack is empty
{
    if(stackTop <= 0)/* && (vals[stackTop] == NULL*/{
        return true;
    }
    else{
        return false;
    }
}

void valStack::push(int val) //Function pushes a value onto the stack
{
    if (stackTop == (size-1)){
        int* tmp_ptr;
        size +=2;
        tmp_ptr = new int[size];
        tmp_ptr = vals;
        //delete[] vals;  <- THIS MIGHT BE A MEMORY LEAK, CHECK ON THIS LATER
        //vals = NULL;
        vals = tmp_ptr;
    }
    vals[stackTop] = val;
    //printf("PUSHED: %d  ", vals[stackTop]);
    stackTop++;
};

int valStack::topPop() //function accesse the top item from the stack and then removes it
{
    if (stackTop > 0){
        stackTop--;
        int retVal = vals[stackTop];
        return retVal;
    }
    else
        return -999;
};

void valStack::reset(){ //function resets the stack
    while (stackTop > 0){
        stackTop--;
    }
    delete[] vals;
};


//Stack function declarations for operator stack
opStack::opStack() //constructor creates an instance of the stack
{
    size = 2;
    vals = new char[size];
    stackTop = 0;
}

bool opStack::isEmpty() //Function checks if the stack is empty
{
    if(stackTop <= 0) /*&& (vals[stackTop] == NULL)*/{
        return true;
    }
    else{
        return false;
    }
}

void opStack::push(char val) //Function pushes an operator onto the stack
{
    if (stackTop == (size-1)){
        char* tmp_ptr;
        size +=2;
        tmp_ptr = new char[size];
        tmp_ptr = vals;
        //delete[] vals;  <- THIS MIGHT BE A MEMORY LEAK, CHECK ON THIS LATER
        //vals = NULL;
        vals = tmp_ptr;
    }
    vals[stackTop] = val;
    //printf("PUSHED: %c  ", vals[stackTop]);
    stackTop++;
};

int opStack::topPop() //Function accesses top of the stack
{
    stackTop--;
    return vals[stackTop];
};

void opStack::reset(){ //Function clears and resets the stack
    while (stackTop > 0){
        stackTop--;
        vals[stackTop] = NULL;
    }
};
