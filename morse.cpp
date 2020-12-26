#include <iostream>

#include "morse.h"
#include "dict.h"

int main(int argc, char* argv[]){
    std::cout << "Le morse c'est génial !" << std::endl;
    Dict* dict = new Dict("source.txt");
    dict->print_source();
    delete dict;
}
