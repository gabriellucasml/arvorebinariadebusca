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