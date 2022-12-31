// Class used to provide a method for storing a list of node objects 
// Uses an array of Node objects

#include "NodeList.h"
#include <iostream>


NodeList::NodeList(){
    length = 0;
    capacity = INITIAL_CAPACITY;
    nodes = new Node*[capacity];
}

NodeList::~NodeList(){
    for (int i = 0; i<length; i++){
        delete nodes[i];
    }
    length = 0;
    delete[] nodes;
}
 
NodeList::NodeList(NodeList& other){
    length = other.length;
    capacity = other.capacity;
    nodes = new Node*[capacity];
    for(int i = 0; i<length; i++){
        nodes[i] = new Node(*(other.nodes[i]));
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
     // Check to see if we have used all current capacity
     if (length == capacity){ 
        // yes we have, so we will double the capacity
        Node** temp = new Node*[capacity * 2];
        for (int i = 0; i<length; ++i){
            temp[i] = nodes[i];
        }
        delete[] nodes;
        nodes = temp;
        capacity *=2;
    }
    
    nodes[length++] = new Node(*newPos);
}

Node* NodeList::getNode(int i){
    return nodes[i];
}