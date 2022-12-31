// Class used to execute the forward search and backtracking algorithms 

#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(int nRows, int nCols){
    nodesExplored = new NodeList();
    startNode = nullptr;
    goalNode = nullptr;
    this->nRows = nRows;
    this->nCols = nCols;
}

PathSolver::~PathSolver(){
    delete nodesExplored;
    delete startNode;
    delete goalNode;
}

void PathSolver::forwardSearch(Env env){

    // open list
    NodeList P; 

    // Search for Start coordinates
    bool S_found = false;
    for (int r = 0; r<nRows && !S_found; r++){
        for (int c = 0; c<nCols && !S_found; c++){
            if (env[r][c] == SYMBOL_START){
                startNode = new Node (r, c, 0);
                // Add S to open list
                P.addElement(startNode);
                S_found = true;
            }
        }
    }

    if (!S_found){
        std::cerr << "ERROR - S was not found in the env!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Search for Goal coordiantes
    bool G_found = false;
    int rowG, colG;
    
    for (int r = 0; r<nRows && !G_found; r++){
        for (int c = 0; c<nCols && !G_found; c++){
            if (env[r][c] == SYMBOL_GOAL){
                // Save the coordiantes of goal
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

    // create a goal node 
    goalNode = new Node(rowG, colG, 0);
    Node* p = P.getNode(0);
    Node* temp;
    bool found_goal = false;
    bool goal_can_be_found = true;

    do{
        std::cout << "p= " << p->getRow() << " " << p->getCol() << '\n';
        // We will be looking in 4 directions
        for (int dir = 1; dir<= 4; ++dir){ 
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
                for (int i =0; i<nodesExplored->getLength() && !found; ++i){
                    temp = nodesExplored->getNode(i);
                    if ((temp->getRow() == newRow) && (temp->getCol() == newCol)){
                        found = true;  
                    }
                }

                if (!found){
                    // Position is not in Closed list
                    Node temp(newRow, newCol, 1+p->getDistanceTraveled());
                    // Add to open list
                    P.addElement(&temp);
                    std::cout << "Node added: " << temp.getRow() << " " << temp.getCol() 
                    << " " << temp.getDistanceTraveled() << '\n';
                }
                
            }
        }
        // add p to Closed list
        nodesExplored->addElement(p);

        //initialised to a high value that will certainly be replaced
        int smallestDistance = 1000; 
        int index = -1; 

        for (int i = 0; i<P.getLength(); ++i){
            Node* pTemp = P.getNode(i);
            // Check to see if Node is in Closed list
            bool found = false;
            for (int j = 0; j<nodesExplored->getLength() && !found; ++j){
                Node* temp = nodesExplored->getNode(j);
                if ((pTemp->getRow() == temp->getRow()) && (pTemp->getCol() == temp->getCol())){
                    found = true;
                }
            }

            if (!found){
                // Position was not found in the closed list
                if (pTemp->getEstimatedDist2Goal(goalNode) < smallestDistance){
                    smallestDistance = pTemp->getEstimatedDist2Goal(goalNode);
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

        if ((p->getRow() == goalNode->getRow()) && (p->getCol() == goalNode->getCol())){
            found_goal = true;
            goalNode->setDistanceTraveled(p->getDistanceTraveled());
        }

    }while(!found_goal && goal_can_be_found);
}


NodeList* PathSolver::getNodesExplored(){
    
    NodeList* temp = new NodeList(*nodesExplored);
    return temp;
}


NodeList* PathSolver::getPath(Env env){

    NodeList * ptr = nullptr;
    // start with empty list
    ptr = new NodeList(); 
    ptr = getPathRecursive(env, goalNode, ptr);
    return ptr;

}

// Using recursive call, returns a NodeList pointer to the shortest path
// from start to goal
NodeList* PathSolver::getPathRecursive
    (Env env, Node* currentNode, NodeList* currentList){

   //std::cout << " Nodes explored lenght: " << nodesExplored->getLength() << '\n';

    // Test for base case
    if ((currentNode->getRow() == startNode->getRow()) &&
        (currentNode->getCol() == startNode->getCol())){
        currentList->addElement(currentNode);
        return currentList;
    }

    // Find Node with distance travelled 1 less than the current Node
    int distanceTravelled = currentNode->getDistanceTraveled();
    // We will be looking in 4 directions
    for (int dir = 1; dir<= 4; ++dir){ 
        int newRow = currentNode->getRow();
        int newCol = currentNode->getCol();
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

        //Check if this location is empty or start location
        Node* temp = nullptr;
        if ((env[newRow][newCol] == SYMBOL_EMPTY) || (env[newRow][newCol] == SYMBOL_START)){
            // Search for node in nodesExplored list
            bool found = false;
            for (int i = 0; (i<nodesExplored->getLength()) && !found; ++i){
                temp = nodesExplored->getNode(i);
                if ((temp->getRow() == newRow) && (temp->getCol() == newCol)){
                    std::cout << "Found\n";
                    found = true;
                }
            } 

            // Check if a Node was found in nodeExplored list 
            if (found){
                std::cout << "Distance travelled: " << distanceTravelled <<
                " Temp distance travelled : " << temp->getDistanceTraveled() << '\n';
                // Check if distance  is 1 less then current node
                if (temp->getDistanceTraveled() == (distanceTravelled - 1)){
                    // We have found node we are looking for
                    std::cout << "Just before recursive call\n";
                    NodeList* ptr = getPathRecursive(env, temp, currentList);
                    ptr->addElement(currentNode);
                    return ptr;
                }
            }
        }
    }  
    // We should never reach this point. 
    // This is here because some compilers require it.
    return currentList; 
    
    
}

//-----------------------------