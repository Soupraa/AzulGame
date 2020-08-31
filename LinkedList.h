#ifndef RKB_BOXLID_H
#define RKB_BOXLID_H
#include<string>
#include<iostream>
#include "Factories.h"

// class Node

class LinkedList{
public: 
    LinkedList();
    ~LinkedList();
    void insertAfter(Tile* tile);
    void insertFront(Tile* tile);
    void insertEnd(Tile* tile);

    Tile* getBack();//done
    Tile* getFront();//done

    void deleteBack();//done
    void deleteFront();//done
    int getSize();

    void display();

    std::string getSavedBoxLid();
    void setBoxLidforLoad(std::string line, int i);


    // void addTile(Tile* tile);
 
 private:
    Node* head;
    Node* tail;
    Node* prev_node;
    int size;

    // Node* getNode(int index);

};
#endif