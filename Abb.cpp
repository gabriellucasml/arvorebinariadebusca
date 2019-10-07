#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
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
                    aux->getPai()->setDir(aux->getDir());
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
                maiorEsq->setPai(aux->getPai());
                if(maiorEsq == aux->getEsq()){//se o maior nó da sub-árvore à esquerda for o único filho a esquerda do nó que será deletado
                    maiorEsq->setEsq(nullptr);
                }else{
                    maiorEsq->setEsq(aux->getEsq());//diz que o filho do maior nó da esquerda é o filho à esquerda do nó que será deletado
                    aux->getEsq()->setPai(maiorEsq);//diz que o pai do nó à esquerda do nó que será deletadado é o maior nó da subárvore à esquerda
                }
                maiorEsq->setDir(aux->getDir());//diz que o filho do maior nó da esquerda é o filho à direita do nó que será deletado
                aux->getDir()->setPai(maiorEsq);//diz que o pai do nó à direita do nó que será deletadado é o maior nó da subárvore à esquerda
                maiorEsq->setQntDir(aux->getQntDir());
                maiorEsq->setQntEsq(aux->getQntEsq());
            }else{                            //existe uma subárvore à esquerda
                ajustarNiveis(maiorEsq->getEsq());
                maiorEsq->setNivel(aux->getNivel());
                maiorEsq->setPai(aux->getPai());
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
            delete(maiorEsq);
        }
    } else{
        cout << "Nó não existe na árvore!" << endl;
    }
}

int Abb::getAltura(){
    return this->altura;
}

void Abb::ajustarNiveis(No* no){
    if(no != nullptr){
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
    int size = this->ordem.size();
    for(int i = 0; i < size; i++){
        if(this->ordem[i]->getValor() == x){
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
    if(this->ordem.size()%2 == 0){
        return this->ordem[(this->ordem.size()/2)-1]->getValor();
    }else{
        return this->ordem[this->ordem.size()/2]->getValor();
    }
}

void Abb::carregaVector(No* raiz){
    if(raiz != nullptr){        
        if (raiz->getEsq() != nullptr){
            carregaVector(raiz->getEsq());
        } 
        this->ordem.push_back(raiz);
        if (raiz->getDir() != nullptr){
            carregaVector(raiz->getDir());
        }
    }
}

void Abb::esvaziarVector(){
    this->ordem.clear();
}

void Abb::toString(){
    esvaziarVector();
    carregaVector(getRaiz());
    vector<string> nivel;
    calcularAltura();
    for(int i = 0; i<=this->altura;i++){
        nivel.push_back(" ");
    }
    for(No* i : this->ordem){
        nivel[i->getNivel()].append(" " + (to_string(i->getValor())));
    }
    for(int i = 1; i < nivel.size(); i++){
        cout << "Nivel " << i << ":" << nivel[i] << endl; 
    }
}

void Abb::importarArvore(){
    ifstream myfile;
    myfile.open("arquivodeentrada.txt");
    string aux;
    getline(myfile, aux);
    istringstream iss(aux);
    vector<string> nos;
    do{
        string subs;
        iss >> subs;
        nos.push_back(subs);
    } while (iss);
    this->setRaiz(stoi(nos[0]));
    for(int i = 1; i<nos.size(); i++){
        if(nos[i] != "")
            inserir(criarNo(stoi(nos[i])));
    }
}

bool Abb::ehCheia(){
    int maior_nivel = 0;
    for (int i = 0; i < ordem.size(); i++){
        if(ordem[i]->getNivel() > maior_nivel){
            maior_nivel = ordem[i]->getNivel();
        }
    }
    for(int i = 0; i < ordem.size(); i++){
        if (ordem[i]->getNivel() != maior_nivel){
            if(ordem[i]->getDir() == nullptr || ordem[i]->getEsq() == nullptr){
                return false;
            }
        }    
    }
    return true;
}

bool Abb::ehCompleta(){
    int maior_nivel = 0;
    for (int i = 0; i < ordem.size(); i++){
        if(ordem[i]->getNivel() > maior_nivel){
            maior_nivel = ordem[i]->getNivel();
        }
    }
    for(int i = 0; i < ordem.size(); i++){
        if(ordem[i]->getNivel() < (maior_nivel-1)){
            if(ordem[i]->getDir() == nullptr || ordem[i]->getEsq() == nullptr){
                return false;
            }
        }
    }
    return true;
}

void Abb::comando(){
    ifstream myfile;
    myfile.open("arquivodecomando.txt");
    string auxiliar; //string onde será armazenada a linha / auxiliará na leitura do arquivo
    while(getline(myfile, auxiliar)){ //espero que isso funcione -_-
        string tokens[2];
        istringstream iss(auxiliar);
        iss >> tokens[0]; //chamada da função
        iss >> tokens[1]; //argumento
        if (tokens[0].compare("ENESIMO") == 0 && tokens[1] != ""){
            std::cout << "> Elemento escolhido: " << enesimoElemento(getRaiz(), std::stoi(tokens[1]))->getValor() << endl;
        } else if (tokens[0].compare("POSICAO") == 0 && tokens[1] != ""){
            cout << "Posição do elemento " << tokens[1] << ": " << posicao(this->raiz, stoi(tokens[1]))<< endl;
        } else if (tokens[0].compare("MEDIANA") == 0){
            cout << "Mediana: " << mediana(this->raiz)<< endl;
        } else if (tokens[0].compare("CHEIA") == 0){
            if(ehCheia())
                cout << "é cheia" << endl;
            else
                cout << "não é cheia" << endl;
        } else if (tokens[0].compare("COMPLETA") == 0){
            if(ehCompleta())
                cout << "é completa" << endl;
            else
                cout << "não é completa" << endl;
        } else if (tokens[0].compare("IMPRIMA") == 0){
            toString();
        } else if (tokens[0].compare("REMOVA") == 0 && tokens[1] != ""){
            cout << "Remover elemento " << tokens[1] << endl;
            remover(std::stoi(tokens[1]));
        } else if (tokens[0].compare("INSIRA") == 0){
            cout << "Inserir elemento " << tokens[1] << endl;
            inserir(criarNo(std::stoi(tokens[1]))); //i hope it works like this :')
        }
    }
    myfile.close();
}

void Abb::calcularAltura(){
    int altura = 0;
    for(No* no : this->ordem){
        if(no->getNivel()>altura){
            altura = no->getNivel();
        }
    }
    this->altura = altura;
}