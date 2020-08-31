#include <string>

#define RKB_TILE_H

// Define a Colour type
typedef char Colour;


class Tile {
public:
  
  Tile(Colour colour);
  ~Tile();
  std::string toString();
  bool equals(Tile* tile);
  void setColour(Colour colour);
  Colour getColour();
  
  private:
  Colour colour;
};

