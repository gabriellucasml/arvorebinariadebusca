#ifndef _NO_H_
#define _NO_H_

class No{
private:
	int valor;
	No *esq;
	No *dir;
public:
	No();	
	int getValor();
	void setValor(int valor);
	No *getEsq();
	void setEsq(No *esq);
	No *getDir();
	void setDir(No *dir); 
};

#endif
