#ifndef _ABB_H_
#define _ABB_H_
#include <vector>

class No;

class Abb{
private:
    No* raiz;
    std::vector<No*> ordem;

public:
    Abb();
    No* criarNo(int valor);
    No* getRaiz();
    void setRaiz(int valor);
    No* buscar(No* raiz, int valor);
    void inserir(No* no);
    void remover(int valor);
    No* enesimoElemento(No* raiz, int n);
    void ordemSimetrica(No* raiz);
    int posicao(No* raiz, int x);
    int mediana(No* raiz);
    void carregaVector(No* raiz);
    void esvaziarVector();
    void ajustarNiveis(No* no);
    void toString();
    void comando();
    void importarArvore();
};

#endif