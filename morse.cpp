#include "morse.h"

// Convention :
// Droite = long = 1
// Gauche = court = 0


int main(int argc, char* argv[]){
    Wav wav ("corres.txt");

    // "Interface utilisateur"
    cout << "Le morse c'est génial !\n";
    cout << "Que voulez-vous faire ?\n";
    cout << "1 - Encoder Français --> Morse\n";
    cout << "2 - Décoder Morse -- >Français\n";

    string rep;
    std::cin >> rep;

    if (rep == "1"){
        cout << "Comment donner le texte en français ?\n";
        cout << "3 - Saisie 1 ligne\n";
        cout << "4 - Fichier texte\n";
        cin >> rep;
        string sortie;
        cout << "Comment appeler le fichier de sortie ? (attention : donner l'extension .wav et ne pas donner de nom de fichier existant sous peine d'écrasement)" << '\n';
        cin >> sortie;
        if (rep == "3"){
            cout << "Entrez le texte :\n";
            cin >> rep;
            wav.ecrire(rep, sortie);
        }
        else {
            cout << "Entrez le nom du fichier source :\n";
            cin >> rep;
            wav.ecrire_fichier(rep, sortie);
        }
    }
    else {
        string source;
        cout << "Entrez le nom du fichier wav source :\n";
        cin >> source;
        string res = wav.lire(source);
        cout << "Que faire du texte décodé ?\n";
        cout << "3 - L'afficher\n";
        cout << "4 - L'écrire dans un fichier texte\n";
        cin >> rep;
        if (rep=="3")
            cout << res << '\n';
        else {
            cout << "Entrez le nom du fichier texte de sortie :";
            cin >> rep;
            std::ofstream sortie (rep);
            sortie << res;
            sortie.close();
        }
    }
    cout << "À bientôt !\n";
    return 0;
}





