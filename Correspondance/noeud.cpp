#include "noeud.h"

char Noeud::get_val(){
    return _val;
}

Noeud* Noeud::fils(const bool droit) {
    return _fils[droit];
}

void Noeud::print(const unsigned int prof) const{
    std::cout << prof << " - " << _val << std::endl;
    for (Noeud* a : _fils){
        if (a != nullptr)
            a->print(prof + 1);
    }
}

void Noeud::set_val(const char val) {
    _val = val;
}

