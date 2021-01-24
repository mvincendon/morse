#include "corres.h"

vector<bool> Correspondance::code (const char c){
    return _theme[c];
}

char Correspondance::decode(const vector<bool> vect){
    _version->reset();
    // On parcourt l'arbre
    for (bool b : vect){
        _version->avance(b);
    }
    return _version->current_val();
}

bool Correspondance::existe(const char car){
    return _theme.count(car);
}

