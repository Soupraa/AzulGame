#ifndef RKB_NODE_h
#include "Tile.h"
#define RKB_Node_h

class Node
{
public:
    Node(Tile *tile, Node *next);
    ~Node();

    Tile* tile; // data
    Node* next; // next
    Node* prev; // prev
};

#endif