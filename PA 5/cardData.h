#ifndef CARDDATA_H
#define CARDDATA_H
#include <string>

// card data file to store across public access files
using namespace std;
struct cardData {

    string name;
    string type;
    int level;
    string race;
    string attribute;
    int ATK;
    int DEF;
};
#endif