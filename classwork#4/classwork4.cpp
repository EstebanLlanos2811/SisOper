#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

class GestorMemoria {
    private:
        int tamanoMemoria;          // Tamaño total de la memoria
        int seg;                    // Número de segmentos
        std::vector<int> memoria;   // Vector que representa el estado de la memoria
        std::vector<int> segmentos; // Vector que almacena los tamaños de los segmentos

    public:
    // Establece el tamaño de la memoria y crea un vector de memoria inicializado en -1
    void setMem(int tamano){
        tamanoMemoria = tamano; 
        memoria = std::vector<int>(tamano, -1);
    }

    // Asigna los valores del vector recibido al vector 'segmentos'
    void asignarVector(const std::vector<int>& vec, int partes) {
        segmentos = vec;
        seg = partes;
    }

    // Implementación del algoritmo First-fit para asignar memoria.
    // Asigna un segmento de memoria al proceso con el identificador 'procesoID' y tamaño 'tamano'
    // Devuelve 0 si se asigna correctamente, -1 si no se puede asignar en ningún segmento.
    int asignarMemoriaFirstFit(int procesoID, int tamano){
        int contAux;      // Contador auxiliar para el tamaño disponible en un segmento
        int flag = 0;     // Bandera para indicar si se ha asignado memoria
        int j = 0;        // Índice auxiliar para recorrer la memoria
        int aux;          // Variable auxiliar para calcular el rango de búsqueda en la memoria
        for (int i = 0; i < seg; i++) {
            int conteo = 0;  // Contador de celdas libres consecutivas en un segmento
            aux = segmentos[i] + j;  // Calcular el rango de búsqueda en la memoria
            for( j; j < aux; j++ ){
                if(memoria[j] == -1){
                    conteo++;
                }
            }
            contAux = segmentos[i] - conteo;
            if( conteo >= tamano ){
                flag = 1;
                aux -= contAux;
                // Asignar el proceso en las celdas consecutivas de la memoria
                for( int k = aux - 1; k >= aux - tamano; k-- ){
                    memoria[k] = procesoID;
                }
                printf("El proceso: %d, fue asignado en memoria en el segmento: %d\n", procesoID, i);
                i = segmentos.size();  // Salir del bucle
            }
        }
        if( !flag ){
            printf("El proceso: %d, no se pudo asignar en ningún segmento de la memoria\n", procesoID);
        }
        return 0;
    }
    // Implementación del algoritmo Best-fit para asignar memoria.
    // Asigna un segmento de memoria al proceso con el identificador 'procesoID' y tamaño 'tamano'
    // Devuelve 0 si se asigna correctamente, -1 si no se puede asignar en ningún segmento.
    int asignarMemoriaBestFit(int procesoID, int tamano){
        int j = 0;           // Índice auxiliar para recorrer la memoria
        int aux = 0;         // Variable auxiliar para calcular el rango de búsqueda en la memoria
        int bestfit = 2147483647;  // Mejor ajuste inicializado a un valor grande
        int bestseg = -1;    // Índice del mejor segmento
        int contAux;         // Contador auxiliar para el tamaño disponible en un segmento

        // Iterar sobre los segmentos de memoria
        for (int i = 0; i < seg; i++) {
            int conteo = 0;  // Contador de celdas libres consecutivas en un segmento
            aux = segmentos[i] + j;  // Calcular el rango de búsqueda en la memoria

            // Contar las celdas libres en el segmento
            for( j; j < aux; j++ ){
                if(memoria[j] == -1){
                    conteo++;
                }
            }

            // Verificar si el segmento es lo suficientemente grande para el proceso
            if( conteo >= tamano ){
                // Actualizar el mejor ajuste si es más adecuado
                if(conteo - tamano < bestfit){
                    bestfit = conteo - tamano;
                    bestseg = i;
                    contAux = segmentos[i] - conteo;
                }
            }
        }

        // Verificar si se encontró un segmento adecuado
        if( bestseg == -1 ){
            printf("El proceso: %d, no se pudo asignar en ningún segmento de la memoria\n", procesoID);
        } else {
            aux = 0;

            // Calcular la posición de inicio del segmento seleccionado
            for( int i = 0; i <= bestseg; i++ ){
                aux += segmentos[i];
            }
            aux -= contAux;

            // Asignar el proceso en las celdas consecutivas de la memoria
            for( int k = aux - 1; k >= aux - tamano; k-- ){
                    memoria[k] = procesoID;
            }

            printf("El proceso: %d, fue asignado en memoria en el segmento: %d\n", procesoID, bestseg);
        }
        return 0;
    }
    // Implementación del algoritmo Worst-fit para asignar memoria.
    // Asigna un segmento de memoria al proceso con el identificador 'procesoID' y tamaño 'tamano'
    // Devuelve 0 si se asigna correctamente, -1 si no se puede asignar en ningún segmento.
    int asignarMemoriaWorstFit(int procesoID, int tamano){
        int j = 0;           // Índice auxiliar para recorrer la memoria
        int aux = 0;         // Variable auxiliar para calcular el rango de búsqueda en la memoria
        int worstFit = -1;   // Peor ajuste inicializado a un valor pequeño
        int wortSeg = -1;    // Índice del peor segmento
        int contAux;         // Contador auxiliar para el tamaño disponible en un segmento

        // Iterar sobre los segmentos de memoria
        for (int i = 0; i < seg; i++) {
            int conteo = 0;  // Contador de celdas libres consecutivas en un segmento
            aux = segmentos[i] + j;  // Calcular el rango de búsqueda en la memoria

            // Contar las celdas libres en el segmento
            for( j; j < aux; j++ ){
                if(memoria[j] == -1){
                    conteo++;
                }
            }

            // Verificar si el segmento es lo suficientemente grande para el proceso
            if( conteo >= tamano ){
                // Actualizar el peor ajuste si es más grande
                if(conteo - tamano > worstFit){
                    worstFit = conteo - tamano;
                    wortSeg = i;
                    contAux = segmentos[i] - conteo;
                }
            }
        }

        // Verificar si se encontró un segmento adecuado
        if( wortSeg == -1 ){
            printf("El proceso: %d, no se pudo asignar en ningún segmento de la memoria\n", procesoID);
        } else {
            aux = 0;

            // Calcular la posición de inicio del segmento seleccionado
            for( int i = 0; i <= wortSeg; i++ ){
                aux += segmentos[i];
            }
            aux -= contAux;

            // Asignar el proceso en las celdas consecutivas de la memoria
            for( int k = aux - 1; k >= aux - tamano; k-- ){
                    memoria[k] = procesoID;
            }

            printf("El proceso: %d, fue asignado en memoria en el segmento: %d\n", procesoID, wortSeg);
        }
        return 0;
    }
    // Implementación de la función para liberar la memoria ocupada por un proceso.
    // Busca y libera todas las instancias del proceso con el identificador 'procesoID' en la memoria.
    // Imprime un mensaje indicando si el proceso fue encontrado y liberado o si no está en memoria.
    void liberarMemoria(int procesoID){
        int flag = 0;   // Bandera para indicar si se encontró y liberó el proceso
        // Iterar sobre todas las celdas de la memoria
        for( int i = 0; i < tamanoMemoria; i++ ){
            // Verificar si la celda contiene el identificador del proceso
            if ( memoria[i] == procesoID ){
                memoria[i] = -1; // Liberar el bloque de memoria
                flag = 1; // Establecer la bandera ya que se encontró y liberó el proceso
            }
        }
        // Imprimir mensajes según el resultado de la operación
        if(flag){
          printf("El proceso: %d, se borro de la memoria\n", procesoID);
        }else{
          printf("El proceso: %d, no esta en memoria\n", procesoID);
        }
    }

    // Función para imprimir el estado actual de la memoria.
    // Imprime en la consola el contenido de cada celda de la memoria.
    void imprimirEstadoMemoria(){
        std:: cout << "Estado de la memoria: ";

        // Iterar sobre todas las celdas de la memoria
        for (int i = 0; i < tamanoMemoria; i++){
            std:: cout << memoria[i] << " ";
        }

        std::cout << std::endl;  // Salto de línea al final para mejorar la legibilidad
    }
};

class Reader {
  private:
      std::string nombreArchivoEntrada;   // Nombre del archivo de entrada
      std::string nombreArchivoSalida;    // Nombre del archivo de salida
  
  public:
      // Constructor que toma los nombres de los archivos de entrada y salida como parámetros.
      Reader(const std::string& entrada, const std::string& salida)
          : nombreArchivoEntrada(entrada), nombreArchivoSalida(salida) {}
  
      // Procesa el archivo de entrada, omite las líneas que comienzan con '#' y guarda el resultado en el archivo de salida.
      void procesarArchivo() {
          std::ifstream archivoEntrada(nombreArchivoEntrada);
  
          // Verificar si el archivo de entrada se pudo abrir correctamente
          if(!archivoEntrada.is_open()){
              std::cerr << "No se puede abrir el archivo de entrada." << std::endl;
              return;
          }
  
          std::ofstream archivoSalida(nombreArchivoSalida);
  
          // Verificar si el archivo de salida se pudo crear correctamente
          if(!archivoSalida.is_open()){
              std::cerr << "No se puede crear el archivo de salida." << std::endl;
              return;
          }
  
          std::string linea;
  
          // Leer el archivo de entrada línea por línea
          while(std::getline(archivoEntrada, linea)){
              // Omitir líneas vacías o aquellas que comienzan con '#'
              if(linea.empty() || linea[0] == '#'){
                  continue;
              }
  
              // Escribir la línea procesada en el archivo de salida
              archivoSalida << linea << std::endl;
          }
  
          // Cerrar los archivos después de su uso
          archivoEntrada.close();
          archivoSalida.close();
  
          // Imprimir mensaje indicando que el proceso se ha completado
          std::cout << "Proceso completado. Las líneas que comenzaban con '#' se han omitido." << std::endl;
      }
};

int main() {
    GestorMemoria mmu;  // Crear una instancia del GestorMemoria
    Reader reader("archivo_entrada.txt", "archivo_salida.txt");  // Crear una instancia del Reader

    // Procesar el archivo de entrada y realizar operaciones en el GestorMemoria según las instrucciones del archivo
    reader.procesarArchivo();

    // Abrir el archivo de salida para realizar operaciones adicionales
    std::ifstream file("archivo_salida.txt");

    if (file.is_open()) {
        std::string line;
        int size, segmento, algoritmo;
        std::vector<int> vector;

        // Leer la primera línea y convertirla a int para establecer el tamaño de la memoria en el GestorMemoria
        if (std::getline(file, line)) {
            size = std::stoi(line);
        }
        mmu.setMem(size);

        // Leer la segunda línea y convertirla a int para establecer el número de segmentos en el GestorMemoria
        if (std::getline(file, line)) {
            segmento = std::stoi(line);
        }

        // Leer la tercera línea y convertirla a un vector de enteros para establecer los tamaños de los segmentos en el GestorMemoria
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            int num;
            while (ss >> num) {
                vector.push_back(num);
                if (ss.peek() == ',') {
                    ss.ignore();
                }
            }
        }
        mmu.asignarVector(vector, segmento);

        // Leer la cuarta línea y convertirla a int para determinar el algoritmo a utilizar en el GestorMemoria
        if (std::getline(file, line)) {
            algoritmo = std::stoi(line);
        }

        // Leer líneas adicionales hasta encontrar una línea vacía
        while (std::getline(file, line) && !line.empty()) {
            std::istringstream iss(line);
            std::string str = iss.str();

            // Realizar operaciones según las instrucciones proporcionadas en el archivo de salida
            if(str == "imprimirEstadoMemoria"){
                mmu.imprimirEstadoMemoria();
            } else if( str.substr(0, 9) == "liberarar" ){
                // Extraer el número de proceso a liberar y llamar a la función en el GestorMemoria
                std::istringstream iss(str.substr(10));
                int num;
                if (iss >> num) {
                    mmu.liberarMemoria(num);
                }
            } else {
                int a, b;
                char coma;

                // Extraer datos de proceso y llamar a la función correspondiente en el GestorMemoria
                if (iss >> a >> coma >> b && coma == ',') {
                    std::vector<int> proceso = {a, b};
                    if( algoritmo == 1 ){
                        mmu.asignarMemoriaFirstFit(proceso[0], proceso[1]);
                    } else if( algoritmo == 2 ){
                        mmu.asignarMemoriaBestFit(proceso[0], proceso[1]);
                    } else if( algoritmo == 3 ){
                        mmu.asignarMemoriaWorstFit(proceso[0], proceso[1]);
                    }
                }
            }
        }

        file.close();  // Cerrar el archivo después de su uso
    } 

    return 0;
}
