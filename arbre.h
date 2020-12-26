#include <iostream>

class Arbre {
    
    protected:
        Arbre* _fils[2];
        char _val;

    public:
        Arbre (): _val(' ') {}
        Arbre (const char val): _val(val) {}

        ~Arbre () {
            for (Arbre* a: _fils){
                delete a;
            }
        }

        void add_fils(const bool droit, const char val);

        char get_val();

        Arbre* fils(const bool droit);

        void print(const unsigned int prof) const;

        void set_val(const char val);
};
