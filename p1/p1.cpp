//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

//Funcionamento do algoritmo: O algoritmo calcula as inversões com auxílio de um merge sort modificado,
// de forma que o número de inversões é contabilizado ao ordenar o vetor.

// Mais especificamente, o algoritmo leva em conta que, no procedimento de intercalar
// do Merge Sort, sempre que um elemento do subvetor da direita é inserido no vetor auxiliar,
// significa que ele é menor que todos os elementos ainda não percorridos (e inseridos no vetor auxiliar)
// da direita.

// Assim, isso significa que para cada elemento do subvetor da esquerda, temos uma inversão
// em relação ao elemento mencionado do subvetor da direita, uma vez que eles tem indice inferior
// mas valor superior.

// Vale notar que, quando um elemento do subvetor da esquerda é inserido no vetor
// auxiliar, uma inversão não deve ser contabilizada pelo simples fato que estamos
// inserindo no vetor o elemento de menor índice e menor valor possíveis.

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <new>

using namespace std;

void merge_sort(int *array, int *aux_array, int beginning, int end, unsigned long long int *counter);
void merge_count(int *array, int *aux_array, int beggining, int middle, int end, unsigned long long int *counter);

int main() {
    int n;
    unsigned long long int counter = 0;
    int *array, *aux_array;

    scanf("%d", &n);
    array = new int[n];
    aux_array = new int[n];

    for(int i = 0; i < n; i++) {
        scanf("%d", &(array[i]));
    }

    merge_sort(array, aux_array, 0, n-1, &counter);
    cout << counter << '\n';

    delete[] array;
    delete[] aux_array;

    return 0;
}

void merge_sort(int *array, int *aux_array, int beginning, int end, unsigned long long int *counter) {
    if (beginning < end) {
        int middle = (beginning + end)/2;
        merge_sort(array, aux_array, beginning, middle, counter);
        merge_sort(array, aux_array, middle + 1, end, counter);
        merge_count(array, aux_array, beginning, middle, end, counter);
    }
}

//Função intercala: A saída é o vetor 'array' ordenado de 'beggining' até 'end'.
void merge_count(int *array, int *aux_array, int beginning, int middle, int end, unsigned long long int *counter){
    //Declaração de variáveis auxiliares para cada ponto chave dos subvetores.
    int i = beginning, j = (middle + 1), k = 0;

    //Intercala enquanto ambos subvetores tiverem elementos, salvando elementos
    //em ordem crescente no vetor auxiliar aux_array.
    while((i <= middle) &&   (j <= end)) {
        if(array[i] <= array[j]) {
            aux_array[k] = array[i];
            i++;
        } else {
            aux_array[k] = array[j];
            *counter += middle - i + 1;
            j++;
        }
        k++;
    }

    //Finaliza a intercalação para os elementos restantes dos subvetores.
    while(i <= middle) {
        aux_array[k] = array[i];
        i++;
        k++;
    }

    while(j <= end) {
        aux_array[k] = array[j];
        j++;
        k++;
    }

    //Copia o vetor auxiliar para o vetor original.
    for(i = beginning; i <= end; i++) {
        array[i] = aux_array[i - beginning];
    }
}
