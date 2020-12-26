#include <vector>

#include "arbre.h"


class Correspondance {

    protected:
        Arbre* _table;

    public:
        Correspondance (const std::string source) {
            _table = new Arbre();

            std::ifstream input;
            input.open(corres);

            std::string ligne;
            std::getline(input, ligne); // De la forme A .-
            while (!ligne.empty()) {
                char car = ligne[0];
                std::string code = ligne.substr(2, ligne.length()-3);
                Arbre* tab_act = table;
                for (char c: code){ // Parcours de l'arbre et ajout des noeuds nécessaires
                    bool droit = (c == '-');
                    if (tab_act->fils(droit) == nullptr)
                        tab_act->add_fils(droit, ' ');
                    tab_act = tab_act->fils(droit);
                }
                tab_act->set_val(car); // On place la lettre sur le bon noeud de l'arbre
                std::getline(input, ligne);
            }

            input.close();
        }

        ~Correspondance() {
            delete _table;
        }

        std::vector<bool> cherche(const char c);
}




