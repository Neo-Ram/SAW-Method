#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Clase base que encapsula los atributos y métodos básicos de una decisión
class Decision {
protected:
    int numCriterios;
    int numAlternativas;
    vector<char> tipoCriterio;
    vector<float> pesoCriterio;
    vector<vector<int>> matrizValores;
    vector<vector<float>> matrizNormalizada;
    vector<float> valorAlternativas;

public:
    Decision() : numCriterios(0), numAlternativas(0) {}

    virtual void inicializar() {
        cout << "Ingrese el numero de criterios: ";
        cin >> numCriterios;

        tipoCriterio.resize(numCriterios);
        pesoCriterio.resize(numCriterios);

        for (int i = 0; i < numCriterios; i++) {
            cout << "El criterio [" << (i + 1) << "] es de costo (c) o beneficio (b)? ";
            cin >> tipoCriterio[i];
            cout << "Ingrese el peso del criterio [" << (i + 1) << "]: ";
            cin >> pesoCriterio[i];
        }

        cout << "Ingrese el numero de alternativas: ";
        cin >> numAlternativas;

        matrizValores.resize(numAlternativas, vector<int>(numCriterios));
        matrizNormalizada.resize(numAlternativas, vector<float>(numCriterios));
        valorAlternativas.resize(numAlternativas, 0);

        for (int i = 0; i < numAlternativas; i++) {
            cout << "Asignación de valores a los criterios de la alternativa [" << (i + 1) << "]: " << endl;
            for (int j = 0; j < numCriterios; j++) {
                cout << "   Ingrese el valor del criterio [" << (j + 1) << "]: ";
                cin >> matrizValores[i][j];
            }
            cout << endl;
        }
    }

    virtual void normalizar() = 0; // Método virtual puro para normalizar (polimorfismo)

    virtual void calcularValores() {
        for (int i = 0; i < numAlternativas; i++) {
            for (int j = 0; j < numCriterios; j++) {
                valorAlternativas[i] += matrizNormalizada[i][j] * pesoCriterio[j];
            }
        }
    }

    void imprimirMatrizNormalizada() const {
        cout << "Matriz Normalizada:" << endl;
        for (const auto& fila : matrizNormalizada) {
            for (float valor : fila) {
                cout << fixed << setprecision(6) << valor << "\t";
            }
            cout << endl;
        }
    }

    void imprimirMejorAlternativa() const {
        float mayorPuntuacion = valorAlternativas[0];
        int indiceMejorAlternativa = 0;

        cout << endl << "Valores de cada alternativa:" << endl;
        for (int i = 0; i < numAlternativas; i++) {
            cout << "Valor alternativa [" << (i + 1) << "]: " << fixed << setprecision(6) << valorAlternativas[i] << endl;
            if (valorAlternativas[i] > mayorPuntuacion) {
                mayorPuntuacion = valorAlternativas[i];
                indiceMejorAlternativa = i;
            }
        }

        cout << endl << "La mejor alternativa es la numero " 
             << (indiceMejorAlternativa + 1) 
             << " con un valor de " << fixed << setprecision(6) 
             << mayorPuntuacion << endl;
    }
};

// Clase derivada que implementa la normalización específica
class DecisionNormalizada : public Decision {
public:
    void normalizar() override {
        for (int i = 0; i < numCriterios; i++) {
            if (tipoCriterio[i] == 'c') {
                int minimo = matrizValores[0][i];
                for (int j = 1; j < numAlternativas; j++) {
                    minimo = min(minimo, matrizValores[j][i]);
                }
                for (int j = 0; j < numAlternativas; j++) {
                    matrizNormalizada[j][i] = static_cast<float>(minimo) / matrizValores[j][i];
                }
            } else if (tipoCriterio[i] == 'b') {
                int maximo = matrizValores[0][i];
                for (int j = 1; j < numAlternativas; j++) {
                    maximo = max(maximo, matrizValores[j][i]);
                }
                for (int j = 0; j < numAlternativas; j++) {
                    matrizNormalizada[j][i] = static_cast<float>(matrizValores[j][i]) / maximo;
                }
            }
        }
    }
};

int main() {
    Decision* decision = new DecisionNormalizada(); // Polimorfismo
    decision->inicializar();
    decision->normalizar();
    decision->imprimirMatrizNormalizada();
    decision->calcularValores();
    decision->imprimirMejorAlternativa();

    delete decision; // Liberar memoria
    return 0;
}
