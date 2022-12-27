#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


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
    Env env;
    readEnvStdin(env);
    for(int r=0; r<ENV_DIM; ++r){
        for (int c=0; c<ENV_DIM; ++c){
            std::cout << env[r][c];
        }
        std::cout << '\n';
    }

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
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

    printEnvStdout(env, solution);


    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env){
     for (int r=0; r<ENV_DIM; ++r){
        for (int c = 0; c<ENV_DIM; ++c){
            std::cin >> env[r][c];
        }
    }
}

void printEnvStdout(Env env, NodeList* solution) {

    int nextRow;
    int nextCol;
    int newRow = solution->getNode(1)->getRow();
    int newCol = solution->getNode(1)->getCol();
    for (int i = 1; i<(solution->getLength()-1); ++i){
        nextRow = solution->getNode(i+1)->getRow();
        nextCol = solution->getNode(i+1)->getCol();
        if (newCol == (nextCol -1)){
            env[newRow][newCol] = '>';    // next node is to the right  
        } 
        else if (newCol == (nextCol +1)){
            env[newRow][newCol] = '<';    // next node is to the left
        }
        else if (newRow == (nextRow +1)){
            env[newRow][newCol] = '^';    // next node is up 
        }
        else if (newRow == (nextRow -1)){
            env[newRow][newCol] = 'v';    // next node is down
        } else {
            std::cout << "Invalid row or column" << std::endl;
        }
        newRow = nextRow;
        newCol = nextCol;
       
    }

    for(int r= 0; r<ENV_DIM; ++r){
        for (int c = 0 ; c<ENV_DIM; ++c){
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