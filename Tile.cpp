#include <iostream>

#include "Tile.h"

Tile::Tile(Colour colour) :
  colour(colour)
  {
    
  }
  

Tile::~Tile() {
  colour = '0';
}

std::string Tile::toString() {
  std::string tileString = "";
  if (colour == '0') {
    tileString = "  ";
  }
  else {
    tileString += colour;
  }
  return tileString;
}

bool Tile::equals(Tile* tile) {
  bool equals = false;
  if (colour == tile->getColour() ) {
    equals = true;
  }
  return equals;
}
void Tile::setColour(Colour colour){
  this->colour = colour;
}
Colour Tile::getColour() {
  return colour;
}
