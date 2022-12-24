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

    // update env with info from NodeList and then print env with existing code
    // 0. go through env
    // 1. go through node list
    // 2. add nodes to env
    // 3. check positing of next node
    // 4. assign the right char and add to 

    // use pointers

    bool matching = false;
    int nextNode = 0;
    int* cPtr =nullptr;
    int* rPtr =nullptr;
    for (int i =0; i<solution->getLength(); ++i){
        //std::cout << "inside nodelist ";
        for(int r= 0; r<ENV_DIM; ++r){
            for (int c = 0 ; c<ENV_DIM; ++c){
                std::cout << env[r][c];
                if ((solution->getNode(i)->getRow() == r) && (solution->getNode(i)->getCol() == c)){
                    std::cout << env[r][c];
                    matching = true;
                } 
                *cPtr = c;
                std::cout << "This is the new env. C = " << *cPtr  << std::endl;
            } 
            std::cout << std::endl;
            *rPtr = r; 
            std::cout << "This is the new env. R = " << *rPtr  << std::endl;
        } // leaving env
        nextNode = i+1;
        std::cout << "next node: " << nextNode << '\n';
        //works to here

        if (matching && (env[*rPtr][*cPtr] != SYMBOL_GOAL)){
            // checking next node to see what direction to print
            if (solution->getNode(nextNode)->getCol() == env[*rPtr][(*cPtr)+1]){
                env[*rPtr][*cPtr] = '>';    // next node is to the right  
            } 
            /*
            else if (solution->getNode(nextNode)->getCol() == env[newR][newC-1]){
                env[newR][newC] = '<';    // next node is to the left
            }
            else if (solution->getNode(nextNode)->getRow() == env[newR-1][newC]){
                env[newR][newC] = '^';    // next node is up 
            }
            else if (solution->getNode(nextNode)->getRow() == env[newR+1][newC]){
                env[newR][newC] = 'v';    // next node is down
            } 
            */
        } 
        //fill the rest of env

       // std::cout << env[newR][newC];
    } // leaving Nodelist
    std::cout << std::endl;
}


   /* below has segmentation fault
            // updating env with solution nodelist
    Env newEnv;
    int nextNode = 0;
    bool matching = false;
    //Node* temp = nullptr;
    // Going through environment
    for (int r= 0; r<ENV_DIM; ++r){
        for (int c = 0 ; c<ENV_DIM; ++c){
            //Going though solution NodeList
            for (int i =0; i<solution->getLength(); ++i){
                // if row and column is in solution, replace it in env
                if ((solution->getNode(i)->getRow() == r) && (solution->getNode(i)->getCol() == c)){
                    //replacing with direction chars
                    //temp[r][c];
                    //move to the nextNode
                    //temp = solution->getNode(i);
                    matching = true;
                    nextNode = i+1;
                }
            }
            if (matching){
                    // checking next node to see what direction to print
                if (solution->getNode(nextNode)->getCol() == env[r][c+1]){
                    newEnv[r][c] = '>';    // next node is to the right  
                } 
                else if (solution->getNode(nextNode)->getCol() == env[r][c-1]){
                    newEnv[r][c] = '<';    // next node is to the left
                }
                else if (solution->getNode(nextNode)->getRow() == env[r-1][c]){
                    newEnv[r][c] = '^';    // next node is up 
                }
                else if (solution->getNode(nextNode)->getRow() == env[r+1][c]){
                    newEnv[r][c] = 'v';    // next node is down
                }

            }

            
            // first update the environment with navigation path, and then print out the whole environment.
            std::cout << newEnv[r][c];
        }
    }
    std::cout << '\n';

    */

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