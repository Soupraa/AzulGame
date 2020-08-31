#include "Node.h"


Node::Node(Tile* tile,Node* next)
{
  this->tile = tile;
  this->next = next;
}
Node::~Node(){

}

// Node::Node(Tile* tile, Node* next,Node* pre) :
//   tile(tile),
//   pre(pre),
//   next(next)
// {
// }
// Tile* Node::getTile(){
//   return tile;
// }
