#include <iostream>
#include "Abb.h"
#include "No.h"

using namespace std;

Abb::Abb(){
    raiz = new No();
}

No* Abb::criarNo(int valor){
    No* novoNo = new No();
    novoNo->setValor(valor);
    return novoNo;
}

No* Abb::getRaiz(){
    return this->raiz;
}
void Abb::setRaiz(int valor){
    this->raiz->setValor(valor);
}

No* Abb::buscar(No* raiz, int valor){
    No* aux = raiz;
    if(valor == aux->getValor()){
        return aux;
    }else if(valor > raiz->getValor()){
        if(aux->getDir() != nullptr){    
            aux = raiz->getDir();
            buscar(aux, valor);
        }else{
            return aux;//se não encontrar o nó específico, retorna o no que viria antes dele
        }    
    }else if(valor < raiz->getValor()){
        if(aux->getEsq() != nullptr){    
            aux = raiz->getEsq();
            buscar(aux, valor);
        }else{
            return aux;//se não encontrar o nó específico, retorna o no que viria antes dele
        }   
    }
}

void Abb::inserir(No* no){
    int valorNo = no->getValor();
    No* aux = buscar(this->getRaiz(), valorNo);
    if(aux->getValor() == no->getValor()){
        cout << "Nó já existe!" << endl;
    }else{
        if(aux->getValor() > no->getValor()){
            no->setPai(aux);
            aux->setEsq(no);
            while(aux != nullptr){
                if(no->getValor() < aux->getValor()){
                    aux->incrementarQntEsq();
                    aux = aux->getPai();
                }else{
                    aux->incrementarQntDir();
                    aux = aux->getPai();
                }    
            }
        }else{
            no->setPai(aux);
            aux->setDir(no);
            while(aux != nullptr){
                if(no->getValor() < aux->getValor()){
                    aux->incrementarQntEsq();
                    aux = aux->getPai();
                }else{
                    aux->incrementarQntDir();
                    aux = aux->getPai();
                }  
            }
        }
    }
}

void Abb::remover(int valor){
    No* aux = this->buscar(this->getRaiz(), valor);
    No* maiorEsq;
    if(aux->getDir() == nullptr && aux->getEsq() == nullptr){//se é folha
        if(aux->getValor() > aux->getPai()->getValor()){
            delete(aux->getPai()->getDir());
        }else{
            delete(aux->getPai()->getEsq());
        }
    }else if(aux->getDir() == nullptr ^ aux->getEsq() == nullptr){//se umas das suas sub-árvores forem nulas
        if(aux->getDir() == nullptr){ //ou seja, a sub-árvore à esquerda não é nula
            if(aux->getValor() > aux->getPai()->getValor()){//ou seja, é uma sub-árvore à direita de seu pai
                aux->getPai()->setDir(aux->getEsq());
                delete(aux);
            }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                aux->getPai()->setEsq(aux->getEsq());
                delete(aux);
            }
        }else{//ou seja, se a sub-árvore à direita não é nula
            if(aux->getValor() > aux->getPai()->getValor()){//ou seja, é uma sub-árvore à direita de seu pai
                aux->getPai()->setDir(aux->getEsq());
                delete(aux);
            }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                aux->getPai()->setEsq(aux->getEsq());
                delete(aux);
            }
        }
    }else{//se nenhuma das sub-árvores for nula
        maiorEsq = aux->getEsq();
        while(maiorEsq != nullptr){//encontrar o maior nó da esquerda
            if(maiorEsq->getDir() == nullptr){
                break;
            }
            maiorEsq = maiorEsq->getDir();
        }
        if(maiorEsq->getEsq() == nullptr){//se o maior nó da sub-árvore à esquerda é folha
            maiorEsq->setDir(aux->getDir());
            aux->getDir()->setPai(maiorEsq);
            maiorEsq->setEsq(aux->getEsq());
            aux->getEsq()->setPai(maiorEsq);
            delete(aux);
        }else{
            maiorEsq->getEsq()->setPai(maiorEsq->getPai());
            maiorEsq->getPai()->setDir(maiorEsq->getEsq());
            maiorEsq->setDir(aux->getDir());
            aux->getDir()->setPai(maiorEsq);
            maiorEsq->setEsq(aux->getEsq());
            aux->getEsq()->setPai(maiorEsq);
            if(maiorEsq->getValor() > aux->getPai()->getValor()){
                aux->getPai()->setDir(maiorEsq);
            }else{
                aux->getPai()->setEsq(maiorEsq);
            }
            delete(aux);
        }
    }
}