#include "wav.h"


void Wav::ecrire(vector<double> tableau){} //Penser à initialiser fsize

bool Wav::ecoute(const double val, const bool silence) const{
    /*
        Dit si la valeur de _data[indice] est bien
        - du silence si silence = 1
        - du son si silence = 0
        Cette fonction évite des disjonctions de cas et allège la fonction periode.
    */
    return ((std::abs(val) <= SEUIL) == silence);
}

template<typename T>
void print(vector<T> v){
    for (T b: v){
        std::cout << b << std::endl;
    }
}

double Wav::sous_mediane(const long unsigned int debut, const long unsigned int fin) const{
    vector<double> sub (_data.begin() + debut, _data.begin() + fin);
    std::for_each(sub.begin() , sub.end(), [](double &n){ n = std::abs(n); });
    size_t moitie = (fin-debut) / 2;
    std::nth_element(sub.begin(), sub.begin() + moitie, sub.end());
    return sub[moitie];
}

int Wav::periode(const long unsigned int debut, const bool silence) const{
    // On avance jusqu'au prochain changement d'état (son ou silence)
    long unsigned int iter = debut;
    while (iter < _data.size() - fluct){
        if (ecoute(_data[iter], silence)){ // Valeur non nulle
            // On regarde si c'est une fluctuation en prenant la médiane des valeurs dans [iter , iter + FLUCT * bps]
            double mediane = sous_mediane(iter, std::min(iter + fluct, _data.size()-1));
            if (!ecoute(mediane, silence)) //Si ce n'est pas une fluctuation
                break;
        }
        iter++;
    }
    return iter;
}

string Wav::interpreter() const {
    Correspondance corres ("corres.txt");
    long unsigned int iter = 0, iterSuiv = 0;
    double temps;   // Seront des ms
    string message;
    vector<bool> lettre;
    if (ecoute(sous_mediane(0, fluct), true)) {iter = periode(iter, true);}   // On enlève un éventuel silence de départ
    bool etat = false;                                      // L'état courant commence donc à false, donc présence d'un son
    while (iter < _data.size()-fluct){
        iterSuiv = periode(iter, etat);
        // On regarde combien d'unités dure cette période
        temps = (iterSuiv-iter) * 1000 / _header.bytesPerSec;
        std::cout << temps << '\n';
        if (!etat){  // S'il y a un son
            if (std::abs(temps - UNIT) < UNIT/2){
                lettre.push_back(false);
            }
            else if (std::abs(temps - 3*UNIT) < UNIT/2){
                lettre.push_back(true);
            }
            else {
                std::cout << "Caractère non reconnu" << '\n';
            }
            std::cout << "on avance" << '\n';
        }
        else {  // Si c'est un silence
            if (std::abs(temps - 3 * UNIT) < UNIT/2){    // Espace entre 2 lettres
                message += corres.decode(lettre);
                lettre = {};
            }
            else if (std::abs(temps - 7 * UNIT) < UNIT/2){    // Espace entre 2 mots
                message += corres.decode(lettre) + " ";
                lettre = {};
            }
        }

        etat = !etat;
        iter = iterSuiv+1;
    }
    return message + corres.decode(lettre);
}


void Wav::lire(const string source){

    int headerSize = sizeof(wav_hdr);

    FILE* wavFile = fopen(source.c_str(), "r");

    //Read the header
    size_t bytesRead = fread(&_header, 1, headerSize, wavFile);
    // std::cout << "Header Read " << bytesRead << " bytes." << std::endl;
    if (bytesRead > 0)
    {
        //Read the data
        static const uint16_t BUFFER_SIZE = 4096;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
            for (int i = 0 ; i < BUFFER_SIZE ; i++)
                _data.push_back(buffer[i]);
            // std::cout << "Read " << bytesRead << " bytes." << std::endl;
        }
        delete [] buffer;
    }
    fluct = FLUCT * _header.bytesPerSec / 1000;
    fclose(wavFile);
}

vector<double> Wav::get_data() const{
    return _data;
}

