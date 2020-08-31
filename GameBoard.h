#include <string>

#ifndef RKB_GAMEBOARD_H
#define RKB_GAMEBOARD_H
#include "LinkedList.h"

class GameBoard
{
public:
    GameBoard(int rows, int cols);
    ~GameBoard();

    Tile** getMosaic();

    // for loading game
    void setTriangle(int i, Tile T, int amount, LinkedList* boxLid);
    void loadTriangle(int i, std::string line);
    void loadMosaic(int i, std::string line);
    void loadFloor(std::string line);

    // for saving game
    std::string getTriangleString();
    std::string getMosaicString();
    std::string getFloorString();

    std::string printBoardTemplate();

    void printGameBoard();
    void makeTriangleRows();

    std::string printTriangleRow(int x);
    std::string printMosaicRow(int x);
    std::vector<Tile> getSelectedRow(int Rownum);
    void setSelectedRow(std::vector<Tile> sRow, int Rownum);
    
    void triangleToMosaicMovement(LinkedList* boxLid);
    void setMosaicRow(Tile* b[5][5]);
    void reMakeRow();


    void clearBrokenTiles(LinkedList* boxLid);
    void clearFPtile();
    void FPtoBroken(Tile* FP);
    bool checkforFPtile();

    bool checkRHSFullRows(int i);
    void printRows(int row);
    //scoring methods
    int countBrokenTilesPoints(int points);
    int countMosaicPoints(int points);

    //colour printing
    Colour printWithColour(Colour c);


private:
    std::string printBoardRow(int x, Tile* b[5][5]);
    // std::string getBoardString(Tile *b[5][5]);

    Tile* red = new Tile('R');
    Tile* yellow = new Tile('Y');
    Tile* darkBlue = new Tile('B');
    Tile* lightBlue = new Tile('L');
    Tile* black = new Tile('U');
    Tile* empty = new Tile('.');


    //for mosaic? 
    Tile* mosaic[5][5] = {
        {empty, empty, empty, empty, empty}, 
        {empty, empty, empty, empty, empty}, 
        {empty, empty, empty, empty, empty}, 
        {empty, empty, empty, empty, empty}, 
        {empty, empty, empty, empty, empty}
    };
    // Template tiles for the 2d temp array
    
    // template mosaic board for moving tiles from triangle to mosaic
    Tile* temp[5][5] = {
    {darkBlue, yellow, red, black, lightBlue}, 
    {lightBlue, darkBlue, yellow, red, black}, 
    {black, lightBlue, darkBlue, yellow, red}, 
    {red, black, lightBlue, darkBlue, yellow}, 
    {yellow, red, black, lightBlue, darkBlue}};

    // Triangle made up of vectors for each row
    std::vector<Tile> R1;
    std::vector<Tile> R2;
    std::vector<Tile> R3;
    std::vector<Tile> R4;
    std::vector<Tile> R5;
    std::vector<std::vector<Tile>> RGrid;

    std::vector<Tile> brokenTiles;
};
#endif /* RKB_GAMEBOARD_H */