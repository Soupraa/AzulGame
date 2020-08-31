#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#ifndef MAIN_CPP
#define MAIN_CPP
#include "Menu.h"
#include "GameManager.h"

void newGame();
void loadGame();
void saveGame();
bool playGame();
int selectCentralFactory(int fnum);
std::string validStrSize();
void checkForCommands(int argc, char **argv);
void instructions();
bool checkForGameEnd(int player, int pastPlayer);
Menu *m = new Menu();
GameManager *gm = new GameManager();
int seed;
bool seedEntered;

int main(int argc, char **argv)
{
    std::string choice;

    checkForCommands(argc, argv);
    while (choice != "5")
    {
        std::cout << m->displayMainMenu();
        std::cin >> choice;
        if (choice == "1")
        {
            std::cout << "Starting new Game\n"
                      << std::endl;
            newGame();
        }
        else if (choice == "2")
        {
            gm->loadGame();
            playGame();
        }
        else if (choice == "3")
        {
            std::cout << m->displayStudentInfo();
        }
        else if (choice == "4" || choice == "help")
        {
            instructions();
        }
        else
        {
            return EXIT_SUCCESS;
        }
    }
}

void newGame()
{
    // 1 Game manager for each new game.
    //player making function.
    gm->makePlayer();
    //tileBag to FActories.
    gm->tileBagToFactory(seed);
    std::cout << "\nLet's Play! \u2694 \n"
              << std::endl;
    playGame();
}

bool playGame()
{
    bool end = false;
    char choice;
    int fnum;
    Colour col;
    int sRow;
    bool invalidturn = true;
    int pastPlayer = 0;
    int i = 0; // player turn.
    int facChoice = 0;
    std::cout << "=== START ROUND ===" << std::endl;
    while (end != true)
    {
        while (i < gm->getPlayers())
        {
            //if factories are empty
            if (gm->accessFactories()->checkFactories() == true)
            {
                std::cout << "=== ENDs OF ROUND ===" << std::endl;
                i = gm->setFirstPlayer();
                gm->rePopulateFactories();
                for (int i = 0; i < gm->getPlayers(); ++i)
                {
                    // checks for full row, if full row game end.(triangle to mosaic).
                    if (checkForGameEnd(i, pastPlayer) == true)
                    {
                        end = true;
                        return end;
                    }
                    pastPlayer = i;
                }
                std::cout << "To  save  and  return  to   menu  enter:  's' \n"
                          << "To return to  menu without saving enter:  'm' \n"
                          << "To continue playing enter any other key:"
                          << std::endl;
                std::cin >> choice;
                if (choice == 's')
                {
                    end = true;
                    gm->saveGame();
                    return end;
                }
                else if (choice == 'm')
                {
                    end = true;
                    return end;
                }
            }
            // i = gm->setFirstPlayer(i);
            std::cout << "TURN FOR PLAYER: " << gm->getPlayer(i)->getName() << std::endl;
            // F->getFactories();
            std::cout << "Current score: " << gm->getPlayer(i)->getScore() << std::endl;
            gm->accessFactories()->getFactories();
            std::cout << "Mosaic for " << gm->getPlayer(i)->getName() << ":" << std::endl;
            //get gameboard for player(i)
            gm->getPlayer(i)->getGameBoard()->printGameBoard();

            while (invalidturn)
            {
                std::string s = validStrSize();
                if (s == "save")
                {
                    end = true;
                    return end;
                }
                else if (s == "exit")
                {
                    end = true;
                    return end;
                }
                std::vector<Tile> tmp;
                std::vector<Tile> tmpRow;
                fnum = stoi(s.substr(0));
                col = s.at(1);
                sRow = stoi(s.substr(2));

                tmp = gm->accessFactories()->getSelectedFactory(fnum);
                tmpRow = gm->getPlayer(i)->getGameBoard()->getSelectedRow(sRow - 1);
                if (gm->validFactoryChoice(fnum, tmp, col) == false || gm->validRowChoice(col, tmpRow, sRow) == false || std::cin.eof() || !std::cin.good())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Turn unsuccessful. \u2639" << std::endl;
                    invalidturn = true;
                }
                else
                {
                    //when there are 2 centre factories.
                    if (gm->accessFactories()->getAmountofFac() == 7)
                    {
                        if (fnum > 1)
                        {
                            //return central fac choice.
                            facChoice = selectCentralFactory(fnum);
                            gm->factoryToTriangle(fnum, col, sRow, i, facChoice);
                        }
                        else
                        {
                            gm->factoryToTriangle(fnum, col, sRow, i, fnum);
                        }

                        std::cout << "Turn successful. \u263A " << std::endl;
                        invalidturn = false;
                    }
                    else
                    {
                        gm->factoryToTriangle(fnum, col, sRow, i, 0);
                        std::cout << "Turn successful." << std::endl;
                        invalidturn = false;
                    }
                }
            }
            invalidturn = true;
            ++i;
        }
        i = 0;
    }
    return playGame();
}
int selectCentralFactory(int fnum)
{
    int choice;
    bool invalidAmount = true;
    std::cout << "0 or 1 for excess tile location:" << std::endl;
    while (invalidAmount)
    {
        std::cout << "> Choice:";
        std::cin >> choice;

        if (choice >= 0 && choice < 2 && std::cin.good())
        {
            invalidAmount = false;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid central factory. \u2639" << std::endl;
            invalidAmount = true;
        }
    }
    return choice;
}
std::string validStrSize()
{
    std::string s;
    bool invalidSize = true;
    while (invalidSize)
    {
        std::cout << "> Turn:";
        std::cin >> s;
        if (s == "help")
        {
            std::cout << "Avaliable commands: " << std::endl;
            std::cout << "turn [factory num] [Tile Colour] [storage Row]" << std::endl;
            std::cout << "save [file name] " << std::endl;
            std::cout << "boards [displays all boards] " << std::endl;
            std::cout << "exit [exits to main menu]" << std::endl;
        }
        else if (s == "save")
        {
            gm->saveGame();
            invalidSize = false;
            return s;
        }
        else if (s == "exit")
        {
            return s;
        }
        else if (s == "boards"){
            gm->printBoards();
        }
        else if (s.size() <= 3 || s.size() < 3)
        {
            invalidSize = false;
        }
        else
        {
            std::cout << "Invalid input. \u2639" << std::endl;
            std::cin.clear();
            invalidSize = true;
        }
    }
    return s;
}
bool checkForGameEnd(int player, int pastPlayer)
{
    bool gameEnd = false;
    gm->triangleToMosaic(player);

    if (gm->checkGameEnd(player) == true)
    {
        std::cout << "=== GAME OVER ===" << std::endl;
        if (gm->getPlayer(player)->getScore() > gm->getPlayer(pastPlayer)->getScore())
        {
            std::cout << "Winner: " << gm->getPlayer(player)->getName() << "\u2655" << std::endl;
            std::cout << "Score: " << gm->getPlayer(player)->getScore() << std::endl;
        }
        else
        {
            std::cout << "Winner: " << gm->getPlayer(pastPlayer)->getName() << "\u2655" << std::endl;
            std::cout << "Score: " << gm->getPlayer(pastPlayer)->getScore() << std::endl;
        }
        gameEnd = true;
        return gameEnd;
    }
    return gameEnd;
}

void checkForCommands(int argc, char **argv)
{
    if (argc > 1)
    {
        std::string seedString = argv[1];
        try
        {
            seed = std::stoi(seedString);
            seedEntered = true;
            std::cout << "Seed of " << seed << " was successfully entered \u2618" << std::endl;
        }
        catch (const std::out_of_range &e)
        {
            std::cout << "Seed entered was not in integer range, discarding seed" << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cout << "Seed entered was not a number, discarding seed" << std::endl;
        }
    }
}
void instructions()
{
    std::cout << "Welcome to Azul.\n"
              << "When you first start a new game you will be asked to enter your name, and your opponents name.\n"
              << "From here each player will be assigned a brand new game board that you'll need to fill with tiles.\n"
              << "Pick from the randomised Factories whenever a prompt of '> Turn: ' appears.\n"
              << "To complete a turn enter the Factory number -> followed by the Tile letter -> followed by the row number.\n"
              << "Then enter the row in the left side Triangle that you'd like to place the Tile.\n"
              << "Next it will be player 2's turn and they will complete their turn in the same way.\n"
              << "Select if you'd like to save and exit, exit without saving or continue playing the game when the prompt appears.\n"
              << "If you opt to save and exit you will be asked to enter a name for the file you'd like to save. Remember this name.\n"
              << "To load a game simply enter the correct filename and it will begin where you left off.\n"
              << "Throughout the game '>' indicate that input is required to continue.\n"
              << "Score points by filling the right side mosaic with tiles. More points are earned by filling it with tiles beside each other.\n"
              << "GOOD LUCK."
              << std::endl;
}
#endif
