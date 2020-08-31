#include <iostream>

#include "Factories.h"

Factories::Factories()
{
    FF.push_back(F1);
    FF.push_back(F2);
    FF.push_back(F3);
    FF.push_back(F4);
    FF.push_back(F5);
}
Factories::~Factories()
{
    FF.clear();
}
void Factories::centreFacAmount(int num)
{
    if (num == 1)
    {
        FF.insert(FF.begin(), F0);
        amountofFac = 6;
    }
    else
    {
        FF.insert(FF.begin(), F02);
        FF.insert(FF.begin(), F0);
        amountofFac = 7;
    }
}
void Factories::populateFactories(TileBag *T)
{
    //populate the factories
    if (FF.size() == 6)
    {
        for (unsigned i = 1; i < 6; ++i)
        {
            for (unsigned j = FF[i].size(); j < FACSIZE; ++j)
            {
                if (FF[0].size() < 1)
                {
                    FF[0].push_back(*FirstPlayerT);
                }
                FF[i].push_back(T->getRandomTile());
            }
        }
    }
    else
    {
        for (unsigned i = 2; i < 7; ++i)
        {
            for (unsigned j = FF[i].size(); j < FACSIZE; ++j)
            {
                if (FF[0].size() < 1)
                {
                    FF[0].push_back(*FirstPlayerT);
                    FF[1].push_back(*FirstPlayerT);
                }
                FF[i].push_back(T->getRandomTile());
            }
        }
    }
}
void Factories::rePopulateFactories(TileBag *T)
{
    for (unsigned i = 1; i < FF.size(); ++i)
    {
        for (unsigned j = FF[i].size(); j < FACSIZE; ++j)
        {
            FF[i].push_back(T->getRandomTile());
        }
    }
}
void Factories::getFactories()
{
    std::cout << "Factories:";
    for (int i = 0; i < getAmountofFac(); ++i)
    {
        std::cout << "\n"
                  << i << ": ";
        for (unsigned j = 0; j < FF[i].size(); ++j)
        {
            printWithColour(FF[i][j].getColour());
        }
    }
    std::cout << std::endl;
}
void Factories::eraseFacF()
{
    if (amountofFac == 7)
    {
        for (unsigned i = 0; i < FF.size(); ++i)
        {
            if (FF[0][i].getColour() == 'F')
            {
                FF[0].erase(FF[0].begin());
            }
            if (FF[1][i].getColour() == 'F')
            {
                FF[1].erase(FF[1].begin());
            }
        }
    }
}
void Factories::printWithColour(Colour c)
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
    if (c == 'F')
    {
        std::cout << c << " ";
    }
}
// saves central factory at current state
std::string Factories::getSaveCentralFactory()
{
    std::string details = "";
    if (amountofFac == 6)
    {
        for (unsigned i = 0; i < FF[0].size(); ++i)
        {
            details += FF[0][i].getColour();
        }
        if (FF[0].empty())
        {
            details = " ";
        }
    }
    else
    {
        for (unsigned i = 0; i < FF[0].size(); ++i)
        {
            details += FF[0][i].getColour();
        }
        for (unsigned i = 0; i < FF[0].size(); ++i)
        {
            details += FF[1][i].getColour();
        }
        if (FF[0].empty() || FF[1].empty())
        {
            details = " ";
        }
    }
    return details;
}
// saves factories at current state
std::string Factories::getSaveFactories()
{
    std::string details = "";
    for (int i = 0; i < getAmountofFac(); ++i)
    {
        for (unsigned j = 0; j < FF[i].size(); ++j)
        {
            details += FF[i][j].getColour();
        }
        if (FF[i].empty())
        {
            details += " ";
        }
        details += '\n';
    }
    return details;
}
void Factories::setSelectedFactory(std::vector<Tile> SF, int fnum)
{
    FF[fnum] = SF;
}
std::vector<Tile> Factories::getSelectedFactory(int fnum)
{
    return FF[fnum];
}
// loads factories
void Factories::setFactoriesForLoad(int i, std::string line)
{
    int size = line.size();
    FF[i].clear();
    for (int j = 0; j < size; ++j)
    {
        FF[i].push_back(line.at(j));
    }
}
void Factories::clearFactory(int i)
{
    FF[i].clear();
}
int Factories::getAmountofFac()
{
    return amountofFac;
}
void Factories::setAmountFac(int size){
    amountofFac = size;
}
//checks if factories are empty.
bool Factories::checkFactories()
{
    bool isEmpty = false;
    for (unsigned i = 0; i < FF.size(); ++i)
    {
        if (FF[i].empty())
        {
            isEmpty = true;
        }
        else
        {
            isEmpty = false;
            return isEmpty;
        }
    }
    return isEmpty;
}
