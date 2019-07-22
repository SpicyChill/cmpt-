/*
 * PriorityQueue.h
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Author: Inspired by Frank M. Carrano and Tim Henry (textbook).
 * Modified: February 2019 by Haoping Yu
 *
 */



/* None of the provided code (basecode) may be modified. */



#pragma once

#include "Node.h"
#include "EmptyDataCollectionException.h"

#include <cstdio>

using namespace std;


template <class T>
class PriorityQueue {

    private:
        // singly-linked list
        Node<T>* head;
        int len;


        /* You may add private methods to this class */
        Node<T>* tail;

    public:
        // Desc: Default Constructor. (O(1))
        PriorityQueue();
 

        // Desc: Copy Constructor. (O(N))
        PriorityQueue(const PriorityQueue& rhs);


        // Desc: Destructor. (O(N))
        ~PriorityQueue();


        // Desc: Returns true if Priority Queue empty. (O(1))
        // Pre: No
        // Post: No
        bool isEmpty() const;


        // Desc: Returns length of the Priority Queue. (O(1))
        // Pre: No
        // Post: No
        int getLength() const;


        // Desc: Inserts x in sorted order. (O(N))
        //  Pre: Priority Queue is sorted.
        // Post: Priority Queue remains sorted.
        void enqueue(const T& x);
    

        // Desc: Removes the element with "highest" priority. (O(1))
        //  Pre: Priority Queue not empty.
        //       Throws EmptyDataCollectionException if Priority Queue empty.
        // Post: length decreased by 1, and the prioirity queue remains sorted
        void dequeue() throw(EmptyDataCollectionException);


        // Desc: Returns the element with the "highest" priority. (O(1))
        //  Pre: Priority Queue not empty.
        //       Throws EmptyDataCollectionException if Priority Queue empty.
        // Post: Priority Queue is unchanged.
        T& peek() const throw(EmptyDataCollectionException);

}; // PriorityQueue

// Desc: Default Constructor. (O(1))
template <class T>
PriorityQueue<T>::PriorityQueue(){
    len = 0;
    head = NULL;
    tail = NULL;
}


// Desc: Copy Constructor. (O(N))
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& rhs){
    Node<T>* node = rhs.head;
    len = rhs.len;
    if(len == 0){
        head = tail = NULL;
        return;
    }
    head = new Node<T>(node->data);
    tail = head;
    node = node->next;
    while(node){
        tail->next = new Node<T>(node -> data);
        tail = tail->next;
        node = node->next;
    }
}


// Desc: Destructor. (O(N))
template <class T>
PriorityQueue<T>::~PriorityQueue(){
    while(!isEmpty()){
        dequeue();
    }
}


// Desc: Returns true if Priority Queue empty. (O(1))
// Pre: No
// Post: No
template <class T>
bool PriorityQueue<T>::isEmpty() const{
    return len == 0;
}


// Desc: Returns length of the Priority Queue. (O(1))
// Pre: No
// Post: No
template <class T>
int PriorityQueue<T>::getLength() const{
    return len;
}


// Desc: Inserts x in sorted order. (O(N))
//  Pre: Priority Queue is sorted.
// Post: Priority Queue remains sorted.
template <class T>
void PriorityQueue<T>::enqueue(const T& x){
    Node<T>* newNode = new Node<T>(x);
    if(isEmpty()){
        head = tail = newNode;
        len++;
        return;
    }
    len++;
    if(x < head -> data){
        newNode -> next = head;
        head = newNode;
        return;
    }
    Node<T>* itre = head;
    while(itre -> next){
        if(itre->next->data > x){
            newNode -> next = itre -> next;
            itre -> next = newNode;
            return;
        }
        itre = itre->next;
    }
    tail -> next = newNode;
    tail = tail -> next;
}


// Desc: Removes the element with "highest" priority. (O(1))
//  Pre: Priority Queue not empty.
//       Throws EmptyDataCollectionException if Priority Queue empty.
// Post: length decreased by 1, and the prioirity queue remains sorted
template <class T>
void PriorityQueue<T>::dequeue() throw(EmptyDataCollectionException){
    if(isEmpty()){
        throw EmptyDataCollectionException();
    }
    len--;
    if(head == tail){
        delete head;
        head = tail = NULL;
        return;
    }
    Node<T>* newHead = head->next;
    delete head;
    head = newHead;
}


// Desc: Returns the element with the "highest" priority. (O(1))
//  Pre: Priority Queue not empty.
//       Throws EmptyDataCollectionException if Priority Queue empty.
// Post: Priority Queue is unchanged.
template <class T>
T& PriorityQueue<T>::peek() const throw(EmptyDataCollectionException){
    if(isEmpty()){
        throw EmptyDataCollectionException();
    }
    return head->data;
}
