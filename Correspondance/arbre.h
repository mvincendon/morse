#include "noeud.h"

class Arbre{
    /**
        On parcourt l'arbre avec un noeud "courant" que l'on fait avancer (0 vers la droite, 1 vers la gauche),
        puis on définit ou récupère la valeur de ce noeud quand on est arrivé.
    **/

    protected:
        Noeud* _racine;
        Noeud* _courant;

    public:
        Arbre(const int hauteur = 0){
            _racine = new Noeud(hauteur);
            _courant = _racine;
        }

        void avance(const bool droite);

        char current_val() const;

        void reset();

        void set_current_val(const char val);

};

