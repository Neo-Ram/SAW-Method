import java.util.Scanner;

public class SAWnormal {

    // Función para imprimir una matriz
    public static void imprimirMatriz(float[][] matrizNormalizada) {
        for (int i = 0; i < matrizNormalizada.length; i++) { // Iterar sobre las filas
            for (int j = 0; j < matrizNormalizada[i].length; j++) { // Iterar sobre las columnas
                System.out.print(matrizNormalizada[i][j] + "\t"); // Imprimir cada valor con tabulación
            }
            System.out.println(); // Cambiar de línea al final de cada fila
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Ingrese el numero de criterios:");
        int numCriterios = scanner.nextInt();

        // Arrays para tipo de criterio y peso
        char[] tipoCriterio = new char[numCriterios];
        float[] pesoCriterio = new float[numCriterios];

        // Pedir criterios
        for (int i = 0; i < numCriterios; i++) {
            System.out.println("El criterio [" + (i + 1) + "] es de costo (c) o beneficio (b)?");
            tipoCriterio[i] = scanner.next().charAt(0);
            System.out.println("Ingrese el peso del criterio [" + (i + 1) + "]:");
            pesoCriterio[i] = scanner.nextFloat();
        }

        System.out.println("Ingrese el numero de alternativas:");
        int numAlternativas = scanner.nextInt();

        // Matriz de valores
        int[][] matrizValores = new int[numAlternativas][numCriterios];

        // Llenar matriz de valores
        for (int i = 0; i < numAlternativas; i++) {
            System.out.println("Asignación de valores a los criterios de la alternativa [" + (i + 1) + "]:");
            for (int j = 0; j < numCriterios; j++) {
                System.out.println("   Ingrese el valor del criterio [" + (j + 1) + "]:");
                matrizValores[i][j] = scanner.nextInt();
            }
            System.out.println();
        }

        // Matriz normalizada
        float[][] matrizNormalizada = new float[numAlternativas][numCriterios];

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
                    matrizNormalizada[j][i] = (float) minimo / matrizValores[j][i];
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
                    matrizNormalizada[j][i] = (float) matrizValores[j][i] / maximo;
                }
            }
        }

        // Imprimir matriz normalizada
        imprimirMatriz(matrizNormalizada);
        
        float[] valorAlternativas = new float[numAlternativas];
        //Calculo del valor de preferencia
        for(int i=0; i<numAlternativas;i++) {
        	valorAlternativas[i]=0;
        	for(int j=0;j<numCriterios;j++) {
        		valorAlternativas[i]+=matrizNormalizada[i][j]*pesoCriterio[j];
        	}
        }
        
        float mayorPuntuacion = valorAlternativas[0];
        //imprimir el valor de las alternativas y determinar mayor valor
        for(int i=0; i<numAlternativas; i++) {
        	if(valorAlternativas[i]>mayorPuntuacion) {
        		mayorPuntuacion = valorAlternativas[i];
        	}
        	System.out.println("Valor alternativa ["+(i+1)+"]: "+valorAlternativas[i]);
        }
        
        System.out.println();
        System.out.println();
        System.out.println();
        
        for(int i=0; i<numAlternativas; i++) {
        	if(valorAlternativas[i]==mayorPuntuacion) {
        		System.out.println("La mejor alternativa es la numero "+(i+1)+" con un valor de "+mayorPuntuacion);
        	}
        }
        
    }
}

