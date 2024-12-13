#include <iostream>
#include <iomanip>
#include <chrono>
#include <sys/resource.h>
using namespace std;

unsigned long long int fibonacci(unsigned long long int valor) {
   if (valor <= 2)
      return 1;
   unsigned long long int n1 = 1; // 1 Termo
   unsigned long long int n2 = 1; // 2 Termo
   for(unsigned long long int i=2; i < valor; ++i){
      unsigned long long int anterior = n1;
      n1 = n2;
      n2 = anterior + n1;
   }
  return n2;
}

int main() {

   struct rusage r_usage;
   getrusage(RUSAGE_SELF,&r_usage);
   cout << r_usage.ru_utime.tv_sec << ":" << r_usage.ru_stime.tv_sec << std::endl;
   cout << "Uso de memória atual: " << r_usage.ru_maxrss << "KB" << endl;

   auto startH = std::chrono::high_resolution_clock::now();

    for (int i = 5; i <= 500; i += 5) {
        auto start = chrono::high_resolution_clock::now();
        fibonacci(i);
        auto stop = chrono::high_resolution_clock::now();
        auto d12 = chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

        cout << i << ";" << d12.count() << endl;
    }

   auto stopH = std::chrono::high_resolution_clock::now();

   auto d1 = std::chrono::duration_cast<std::chrono::microseconds>(stopH - startH);

   getrusage(RUSAGE_SELF, &r_usage);
   auto userTime = r_usage.ru_utime.tv_sec * 1000000.0 + r_usage.ru_utime.tv_usec;
   auto sysTime = r_usage.ru_stime.tv_sec * 1000000.0 + r_usage.ru_stime.tv_usec;

   cout << endl;
   cout << "O programa demorou " << setprecision(5) << d1.count() << " microssegundos para terminar de rodar." << endl;
   cout << "O programa teve " << userTime << " microssegundos de tempo de usuário e " << sysTime << " microssegundos de tempo de sistema." << endl;
   cout << "O programa está utilizando atualmente " << r_usage.ru_maxrss << " KB de memória RAM" << endl; 
}