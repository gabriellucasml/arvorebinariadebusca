#include <iostream>
#include "No.h"
#include "Abb.h"

using namespace std;

int main(int argc, char* argv[]){
    Abb *arvore = new Abb();
    No* no = new No();
    No* aux = new No();
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
    arvore->ordemSimetrica(arvore->getRaiz());
    
    /*
        Comentários do Gabriel H. para como utilizar a carregarVector(), posicao() e mediana():
        Infelizmente eu fui deveras incompetente e acabei fazendo gambiarras estúpidas pra fazer
        isso funcionar.
        O fato é que as funções posição e mediana utilizam a carregaVector, que vai colocar o 
        percurso bem direitinho dentro de um vetor.
        Qual é o problema? se tu chamar o carregaVector mais do que deves, ele vai duplicar o tamanho.
        portanto, para posiçao e mediana funcionar, chama o carregaVector só uma vez, pelo amor de deus, eu suplico.
    */
    arvore->carregaVector(arvore->getRaiz());
    cout << arvore->enesimoElemento(arvore->getRaiz(), 6)->getValor() << " <- Enesimo Elemento" << endl;
    cout << arvore->posicao(arvore->getRaiz(),16) << " <- posicao" <<endl;
    cout << arvore->mediana(arvore->getRaiz()) << " <- Mediana" << endl;
    return 0;
}