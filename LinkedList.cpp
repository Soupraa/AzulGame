#include "LinkedList.h"

LinkedList::LinkedList()
{
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

LinkedList::~LinkedList()
{
}
//insert tile at front if list
void LinkedList::insertFront(Tile *tile)
{
  //new node is head since added to front.
  Node *newNode = new Node(tile, head);

  newNode->next = head;
  newNode->prev = nullptr;

  if (head != nullptr)
  {
    head->prev = newNode;
  }
  head = newNode;
  ++size;
}
/* Given a node as prev_node, insert a new node after the given node */
void LinkedList::insertAfter(Tile *tile)
{
  if (prev_node == nullptr)
  {
    //prev node is required.
    return;
  }
  Node *newNode = new Node(tile, prev_node);
  //set next of new node to next of prev node.
  newNode->next = prev_node->next;
  //set next of prev node to new Node.
  prev_node->next = newNode;
  //set prev of new node to prev node.
  newNode->prev = prev_node;
  //set prev of newNode's next to newNode.
  if (newNode->next != nullptr)
  {
    newNode->next->prev = newNode;
  }
  ++size;
}
//insert a node at the end of a linkedlist
void LinkedList::insertEnd(Tile *tile)
{
  tail = head;

  Node *newNode = new Node(tile, tail);

  newNode->next = nullptr;

  /*checks if list is empty, if yes make new Node*/
  if (head == nullptr)
  {
    newNode->prev = nullptr;
    head = newNode;
    return;
  }
  //else traverse list to go to last.
  while (tail->next != nullptr)
  {
    tail = tail->next;
  }
  tail->next = newNode;

  newNode->prev = tail;
  ++size;
}

Tile *LinkedList::getBack()
{
  return tail->tile;
}

Tile *LinkedList::getFront()
{
  return head->tile;
}

void LinkedList::deleteBack()
{
  if (tail == nullptr)
  {
    return;
  }
  Node *del = tail;

  tail = tail->prev;

  tail->next = nullptr;

  delete (del);
  --size;
}

void LinkedList::deleteFront()
{
  if (head == nullptr)
  {
    return;
  }
  Node *del = head;

  head = head->next;

  head->prev = nullptr;

  delete (del);
  --size;
}

int LinkedList::getSize()
{
  return size;
}
void LinkedList::display()
{
  Node *ptr;
  ptr = head;
  while (ptr != NULL)
  {
    std::cout << ptr->tile->getColour() << " ";
    ptr = ptr->next;
  }
}
std::string LinkedList::getSavedBoxLid()
{
  std::string details = "";
  Node *ptr;
  ptr = head;
  if (head == nullptr)
  {
    details += "_";
  }
  else
  {
    while (ptr != NULL)
    {
      details += ptr->tile->getColour();
      ptr = ptr->next;
    }
  }
  return details;
}
void LinkedList::setBoxLidforLoad(std::string line, int i)
{
  int size = line.size();
  for (int i = 0; i < size; ++i)
  {
    Tile c = line.at(i);
    insertFront(&c);
  }
}
