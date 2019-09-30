#include "No.h"

No::No(){
	esq = nullptr;
	dir = nullptr;
	valor = 0;
}
	
int No::getValor(){
	return this->valor;
}
void No::setValor(int valor){
	this->valor = valor;
}

No *No::getEsq(){
	return this->esq;
}
void No::setEsq(No *esq){
	this->esq = esq;
}

No *No::getDir(){
	return this->dir;
}
void No::setDir(No *dir){
	this->dir = dir;
} 