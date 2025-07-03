#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void pivoteamentoParcial(double** matriz, int n, int coluna) {
    int linhaMax = coluna;
    for (int i = coluna + 1; i < n; ++i) {
        if (abs(matriz[i][coluna]) > abs(matriz[linhaMax][coluna])) {
            linhaMax = i;
        }
    }
    if (linhaMax != coluna) {
        for (int j = 0; j <= n; ++j) {
            double temp = matriz[coluna][j];
            matriz[coluna][j] = matriz[linhaMax][j];
            matriz[linhaMax][j] = temp;
        }
    }
}

int main() {
    int n;
    cin >> n;

    double** matriz = new double*[n];

    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;

        matriz[i] = new double[n + 1];
        for (int j = 0; j < n; ++j)
            matriz[i][j] = pow(x, j);

        matriz[i][n] = y; 
    }

    for (int i = 0; i < n; ++i) {
        pivoteamentoParcial(matriz, n, i);

        for (int j = i + 1; j < n; ++j) {
            double fator = matriz[j][i] / matriz[i][i];
            for (int k = i; k <= n; ++k) {
                matriz[j][k] -= fator * matriz[i][k];
            }
        }
    }

    double* resultado = new double[n];
    for (int i = n - 1; i >= 0; --i) {
        resultado[i] = matriz[i][n];
        for (int j = i + 1; j < n; ++j)
            resultado[i] -= matriz[i][j] * resultado[j];
        resultado[i] /= matriz[i][i];
    }

    for (int i = 0; i < n; ++i) {
        cout << resultado[i] << endl;
    }

    for (int i = 0; i < n; ++i)
        delete[] matriz[i];
    delete[] matriz;
    delete[] resultado;

    return 0;
}
