#include "No.h"

No::No(){
	pai = nullptr;
	esq = nullptr;
	dir = nullptr;
	nivel = 0;
	valor = 0;
	qntEsq = 0;
	qntDir = 0;
}
	
int No::getValor(){
	return this->valor;
}
void No::setValor(int valor){
	this->valor = valor;
}

int No::getNivel(){
	return this->nivel;
}

void No::setNivel(int nivel){
	this->nivel = nivel;
}

void No::incrementarNivel(){
	this->nivel += 1;
}

void No::decrementarNivel(){
	this->nivel -= 1;
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

No *No::getPai(){
	return this->pai;
}
void No::setPai(No *pai){
	this->pai = pai;
}

int No::getQntEsq(){
	return this->qntEsq;
}

void No::setQntEsq(int valor){
	this->qntEsq = valor;
}
	
void No::incrementarQntEsq(){
	this->qntEsq += 1;
}

int No::getQntDir(){
	return this->qntDir;
}

void No::setQntDir(int valor){
	this->qntDir = valor;
}

void No::incrementarQntDir(){
	this->qntDir += 1;
}

void No::decrementarQntEsq(){
	this->qntEsq -= 1;
}

void No::decrementarQntDir(){
	this->qntDir -= 1;
}