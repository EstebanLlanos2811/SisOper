#include <iostream>
#include <vector>
//#include <string>
//#include <algorithm>

using namespace std;

struct Pagina {
    int numero; // Número de página
    int procesoID; // ID del proceso al que pertenece la página
    // Otros atributos relevantes según la lógica de tu sistema de paginación
};

struct Proceso {
    int id;
    int tamano;
    vector<int> paginasAsignadas;
};

class simuladorSegmentacion{
private:
    int tamanoMemoria;
    int tamanoPagina;
    vector<Pagina> memoriaPaginada;
    vector<Proceso> procesos;
public:
    simuladorSegmentacion(int tamano, int tamanoPag) : tamanoMemoria(tamano), tamanoPagina(tamanoPag){
        this->memoriaPaginada = {};
        this->procesos = {};
    }

    bool asignarMemoria(int procesoID, int tamano) {
        int paginasNecesarias = tamano % tamanoPagina == 0 ? tamano / tamanoPagina : tamano / tamanoPagina + 1;

        if (tamanoMemoria < paginasNecesarias) {
            return false;
        }

        vector<int> paginas;
        for (int i = 0; i < paginasNecesarias; i++) {
            Pagina pagina;
            pagina.numero = i;
            pagina.procesoID = procesoID;
            memoriaPaginada.push_back(pagina);
            paginas.push_back(i);
        }

        Proceso proceso;
        proceso.id = procesoID;
        proceso.tamano = tamano;
        proceso.paginasAsignadas = paginas;

        procesos.push_back(proceso);

        return true;
    }

    void liberarMemoria(int procesoID) {

        for (auto it = memoriaPaginada.begin(); it != memoriaPaginada.end();) {
            if (it->procesoID == procesoID) {
                it = memoriaPaginada.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = procesos.begin(); it != procesos.end();) {
            if (it->id == procesoID) {
                it = procesos.erase(it);
            } else {
                ++it;
            }
        }
    }

    void imprimirEstadoMemoria() {

        cout << "Estado de la memoria paginada" << endl;
        for (const Pagina &pagina : memoriaPaginada) {
            cout << "Pagina numero: " << pagina.numero << ", Proceso ID: " << pagina.procesoID << endl;
        }
        cout << endl;

        cout << "Procesos en memoria:" << endl;
        for (const Proceso &p : procesos) {
            cout << "Proceso ID: " << p.id << ", Tamano: " << p.tamano << ", Paginas: ";
            for (int pagina : p.paginasAsignadas) {
                cout << pagina << ", ";
            }
            cout << endl;
        }
    }
};

int main(){
    int tamanoMemoria = 100;
    int tamanoPagina = 20;
    simuladorSegmentacion simulador(tamanoMemoria,tamanoPagina);
    simulador.asignarMemoria(1,30);
    simulador.asignarMemoria(2,40);
    simulador.asignarMemoria(3,15);

    simulador.liberarMemoria(1);
    simulador.imprimirEstadoMemoria();

    return 0;
}