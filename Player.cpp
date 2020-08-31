#include "Player.h"

Player::Player(std::string name, GameBoard* g, int score)
{
    this->name = name;
    this->g = g;
    this->score = score;
}
Player::Player()
{    
}
Player::~Player()
{
}
std::string Player::getName()
{
    return name;
}
void Player::setName(std::string name)
{
    this->name = name;
}
int Player::getScore() {
    return score;
}
void Player::setStringScore(std::string i) {
    this->score = std::stoi(i);
}
void Player::setScore(int score) {
    this->score = score;
}
void Player::setGameBoard(GameBoard* g){
    this->g = g;
}
GameBoard* Player::getGameBoard() {
    return g;
}