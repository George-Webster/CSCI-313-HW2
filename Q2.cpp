#include <iostream>  
#include <iomanip>
#include <fstream>
#include "myStack.h"
#include <string>
#include <stdio.h>
#include <cctype>

//function headers, commented below main
void evaluateExpression( ofstream& outF, stackType<double>& stack, string str, bool& isExpOk);
void evaluateOpr(ofstream& out, stackType<double>& stack, char ch, bool& isExpOk);
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk);

int main()
{
    //create an expression ok flag, so the program can "know" if there is an input error
    bool expressionOk;

    //create a character that will be the next element read from the string
    char ch;

    //create a stack to use for the calculation
    stackType<double> stack(100);

    //create fstream objects to read the file and write the answer
    ifstream infile;
    ofstream outfile;

    //attempt to open the text file containing the expression
    infile.open("Expression.txt");

    //if the file has not been accessed, report the issue and terminate the program
    if (!infile)
    {
        cout << "Cannot open the input file. "
            << "Program terminates!" << endl;
        return 1;
    }

    //create an output file to write the answer
    outfile.open("RpnOutput.txt");

    //because the file writes doubles, show the decimal point and round to 2 decimal places
    outfile << fixed << showpoint;
    outfile << setprecision(2);

    //read the entire expression as a string
    string s;
    getline(infile, s);


    //create a while loop to be able to read multiple expressions, and terminates when the infile ends
    while (infile)
    {
        //set the stack to empty
        stack.initializeStack();

        //set the expessionOk flag to true for each new expression
        expressionOk = true;

        //write the string expression
        outfile << s << ' ';

        //call the evaluate expression function
        evaluateExpression(outfile, stack, s, expressionOk);

        //write the result to the outfile
        printResult(outfile, stack, expressionOk);

        //advance to the next expression
        getline(infile, s);
    } //end while 

    //close the fstream objects
    infile.close();
    outfile.close();

    return 0;

} //end main


void evaluateExpression (ofstream& outF, stackType<double>& stack, string str, bool& isExpOk){
    //create a temporary double to assign numbers read from the file
    double num;

    //read the string backwards
    for(int i = (str.length()-1); i>=0; i--)
    {
        //check if the character is a number
        if (isdigit(str[i])) {
            //if it is, convert it to a number from char by subtracting 0
            num = str[i] - 0;
            //check if the stack is full
            if (!stack.isFullStack())
                //if the stack is not full, push num to the stack
                stack.push(num);
            //if the stack is full, alert the user and terminate the program
            else
            {
                cout << "Stack overflow. "
                    << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }
        }
        else if (str[i] == '=') continue;
        else {
            evaluateOpr(outF, stack, str[i], isExpOk);
        }

        //check if the expression is ok
        if (!isExpOk) //if no error
        {
            outF << "Error: cannot compute";
        }
    } //end for loop
} //end evaluateExpression

//function evaluateOpr, to exaluate operators and push their results to the stack
void evaluateOpr(ofstream& out, stackType<double>& stack, char ch, bool& isExpOk) {
    //create two temporary doubles
    double op1, op2;

    //if the stack is empty, something has gone wrong
    if (stack.isEmptyStack())
    {
        // alert the user
        out << " (Not enough operands)";
        // set the isExpOk flag to false so the program can discard this expression
        isExpOk = false;
    }
    //if it is not empty, proceed
    else
    {
        //set op2 equal to the top of the stack
        op1 = stack.top();
        //remove the top of the stack
        stack.pop();

        //check again if the stack is empty, because each operation requires 2 operands
        if (stack.isEmptyStack())
        {
            // alert the user
            out << " (Not enough operands)";
            // set the isExpOk flag to false so the program can discard this expression
            isExpOk = false;
        }
        else
        {
            //set op2 equal to the top of the stack
            op2 = stack.top();
            //remove the top of the stack
            stack.pop();

            //switch statement on char, to evaluate the desired operation
            switch (ch)
            {
                //in addition case
            case '+':
                //push sum to the stack
                stack.push(op1 + op2);
                break;
                //in subtraction case
            case '-':
                //push difference to the stack
                stack.push(op1 - op2);
                break;
                //in multiplication case
            case '*':
                //push product to the stack
                stack.push(op1 * op2);
                break;
                //in division case
            case '/':
                //check to avoid division by zero
                if (op2 != 0)
                    //push quotient to the stack
                    stack.push(op1 / op2);
                //if the expression requires division by zero
                else
                {
                    //alert the user
                    out << " (Division by 0)";
                    //let the program discard this expression
                    isExpOk = false;
                }
                break;
                //if none of the cases applied, then the operator was incorrect
            default:
                //alert the user
                out << " (Illegal operator)";
                //let the program discard this expression
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr


//function printResult, check for any remaining errors, then writes the result after the = sign
void printResult(ofstream& outF, stackType<double>& stack, bool isExpOk)
{
    //create a temporary double for the result
    double result;

    //if there is no error, the expressionOk flag will be true
    if (isExpOk)
    {
        //if the expression is correctly written, the stack should contain one number
        if (!stack.isEmptyStack())
        {
            //set result equal to stack
            result = stack.top();
            //remove the top of the stack
            stack.pop();

            //check if the stack is correctly empty now
            if (stack.isEmptyStack())
                //if it is empty, everything worked, and print the result
                outF << result << endl;
            else
                //if it is not empty, an error has occurred, alert the user
                outF << " (Error: Too many operands)" << endl;
        } //end if
        //if the stack was received empty by the function, there is an error, alert the user
        else
            outF << " (Error in the expression)" << endl;
    }
    //if the expressionOk flag is false, there is an error, alert the user
    else
        outF << " (Error in the expression)" << endl;

    //output an underline to distinguish between multiple expressions
    outF << "_________________________________"
        << endl << endl;
} //end printResult

