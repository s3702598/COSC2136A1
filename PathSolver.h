#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver(int nRows, int nCols);
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    // Pointer to a start Node
    Node* startNode;
    // Pointer to a goal Node
    Node* goalNode;
    // number of rows in the environment being solved
    int nRows; 
    // number of columns in the environment being solved
    int nCols; 

    // Helper function that executes backtracking utilising recursion
    NodeList* getPathRecursive(Env env, Node* currentNode, NodeList* currentList);
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER