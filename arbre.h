#include <iostream>

class Arbre {
    
    protected:
        Arbre* _fils[2];
        char _val;

    public:
        Arbre (const char val): _val(val) {}

        ~Arbre () {
            for (Arbre* a: _fils){
                delete a;
            }
        }

        void add_fils(const bool droit, const char val);

        void print(const unsigned int prof) const;

};
