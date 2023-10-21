#include <iostream>

int main() {
    int** matrizDinamica;
    int filas = 3;
    int columnas = 4;

    matrizDinamica = new int*[filas];

    for (int i = 0; i < filas; i++){
        matrizDinamica[i] = new int[columnas]; 
    }

    int valor = 1;
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            matrizDinamica[i][j] = valor++;
        }
    }
    
    std::cout << "Matriz Dinámica:" << std::endl;
    for (int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            std::cout << matrizDinamica[i][j] << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < filas; i++){
        delete[] matrizDinamica[i];
    }
    delete[] matrizDinamica;

    return 0;
}