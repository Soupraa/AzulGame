#include <string>

#ifndef RKB_PLAYER_h
#define RKB_PLAYER_h
#include "GameBoard.h"
class GameBoard;

class Player
{
public:
    Player(std::string name, GameBoard *g, int score);
    Player();

    ~Player();

    std::string getName();
    int getScore();

    void setName(std::string name);
    void setScore(int i);
    void setStringScore(std::string i);
    void setGameBoard(GameBoard *g);
    GameBoard *getGameBoard();

private:
    std::string name;
    int score;
    GameBoard *g;
};
#endif