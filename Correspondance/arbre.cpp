#include "arbre.h"

void Arbre::avance(const bool droite){
    _courant = _courant->fils(droite);
}

char Arbre::current_val() const{
    return _courant->get_val();
}

void Arbre::reset(){
    _courant = _racine;
}

void Arbre::set_current_val(const char val){
    _courant->set_val(val);
}
