#ifndef _ABB_H_
#define _ABB_H_

class No;

class Abb{
private:
    No* raiz;
public:
    Abb();
    No* criarNo(int valor);
    No* buscar(No* raiz, int valor);
    void inserir(No* no);
    No* getRaiz();
    void setRaiz(int valor);

};
#endif