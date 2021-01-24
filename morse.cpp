#include "morse.h"
#include "wav.h"

// Convention :
// Droite = long = 1
// Gauche = court = 0

template<typename T>
void print(vector<T> v){
    for (T b: v){
        std::cout << b << std::endl;
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

int main(int argc, char* argv[]){
    // std::cout << "Le morse c'est génial !" << std::endl;
    // Correspondance corres ("corres.txt");

    Wav wav;
    wav.lire("R.wav");
    // std::cout << wav.periode(0,0) << '\n';
    // print_in_file(wav.get_tab(), "test3.txt");
    std::cout << wav.interpreter() << std::endl;

}





