//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <new>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using namespace std;

int main() {
  long int size, separators_amount;
  vector<int> values, separators;

  //Obtém entrada.
  cin >> size;
  cin >> bin_separator_amount;

  srand(0);

  for(int i = 0; i < size; i++) {
    int temp;
    cin >> temp;
    values.push_back(temp);
  }

  Find_Separators(&values, &separators, 0, size, k);

  for(int i = 0; i < size; i++) {
    cout << values[i];
  }
  cout << '\n' << bin_separator_amount << '\n';
  return 0;
}

void Find_Separators(vector<long int> *values, vector<long int> *separators, long int beginning, long int end, long int k) {
  if(k > 0) {
    // Acha posição (no vetor ordenado) da mediana do vetor atual.
    long int median_pos = (end - beginning) / 2 + beginning;
    // Encontra a mediana e a coloca na posição correta.
    Rand_Select(vector<long int> *values, beginning, end, median_pos);

    //Encontra as medianas dos subvetores da esquerda e direita, caso hajam.
    Find_Separators(values, separators, beginning, median_pos -1, k/2);
    // Inclui mediana atual no vetor, mantendo a ordenação dos separadores.
    (*separators).push_back((*values)[median_pos]);
    Find_Separators(values, separators, median_pos +1, end, k/2);
  }
  return;
}

long int Rand_Select(vector<int> *values, long int beginning, long int end, long int i) {
  //acha mediana e salva no vetor de saida, se o size do vetor de medianas é < k,
  //usa mediana como pivo pra particionar, chama select recursivamente pra cada lado da mediana
  if(beginning == end) {
    return (*values)[beginning];
  } else {
    long int middle = Rand_Partitioning(values, beginning, end);
    long int k = middle-beginning;
    if(i == k) {
      return (*values)[i];
    } else if(i < k) {
      Rand_Select(values, beginning, middle-1, i);
    } else {
      Rand_Select(values, middle + 1, end, i-k);
    }
  }
}

// Particiona um (sub)vetor através de um pivô aleatório.
long int Rand_Partitioning(vector<int> *values, long int beginning, long int end) {
  // Seleciona pivô aleatório.
  long int pivot = rand()%(end-beginning+1);

  swap(values, pivot, end);
  pivot = (*values)[end];
  long int partition_aux = beginning - 1;

  //Particiona.
  for(long int j = beginning; j < end - 1; j++) {
    if((*values)[j] <= pivot) {
      partition_aux++;
      swap(values, partition_aux, j);
    }
  }
  swap(values, partition_aux + 1, end);
  return partition_aux + 1;
}

// Troca os valores armazenados em index1 e index2 entre si.
void swap(vector<int> *values, long int index1, long int index2) {
  long int swap_aux = (*values)[end];
  (*values)[end] = (*values)[pivot];
  (*values)[pivot] = swap_aux;

  return;
}
