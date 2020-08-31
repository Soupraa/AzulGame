#include <vector>
#ifndef RKB_TILE_h
#define RKB_TILE_h
#include "Node.h"


class TileBag{
    public:
    TileBag();
    ~TileBag();
    void fillTileBag();
    std::vector<Tile> shuffleBag(int seed);
    Tile getRandomTile();
    int getSeed();
    bool isEmpty();

    std::string getBagSave();
    void setTileBag(std::string line);
    void reFillBag(Tile* tile);
    
    private:
    // char colour;
    // Tile* T = new Tile(colour);
    Tile* red = new Tile('R');
    Tile* yellow = new Tile('Y');
    Tile* darkBlue = new Tile('B');
    Tile* lightBlue = new Tile('L');
    Tile* black = new Tile('U');
    std::vector<Tile> tileBag;

    int randomSeed;
};
#endif