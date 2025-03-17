#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <sys/resource.h>
using namespace std;

//Estrutura generica requerida no enunciado
struct Generico {
    string text;
    double numA;
    double numB;
} ;

//coisas/iniciador para a biblioteca random funcionar
const string CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
random_device rd;
mt19937 gen(rd());
uniform_int_distribution <> texto(0, CHARS.size() -1);
uniform_real_distribution <> valorA(1, 10000000);           //possui dois geradores de numeros reais
uniform_real_distribution <> valorB(1, 10000000);           //para nao gerarem o mesmo numero
uniform_int_distribution <> qtd(100, 500);

//funcao para gerar uma string aleatoria, entre 100 a 500 caracteres
string randomStringGen (int length) {
    string randomString;
    for (long int j = 0; j < length; ++j) {
        randomString += CHARS[texto(gen)];
    }
    return randomString;
}

//funcao para medir o tempo do programa
//copiado do programa_mede_memoria.cpp e transformado em funcao
void tempoDeUso() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    cout << endl;
    cout << "Tempo de usuario (user): " << usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0 << "s" << endl;
    cout << "Tempo de sistema (sys): " << usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0 << "s" << endl;
    cout << endl;
}

int main() {

    long int i = 0;

    struct rusage medeMemoria;
    getrusage(RUSAGE_SELF, &medeMemoria);
    cout << "Uso de memoria antes do programa: " << medeMemoria.ru_maxrss << " KB" << endl;

    Generico* generico = new Generico;

    tempoDeUso();

    //loop que gera 10000 strings (entre 100 a 500 caracteres) e 2 valores reais (doubles)
    for (i = 0; i < 10000; i++) {
        
        Generico* generico = new Generico;
        generico->text = randomStringGen(qtd(gen));
        generico->numA = valorA(gen);
        generico->numB = valorB(gen);

    }

    tempoDeUso();

    //loop que vai ate 1e6
    for (i = 10000; i <= 1000000; i += 5000) {

        for (int j = 1; j <= 5000; j++) {
            
        Generico* generico = new Generico;
        generico->text = randomStringGen(qtd(gen));
        generico->numA = valorA(gen);
        generico->numB = valorB(gen);

        }

        getrusage(RUSAGE_SELF, &medeMemoria);
        cout << "Processo: " << i << endl;
        cout << "Uso de memoria atual: " << medeMemoria.ru_maxrss << " KB" << endl;
        cout << "Endereco: " << &generico << "\n \n";

    }
    
    tempoDeUso();

    getrusage(RUSAGE_SELF, &medeMemoria);
    cout << "Uso de memoria depois do programa: " << medeMemoria.ru_maxrss << " KB" << endl;

    delete generico;

    cout << "\n" << "confirmacao que o codigo terminou de rodar, depois de deletar" << endl;

    return 0;
}