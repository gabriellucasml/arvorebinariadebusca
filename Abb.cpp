#include <iostream>
#include <vector>
#include "Abb.h"
#include "No.h"

using namespace std;

Abb::Abb(){
    raiz = new No();
    raiz->setNivel(1);
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
            no->setNivel(no->getPai()->getNivel()+1);
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
            no->setNivel(no->getPai()->getNivel()+1);
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
                    ajustarNiveis(aux);
                    aux->getPai()->setDir(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                        decrementoQntFilhos->getPai()->decrementarQntEsq();
                        decrementoQntFilhos = decrementoQntFilhos->getPai();
                    }
                    delete(aux);
                    delete(decrementoQntFilhos);
                }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                    ajustarNiveis(aux);
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
                    ajustarNiveis(aux);
                    aux->getPai()->setDir(aux->getEsq());
                    while(decrementoQntFilhos->getPai() != nullptr){
                        decrementoQntFilhos->getPai()->decrementarQntDir();
                        decrementoQntFilhos = decrementoQntFilhos->getPai();
                    }
                    delete(aux);
                    delete(decrementoQntFilhos);
                }else{//ou seja, é uma sub-árvore à esquerda do seu pai
                    ajustarNiveis(aux);
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
                maiorEsq->setNivel(aux->getNivel());//Diz que o nível do maior nó da esquerda é igual ao nível do no que será deletado
                maiorEsq->setDir(aux->getDir());//diz que o filho do maior nó da esquerda é o filho à direita do nó que será deletado
                aux->getDir()->setPai(maiorEsq);//diz que o pai do nó à direita do nó que será deletadado é o maior nó da subárvore à esquerda
                maiorEsq->setEsq(aux->getEsq());//diz que o filho do maior nó da esquerda é o filho à esquerda do nó que será deletado
                aux->getEsq()->setPai(maiorEsq);//diz que o pai do nó à esquerda do nó que será deletadado é o maior nó da subárvore à esquerda
                maiorEsq->setQntDir(aux->getQntDir());
                maiorEsq->setQntEsq(aux->getQntEsq());
                decrementoQntFilhos = maiorEsq;
            }else{                            //existe uma subárvore à esquerda
                ajustarNiveis(maiorEsq->getEsq());
                maiorEsq->setNivel(aux->getNivel());
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

void Abb::ajustarNiveis(No* no){
    if(no->getEsq() == nullptr && no->getDir() == nullptr)
        no->decrementarNivel();
    if(no->getEsq() != nullptr){
        ajustarNiveis(no->getEsq());
        no->decrementarNivel();
        ajustarNiveis(no->getDir());
    }
}

No* Abb::enesimoElemento(No* raiz, int n){
    static vector<No*> ordem;
    if(raiz != nullptr){        
        if (raiz->getEsq() != nullptr){
            enesimoElemento(raiz->getEsq(), n);
        } 
        ordem.push_back(raiz);
        if (raiz->getDir() != nullptr){
            enesimoElemento(raiz->getDir(), n);
        }
    }
    return ordem[n-1];
}


int Abb::posicao(No* raiz,int x){
    int retorno;
    int size = ordem.size();
    for(int i = 0; i < size; i++){
        if(ordem[i]->getValor() == x){
            retorno = i+1;
        }
    }
    return retorno;
}

void Abb::ordemSimetrica(No* raiz){
        static int x;
        if(raiz != nullptr){
            if(raiz->getEsq() != nullptr){
                ordemSimetrica(raiz->getEsq());
            }
            x++;
            std::cout << x << " " << raiz->getValor()<< " " << endl;
            if(raiz->getDir() != nullptr){
                ordemSimetrica(raiz->getDir());
            }
        }    
}

int Abb::mediana(No* raiz){
    if(ordem.size()%2 == 0){
        return ordem[(ordem.size()/2)-1]->getValor();
    }else{
        return ordem[ordem.size()/2]->getValor();
    }
}

void Abb::carregaVector(No* raiz){
    static vector<No*> tqr ;
    if(raiz != nullptr){        
        if (raiz->getEsq() != nullptr){
            carregaVector(raiz->getEsq());
        } 
        tqr.push_back(raiz);
        if (raiz->getDir() != nullptr){
            carregaVector(raiz->getDir());
        }
    }
    this->ordem = tqr;  
}

void Abb::esvaziarVector(){
    this->ordem.clear();
}

void Abb::toString(No* raiz){
    //je sais pas qu'est-ce je suis en train de fair ici ;-;
}
