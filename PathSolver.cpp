// Class used to execute the forward search and backtracking algorithms

#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
    /* Path solver algoritm:
    Estimated distance = distance_travelled of node p + Manhattan distance from p to G
    The Manhattan distance from node p with coordinates (colp, rowp) to node G with coordinates (colG, rowG) is
    computed as:
    Manhattan_distance = |colp − colG| + |rowp − rowG|
    here x is the absolute value of x. The Manhattan distance represent the shortest distance from a node to goal
    if there are no obstacles.
    */
}

PathSolver::~PathSolver(){
    // TODO
}

void PathSolver::forwardSearch(Env env){

    NodeList open;
    NodeList closed;

    // Search for S and G
    bool S_found = false;
    

    for (int r = 0; r<ENV_DIM && !S_found; r++){
        for (int c = 0; c<ENV_DIM && !S_found; c++){
            if (env[r][c] == 'S'){
                Node temp(r, c, 0);
                open.addElement(&temp);
                S_found = true;
            }
        }
    }

    if (!S_found){
        std::cerr << "ERROR - S was not found in the env!" << std::endl;
        exit(EXIT_FAILURE);
    }

    bool G_found = false;
    int rowG, colG;
    for (int r = 0; r<ENV_DIM && !G_found; r++){
        for (int c = 0; c<ENV_DIM && !G_found; c++){
            if (env[r][c] == 'S'){
                rowG = r;
                colG = c;
                G_found = true;
            }
        }
    }

    if (!G_found){
        std::cerr << "ERROR - G was not found in the env!" << std::endl;
        exit(EXIT_FAILURE);
    }

}

NodeList* PathSolver::getNodesExplored(){
    //TODO
}

NodeList* PathSolver::getPath(Env env){
    // TODO
}

//-----------------------------