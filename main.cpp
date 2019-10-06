#include <iostream>
#include "No.h"
#include "Abb.h"

using namespace std;

int main(int argc, char* argv[]){
    Abb *arvore = new Abb();
    No* no = new No();
    No* aux = new No();
    arvore->importarArvore();
    arvore->ordemSimetrica(arvore->getRaiz());
    arvore->carregaVector(arvore->getRaiz());
    cout << arvore->enesimoElemento(arvore->getRaiz(), 6)->getValor() << " <- Enesimo Elemento" << endl;
    cout << arvore->posicao(arvore->getRaiz(),30) << " <- posicao" <<endl;
    cout << arvore->mediana(arvore->getRaiz()) << " <- Mediana" << endl;
    arvore->toString();
    return 0;
}