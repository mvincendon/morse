#include "arbre.h"

void Arbre::add_fils(const bool droit, const char val) {
    _fils[droit] = new Arbre(val);
}

void Arbre::print(const unsigned int prof = 0) const{
    std::cout << prof << " - " << _val << std::endl;
    for (Arbre* a : _fils){
        if (a != nullptr)
            a->print(prof + 1);
    }
}
