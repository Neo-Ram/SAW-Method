#include <iostream>
#include <vector>
using namespace std;

// Función para imprimir una matriz
void imprimirMatriz(const vector<vector<float>>& matrizNormalizada) {
    for (size_t i = 0; i < matrizNormalizada.size(); i++) { // Iterar sobre las filas
        for (size_t j = 0; j < matrizNormalizada[i].size(); j++) { // Iterar sobre las columnas
            cout << matrizNormalizada[i][j] << "\t"; // Imprimir cada valor con tabulación
        }
        cout << endl; // Cambiar de línea al final de cada fila
    }
}

int main() {
    int numCriterios;
    cout << "Ingrese el numero de criterios: ";
    cin >> numCriterios;

    // Vectores para tipo de criterio y peso
    vector<char> tipoCriterio(numCriterios);
    vector<float> pesoCriterio(numCriterios);

    // Pedir criterios
    for (int i = 0; i < numCriterios; i++) {
        cout << "El criterio [" << (i + 1) << "] es de costo (c) o beneficio (b)? ";
        cin >> tipoCriterio[i];
        cout << "Ingrese el peso del criterio [" << (i + 1) << "]: ";
        cin >> pesoCriterio[i];
    }

    int numAlternativas;
    cout << "Ingrese el numero de alternativas: ";
    cin >> numAlternativas;

    // Matriz de valores
    vector<vector<int>> matrizValores(numAlternativas, vector<int>(numCriterios));

    // Llenar matriz de valores
    for (int i = 0; i < numAlternativas; i++) {
        cout << "Asignación de valores a los criterios de la alternativa [" << (i + 1) << "]: " << endl;
        for (int j = 0; j < numCriterios; j++) {
            cout << "   Ingrese el valor del criterio [" << (j + 1) << "]: ";
            cin >> matrizValores[i][j];
        }
        cout << endl;
    }

    // Matriz normalizada
    vector<vector<float>> matrizNormalizada(numAlternativas, vector<float>(numCriterios));

    // Normalización de datos
    for (int i = 0; i < numCriterios; i++) {
        if (tipoCriterio[i] == 'c') {
            // Minimizar: buscar el valor mínimo en la columna
            int minimo = matrizValores[0][i];
            for (int j = 1; j < numAlternativas; j++) {
                if (matrizValores[j][i] < minimo) {
                    minimo = matrizValores[j][i];
                }
            }
            // Normalizar los valores dividiendo el mínimo entre cada valor
            for (int j = 0; j < numAlternativas; j++) {
                matrizNormalizada[j][i] = static_cast<float>(minimo) / matrizValores[j][i];
            }

        } else if (tipoCriterio[i] == 'b') {
            // Maximizar: buscar el valor máximo en la columna
            int maximo = matrizValores[0][i];
            for (int j = 1; j < numAlternativas; j++) {
                if (matrizValores[j][i] > maximo) {
                    maximo = matrizValores[j][i];
                }
            }
            // Normalizar los valores dividiendo cada valor por el máximo
            for (int j = 0; j < numAlternativas; j++) {
                matrizNormalizada[j][i] = static_cast<float>(matrizValores[j][i]) / maximo;
            }
        }
    }

    // Imprimir matriz normalizada
    imprimirMatriz(matrizNormalizada);

    vector<float> valorAlternativas(numAlternativas, 0);
    // Cálculo del valor de preferencia
    for (int i = 0; i < numAlternativas; i++) {
        for (int j = 0; j < numCriterios; j++) {
            valorAlternativas[i] += matrizNormalizada[i][j] * pesoCriterio[j];
        }
    }

    float mayorPuntuacion = valorAlternativas[0];
    // Imprimir el valor de las alternativas y determinar mayor valor
    for (int i = 0; i < numAlternativas; i++) {
        if (valorAlternativas[i] > mayorPuntuacion) {
            mayorPuntuacion = valorAlternativas[i];
        }
        cout << "Valor alternativa [" << (i + 1) << "]: " << valorAlternativas[i] << endl;
    }

    cout << endl << endl;

    // Imprimir la mejor alternativa
    for (int i = 0; i < numAlternativas; i++) {
        if (valorAlternativas[i] == mayorPuntuacion) {
            cout << "La mejor alternativa es la numero " << (i + 1) << " con un valor de " << mayorPuntuacion << endl;
        }
    }

    return 0;
}
