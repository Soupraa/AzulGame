#ifndef RKB_GAMEMANAGER_H
#define RKB_GAMEMANAGER_H
#include <fstream>
#include <cstring>
#include <algorithm>
#include "Player.h"
// #include "LinkedList.h"


class GameManager
{
public:
    GameManager();
    ~GameManager();

    TileBag* getTileBag();
    
    void saveGame();
    void loadGame();

    //movement methods.
    void tileBagToFactory(int seed);
    void factoryToTriangle(int fnum, Colour c, int sRow, int player, int centralFac);
    void triangleToMosaic(int player);
    void boxLidtoTileBag();
    
    //accessing data structures.
    Factories* accessFactories();
    void makePlayer();
    Player* getPlayer(int i);

    //validation methods
    bool validFactoryChoice(int fnum, std::vector<Tile> factory, Colour c);
    bool validFactoryColour(Colour c, std::vector<Tile> fac);
    bool validRowChoice(Colour c,std::vector<Tile> row,int sRow);
    bool checkGameEnd(int player);
    bool valiadatePlayerAmount(int amount);

    //refilling the factories
    void setAmountCFactories();
    void rePopulateFactories();

    //player related
    int setFirstPlayer();
    void setPlayers(int inputPlayer); //setting amount of players
    int getPlayers();

    void printBoards();
    

private:
    Factories* F;
    TileBag* T;
    Tile* CT;
    LinkedList* boxLid = new LinkedList();
    int player;
    Player* players[4];
    std::string getNewLine(std::ifstream& f);
    void makeStartPlayers();
};
#endif