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

class tree{
  public:
    int age;
    bool marked;
};

class tree_specie {
  public:
    vector<tree*> trees;
};

void mark_trees(vector<tree_specie> &species, int index, vector<tree_specie*> &to_be_cut, int age_oldest_tree);
bool compare_oldest_species(tree_specie specie1, tree_specie specie2);
bool compare_60_species(tree_specie *specie1, tree_specie *specie2);
bool its_young_specie(tree_specie specie, int age_oldest_tree);
bool has_cut(vector<tree_specie*> to_be_cut);

int main() {
  int species_amount, species_trees;
  vector<tree_specie> species;
  vector<tree_specie*> heap_60_species;
  vector<tree_specie> oldest_species;

  //Obtém entrada.
  cin >> species_amount;
  for(int i = 0; i < species_amount; i++) {
    cin >> species_trees;
    species.push_back(tree_specie());
    for(int j = 0; j < species_trees; j++) {
      species[i].trees.push_back(new tree());
      cin >> species[i].trees[j]->age;
      species[i].trees[j]->marked = false;
    }
  }

  //Ordena os heaps auxiliares, um ordenado pelo 60% da especie, outro pelo max.
  for(int i = 0; i < species_amount; i++) {
    oldest_species.push_back(species[i]);
    push_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    heap_60_species.push_back(&species[i]);
    push_heap(heap_60_species.begin(), heap_60_species.end(), compare_60_species);
  }

  //Utiliza o heap ordenado pelos maximos para obter um vetor decrescente de todas
  //as árvores ordenado pela idade.
  std::vector<tree*> all_trees;
  while(!oldest_species.empty()) {
    all_trees.push_back(oldest_species[0].trees.back());
    oldest_species[0].trees.pop_back();
    pop_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    if(oldest_species[oldest_species.size() - 1].trees.empty()) {
      oldest_species.pop_back();
    } else {
      push_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    }
  }

  //Realiza os cortes necessários.
//  bool cut_happened = true;
  // int cut_counter = 0;
//    int age_oldest_tree;
  // vector<tree_specie*> to_be_cut;
//  while(cut_happened) {
    //Obtem arvore mais velha.

    //Percorre heap de 60% em busca de especies velhas, salvando o endereço de
    //especies que terão árvores cortadas em to_be_cut.

    //Exclui arvores, atualiza o vetor ordenado de árvores mais velhas (oldest_species).

    //Atualiza contador de cortes.
//  }


cout << "==============================================================================teste\n";
  cout << "TREES\n";

  cout << "\n\nSPECIES\n";


  cout << "\nOLDEST\n";

cout << "==============================================================================\n";

  //Desaloca memória.
  // for(int i = 0; i < species_amount; i++) {
  //   species[i].trees.erase(species[i].trees.begin(), species[i].trees.end());
  //   oldest_species[i].trees.erase(oldest_species[i].trees.begin(), oldest_species[i].trees.end());
  // }
  // species.erase(species.begin(), species.end());
  return 0;
}


void mark_trees(vector<tree_specie> &species, int index, vector<tree_specie*> &to_be_cut, int age_oldest_tree) {
  //Só olha se o indice atual for válido.
  if(index < (int)  species.size()) {
    //Se a especie atual for velha...
    if(!its_young_specie(species[index], age_oldest_tree)) {

      species[index].trees[species[index].trees.size() - 1]->marked = true;
      //... Chama a função para as espécies abaixo dela no heap...
      mark_trees(species, 2*index + 1, to_be_cut, age_oldest_tree);
      mark_trees(species, 2*index + 2, to_be_cut, age_oldest_tree);

      //... E marca a mesma para corte.
      to_be_cut.push_back(&(species[index]));
    }
  }
  return;
}

bool compare_oldest_species(tree_specie specie1, tree_specie specie2) {
  return ((specie1).trees[(specie1).trees.size()-1]->age) < ((specie2).trees[(specie2).trees.size()-1]->age);
}

bool compare_60_species(tree_specie *specie1, tree_specie *specie2) {
  return ((*specie1).trees[(int) ceil(0.6 * (*specie1).trees.size()) - 1]->age) < ((*specie2).trees[(int) ceil(0.6 * (*specie2).trees.size()) - 1]->age);
}

bool its_young_specie(tree_specie specie, int age_oldest_tree) {
  if(specie.trees[(int) ceil(0.6 * specie.trees.size()) - 1]->age <= (0.6 * age_oldest_tree)) {
    return true;
  }
  return false;
}

bool has_cut(vector<tree_specie*> to_be_cut) {
  if (to_be_cut.size() > 0) {
    return true;
  }
  return false;
}
