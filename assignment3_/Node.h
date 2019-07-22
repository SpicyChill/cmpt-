/*
 * Node.h
 *
 * Class Definition: Node of a singly linked list (template)
 *                   Designed and implemented as a non-ADT.
 *
 * Created on: 
 * Author: 
 */
 
#pragma once

#include <cstdio>  // Needed for NULL

using namespace std;


template <class T>
class Node {
    public:
        T data;
        Node* next;
        Node(T data); // Constructor
        Node(){};


}; // Node


template <class T>
Node<T>::Node(T data) {
    this->data = data;
    this->next = NULL;
}
