#include <iostream>

int main(){
    const int tamanoArray = 5;
    int numeros[tamanoArray] = {10,20,30,40,50};
    
    std::cout << "Contenido del array 'numeros': ";
    for (int i = 0; i < tamanoArray; i++)
    {
        std::cout << numeros[i] << " ";
    }
    std::cout << std::endl;

    int* punteroNumeros = numeros;
    
    punteroNumeros[1] = 99;

    std::cout << "Contenido del array 'numeros' despues de la modificacion: ";
    for (int i = 0; i < tamanoArray; i++)
    {
        std::cout << numeros[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;    
}