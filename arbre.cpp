#include "arbre.h"


void Arbre::add_fils(const bool droit, const char val) {
    if (_fils[droit] == nullptr)
        _fils[droit] = new Arbre(val);
    else
        _fils[droit]->set_val(val);
}

char Arbre::get_val(){
    return _val;
}

Arbre* Arbre::fils(const bool droit) {
    return _fils[droit];
}

void Arbre::print(const unsigned int prof) const{
    std::cout << prof << " - " << _val << std::endl;
    for (Arbre* a : _fils){
        if (a != nullptr)
            a->print(prof + 1);
    }
}

void Arbre::set_val(const char val) {
    _val = val;
}

