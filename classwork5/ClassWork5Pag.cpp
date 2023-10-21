#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Pagina {
    int idProceso;
};

struct Proceso{
    int id;
    int tamano;
    vector <int> paginasAsignadas;
};

class simuladorPaginacion {
private:
    int tamanoMemoria;
    int tamanoPagina;
    vector<Pagina> memoriaPaginada;
    vector<Proceso> procesos;

public:
    simuladorPaginacion(int tamano, int tamanoPag) : tamanoMemoria(tamano), tamanoPagina(tamanoPag){
        int numPaginas = tamanoMemoria/tamanoPagina;
        memoriaPaginada.resize(numPaginas,{-1});
    }

    void asignarMemoria(Proceso proceso) {
        int numPaginasNecesarias = proceso.tamano / tamanoPagina + (proceso.tamano % tamanoPagina == 0 ? 0 : 1);
        int paginasAsignadas = 0;
        for (int i = 0; i < memoriaPaginada.size() && paginasAsignadas < numPaginasNecesarias; i++) {
            if (memoriaPaginada[i].idProceso == -1) {
                memoriaPaginada[i].idProceso = proceso.id;
                proceso.paginasAsignadas.push_back(i);
                paginasAsignadas++;
            }
        }
        if (paginasAsignadas < numPaginasNecesarias) {
            cout << "No hay suficiente memoria disponible para asignar al proceso " << proceso.id << endl;
        } else {
            procesos.push_back(proceso);
        }
    }

    void liberarMemoria(int idProceso) {
        for (auto &pagina : memoriaPaginada) {
            if (pagina.idProceso == idProceso) {
                pagina.idProceso = -1;
            }
        }
        procesos.erase(remove_if(procesos.begin(), procesos.end(), [idProceso](const Proceso &p) { return p.id == idProceso; }), procesos.end());
    }

    void imprimirEstadoMemoria() {
        for (int i = 0; i < memoriaPaginada.size(); i++) {
            cout << "Pagina " << i << ": ";
            if (memoriaPaginada[i].idProceso == -1) {
                cout << "Libre" << endl;
            } else {
                cout << "Proceso " << memoriaPaginada[i].idProceso << endl;
            }
        }
    }
};

int main() {
    int tamanoMemoria = 100;
    int tamanoPagina = 20;
    simuladorPaginacion simulador(tamanoMemoria, tamanoPagina);

    Proceso proceso1 = {1, 40, {}};
    Proceso proceso2 = {2, 30, {}};
    Proceso proceso3 = {3, 60, {}};

    simulador.asignarMemoria(proceso1);
    simulador.asignarMemoria(proceso2);
    simulador.imprimirEstadoMemoria();
    cout << "--------------------" << endl;
    simulador.liberarMemoria(1);
    simulador.asignarMemoria(proceso3);
    simulador.imprimirEstadoMemoria();

    return 0;
}