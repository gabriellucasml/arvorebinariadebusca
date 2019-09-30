#include <iostream>
#include "No.h"
#include "Abb.h"

using namespace std;

int main(int argc, char* argv[]){
    Abb *arvore = new Abb();
    No* no = new No();
    arvore->setRaiz(11);
    no = arvore->buscar(arvore->getRaiz(),11);
    if(no->getValor() == 11)
        cout << "no encontrado" << endl;
    else
        cout << "no não encontrado" << endl;
    
    no = arvore->criarNo(12);
    arvore->inserir(no);
    cout << "Raiz: " << arvore->getRaiz()->getValor() << endl;
    cout << "filho direita: " << arvore->getRaiz()->getDir()->getValor() << endl;  
    return 0;
}