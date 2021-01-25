#include "wav.h"

template<typename T>
void print(vector<T> v){
    for (T b: v){
        std::cout << b;
    }
}

template<typename T>
void print_in_file(vector<T> v, string path){
    std::ofstream file;
    file.open(path);
    for (T x: v){
        file << x << "\n";
    }
    file.close();
}

// ########################### Partie écriture ############################

string Wav::lire_fichier(const string source){
    string texte;
    std::ifstream message;
    message.open(source);
    string ligne;
    while(!message.eof()){
        std::getline(message, ligne);
        texte += ligne;
    }
    message.close();
    std::cout << "Fichier d'entrée lu." << '\n';
    return texte;
}

void Wav::convertir(char &car){
    car = std::toupper(car);
    if (!_corres->existe(car) && car != ' ')
        car = '?';
}

void Wav::generer(const unsigned short int nbUnits, const bool silence){
    double frequence = 440;
    // int periode = _header.bytesPerSec / frequence; //En bytes
    unsigned long int N = nbUnits * UNIT * _header.bytesPerSec / 1000;
    for (unsigned long int i = 0 ; i < N; i++){
        
        _data.push_back(AMPL * !silence * sin(6.283 * frequence * _data.size() / _header.bytesPerSec)); // Sinusoide
        // bool positif = ((long int)_data.size() % (periode) < periode/2);
        // _data.push_back(AMPL * !silence * (positif - !positif)); // Créneau
    }
}

void Wav::ecrire_fichier(const string source, const string target){
    ecrire(lire_fichier(source), target);
}

void Wav::ecrire(string texte, const string target){
    std::for_each(texte.begin(), texte.end(), [this](char &car){this->convertir(car);});

    vector<bool> code;  // Contiendra les codes successifs de chaque caractère

    for (int i = 0 ; i < (int)texte.length() ; i++){
        if (texte[i] == ' '){
            generer(7, true);
        }
        else {
            code = _corres->code(texte[i]);
            generer(!code[0] + 3*code[0], false);   // Génèrera 1 unité si 0 (court) et 3 si 1 (long)
            for (short int j = 1 ; j < (short)code.size() ; j++){
                generer(1, true);
                generer(!code[j] + 3*code[j], false);
            }
            if (i+1 < (int)texte.length() && (texte[i+1]!=' '))
                generer(3, true);
        }
    }

    _header.Subchunk2Size = _data.size();
    _header.ChunkSize = _header.Subchunk2Size + 36;
    std::ofstream file(target, std::ios::binary);
    file.write(reinterpret_cast<const char *>(&_header), sizeof(_header));
    for (int d : _data){    // On a besoin de caster en int pour la réinterprétation
        file.write(reinterpret_cast<char *>(&d), 1);
    }
    file.close();
}

bool Wav::ecoute(const double val, const bool silence) const{
    /*
        Dit si la valeur de _data[indice] est bien
        - du silence si silence = 1
        - du son si silence = 0
        Cette fonction évite des disjonctions de cas et allège la fonction periode.
    */
    return ((std::abs(val) <= SEUIL) == silence);
}

// ########################### Partie lecture ###############################

double Wav::sous_mediane(const long unsigned int debut, const long unsigned int fin) const{
    vector<double> sub (_data.begin() + debut, _data.begin() + fin);
    std::for_each(sub.begin() , sub.end(), [](double &n){ n = std::abs(n); });
    size_t moitie = (fin-debut) / 2;
    std::nth_element(sub.begin(), sub.begin() + moitie, sub.end());
    return sub[moitie];
}

int Wav::periode(const long unsigned int debut, const bool silence) const{
    /* 
        On avance jusqu'au prochain changement d'état (son ou silence)
    */
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
    long unsigned int iter = 0, iterSuiv = 0;
    double temps;   // Seront des ms
    string message;
    vector<bool> lettre;
    if (ecoute(sous_mediane(0, fluct), true)) {iter = periode(iter, true);}   // On enlève un éventuel silence de départ
    bool etat = false;                                      // L'état courant commence donc à false, donc présence d'un son
    // int compt = 0;
    while (iter < _data.size()-fluct){
        iterSuiv = periode(iter, etat);
        // On regarde combien d'unités dure cette période
        temps = (iterSuiv-iter) * 1000 / _header.bytesPerSec;
        
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
        }
        else {  // Si c'est un silence
            if (std::abs(temps - 3 * UNIT) < UNIT/2){    // Espace entre 2 lettres
                message += _corres->decode(lettre);
                lettre = {};
            }
            else if (std::abs(temps - 7 * UNIT) < UNIT/2){    // Espace entre 2 mots
                message += _corres->decode(lettre);
                message += " ";
                lettre = {};
            }
            else if (std::abs(temps - UNIT) >= UNIT/2){     // Si l'on n'est pas dans le cas d'un silence simple
                message += _corres->decode(lettre);
                lettre = {};
                while (temps > 0 && std::abs(temps - UNIT) >= UNIT){
                    message += " ";
                    temps -= 7 * UNIT;
                }
            }
        }

        etat = !etat;
        iter = iterSuiv+1;
    }
    return message + _corres->decode(lettre);
}

string Wav::lire(const string source){

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

    return interpreter();
}


