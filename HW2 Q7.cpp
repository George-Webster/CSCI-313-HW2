// HW2 Q7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "myStack.h"


using namespace std;

//function headers
int convertChar(char a);
char convertInt(int a);
void checkNode(int node, vector<vector<int>> n, bool* v, stackType<int>& stack);

int main()
{
    //this is the representation of the maze as a two dimensional vector
    //for a visual representation of the maze, see the attached white paper
    const int SIZE = 14;
    vector <vector<int>> maze(SIZE);
    maze[convertChar('A')].push_back(convertChar('D'));
    maze[convertChar('B')].push_back(convertChar('G'));
    maze[convertChar('C')].push_back(convertChar('D'));
    maze[convertChar('C')].push_back(convertChar('H'));
    maze[convertChar('D')].push_back(convertChar('A'));
    maze[convertChar('D')].push_back(convertChar('C'));
    maze[convertChar('D')].push_back(convertChar('E'));
    maze[convertChar('E')].push_back(convertChar('D'));
    maze[convertChar('E')].push_back(convertChar('F'));
    maze[convertChar('F')].push_back(convertChar('E'));
    maze[convertChar('F')].push_back(convertChar('G'));
    maze[convertChar('F')].push_back(convertChar('I'));
    maze[convertChar('G')].push_back(convertChar('B'));
    maze[convertChar('G')].push_back(convertChar('F'));
    maze[convertChar('H')].push_back(convertChar('C'));
    maze[convertChar('H')].push_back(convertChar('J'));
    maze[convertChar('I')].push_back(convertChar('F'));
    maze[convertChar('I')].push_back(convertChar('K'));
    maze[convertChar('J')].push_back(convertChar('H'));
    maze[convertChar('J')].push_back(convertChar('M'));
    maze[convertChar('K')].push_back(convertChar('I'));
    maze[convertChar('K')].push_back(convertChar('L'));
    maze[convertChar('L')].push_back(convertChar('K'));
    maze[convertChar('L')].push_back(convertChar('N'));
    maze[convertChar('M')].push_back(convertChar('J'));
    maze[convertChar('N')].push_back(convertChar('L'));

    //creation of the stack
    stackType<int> solutionStack;
    solutionStack.initializeStack();
    
    //creation of the visited array to keep track of which nodes have already been seen
    bool* visited = new bool[SIZE];
    for (int i = 0; i < SIZE; i++) {
        *(visited + i) = false;
    }//end for loop

    //Add the start of the maze to visited
    *(visited + convertChar('A')) = true;

    //Call the checkNode function to analyze the nodes that A sees
    checkNode(convertChar('A'), maze, visited, solutionStack);

    //At this point, if the stack is empty, there is no solution to the maze
    if (solutionStack.isEmptyStack()) {
        cout << "No solution was found.";
    }//end if
    //otherwise, there is a solution
    else {
        //create a temporary stack to reverse the solution stack
        stackType<int> temp;
        while (!solutionStack.isEmptyStack()) {
            temp.push(solutionStack.top());
            solutionStack.pop();
        }//end while loop
        //output temp, showing the solution from start to finish
        cout << "Solution: ";
        while (!temp.isEmptyStack()) {
            cout << convertInt(temp.top()) << " -> ";
            temp.pop();
        }//end while loop
    }//end else
}

//a recursive function that takes in an integer marking the node, the maze, the visited array, and the solution stack
void checkNode(int node, vector<vector<int>> n, bool* v, stackType<int>& stack) {
    //if the target has been found, return
    if (*(v + 13) == true)return;
    //create an iterator to access all of the nodes seen by the current node
    vector<int>::iterator it;
    //use a for loop to iterate through the list of nodes seen by the current node
    for (it = n[node].begin(); it != n[node].end(); it++) {
        //if the node seen is the target, a solution has been found, add it to the stack and return
        if (*it == 13) {
            stack.push(*it);
            return;
        }
        //if the node seen has already been visited, skip it
        if (*(v + *it)==true) continue;
        //otherwise, mark the node as visited, add it to the stack, and check that node
        else {
            *(v + *it) = true;
            stack.push(*it);
            checkNode(*it, n, v, stack);
        }//end else
    }//end for loop
    //if the function makes it to this point, then the current node cannot be on a path to the target, pop it and return
    stack.pop();
    return;
}

//simple function for converting characters to integers. Note that if the character is not a letter, it returns -1
int convertChar(char a) {
    if (a == 'A' || a == 'a') return 0;
    if (a == 'B' || a == 'b') return 1;
    if (a == 'C' || a == 'c') return 2;
    if (a == 'D' || a == 'd') return 3;
    if (a == 'E' || a == 'e') return 4;  
    if (a == 'F' || a == 'f') return 5;
    if (a == 'G' || a == 'g') return 6;
    if (a == 'H' || a == 'h') return 7;
    if (a == 'I' || a == 'i') return 8;
    if (a == 'J' || a == 'j') return 9;
    if (a == 'K' || a == 'k') return 10;
    if (a == 'L' || a == 'l') return 11;
    if (a == 'M' || a == 'm') return 12;
    if (a == 'N' || a == 'n') return 13;
    if (a == 'O' || a == 'o') return 14;
    if (a == 'P' || a == 'p') return 15;
    if (a == 'Q' || a == 'q') return 16;
    if (a == 'R' || a == 'r') return 17;
    if (a == 'S' || a == 's') return 18;
    if (a == 'T' || a == 't') return 19;
    if (a == 'U' || a == 'u') return 20;
    if (a == 'V' || a == 'v') return 21;
    if (a == 'W' || a == 'w') return 22;
    if (a == 'X' || a == 'x') return 23;
    if (a == 'Y' || a == 'y') return 24;
    if (a == 'Z' || a == 'z') return 25;
    return -1;
}

//Simple function to convert integers to characters. Note that if a<0 or a>25, it returns & to indicate an error
char convertInt(int a) {
    if (a == 0) return 'A';
    if (a == 1) return 'B';
    if (a == 2) return 'C';
    if (a == 3) return 'D';
    if (a == 4) return 'E';
    if (a == 5) return 'F';
    if (a == 6) return 'G';
    if (a == 7) return 'H';
    if (a == 8) return 'I';
    if (a == 9) return 'J';
    if (a == 10) return 'K';
    if (a == 11) return 'L';
    if (a == 12) return 'M';
    if (a == 13) return 'N';
    if (a == 14) return 'O';
    if (a == 15) return 'P';
    if (a == 16) return 'Q';
    if (a == 17) return 'R';
    if (a == 18) return 'S';
    if (a == 19) return 'T';
    if (a == 20) return 'U';
    if (a == 21) return 'V';
    if (a == 22) return 'W';
    if (a == 23) return 'X';
    if (a == 24) return 'Y';
    if (a == 25) return 'Z';
    return '&';
}