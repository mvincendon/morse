#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "arbre.h"

using std::vector;
using std::map;
using std::string;

class Correspondance {
    /**
        But : morse <--> lettre
        On utilise
        - une map           pour lettre --> morse (thème)
        - un arbre binaire  pour morse --> lettre (version)
        Ce qui vise à optimiser la vitesse de traduction.
    **/

    protected:
        map<char, vector<bool>> _theme;
        Arbre* _version;

        vector<bool> string_to_vect(string str){
            vector<bool> v;
            for (char c : str){
                v.push_back(c=='-');
            }
            return v;
        }

    public:
        Correspondance (const string source) { // Lecture des correspondances dans le fichier
            _version = new Arbre(5);  // a priori il n'y aura pas plus de 5 . ou - à la fois

            std::ifstream input;
            input.open(source);

            string ligne;
            std::getline(input, ligne); // De la forme A .-
            while (!ligne.empty()) {
                char car = ligne[0];
                string code_str = ligne.substr(2, ligne.length() - 3);
                vector<bool> code = string_to_vect(code_str);
                
                _theme[car] = code; //On remplit la map

                _version->reset();
                for (bool b : code){
                    _version->avance(b);
                }
                _version->set_current_val(car); // On remplit l'arbre

                std::getline(input, ligne);
            }

            input.close();
        }

        ~Correspondance() {
            delete _version;
        }

        vector<bool> code(const char c);

        char decode(const vector<bool> vect);

};




