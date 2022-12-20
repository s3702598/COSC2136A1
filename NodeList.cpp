// Class used to provide a method for storing a list of node objects 
// Uses an array of Node objects

#include "NodeList.h"
#include <iostream>


NodeList::NodeList(){
    length = 0;
}

NodeList::~NodeList(){
    for (int i = 0; i<length; i++){
        delete nodes[i];
    }
    length = 0;
}
 
NodeList::NodeList(NodeList& other){
    length = other.length;
    for(int i = 0; i<length; i++){
        nodes[i] = new Node(*(other.nodes[i]));
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    nodes[length++] = new Node(*newPos);
}

Node* NodeList::getNode(int i){
    return nodes[i];
}