// Class used to execute the forward search and backtracking algorithms

#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){
    // TODO
}

PathSolver::~PathSolver(){
    // TODO
}

void PathSolver::forwardSearch(Env env){

    NodeList P; // open list
    NodeList C; // closed list

    // Search for S
    bool S_found = false;
    for (int r = 0; r<ENV_DIM && !S_found; r++){
        for (int c = 0; c<ENV_DIM && !S_found; c++){
            if (env[r][c] == SYMBOL_START){
                Node temp(r, c, 0);
                P.addElement(&temp);
                S_found = true;
            }
        }
    }

    if (!S_found){
        std::cerr << "ERROR - S was not found in the env!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Search for G
    bool G_found = false;
    int rowG, colG;
    
    for (int r = 0; r<ENV_DIM && !G_found; r++){
        for (int c = 0; c<ENV_DIM && !G_found; c++){
            if (env[r][c] == SYMBOL_GOAL){
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

    Node goal(rowG, colG, 0);
    Node* p = P.getNode(0);
    Node* temp;
    bool found_goal = false;
    bool goal_can_be_found = true;

    do{
        std::cout << "p= " << p->getRow() << " " << p->getCol() << '\n';
        for (int dir = 1; dir<= 4; ++dir){ // We will be looking in 4 directions
            int newRow = p->getRow();
            int newCol = p->getCol();
            switch (dir){
                case 1: 
                    ++newCol;
                    break;
                case 2:
                    --newCol;
                    break;
                case 3: 
                    ++newRow;
                    break;
                case 4:
                    --newRow;
                    break;
            }      

            if ((env[newRow][newCol] == SYMBOL_EMPTY) || (env[newRow][newCol] == SYMBOL_GOAL)){ 
                // Look to see if already in Closed list
                bool found = false;
                for (int i =0; i<C.getLength() && !found; ++i){
                    temp = C.getNode(i);
                    if ((temp->getRow() == newRow) && (temp->getCol() == newCol)){
                        found = true;  
                    }
                }

                if (!found){
                    // Position is not in Closed list
                    Node temp(newRow, newCol, 1+p->getDistanceTraveled());
                    P.addElement(&temp);
                    std::cout << "Node added: " << temp.getRow() << " " << temp.getCol() << " " << temp.getDistanceTraveled() << '\n';
                }
                
            }
        }
        // add p to Closed list
        C.addElement(p);

        int smallestDistance = 1000; //initialised to a high value that will certainly be replaced
        int index = -1; 

        for (int i = 0; i<P.getLength(); ++i){
            Node* pTemp = P.getNode(i);
            // Check to see if Node is in Closed list
            bool found = false;
            for (int j = 0; j<C.getLength() && !found; ++j){
                Node* temp = C.getNode(j);
                if ((pTemp->getRow() == temp->getRow()) && (pTemp->getCol() == temp->getCol())){
                    found = true;
                }
            }

            if (!found){
                // Position was not found in the closed list
                if (pTemp->getEstimatedDist2Goal(&goal) < smallestDistance){
                    smallestDistance = pTemp->getEstimatedDist2Goal(&goal);
                    index = i;
                }
            }
        }

        std::cout << smallestDistance << " ";

        if (index != -1){
            p=P.getNode(index);
        } else {
            goal_can_be_found = false;
        }

        if ((p->getRow() == goal.getRow()) && (p->getCol() == goal.getCol())){
            found_goal = true;
        }

    }while(!found_goal && goal_can_be_found);
}

NodeList* PathSolver::getNodesExplored(){
    
    return nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
    // get nodes explored
    // start in last position of nodes explored (goal)
    // check what options are and see if option is in nodes explored
    // if it's there assign L-1 value
    // if not in nodes explored, ignore it

    //TODO
    NodeList * ptr = nullptr;
    return ptr;

}

//-----------------------------