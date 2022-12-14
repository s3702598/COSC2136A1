// Class used to to represent a position 
// using tuple - (col, row, distance_travelled) of the robot

#include "Node.h"
#include <iostream>
#include <cmath>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){
    // Nothing to do
}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    
    return std::abs(col-(goal->col)) + std::abs(row-(goal->row)) + dist_traveled;
}
    
                            