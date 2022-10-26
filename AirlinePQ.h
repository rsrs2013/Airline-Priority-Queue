#ifndef _AIRLINEPQ_

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Flyer.h"
using namespace std;

#include <unordered_map>
 
// Data structure to store a max-heap node
class AirlinePQ
{
private:
    // vector to store heap elements
    vector<Flyer> A;
    int clock; // used to note when a Flyer is added in the queue and wait time;

    unordered_map<int,int> map; // map to store the confirm code and index;

    /*swap the index stored in the map
      whenever, there is a change in the position of flyer
      in the priority queue;
    */
    void swap_index(int i, int j)
    {
        int temp =  map[A[i].getCode()];
        map[A[i].getCode()] = map[A[j].getCode()];
        map[A[j].getCode()] =  temp;
    }
 
    // return parent of `A[i]`
    // don't call this function if `i` is already a root node
    int PARENT(int i) {
        return (i - 1) / 2;
    }
 
    // return left child of `A[i]`
    int LEFT(int i) {
        return (2*i + 1);
    }
 
    // return right child of `A[i]`
    int RIGHT(int i) {
        return (2*i + 2);
    }
 
    // Recursive heapify-down algorithm.
    // The node at index `i` and its two direct children
    // violates the heap property
    void heapify_down(int i)
    {
        // get left and right child of node at index `i`
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int largest = i;
 
        // compare `A[i]` with its left and right child
        // and find the largest value
        if (left < size() && A[left] > A[i]) {
            largest = left;
        }
 
        if (right < size() && A[right] > A[largest]) {
            largest = right;
        }
 
        // swap with a child having greater value and
        // call heapify-down on the child
        if (largest != i)
        {
            swap_index(i, largest);
            swap(A[i], A[largest]);
            heapify_down(largest);
        }
    }
 
    // Recursive heapify-up algorithm
    void heapify_up(int i)
    {
        // check if the node at index `i` and its parent violate the heap property
        if (i && A[PARENT(i)] < A[i])
        {
            // swap the two if heap property is violated
            swap_index(i, PARENT(i));
            swap(A[i], A[PARENT(i)]);

            
            // call heapify-up on the parent
            heapify_up(PARENT(i));
        }
    }
 
public:

    AirlinePQ()
    {
        clock = 0;
    }

    // return size of the heap
    unsigned int size() {
        return A.size();
    }
 
    // Function to check if the heap is empty or not
    bool empty() {
        return size() == 0;
    }
 
    // insert flyer into the heap. Return the confirmation code;
    int push(Flyer flyer)
    {
        //increment the clock;
        ++clock;
        //set the waitTime and code to clock;
        flyer.setWaitTime(clock);
        //set the confirmatin code to clock, because it is unique;
        flyer.setCode(clock);

        // insert a new element at the end of the vector
        A.push_back(flyer);
        
        //use the code as the key of the map;
        int key = clock;
        map[key] = size() - 1;
 
        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
        return key;
    }
 
    // Function to remove an element with the highest priority (present at the root)
    void pop()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // replace the root of the heap with the last element
            // of the vector
            //cout<<"Last person is:"<<A.back().getName()<<endl;
            //swap_index(0,size()-1);
            map.erase(A[0].getCode());
            A[0] = A.back();
            map[A[0].getCode()] = 0;
            A.pop_back();

 
            // call heapify-down on the root node
            heapify_down(0);
        }
        // catch and print the exception
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
            throw oor;
        }
    }
 
    // Function to return the Flyer with the highest priority (present at the root)
    Flyer top()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // otherwise, return the top (first) element
            return A.at(0);        // or return A[0];
        }
        // catch and print the exception
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
        return Flyer("",0);
    }

    void increasePriority(int index, STATUS status, int time)
    {
        A[index].setStatus(status);
        A[index].setWaitTime(time);
        heapify_up(index);
        cout<<"After Heapify\n";
        getList();
    }

    bool deleteFlyer(int code)
    {
        if(!map.count(code)){
            cout<<"No flyer with confirmation code: "<<code<<endl;
            return false;
        } 
        int index =  map[code];
        increasePriority(index, SUPER, -1);

        pop();
        return true;
    }

    void getList()
    {
        for(auto i: map)
        {
            Flyer& f = A[i.second];
            cout<<"Name: "<<f.getName()<<"\tStatus: "<<f.getStatusString()<<endl;
            cout<<"Confirmation code:\t"<<i.first<<endl;
            cout<<"\n";

        }
        cout<<"\n";
    }

};

#endif