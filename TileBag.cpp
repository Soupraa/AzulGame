#include "TileBag.h"
#include <iostream>
#include <algorithm>
#include <random>
TileBag::TileBag()
{
}
TileBag::~TileBag()
{
    tileBag.clear();
}
void TileBag::fillTileBag()
{
    //push 20 of each tile into the vector
    for (int i = 0; i < 20; ++i)
    {
        tileBag.push_back(red->getColour());
        tileBag.push_back(yellow->getColour());
        tileBag.push_back(darkBlue->getColour());
        tileBag.push_back(lightBlue->getColour());
        tileBag.push_back(black->getColour());
    }
}
//get a random tile.
std::vector<Tile> TileBag::shuffleBag(int seed)
{
    randomSeed = seed;
    std::default_random_engine engine(seed);
    std::shuffle(std::begin(tileBag), std::end(tileBag), engine);
    // srand(time(0));
    // std::random_shuffle(std::begin(tileBag),std::end(tileBag));
    return tileBag;
}
//returns a copy of the front tile and erases the original copy
Tile TileBag::getRandomTile()
{
    Tile tmp = tileBag.front();
    tileBag.erase(tileBag.begin());
    return tmp;
}
int TileBag::getSeed()
{
    return randomSeed;
}
std::string TileBag::getBagSave()
{
    std::string details = "";
    int size = tileBag.size();
    for (int i = 0; i < size; ++i)
    {
        details += tileBag[i].getColour();
    }
    if (size == 0)
    {
        details = " ";
    }
    return details;
}
void TileBag::setTileBag(std::string line)
{
    int size = line.size();
    tileBag.clear();
    for (int i = 0; i < size; ++i)
    {
        tileBag.push_back(line.at(i));
    }
}
void TileBag::reFillBag(Tile *tile)
{
    tileBag.push_back(*tile);
}
bool TileBag::isEmpty()
{
    if (tileBag.empty())
    {
        return true;
    }
    return false;
}