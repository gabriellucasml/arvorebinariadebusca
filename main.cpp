#include <iostream>
#include "No.h"
#include "Abb.h"

using namespace std;

int main(int argc, char* argv[]){
    Abb *arvore = new Abb();
    No* no = new No();
    arvore->setRaiz(11);
    no = arvore->buscar(arvore->getRaiz(),11); 
    no = arvore->criarNo(15);
    arvore->inserir(no);
    no = arvore->buscar(arvore->getRaiz(), 12);
    no = arvore->criarNo(12);
    arvore->inserir(no);
    no = arvore->buscar(arvore->getRaiz(), 12);
    no = arvore->criarNo(14);
    arvore->inserir(no);
    no = arvore->criarNo(16);
    arvore->inserir(no);
    no = arvore->criarNo(4);
    arvore->inserir(no);
    no = arvore->criarNo(13);
    arvore->inserir(no);
    arvore->remover(15);

    return 0;
}