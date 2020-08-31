#include <vector>

#ifndef RKB_TILEBAG_H
#define RKB_TILEBAG_H
#include "TileBag.h"
#define FACSIZE 4
class TileBag;

class Factories
{
public:
    Factories();
    ~Factories();
    void populateFactories(TileBag *T);
    void getFactories();
    std::string getSaveCentralFactory();
    std::string getSaveFactories();
    std::vector<Tile> getSelectedFactory(int fnum);
    void setSelectedFactory(std::vector<Tile> SF, int fnum);
    void setFactoriesForLoad(int i, std::string line);
    void clearFactory(int i);
    bool checkFactories();
    void rePopulateFactories(TileBag *T);

    void printWithColour(Colour c);

    void centreFacAmount(int num);
    int getAmountofFac();
    void eraseFacF();
    void setAmountFac(int size);

private:
    std::vector<Tile> F0; // central factory
    std::vector<Tile> F1;
    std::vector<Tile> F2;
    std::vector<Tile> F3;
    std::vector<Tile> F4;
    std::vector<Tile> F5;
    std::vector<Tile> F02;             //central factory 2.
    std::vector<std::vector<Tile>> FF; // vector for Factories.
    Tile *FirstPlayerT = new Tile('F');
    int amountofFac;
};
#endif