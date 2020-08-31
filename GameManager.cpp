#include <iostream>

#include "GameManager.h"

/* Class: GameManager
* This Class handles most of the game logic including valid input.
*/
GameManager::GameManager()
{
    F = new Factories();
    T = new TileBag();
    makeStartPlayers();
}

GameManager::~GameManager()
{
}
TileBag *GameManager::getTileBag()
{
    return T;
}
// Moves tile from tileBag to factory
void GameManager::tileBagToFactory(int seed)
{
    //tile bag initialisations
    T->~TileBag();
    T = new TileBag();
    T->fillTileBag();
    //factory initilsations
    F->~Factories();       // clears factories
    F = new Factories();   // makes new ones
    setAmountCFactories(); // makes new central facs

    //populate data sturctures
    getTileBag()->shuffleBag(seed);
    F->populateFactories(T);
}
// repopulates tile bag
void GameManager::rePopulateFactories()
{
    F->populateFactories(T);
}
// Moves tile from factory to triangle
void GameManager::factoryToTriangle(int fnum, Colour c, int sRow, int player, int CF)
{
    std::vector<Tile> tmp;
    std::vector<Tile> centralfac;
    int amount = 0;
    // std::cout << fnum << "  " << CF << std::endl;
    tmp = F->getSelectedFactory(fnum);
    centralfac = F->getSelectedFactory(CF);
    for (int i = tmp.size() - 1; i >= 0; --i)
    {
        if (tmp[i].getColour() == c)
        {
            ++amount;
            tmp.erase(tmp.begin() + i);
        }
        else
        {
            //when centre fac are selected.
            if (fnum == CF)
            {
                //pushes centre tiles that are NOT selected to boxlid.
                if (tmp[i].getColour() != 'F')
                {
                    boxLid->insertFront(new Tile(tmp[i]));
                }
                else
                {
                    //tile is F push to broken.
                    Tile *newFP = new Tile(tmp[i]);
                    getPlayer(player)->getGameBoard()->FPtoBroken(newFP);
                    //removes all F in centre if 2 exist.
                    F->eraseFacF();
                }
            }
            //clears factory and moves tiles to centre fac.
            tmp.erase(tmp.begin() + i);
            centralfac.push_back(tmp[i].getColour());
            //sets tmp fac to actual fac (update the factories).
            F->setSelectedFactory(centralfac, CF);
        }
        F->setSelectedFactory(tmp, fnum);
    }
    getPlayer(player)->getGameBoard()->setTriangle(sRow - 1, c, amount, boxLid);
}
// moves tiles from triangle to mosaic with a few additions.
void GameManager::triangleToMosaic(int player)
{
    int currentScore;
    int updatedScore;
    //moves tiles from LHS TO RHS
    getPlayer(player)->getGameBoard()->triangleToMosaicMovement(boxLid);
    //scoring the broken tiles
    currentScore = getPlayer(player)->getScore();
    getPlayer(player)->setScore(getPlayer(player)->getGameBoard()->countBrokenTilesPoints(currentScore));
    //scoring the mosaic tiles
    updatedScore = getPlayer(player)->getScore();
    getPlayer(player)->setScore(getPlayer(player)->getGameBoard()->countMosaicPoints(updatedScore));
    //clears the broken tiles.
    getPlayer(player)->getGameBoard()->clearBrokenTiles(boxLid);
}
int GameManager::setFirstPlayer()
{
    // boxLid->display();
    int playerNum = 0;
    for (int i = 0; i < getPlayers(); ++i)
    {
        if (getPlayer(i)->getGameBoard()->checkforFPtile() == true)
        {
            //removes F tile from broken.
            getPlayer(i)->getGameBoard()->clearFPtile();
            playerNum = i;
            return playerNum;
        }
    }
    return playerNum;
}
void GameManager::boxLidtoTileBag()
{
    if (T->isEmpty() == true)
    {
        for (int i = 0; i < boxLid->getSize(); ++i)
        {
            T->reFillBag(boxLid->getFront());
            boxLid->deleteFront();
        }
    }
}
void GameManager::saveGame()
{
    std::string fileName;
    std::cout << "Enter file name to save to: " << std::endl;
    std::cin >> fileName;
    std::ofstream myfile("testCases/" + fileName + ".txt");
    if (myfile.is_open())
    {
        myfile << "# amount of Players" << std::endl;
        myfile << getPlayers() << std::endl;
        myfile << "# tile bag" << std::endl;
        myfile << T->getBagSave() << std::endl;
        myfile << "# lid" << std::endl;
        myfile << boxLid->getSavedBoxLid() << std::endl;
        // myfile <<"_"<<std::endl;
        // myfile << "# Central Factories" << std::endl;
        // myfile << F->getSaveCentralFactory() << std::endl;
        myfile << "# Factories amount" << std::endl;
        myfile << F->getAmountofFac() << std::endl;
        myfile << "# Factories" << std::endl;
        myfile << F->getSaveFactories();

        // random number seed goes here
        myfile << "# random number seed" << std::endl;
        myfile << T->getSeed();
        myfile << std::endl;

        for (int z = 0; z < getPlayers(); ++z)
        {
            myfile << "# Player " << z + 1 << " Name" << std::endl;
            myfile << players[z]->getName() << std::endl;
            myfile << "# Player " << z + 1 << " Score" << std::endl;
            myfile << std::to_string(players[z]->getScore()) << std::endl;
            myfile << "# Player " << z + 1 << " Triangle" << std::endl;
            myfile << players[z]->getGameBoard()->getTriangleString();
            myfile << "# Player " << z + 1 << " Mosaic" << std::endl;
            myfile << players[z]->getGameBoard()->getMosaicString();
            myfile << "# Player " << z + 1 << " Floor/brokenTiles" << std::endl;
            myfile << players[z]->getGameBoard()->getFloorString() << std::endl;
        }
        myfile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;
}

void GameManager::loadGame()
{
    bool loading = true;
    std::string fileName = "";
    std::string line;
    std::ifstream myfile(fileName + ".txt");
    while (loading)
    {
        std::cout << "Enter file name to load: \n> ";
        std::cin >> fileName;
        std::ifstream myfile("testCases/" + fileName + ".txt");
        if (myfile.good())
        {
            loading = false;
        }
    }
    myfile.open("testCases/" + fileName + ".txt");
    if (myfile.is_open())
    {
        //set amount of players
        line = getNewLine(myfile);
        setPlayers(stoi(line.substr(0)));

        for (int i = 0; i < getPlayers(); ++i)
        {
            delete (players[i]);
            players[i] = new Player();
            players[i]->setGameBoard(new GameBoard(5, 5));
        }

        //load tilebag
        T->~TileBag();
        line = getNewLine(myfile);
        T = new TileBag();
        T->setTileBag(line);
        std::cout << "TileBag loaded" << std::endl;
        //load boxlid
        line = getNewLine(myfile);
        for (unsigned i = 0; i < line.size(); ++i)
        {
            boxLid->setBoxLidforLoad(line, i);
        }
        //load amount fac
        F->~Factories();     // clears factories
        F = new Factories(); // makes new ones
        line = getNewLine(myfile);
        F->setAmountFac(stoi(line.substr(0))); // sets amount of facs

        //load factories
        line = getNewLine(myfile);
        for (int i = 0; i < F->getAmountofFac(); ++i)
        {
            while (line.at(0) == ' ')
            {
                line = getNewLine(myfile);
                F->clearFactory(i);
                ++i;
            }
            if (i < F->getAmountofFac())
            {
                F->setFactoriesForLoad(i, line);
                line = getNewLine(myfile);
            }
        }

        std::cout << "Factories loaded" << std::endl;
        // Random Seed for TileBag
        int seed = stoi(line);
        T->shuffleBag(seed);

        //player gameboard info(score, mosaic status .. etc)
        line = getNewLine(myfile);
        for (int z = 0; z < getPlayers(); ++z)
        {
            players[z]->setName(line);
            std::cout << "PLAYER " << z + 1 << " " << players[z]->getName() << " .. loading..." << std::endl;
            line = getNewLine(myfile);
            players[z]->setStringScore(line);
            line = getNewLine(myfile);
            for (int i = 0; i < 5; ++i)
            {
                players[z]->getGameBoard()->loadTriangle(i, line);
                line = getNewLine(myfile);
            }
            for (int i = 0; i < 5; ++i)
            {
                players[z]->getGameBoard()->loadMosaic(i, line);
                line = getNewLine(myfile);
            }
            players[z]->getGameBoard()->loadFloor(line);
            line = getNewLine(myfile);
        }
        std::cout << "Game Loaded" << std::endl;
        myfile.close();
    }
    else
        std::cout << "Unable to open file" << std::endl;
}
std::string GameManager::getNewLine(std::ifstream &f)
{
    std::string line = "";
    getline(f, line);
    if (!line.empty())
    {
        while (line.at(0) == '#')
        {
            getline(f, line);
        }
    }
    return line;
}
//amount of factories.
void GameManager::setAmountCFactories()
{
    int amount;
    bool invalidAmount = true;
    std::cout << "Enter 1 or 2 central Factories: " << std::endl;
    while (invalidAmount)
    {
        std::cout << "> Amount:";
        std::cin >> amount;
        if (amount > 0 && amount < 3 && std::cin.good())
        {
            F->centreFacAmount(amount);
            invalidAmount = false;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\u26CC Invalid input, enter a number between 1-2." << std::endl;
            invalidAmount = true;
        }
    }
}
Factories *GameManager::accessFactories()
{
    return F;
}
//validates factory choice.
bool GameManager::validFactoryChoice(int fnum, std::vector<Tile> factory, Colour c)
{
    bool validFac = true;
    if (fnum > 5 || fnum < 0)
    {
        validFac = false;
    }
    if (factory.empty())
    {
        validFac = false;
    }
    if (validFactoryColour(c, factory) == true)
    {
        validFac = false;
    }
    else
    {
        validFac = true;
    }

    return validFac;
}
//assists with validating factory choice checks if colour in factoy exists.
bool GameManager::validFactoryColour(Colour c, std::vector<Tile> fac)
{
    bool invalidColour = true;
    unsigned i = 0;
    while (i < fac.size())
    {
        if (c == fac[i].getColour() && c != 'F')
        {
            invalidColour = false;
            return invalidColour;
        }
        else
        {
            invalidColour = true;
        }
        i++;
    }
    return invalidColour;
}
//validates if inserting tiles in a row is possible.
bool GameManager::validRowChoice(Colour c, std::vector<Tile> row, int sRow)
{
    bool validRow = true;
    unsigned int j = 0;
    while (validRow && j < row.size())
    {
        //validates row number selected.
        if (sRow > 5 || sRow < 1)
        {
            validRow = false;
        }
        //checks if row is full.
        if (row[0].getColour() != '.')
        {
            validRow = false;
            return validRow;
        }
        //checks if a tile already exists in the row.
        if (row[j].getColour() != c && row[j].getColour() != '.')
        {
            validRow = false;
        }
        else
        {
            validRow = true;
        }
        j++;
    }
    return validRow;
}
bool GameManager::checkGameEnd(int player)
{
    bool endGame = false;
    int i = 0;
    while (!endGame && i < 5)
    {
        endGame = getPlayer(player)->getGameBoard()->checkRHSFullRows(i);
        ++i;
    }
    return endGame;
}
bool GameManager::valiadatePlayerAmount(int amount)
{
    bool validAmount = false;
    if (amount >= 2 && amount <= 4)
    {
        validAmount = true;
    }
    return validAmount;
}
void GameManager::makePlayer()
{
    int num = 1;
    int playerCount = 0;
    int score = 0;
    int playerNum;
    bool invalidAmount = true;
    std::cout << "Enter Amount of Players: " << std::endl;
    while (invalidAmount)
    {
        std::cout << "> Amount:";
        std::cin >> playerNum;
        if (valiadatePlayerAmount(playerNum) == true && std::cin.good())
        {
            setPlayers(playerNum);
            while (num != playerNum + 1)
            {
                std::string name;
                std::cout << "Enter a name for player " << num << std::endl
                          << "> ";
                std::cin >> name;
                players[playerCount++] = new Player(name, new GameBoard(5, 5), score);
                ++num;
            }
            invalidAmount = false;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\u26CC Invalid input, enter a number between 2-4." << std::endl;
            invalidAmount = true;
        }
    }
}
Player *GameManager::getPlayer(int i)
{
    return players[i];
}
void GameManager::makeStartPlayers()
{
    for (int i = 1; i < getPlayers(); ++i)
    {
        Player *p = new Player();
        players[i] = p;
    }
}

void GameManager::setPlayers(int inputPlayer)
{
    player = inputPlayer;
}
int GameManager::getPlayers()
{
    return player;
}
void GameManager::printBoards()
{
    for (int i = 0; i < getPlayers(); ++i)
    {
        std::cout << "Board for: " << players[i]->getName();
        std::cout << "\t\t";
    }
    std::cout << std::endl;

    for (int k = 0; k < 5; ++k)
    {
        for (int i = 0; i < getPlayers(); ++i)
        {
            players[i]->getGameBoard()->printRows(k);
            std::cout<<"\t";
        }
        std::cout<<std::endl;
    }
    

}
