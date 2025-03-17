#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double pi = 0;
    for (long long int n = 0; n < 1000000000; ++n) {
        pi += (pow(-1, n) / (2 * n + 1)) * 4;
    }
    cout << "Resultado: " << pi << endl;
}