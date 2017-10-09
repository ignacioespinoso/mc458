//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <vector>
#include <new>
#include<algorithm>
#include <cmath>

using namespace std;

struct tree_specie {
  vector<int> trees;
  int oldest_tree;
  int tree_amount;
};

bool compare_species(tree_specie specie1, tree_specie specie2);
bool its_young_specie(tree_specie specie, int age_oldest_tree);

int main() {
  int species_amount, trees_amount, age_oldest_tree;
  int cut_counter = 0;
  vector<tree_specie> species;

  //Obtém entrada.
  cin >> species_amount;
  for(int i = 0; i < species_amount; i++) {
    cin >> trees_amount;
    species.push_back(tree_specie());
    species[i].tree_amount = trees_amount;
    for(int j = 0; j < trees_amount; j++) {
      species[i].trees.push_back(int());
      cin >> species[i].trees[j];
    }
    species[i].oldest_tree = species[i].trees[trees_amount - 1];
  }

  //Faz um heap com as árvores mais velhas de cada especie.
  make_heap(species.begin(), species.end(), compare_species);
  age_oldest_tree = species[0].oldest_tree;

  //Realiza os cortes necessários.
  for(int i = 0; i < species_amount; i++) {
    while(!its_young_specie(species[i], age_oldest_tree) && species[i].tree_amount > 0) {
      species[i].trees.pop_back();
      species[i].tree_amount--;
      cut_counter++;
      make_heap(species.begin(), species.end(), compare_species);
    }

    age_oldest_tree = species[0].oldest_tree;   //Atualiza árvore mais velha de todas
  }

//==============================================================================teste
  cout << "===================================================================\n";
  cout <<"ARVORE MAIS VELHA GERAL: " << age_oldest_tree << '\n';
  for(int i = 0; i < species_amount; i++) {
    cout << "Valores da especie " << i << " , de total "<<  species[i].tree_amount <<" e arvore mais velha "<< species[i].oldest_tree << " \n";
    for(int j = 0; j < species[i].tree_amount; j++) {
      cout << species[i].trees[j] << ' ';
    }
    cout << '\n';
  }
  cout << "cut_counter: " << cut_counter << '\n';
  cout << "===================================================================\n";
//==============================================================================

  //Desaloca memória.
  for(int i = 0; i < species_amount; i++) {
    species[i].trees.erase(species[i].trees.begin(), species[i].trees.end());
  }
  species.erase(species.begin(), species.end());
  return 0;
}

bool compare_species(tree_specie specie1, tree_specie specie2) {
  return specie1.oldest_tree < specie2.oldest_tree;
}

bool its_young_specie(tree_specie specie, int age_oldest_tree) {
  if(specie.trees[(int) ceil(0.6 * specie.tree_amount) - 1] <= (0.6 * age_oldest_tree)) {
    return true;
  }
  return false;
}
