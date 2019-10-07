#ifndef _ABB_H_
#define _ABB_H_
#include <vector>

class No;

class Abb{
private:
    No* raiz;
    std::vector<No*> ordem;
    int altura;

public:
    Abb();
    No* criarNo(int valor);
    No* getRaiz();
    No* buscar(No* raiz, int valor);
    No* enesimoElemento(No* raiz, int n);
    bool ehCheia();
    bool ehCompleta();
    int posicao(No* raiz, int x);
    int mediana(No* raiz);
    int getAltura();
    void calcularAltura();
    void setRaiz(int valor);
    void inserir(No* no);
    void remover(int valor);
    void carregaVector(No* raiz);
    void esvaziarVector();
    void ajustarNiveis(No* no);
    void ordemSimetrica(No* raiz);
    void toString();
    void comando();
    void importarArvore();
};

#endif