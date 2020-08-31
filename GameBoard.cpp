#include <iostream>

#include "GameBoard.h"

/*Class: GameBoard
* This Class is used for updating and printing the state of the game board.
*/
GameBoard::GameBoard(int rows, int cols)
{
    makeTriangleRows();
}
GameBoard::~GameBoard()
{
}
Tile **GameBoard::getMosaic()
{
    return *mosaic;
}

//adds tiles to the triangles.
void GameBoard::setTriangle(int sRow, Tile T, int amount, LinkedList *boxLid)
{
    int j = 0;
    int counter = 0;
    int g = 0;
    unsigned sizeCheck = sRow;
    int emptyCounter = 0;
    while (j < 5)
    {
        if (RGrid[sRow][j].equals(empty))
        {
            while (counter < amount)
            {
                RGrid[sRow].erase(RGrid[sRow].begin() + j);
                counter++;
            }
            ++emptyCounter;
        }
        ++j;
    }
    int sendToBroken = (amount - emptyCounter);
    //sends to broken if amount of tiles is greater than row size.
    if (RGrid[sRow].size() > sizeCheck)
    {
        while (g < sendToBroken)
        {
            if (brokenTiles.size() < 7)
            {
                brokenTiles.push_back(T);
            }
            else
            {
                boxLid->insertFront(new Tile(T));
            }
            ++g;
        }
    }
    RGrid[sRow].insert(RGrid[sRow].end(), amount, T);
}
// loadGame() calls this to load triangle from txt
void GameBoard::loadTriangle(int i, std::string line)
{
    RGrid[i].clear();
    int size = line.length();
    Tile *tmp = new Tile('.');
    for (int j = 0; j < size; ++j)
    {
        if (line.at(j) != ' ')
        {
            tmp->setColour(line.at(j));
            RGrid[i].push_back(*tmp);
        }
    }
}
// loadGame() call this to load mosaic from txt
void GameBoard::loadMosaic(int i, std::string line)
{
    int size = line.length();
    Tile *copy;
    for (int j = 0; j < size; ++j)
    {
        copy = new Tile(line.at(j));
        Tile *tmp = new Tile(*copy);
        mosaic[i][j] = tmp;
    }
}
// loadGame() calls this to load floor/broken tiles
void GameBoard::loadFloor(std::string line)
{
    if (line.at(0) != ' ')
    {
        int size = line.length();
        for (int i = 0; i < size; ++i)
        {
            brokenTiles.push_back(line.at(i));
        }
    }
}
// Prints out complete mosaic
std::string GameBoard::printBoardTemplate()
{
    std::string details;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            details += temp[i][j]->getColour();
            details += " ";
        }
        details += '\n';
    }
    return details;
}

// Next 3 methods help to build for saving gamestate. getBoardString() is for duplicate code
std::string GameBoard::getTriangleString()
{
    std::string details = "";
    int count = 4;
    int tmp = 4;
    for (int i = 0; i < 5; ++i)
    {
        while (count > 0)
        {
            details += " ";
            --count;
        }
        count = tmp - 1;
        --tmp;
        for (unsigned j = 0; j < RGrid[i].size(); ++j)
        {
            details += RGrid[i][j].getColour();
        }
        details += "\n";
    }
    return details;
}

std::string GameBoard::getMosaicString()
{
    std::string details = "";
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            details += mosaic[i][j]->getColour();
        }
        details += "\n";
    }
    return details;
}
// saves the current state of floor/brokenTiles
std::string GameBoard::getFloorString()
{
    std::string details = "";
    int size = brokenTiles.size();
    if (size == 0)
    {
        details += " ";
    }
    for (int i = 0; i < size; ++i)
    {
        details += brokenTiles[i].getColour();
    }
    return details;
}
//prints the game board state for each player.
void GameBoard::printGameBoard()
{
    int count = 5;
    int tmp = 5;
    for (int i = 0; i < 5; ++i)
    {
        std::cout << i + 1 << ":";
        while (count > 0)
        {
            std::cout << "  ";
            --count;
        }
        count = tmp - 1;
        --tmp;
        for (unsigned j = 0; j < RGrid[i].size(); ++j)
        {
            printWithColour(RGrid[i][j].getColour());
        }
        std::cout << "|| ";
        printMosaicRow(i);
        std::cout << std::endl;
    }
    std::cout << "Broken: ";
    for (unsigned i = 0; i < brokenTiles.size(); ++i)
    {
        printWithColour(brokenTiles[i].getColour());
    }
    std::cout << std::endl;
}
std::string GameBoard::printMosaicRow(int x)
{
    std::string details = "";
    details += printBoardRow(x, mosaic);
    return details;
}
// This method is private, and is for duplicate code
std::string GameBoard::printBoardRow(int x, Tile *b[5][5])
{
    std::string details = "";
    for (int i = 0; i < 5; ++i)
    {
        details += printWithColour(b[x][i]->getColour());
        details += " ";
    }
    return details;
}
std::vector<Tile> GameBoard::getSelectedRow(int Rownum)
{
    return RGrid[Rownum];
}
void GameBoard::setSelectedRow(std::vector<Tile> sRow, int Rownum)
{
    RGrid[Rownum] = sRow;
}
void GameBoard::makeTriangleRows()
{
    R1.push_back(*empty);
    for (int i = 0; i < 2; ++i)
    {
        R2.push_back(*empty);
    }
    for (int i = 0; i < 3; ++i)
    {
        R3.push_back(*empty);
    }
    for (int i = 0; i < 4; ++i)
    {
        R4.push_back(*empty);
    }
    for (int i = 0; i < 5; ++i)
    {
        R5.push_back(*empty);
    }
    RGrid.push_back(R1);
    RGrid.push_back(R2);
    RGrid.push_back(R3);
    RGrid.push_back(R4);
    RGrid.push_back(R5);
}
//sets the mosaic to the tile on the LHS row.
void GameBoard::triangleToMosaicMovement(LinkedList *boxLid)
{
    Tile *copyTile;
    for (int i = 0; i < 5; ++i)
    {
        // if row is full.
        if (RGrid[i][0].getColour() != '.')
        {
            copyTile = &RGrid[i][0];
            Tile *tileToAdd = new Tile(*copyTile);
            for (int j = 0; j < 5; ++j)
            {
                if (RGrid[i][0].equals(red) && temp[i][j] == red)
                {
                    mosaic[i][j] = tileToAdd;
                }
                if (RGrid[i][0].equals(yellow) && temp[i][j] == yellow)
                {
                    mosaic[i][j] = tileToAdd;
                }
                if (RGrid[i][0].equals(darkBlue) && temp[i][j] == darkBlue)
                {
                    mosaic[i][j] = tileToAdd;
                }
                if (RGrid[i][0].equals(lightBlue) && temp[i][j] == lightBlue)
                {
                    mosaic[i][j] = tileToAdd;
                }
                if (RGrid[i][0].equals(black) && temp[i][j] == black)
                {
                    mosaic[i][j] = tileToAdd;
                }
            }
            for (unsigned j = 1; j < RGrid[i].size(); ++j)
            {
                boxLid->insertFront(tileToAdd);
            }
        }
    }
    reMakeRow();
}
//clears the row
void GameBoard::reMakeRow()
{
    for (int i = 0; i < 5; ++i)
    {
        if (RGrid[i][0].getColour() != '.')
        {
            RGrid[i].clear();

            for (int g = 0; g < i + 1; ++g)
            {
                RGrid[i].push_back(*empty);
            }
        }
    }
}
//checks for a Full Row.
bool GameBoard::checkRHSFullRows(int i)
{
    bool fullRow = true;
    int g = 0;
    int tileCount = 0;
    while (g < 5)
    {
        if (mosaic[i][g]->getColour() != '.')
        {
            ++tileCount;
        }
        else
        {
            tileCount = 0;
        }
        ++g;
    }
    if (tileCount == 5)
    {
        fullRow = true;
    }
    else
    {
        fullRow = false;
    }
    return fullRow;
}
void GameBoard::printRows(int row)
{
    std::cout << row + 1 << ":";
    for (unsigned g = 0; g != 5 - RGrid[row].size(); ++g)
    {
        std::cout << " "
                  << " ";
    }
    for (unsigned j = 0; j < RGrid[row].size(); ++j)
    {
        printWithColour(RGrid[row][j].getColour());
    }
    std::cout << "|| ";
    for (int i = 0; i < 5; ++i)
    {
        printWithColour(mosaic[row][i]->getColour());
    }
    if (row == 5)
    {
        std::cout << "Broken: ";
        for (unsigned i = 0; i < brokenTiles.size(); ++i)
        {
            printWithColour(brokenTiles[i].getColour());
        }
        std::cout << std::endl;
    }
}
//broken tiles related
void GameBoard::FPtoBroken(Tile *tile)
{
    brokenTiles.push_back(*tile);
}
void GameBoard::clearBrokenTiles(LinkedList *boxLid)
{
    for (unsigned i = 0; i < brokenTiles.size(); ++i)
    {
        boxLid->insertFront(&brokenTiles.at(i));
        if (brokenTiles.at(i).getColour() != 'F')
        {
            brokenTiles.erase(brokenTiles.begin() + i);
        }
    }
}
void GameBoard::clearFPtile()
{
    brokenTiles.clear();
}
bool GameBoard::checkforFPtile()
{
    for (unsigned i = 0; i < brokenTiles.size(); ++i)
    {
        if (brokenTiles.at(i).getColour() == 'F')
        {
            return true;
        }
    }
    return false;
}
//scoring on the mosaic board.
int GameBoard::countMosaicPoints(int points)
{
    int tmpPoints = 0;  //total mosaic points
    int pointCombo = 0; //each tile and tiles togetehr points.
    int g = 0;
    int i = 0;
    int verticalCount = 0;
    while (i < 5)
    {
        while (g < 5)
        {
            //horizontal tiles for point counting
            if (mosaic[i][g] != empty)
            {
                pointCombo += 1;
            }
            //checks for full row
            if (checkRHSFullRows(i) == true)
            {
                tmpPoints += 2;
            }
            //checks vertical tiles together
            if (mosaic[g][i] != empty)
            {
                pointCombo += 1;
                ++verticalCount;
            }
            //checks a full column of vertical tiles.
            if (mosaic[g][i] != empty && verticalCount == 5)
            {
                tmpPoints += 7;
            }
            else
            {
                tmpPoints += pointCombo;
                pointCombo = 0;
                verticalCount = 0;
            }
            ++g;
        }
        ++i;
    }
    return tmpPoints;
}
//scoring for broken tiles.
int GameBoard::countBrokenTilesPoints(int points)
{
    for (unsigned i = 0; i < brokenTiles.size(); ++i)
    {
        if (i == 0)
        {
            --points;
        }
        if (i == 1)
        {
            --points;
        }
        if (i == 2)
        {
            points -= 2;
        }
        if (i == 3)
        {
            points -= 2;
        }
        if (i == 4)
        {
            points -= 2;
        }
        if (i == 5)
        {
            points -= 3;
        }
        if (i == 6)
        {
            points -= 3;
        }
    }
    return points;
}
Colour GameBoard::printWithColour(Colour c)
{
    if (c == 'R')
    {
        std::cout << "\u001b[31m" << c << "\u001b[0m"
                  << " ";
    }
    if (c == 'Y')
    {
        std::cout << "\u001b[33m" << c << "\u001b[0m"
                  << " ";
    }
    if (c == 'B')
    {
        std::cout << "\u001b[34m" << c << "\u001b[0m"
                  << " ";
    }
    if (c == 'L')
    {
        std::cout << "\u001b[36m" << c << "\u001b[0m"
                  << " ";
    }
    if (c == 'U')
    {
        std::cout << "\u001b[30m" << c << "\u001b[0m"
                  << " ";
    }
    if (c == '.')
    {
        std::cout << c << " ";
    }
    if (c == 'F')
    {
        std::cout << c << " ";
    }
    return c;
}
