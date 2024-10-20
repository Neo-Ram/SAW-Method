#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

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

    virtual void inicializar(const string& filename) {
        ifstream inputFile(filename);

        inputFile >> numCriterios >> numAlternativas;

        tipoCriterio.resize(numCriterios);
        pesoCriterio.resize(numCriterios);
        matrizValores.resize(numAlternativas, vector<int>(numCriterios));
        matrizNormalizada.resize(numAlternativas, vector<float>(numCriterios));
        valorAlternativas.resize(numAlternativas, 0);

        for (int i = 0; i < numCriterios; i++) {
            inputFile >> tipoCriterio[i] >> pesoCriterio[i];
        }

        for (int i = 0; i < numAlternativas; i++) {
            for (int j = 0; j < numCriterios; j++) {
                inputFile >> matrizValores[i][j];
            }
        }

        inputFile.close();
    }

    virtual void normalizar() = 0;

    virtual void calcularValores() {
        for (int i = 0; i < numAlternativas; i++) {
            for (int j = 0; j < numCriterios; j++) {
                valorAlternativas[i] += matrizNormalizada[i][j] * pesoCriterio[j];
            }
        }
    }

    void imprimirMejorAlternativa() const {
    float mayorPuntuacion = valorAlternativas[0];
    int indiceMejorAlternativa = 0;

    for (int i = 0; i < numAlternativas; i++) {
        if (valorAlternativas[i] > mayorPuntuacion) {
            mayorPuntuacion = valorAlternativas[i];
            indiceMejorAlternativa = i;
        }
    }

    // Imprimir el índice de la mejor alternativa y su valor
    
    cout << "La mejor alternativa es la número " << (indiceMejorAlternativa + 1) << " con un valor de " << mayorPuntuacion << endl; 
    fflush(stdout);
}

};

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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <archivo_entrada>" << endl;
        return 1;
    }

    string filename = argv[1];
    Decision* decision = new DecisionNormalizada();
    decision->inicializar(filename);
    decision->normalizar();
    decision->calcularValores();
    decision->imprimirMejorAlternativa();

    delete decision;
    return 0;
}
