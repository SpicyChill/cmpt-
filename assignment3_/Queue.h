//
//  Queue.h
//  Assignment3
//
//  Created by Haoping Yu on 2019/3/2.
//  Copyright © 2019 Haoping Yu. All rights reserved.
//

// Class Invariant:  FIFO order
 

/* None of the provided code (basecode) may be modified. */


#pragma once

#include "Node.h"
#include "EmptyDataCollectionException.h"

#include <cstdio>

using namespace std;

template <class T>
class Queue {
    private:


        /* you choose your implementation */
        int length;
        Node<T>* head;
        Node<T>* tail;

        
    public:

        // Desc: Constructor. (O(1))
        Queue();


    
        // Desc: Returns true if Queue is empty. (O(1))
        // Pre:  No
        // Post: No
        bool isEmpty() const;

    
        // Desc: Inserts x at the "back" of this Queue. (O(1))
        // Pre:  No
        // Post: length will increase by 1, and tail changed.
        void enqueue(const T& x);

    
        // Desc: Removes the element at the "front". (O(1))
        //  Pre: Queue not empty.
        //       Throws EmptyDataCollectionException if Queue empty.
        // Post: length will decrease by 1, and tail changed
        void dequeue() throw(EmptyDataCollectionException);
   

        // Desc: Returns the element at the "front". (O(1))
        //  Pre: Queue not empty.
        //       Throws EmptyDataCollectionException if Queue empty.
        // Post: Queue is unchanged.
        T& peek() const throw(EmptyDataCollectionException);  



        /* you may add more methods */
        // Desc: Destructor
        ~Queue();
    
        // Desc: Assignment Operator
        Queue& operator=(const Queue& rhs);
    
        // Desc: Copy Constructor
        Queue(const Queue& cpy);
};


// Desc: Constructor. (O(1))
template <class T>
Queue<T>::Queue() {
    length = 0;
    head = NULL;
    tail = NULL;
} // constructor



// Desc: Returns true if Queue is empty. (O(1))
// Pre:  No
// Post: No
template <class T>
bool Queue<T>::isEmpty() const {
    return length == 0;
} // isEmpty



// Desc: Inserts x at the "back" of this Queue. (O(1))
// Pre:  No
// Post: length will increase by 1, and tail changed.
template <class T>
void Queue<T>::enqueue(const T& x) {
    Node<T>* newNode = new Node<T>(x);
    if(isEmpty()){
        head = newNode;
        tail = newNode;
        length++;
        return;
    }
    tail->next = newNode;
    tail = newNode;
    length++;
} // enqueue



// Desc: Removes the element at the "front". (O(1))
//  Pre: Queue not empty.
//       Throws EmptyDataCollectionException if Queue empty.
// Post: length will decrease by 1, and tail changed
template <class T>
void Queue<T>::dequeue() throw(EmptyDataCollectionException) {
    if(isEmpty()){
        throw EmptyDataCollectionException();
    }
    if(head == tail){
        delete head;
        head = NULL;
        tail = NULL;
        length--;
        return;
    }
    Node<T>* newHead = head->next;
    delete head;
    head = newHead;
    length--;
} // dequeue



// Desc: Returns the element at the "front". (O(1))
//  Pre: Queue not empty.
//       Throws EmptyDataCollectionException if Queue empty.
// Post: Queue is unchanged.
template <class T>
T& Queue<T>::peek() const throw(EmptyDataCollectionException) {
    if(isEmpty()){
        throw EmptyDataCollectionException();
    }
    return head->data;
} // peek

// Desc: Destructor
template <class T>
Queue<T>::~Queue(){
    while(!isEmpty()){
        dequeue();
    }
}

// Desc: Assignment Operator
template <class T>
Queue<T>& Queue<T>::operator=(const Queue& rhs){
    while(!isEmpty()){
        dequeue();
    }
    Node<T>* n = rhs.head;
    while(n){
        enqueue(n -> data);
        n = n->next;
    }
    return *this;
}

// Desc: Copy Constructor
template <class T>
Queue<T>::Queue(const Queue& cpy){
    Node<T>* n = cpy.head;
    while(n){
        enqueue(n -> data);
        n = n->next;
    }
}
