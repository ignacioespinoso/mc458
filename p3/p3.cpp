//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

/*
Tarefa P3.1 de mc458a — Exercício de Programação 03
O algoritmo funciona seguindo o princípio de divisão e conquista para atingir
a complexidade desejada.
Para tal, na função Find_Separators primeiramente é encontrado o índice da
mediana do (sub)vetor passado. Com tal índice, temos como encontrar o valor da
mediana (que é um separador binário) com auxílio da função nth_element, que
executa com complexidade linear (proporcional ao tamanho do vetor) a seleção da
mediana, colocando-a na posição onde estaria se o vetor fosse ordenado e
separando o vetor em valores maiores que a mediana, à direita, e valores menores,
à esquerda.
Mantendo o raciocínio de divisão e conquista, a função Find_Separators é chamada
recursivamente para cada um desses subvetores da esquerda e direita. Se ainda há
separador a ser encontrado, a função realiza suas operações já descritas, se não
retorna para seu local de chamada. A ordem de chamada recursiva é feita de modo
que a ordenação do vetor de separadores ocorra naturalmente, resolvendo o problema.
*/
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Encontra k separadores binarios do vetor values.
void Find_Separators(vector<long int> *values, vector<long int> *separators, long int beginning, long int end, long int k);

int main() {
  long int size, separators_amount;
  vector<long int> values, separators;

  //Obtém entrada.
  cin >> size;
  cin >> separators_amount;
  for(int i = 0; i < size; i++) {
    long int temp;
    cin >> temp;
    values.push_back(temp);
  }

  // Realiza operações
  Find_Separators(&values, &separators, 0, size, separators_amount);

  // Imprime saída.
  for(int i = 0; i < separators_amount; i++) {
    cout << separators[i] << ' ';
  }
  cout << '\n';
  return 0;
}

void Find_Separators(vector<long int> *values, vector<long int> *separators, long int beginning, long int end, long int k) {
  if(k > 0) {
    // Acha posição (no vetor ordenado) da mediana do vetor atual.
    long int median_pos = (end - beginning) / 2 + beginning;
    // Encontra a mediana e a coloca na posição correta.
    nth_element(values->begin() + beginning, values->begin() + median_pos, values->begin() + end);

    //Encontra as medianas dos subvetores da esquerda e direita, caso hajam.
    Find_Separators(values, separators, beginning, median_pos -1, k/2);
    // Inclui mediana atual no vetor, mantendo a ordenação dos separadores.
    (*separators).push_back((*values)[median_pos]);
    Find_Separators(values, separators, median_pos +1, end, k/2);
  }
  return;
}
