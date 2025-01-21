#include <iostream>
using namespace std;

//no = nó
struct No {
    int dado;
    No* esquerda;
    No* direita;

    No(int valor) {
        dado = valor;
        esquerda = nullptr;
        direita = nullptr;
    }
};

int alturaArvore(No* raiz) {
    if (raiz == nullptr) 
        return 0;
    
    int alturaEsquerda = alturaArvore(raiz->esquerda);
    int alturaDireita = alturaArvore(raiz->direita);
    return max(alturaEsquerda, alturaDireita) + 1;
}

int main() {
    //usando a árvore com meu nome, trocando as letras por números, A=1, B=2, ... , Z=26
    No* raiz = new No(7);
    raiz->esquerda = new No(1);
    raiz->esquerda->direita = new No(2);
    raiz->esquerda->direita->esquerda = new No(1);
    raiz->esquerda->direita->direita = new No(5);
    raiz->esquerda->direita->esquerda->direita = new No(1);
    raiz->esquerda->direita->esquerda->direita->direita = new No(1);
    raiz->esquerda->direita->esquerda->direita->direita->direita = new No(1);
    raiz->esquerda->direita->direita->direita = new No(5);
    raiz->esquerda->direita->direita->esquerda = new No(4);
    raiz->direita = new No(18);
    raiz->direita->esquerda = new No(9);
    raiz->direita->esquerda->esquerda = new No(7);
    raiz->direita->esquerda->direita = new No(12);
    raiz->direita->esquerda->direita->esquerda = new No(9);
    raiz->direita->esquerda->direita->direita = new No(16);
    raiz->direita->esquerda->direita->direita->direita = new No(16);
    raiz->direita->esquerda->direita->direita->direita->direita = new No(16);
    raiz->direita->esquerda->direita->direita->esquerda = new No(12);
    raiz->direita->esquerda->direita->direita->esquerda->direita = new No(14);
    raiz->direita->esquerda->direita->direita->esquerda->direita->direita = new No(15);
    raiz->direita->direita = new No(21);
    raiz->direita->direita->esquerda = new No(19);
    raiz->direita->direita->esquerda->esquerda = new No(18);
    raiz->direita->direita->esquerda->direita = new No(20);

    cout << "Altura da árvore: " << alturaArvore(raiz) << endl;

    return 0;
}