#include <chrono>

#include <iomanip>
#include <sys/resource.h>
#include <unistd.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Registro {
    int n1;
    int n2;
};

int mdc_recursivo(int m, int n)
{
    if( m == n)
    {
        return m;
    }
    if( m-n >= n)
    {
        return mdc_recursivo(m-n,n);
    }
    return mdc_recursivo(n,m-n);
}

int mdc_iterativo(int m, int n)
{
    if( n == 0)
    {
        return m;
    }
    while( m % n != 0)
    {
        int resto = m % n;
        m = n;
        n = resto;
    }
    return n;

}

int mdc_sub_recursivo(int m, int n)
{
    if( m == n)
    {
        return m;
    }
    if( m-n >= n)
    {
        return mdc_sub_recursivo(m-n,n);
    }
    return mdc_sub_recursivo(n,m-n);
}

std::vector<Registro> lerArquivoCSV(const std::string& nomeArquivo) {
    std::vector<Registro> registros;
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << nomeArquivo << std::endl;
        return registros;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::size_t pos = linha.find(";");
        if (pos != std::string::npos) {
            Registro registro;
            registro.n1 = atoi(linha.substr(0, pos).c_str());
            registro.n2 = atoi(linha.substr(pos + 1).c_str());
            //garantindo que o maior está em n1
            if( registro.n1 < registro.n2 ){
               int aux = registro.n2;
               registro.n2 = registro.n1;
               registro.n1 = aux;
            }
            registros.push_back(registro);
        }
    }

    arquivo.close();
    return registros;
}

int main() {
    std::string nomeArquivo = "teste.csv";
    std::vector<Registro> dados = lerArquivoCSV(nomeArquivo);

    for( int i=5; i<=200; i+=5){

       //iterativo
       auto start_mdciterativo = std::chrono::steady_clock::now();
       for( int k=0;k<i;++k){
           mdc_iterativo(dados[k].n1, dados[k].n2);
       }
       auto stop_mdciterativo = std::chrono::steady_clock::now();

       //recursivo
       auto start_mdcrecursivo = std::chrono::steady_clock::now();
       for( int k=0;k<i;++k){
           mdc_recursivo(dados[k].n1, dados[k].n2);
       }
       auto stop_mdcrecursivo = std::chrono::steady_clock::now();

       //recursivo sub
       auto start_mdcsubrecursivo = std::chrono::steady_clock::now();
       for( int k=0;k<i;++k){
           mdc_sub_recursivo(dados[k].n1, dados[k].n2);
       }
       auto stop_mdcsubrecursivo = std::chrono::steady_clock::now();

       auto d1 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_mdciterativo - start_mdciterativo);
       auto d2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_mdcrecursivo - start_mdcrecursivo);
       auto d3 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_mdcsubrecursivo - start_mdcsubrecursivo);

       std::cout << i << ";" << d1.count() << ";" << d2.count() << ";" << d3.count() << ";" << std::endl;

       /*
        cout pro iterativo: std::cout << "(" << i << ", " << d1.count() << ") ";
        cout pro recursivo: std::cout << "(" << i << ", " << d2.count() << ") ";
        cout pro subrecursivo: std::cout << "(" << i << ", " << d3.count() << ") ";
       */
    }

    return 0;
}