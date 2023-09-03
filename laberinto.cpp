#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void imprimir(const vector<vector<char>>& laberinto) {
    for (const auto& row : laberinto) {
        for (char value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

void EntradaSalida(vector<vector<char>>& laberinto) {
    // Buscar la entrada y la salida en los bordes superiores e inferiores
    for (int columna = 0; columna < laberinto[0].size(); ++columna) {
        if (laberinto[0][columna] == ' ') {
            laberinto[0][columna] = 'e';
        }
        if (laberinto[laberinto.size() - 1][columna] == ' ') {
            laberinto[laberinto.size() - 1][columna] = 's';
        }
    }

    // Buscar la entrada y la salida en los bordes izquierdo y derecho
    for (int fila = 0; fila < laberinto.size(); ++fila) {
        if (laberinto[fila][0] == ' ') {
            laberinto[fila][0] = 'e';
        }
        if (laberinto[fila][laberinto[fila].size() - 1] == ' ') {
            laberinto[fila][laberinto[fila].size() - 1] = 's';
        }
    }
}


bool Encontrar_camino_dfs(vector<vector<char>>& laberinto, int fila, int columna) {
    if (fila < 0 || fila >= laberinto.size() || columna < 0 || columna >= laberinto[fila].size() ||
        laberinto[fila][columna] == '#' || laberinto[fila][columna] == '*') {
        return false; // Fuera de los límites, es una pared o ya visitado
    }

    if (laberinto[fila][columna] == 's') {
        return true; // Encontramos la salida
    }

    // Marcar la celda como visitada solo temporalmente
    char temp = laberinto[fila][columna];
    laberinto[fila][columna] = '*';

    // Intentamos moverse en todas las direcciones (arriba, abajo, izquierda, derecha)
    if (
        Encontrar_camino_dfs(laberinto, fila, columna + 1) || // Derecha
        Encontrar_camino_dfs(laberinto, fila + 1, columna) || // Abajo
        Encontrar_camino_dfs(laberinto, fila - 1, columna) || // Arriba
        Encontrar_camino_dfs(laberinto, fila, columna - 1)) { // Izquierda
        return true;
    }

    // No hay camino desde esta celda, revertir la marca
    laberinto[fila][columna] = temp;

    return false;
}

void guardar(vector<vector<char>>& laberinto){
        cout << "\nSe guardara el archivo en nuevo2.txt...\n";
        ofstream salida("nuevo2.txt");
        if (salida.is_open()) {
        // Escribir la matriz en el archivo
        for (int i = 0; i<laberinto.size(); ++i) {
            for (int j = 0; j<laberinto[i].size(); ++j) {
                salida << laberinto[i][j] ;
            }
            salida <<endl; // Nueva línea al final de cada fila
        }

        // Cerrar el archivo
        salida.close();
        cout << "\nGuardado exitosamente en 'nuevo2.txt\n";
    } else {
        cerr << "No se pudo abrir el archivo para escritura.\n";
    }

}




int main() {
    ifstream entrada("nuevo.txt");

    if (!entrada.is_open()) {
        cout << "error al leer." << endl;
        return 1;
    }

    char pared = '█';
    char vacio = ' ';

    vector<vector<char>> laberinto;
    string line;
    while (getline(entrada, line)) {
        vector<char> row;
        for (char dato : line) {
            if (dato == pared) {
                row.push_back('#');
            }
            else if (dato == vacio) {
                row.push_back(' ');
            }
        }
        laberinto.push_back(row);
    }
    entrada.close();

    imprimir(laberinto);
    EntradaSalida(laberinto);

    // Obtén las coordenadas de la entrada ('e')
    int entradaFila = -1;
    int entradaColumna;
    for (int fila = 0; fila < laberinto.size(); ++fila) {
        for (int columna = 0; columna < laberinto[fila].size(); ++columna) {
            if (laberinto[fila][columna] == 'e') {
                entradaFila = fila;
                entradaColumna = columna;
                break;
            }
        }
        if (entradaFila != -1) {
            break;
        }
    }

    cout << "\nLaberinto con entradas (e) y salidas (s):\n";
    imprimir(laberinto);

    // Llamamos a la función para encontrar el camino
    if (Encontrar_camino_dfs(laberinto, entradaFila, entradaColumna)) {
        cout << "\nCamino encontrado\n";
        imprimir(laberinto);
        guardar(laberinto);

    }
    else {
        cout << "\nNo se encontró un camino.\n";
    }

    

    return 0;

}
