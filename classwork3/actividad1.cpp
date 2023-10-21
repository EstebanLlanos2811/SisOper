#include <iostream>

int main(){
    int numero = 42;

    std::cout << "Valor de la cariable 'numero': " << numero << std::endl;
    
    std::cout << "Dirección de memoria de 'numero': " << &numero << std::endl;

    int* punteroNumero = &numero;
    *punteroNumero = 100;

    std::cout << "Nuevo valor de la variable 'numero': " << numero << std::endl;

    return 0;
}