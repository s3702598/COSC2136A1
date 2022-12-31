/*
Program to navigate a robot through a 2D environment and find the shortest 
way from start to goal.

I have completed the program utilising the alogoritm given in the Assignment prompt
for finding a path from start to goal as well as recurrence for 
finding the shortest way from start to finish. 
In Milestone 4 I utilised vectors as the NodeList array size changes, 
which vector as a container can accommodate. 

My biggest struggle was to come up with the algoritm for getting the shortest path.
After research and some refresher of my previous coding I've decided to use recurrence
as it seemed to be the most straight forward way.
Pointers are new to me so I had to do a lot of additional studies to use them 
without errors in the code.

Created by: Honorata Trojanowska s3702598
*/



#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(int& nRows, int& nCols);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution, int nRows, int nCols);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    int noOfRows;
    int noOfCols;
    Env env = readEnvStdin(noOfRows, noOfCols); 
    std::cout << "Back in main \n";
    for(int r=0; r<noOfRows; ++r){
        for (int c=0; c<noOfCols; ++c){
            std::cout << env[r][c];
        }
        std::cout << '\n';
    }

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver(noOfRows, noOfCols);
    pathSolver->forwardSearch(env);

    
    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    
    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);
    std::cout << "Solution lenght is: " << solution->getLength() << '\n';
    for (int i = 0; i<solution->getLength(); ++i){
        std:: cout << solution->getNode(i)->getRow() << ' ' 
            << solution->getNode(i)->getCol() << '\n';
    }

    printEnvStdout(env, solution, noOfRows, noOfCols);


    delete pathSolver;
    delete exploredPositions;
    delete solution;
    for (int r = 0; r<noOfRows; ++r){
        delete[] env[r];
    }
    delete[] env;

}

Env readEnvStdin(int& nRows, int& nCols){
    std::vector<char> temp;
    std::vector<char*> temp2;
    char newline = '\n';
    char ch;

    // We will read in the first line of the environment to find out the number of columns
    nCols = 0; 

    std::cin.get(ch);
    while ((ch != newline) && !std::cin.eof()){
        temp.push_back(ch);
        ++nCols;
        std::cin.get(ch);
    }

    // We now know how many columns in the environment

    char* ptr = new char[nCols];
    temp2.push_back(ptr);

    // We will copy from temp into the new dynamically allocated array
    for (int i = 0; i<nCols; ++i){
        temp2[0][i] = temp[i];
    }

    nRows = 1;
    while (!std::cin.eof()){
        ptr = new char[nCols];
        temp2.push_back(ptr);
        std::cin.get(ch);
        int c = 0;
        while ((ch != newline) && !std::cin.eof()){
            temp2[nRows][c] = ch;
            std::cin.get(ch);
            ++c;
        }
        ++nRows;
    }

    // We now know how many rows there are

    Env env = new char* [nRows];

    for (int r =0; r<nRows; ++r){
        env[r] = temp2[r];
    }

    return env;
}

void printEnvStdout(Env env, NodeList* solution, int nRows, int nCols) {

    int nextRow;
    int nextCol;
    int newRow = solution->getNode(1)->getRow();
    int newCol = solution->getNode(1)->getCol();
    for (int i = 1; i<(solution->getLength()-1); ++i){
        nextRow = solution->getNode(i+1)->getRow();
        nextCol = solution->getNode(i+1)->getCol();
        if (newCol == (nextCol -1)){
            // next node is to the right
            env[newRow][newCol] = '>';      
        } 
        else if (newCol == (nextCol +1)){
            // next node is to the left
            env[newRow][newCol] = '<';    
        }
        else if (newRow == (nextRow +1)){
            // next node is up 
            env[newRow][newCol] = '^';    
        }
        else if (newRow == (nextRow -1)){
            // next node is down
            env[newRow][newCol] = 'v';    
        } else {
            std::cout << "Invalid row or column" << std::endl;
        }
        newRow = nextRow;
        newCol = nextCol;
       
    }

    for(int r= 0; r<nRows; ++r){
        for (int c = 0 ; c<nCols; ++c){
            std::cout << env[r][c];
        }
        std::cout << std::endl;
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}