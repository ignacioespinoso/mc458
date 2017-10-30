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
  cin >> number_bin_separator;
  for(int i = 0; i < size; i++) {
    int temp;
    cin >> temp;
    values.push_back(temp);
  }

  for(int i = 0; i < size; i++) {
    cout << values[i];
  }
  cout << '\n' << number_bin_separator << '\n';
  return 0;
}

void Rand_Select(vector<int> values, long int beginning, long int end, long int i) {
  if(beginning == end) {
    return;
  } else {
    long int middle = Rand_Partitioning(values, beginning, end);
    long int k = middle-beginning;
    if(i =  k) {
      return;
    } else if(i < k) {
      Rand_Select(values, beginning, middle-1, i);
    } else {
      Rand_Select(values, middle + 1, end, i-k);
    }
    return;
  }
}

void Rand_Partitioning(vector<int> values, long int beginning, long int end) {
  i = srand(0);
  return;
}
