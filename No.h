#ifndef _NO_H_
#define _NO_H_

class No{
private:
	int valor;  //chave ou valor que nó segura
	int qntEsq; //Quantidade de nós na sub-árvore à esquerda
	int qntDir; //Quantidade de nós na sub-árvore à direita
	int nivel;  //Nível em que está localizado o nó
	No *esq;    //Ponteiro que aponta para o filho da esquerda
	No *dir;    //Ponteiro que aponta para o filho da direita
	No *pai;    //Ponteiro que aponta para o pai
public:
	No();	
	int getValor();
	void setValor(int valor);
	No *getEsq();
	void setEsq(No *esq);
	No *getDir();
	void setDir(No *dir); 
	No *getPai();
	void setPai(No *pai);
	int getQntEsq();
	void setQntEsq(int valor);
	void incrementarQntEsq();
	void decrementarQntEsq();
	int getQntDir();
	void setQntDir(int valor);
	void incrementarQntDir();
	void decrementarQntDir();
	int getNivel();
	void setNivel(int nivel);
	void incrementarNivel();
	void decrementarNivel();
};

#endif
