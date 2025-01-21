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

int nivelNo(No* raiz, int valor, int nivelAtual) {
    if (raiz == nullptr)
        return -1;

    if (raiz->dado == valor) 
        return nivelAtual;

    int nivelEsquerda = nivelNo(raiz->esquerda, valor, nivelAtual + 1);
    if (nivelEsquerda != -1)
        return nivelEsquerda;

    return nivelNo(raiz->direita, valor, nivelAtual + 1);
}

int main() {
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

    cout << "Nível do nó A: " << nivelNo(raiz, 1, 1) << endl;
    cout << "Nível do nó L: " << nivelNo(raiz, 12, 1) << endl;
    cout << "Nível do nó P: " << nivelNo(raiz, 16, 1) << endl;
    cout << "Nível do nó U: " << nivelNo(raiz, 21, 1) << endl;
    cout << "Nível do nó O: " << nivelNo(raiz, 15, 1) << endl;
    cout << "Nível da raiz: " << nivelNo(raiz, 7, 1) << endl;

    return 0;
}
