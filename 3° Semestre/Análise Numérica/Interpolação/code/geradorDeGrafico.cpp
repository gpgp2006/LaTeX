#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void pivoteamentoParcial(double **matriz, int n, int coluna) {
  int linhaMax = coluna;
  for (int i = coluna + 1; i < n; ++i) {
    if (abs(matriz[i][coluna]) > abs(matriz[linhaMax][coluna])) {
      linhaMax = i;
    }
  }
  if (linhaMax != coluna) {
    for (int j = 0; j <= n;
         ++j) { // precisa ir ate n, incluindo termo independente
      swap(matriz[coluna][j], matriz[linhaMax][j]);
    }
  }
}

int main() {
  int n;
  cin >> n;

  double **matriz = new double *[n];

  for (int i = 0; i < n; ++i) {
    double x, y;
    cin >> x >> y;

    matriz[i] = new double[n + 1];
    for (int j = 0; j < n; ++j)
      matriz[i][j] = pow(x, j);

    matriz[i][n] = y; // termo independente
  }

  // Eliminacao de Gauss com pivoteamento parcial
  for (int i = 0; i < n; ++i) {
    pivoteamentoParcial(matriz, n, i);

    for (int j = i + 1; j < n; ++j) {
      double fator = matriz[j][i] / matriz[i][i];
      for (int k = i; k <= n; ++k) {
        matriz[j][k] -= fator * matriz[i][k];
      }
    }
  }

  // Substituicao regressiva
  double *resultado = new double[n];
  for (int i = n - 1; i >= 0; --i) {
    resultado[i] = matriz[i][n];
    for (int j = i + 1; j < n; ++j)
      resultado[i] -= matriz[i][j] * resultado[j];
    resultado[i] /= matriz[i][i];
  }

  string saida = "";

  for (int i = 0; i < n; ++i) {
    cout<<resultado[i]<<endl;
    if (resultado[i] < 0)
      saida = saida + " " +to_string(resultado[i]) + "*x**" + to_string(i);
    else
      saida = saida + " + " + to_string(resultado[i]) + "*x**" + to_string(i);
  }

  saida = "gnuplot -e \"set terminal png; set grid; unset key; set output "
          "'saida.png'; "
          "plot " +
          saida + " with lines dashtype 2 lc 'blue', 'entrada' skip 2 with points pt 7 lc 'black' \"";

  system(saida.c_str());
  system("xdg-open saida.png");
  // Liberacao de memoria
  for (int i = 0; i < n; ++i)
    delete[] matriz[i];
  delete[] matriz;
  delete[] resultado;

  return 0;
}