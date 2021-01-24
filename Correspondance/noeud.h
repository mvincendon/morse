#include <iostream>

class Noeud {
    /**
        Noeud d'arbre binaire
    **/
    
    protected:
        Noeud* _fils[2];
        char _val;

    public:
        Noeud(): _val(' ') {}
        Noeud (const int prof) : _val(' ') {
            if (prof > 0){
                _fils[0] = new Noeud(prof-1);
                _fils[1] = new Noeud(prof-1);
            }
        }

        ~Noeud () {
            delete _fils[0];
            delete _fils[1];
        }

        char get_val();

        Noeud* fils(const bool droit);

        void print(const unsigned int prof) const;

        void set_val(const char val);
};
