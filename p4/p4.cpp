//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

// A resolução é feita na função best_ice_cream_cost.
// Neste problema foi definido optimized_costs[i] como o menor custo para atender a
// demanda do dia i+1 até o dia N (apesar de no código os indices irem de 0 a N-1).
// Assim, como subproblema foi adotada a abordagem:
// As possibilidades de escolha envolvem, para um dia i:
//   -custo de comprar no dia i até o dia i + optimized_costs(i+1);
//   -custo de comprar no dia i até o dia (i+1) + optimized_costs(i+2);
//   ...
//   -custo de comprar no dia i até o dia N.
// Dessa forma, é possivel notar que optimized_costs[x] é o subproblema que
// começa no dia x.
//
// Mantendo o raciocinio, a recorrencia fica como
// optimized_costs[i] = min{custo_sequencial + optimized_costs[j+1], onde i<=j<N}
// ,onde o custo_sequencial = K[i] + H*D[j]*((j-i) + (j-1-i) + (j-2-i) + ... + (i-i))
// , correspondendo ao custo envolvendo comprar toda mercadoria no dia i,
// para que a mesma dure até o dia j.
//
// Na resolução, a resolução está concentrada nos dois for's. O primeiro itera
// de trás para a frente, garantindo que os subproblemas podem ser resolvidos,
// dado que i determina a data inicial.
// o segundo for itera normalmente, calculando o custo sequencial até j, increme-
// mentando o valor da estadia correspondente a cada iteração.
// Após isso,current_cost armazena o custo total atual, somando a o menor custo
// de j+1 até N, computando o custo total de compra, na abordagem da iteração,
// de i até j.
// Caso current_cost seja menor que o menor custo armazenado de i até N, o menor
// custo é atualizado. Ao final do segundo loop temos o menor valor de todos,
// garantindo a resolução da recorrencia.
//
// Ao final do primeiro loop, teremos o menor custo de 1 até N, resolvendo o
// problema.

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

long int best_ice_cream_cost(long int &N, long int &H, vector<long int> &K, vector<long int> &D);

int main() {
  long int H, N;
  vector<long int> K, D, optimized_costs;

  //Obtém entrada.
  cin >> H;
  cin >> N;

  long int input;
  for(long int i = 0; i < N; i++) {
    cin >> input;
    K.push_back(input);
  }
  for(long int i = 0; i < N; i++) {
    cin >> input;
    D.push_back(input);
  }

  long int best_cost = best_ice_cream_cost(N, H, K, D);
  cout << best_cost << '\n';
  return 0;
}

long int best_ice_cream_cost(long int &N, long int &H, vector<long int> &K, vector<long int> &D) {
  //optimized_costs[i] armazena o melhor custo do dia i+1 até o dia N.
  vector<long int> optimized_costs;
  optimized_costs.reserve(N+1);
  optimized_costs[N] = 0;

  long int least_cost, current_cost, current_sequential_cost, stay_cost;

  // i corresponde à data inicial
  for(long int i = N-1; i >= 0; i--) {
    least_cost = -1;
    current_sequential_cost = K[i];        //Custo sequencial de dia é o frete.
    stay_cost = 0;
    // j corresponde à data final.
    for(long int j = i; ((j < N) && (stay_cost < least_cost || least_cost == -1)); j++) {
      // Atualiza custo sequencial
      stay_cost = H*(j-i)*D[j];
      current_sequential_cost += H*(j-i)*D[j];
      // Inclui no custo atual a refrigeração para mais um dia.
      current_cost = current_sequential_cost + optimized_costs[j+1];
      // Caso o custo atual para o período analizado seja menor que o menor
      // custo registrado, atualiza o menor custo.
      if((current_cost < least_cost ) || (least_cost == -1)) {
        least_cost = current_cost;
      }
    }
    // Atualiza o vetor de menores custos.
    optimized_costs[i] = least_cost;
  }

  return optimized_costs[0];
}
