#include <iostream>

int main(){
    int numero = 42;
    int *punteroNumero = &numero;

    std::cout << "Valor de 'numero' a través del puntero: " << *punteroNumero << std::endl;

    *punteroNumero = 100;

    std::cout << "Nuevo valor de 'numero': " << numero << std::endl;

    int& referenciaNumero = numero;
    referenciaNumero = 200;

    std::cout << "Valor de 'numero' a través de la referencia: " << numero << std::endl;

    return 0;
}