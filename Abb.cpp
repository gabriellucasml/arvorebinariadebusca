#include <iostream>
#include <vector>
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
    No* decrementoQntFilhos = aux;
    if(aux->getValor()==valor){
        No* maiorEsq;
        if(aux->getDir() == nullptr && aux->getEsq() == nullptr){//se é folha
            if(aux->getValor() > aux->getPai()->getValor()){
                while(decrementoQntFilhos->getPai() != nullptr){
                    decrementoQntFilhos->getPai()->decrementarQntDir();
                    decrementoQntFilhos = decrementoQntFilhos->getPai();
                }
                delete(aux->getPai()->getDir());
                delete(decrementoQntFilhos);
            }else{
                while(decrementoQntFilhos->getPai() != nullptr){
                    decrementoQntFilhos->getPai()->decrementarQntEsq();
                    decrementoQntFilhos = decrementoQntFilhos->getPai();
                }
                delete(aux->getPai()->getEsq());
                delete(decrementoQntFilhos);
            }
        }else if((aux->getDir() == nullptr) ^ (aux->getEsq() == nullptr)){//se umas das suas sub-árvores forem nulas
            if(aux->getDir() == nullptr){ //ou seja, a sub-árvore à esquerda não é nula
                if(aux->getValor() > aux->getPai()->getValor()){//ou seja, é uma sub-árvore à direita de seu pai
                    aux->getPai()->setDir(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                    decrementoQntFilhos->getPai()->decrementarQntEsq();
                    decrementoQntFilhos = decrementoQntFilhos->getPai();
                }
                    delete(aux);
                    delete(decrementoQntFilhos);
                }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                    aux->getPai()->setEsq(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                        decrementoQntFilhos->getPai()->decrementarQntDir();
                        decrementoQntFilhos = decrementoQntFilhos->getPai();
                    }
                    delete(aux);
                    delete(decrementoQntFilhos);
                }
            }else{//ou seja, se a sub-árvore à direita não é nula
                if(aux->getValor() > aux->getPai()->getValor()){//ou seja, é uma sub-árvore à direita de seu pai
                    aux->getPai()->setDir(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                        decrementoQntFilhos->getPai()->decrementarQntDir();
                        decrementoQntFilhos = decrementoQntFilhos->getPai();
                    }
                    delete(aux);
                    delete(decrementoQntFilhos);
                }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                    aux->getPai()->setEsq(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                        decrementoQntFilhos->getPai()->decrementarQntEsq();
                        decrementoQntFilhos = decrementoQntFilhos->getPai();
                    }
                    delete(aux);
                    delete(decrementoQntFilhos);
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
            No* aux1 = maiorEsq;//Ponteiro auxiliar para ajudar no decremento da quantidade de nós
            while(aux1->getPai()!=nullptr){
                if(aux1->getValor()<aux1->getPai()->getValor()){
                    aux1->getPai()->decrementarQntEsq();
                }else{
                    aux1->getPai()->decrementarQntDir();    
                }
                aux1 = aux1->getPai();
            }
            if(maiorEsq->getEsq() == nullptr){//se o maior nó da sub-árvore à esquerda é folha
                maiorEsq->setDir(aux->getDir());
                aux->getDir()->setPai(maiorEsq);
                maiorEsq->setEsq(aux->getEsq());
                aux->getEsq()->setPai(maiorEsq);
                maiorEsq->setQntDir(aux->getQntDir());
                maiorEsq->setQntEsq(aux->getQntEsq());
                decrementoQntFilhos = maiorEsq;
            }else{
                maiorEsq->getEsq()->setPai(maiorEsq->getPai());
                maiorEsq->getPai()->setDir(maiorEsq->getEsq());
                maiorEsq->setDir(aux->getDir());
                aux->getDir()->setPai(maiorEsq);
                maiorEsq->setEsq(aux->getEsq());
                aux->getEsq()->setPai(maiorEsq);
                maiorEsq->setPai(aux->getPai());
                maiorEsq->setQntDir(aux->getQntDir());
                maiorEsq->setQntEsq(aux->getQntEsq());
                if(maiorEsq->getValor() > aux->getPai()->getValor()){
                    aux->getPai()->setDir(maiorEsq);
                }else{
                    aux->getPai()->setEsq(maiorEsq);
                }
            }
            delete(aux);
        }
    } else{
        cout << "Nó não existe na árvore!" << endl;
    }
}

No* Abb::enesimoElemento(No* raiz, int n){
    int i = 0;
    vector<No*> ordem;
    if(raiz != nullptr){        
        raiz = enesimoElemento(raiz->getEsq(), n);
        ordem.push_back(raiz);
        i++;
        if(i == n){
            return ordem.back();
        }
        enesimoElemento(raiz->getDir(), n);
    }    
}

void Abb::ordemSimetrica(No* raiz){
    for(int i = 0; i <= 2; i++){    
        if(raiz != nullptr){
            ordemSimetrica(raiz->getEsq());
            std::cout << raiz->getValor()<< " " << endl;
            ordemSimetrica(raiz->getDir());
        }
    }    
}