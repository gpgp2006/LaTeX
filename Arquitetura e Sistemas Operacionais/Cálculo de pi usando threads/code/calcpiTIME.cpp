#include <iostream>
#include <iomanip>
#include <cmath>
#include <pthread.h>
#include <chrono>
using namespace std;

#define NUM_THREADS 1

double results[NUM_THREADS];

void *calcpi(void *threadid) {
    long id = (long)threadid;
    double soma = 0;

    long long inicio = id * (1000000000 / NUM_THREADS);
    long long fim = (id + 1) * (1000000000 / NUM_THREADS);

    for (long long n = inicio; n < fim; ++n) {
        soma += (pow(-1, n) / (2 * n + 1)) * 4;
    }

    results[id] = soma;
    pthread_exit(nullptr);
}

int main() {
    int media = 0;
    for (int vezes = 1; vezes <= 5; vezes++) {
    auto start = std::chrono::high_resolution_clock::now();
    pthread_t threads[NUM_THREADS];
    int status;

    for (long i = 0; i < NUM_THREADS; i++) {
        //cout << "Criando thread " << i << endl;
        status = pthread_create(&threads[i], nullptr, calcpi, (void *)i);

        if (status) {
            cerr << "Erro ao criar thread " << i << endl;
            exit(-1);
        }
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], nullptr);
    }

    double pi = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pi += results[i];
    }

    //cout << fixed << setprecision(10) << "Resultado: " << pi << endl;

    auto stop = std::chrono::high_resolution_clock::now();

    auto d1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    cout << "(" << vezes << ", " << d1.count() << ") ";

    media += d1.count();
    }
    cout << endl;
    cout << "media: " << media / 5 << endl;
    return 0;
}
