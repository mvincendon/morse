#include "morse.h"

int main(int argc, char* argv[]){
    std::cout << "Le morse c'est génial !" << std::endl;
    Correspondance* corres = new Correspondance("corres.txt");
    delete corres;
}





