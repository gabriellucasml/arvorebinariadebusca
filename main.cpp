#include <iostream>
#include "No.h"
#include "Abb.h"

using namespace std;

int main(int argc, char* argv[]){
    Abb *arvore = new Abb();
    No* no = new No();
    No* aux = new No();
    arvore->importarArvore();
    arvore->remover(50);
    arvore->remover(85);
    //arvore->comando();
    return 0;
}