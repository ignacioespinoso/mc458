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

void mark_trees(vector<tree_specie*> &heap_60_species, int index, vector<int> &to_be_cut, int age_oldest_tree);
void heapify_60(vector<tree_specie*> &heap_60_species, int index);
void remove_element_heap (vector<tree_specie*> &heap_60_species, int index);
bool compare_oldest_species(tree_specie specie1, tree_specie specie2);
bool compare_60_species(tree_specie *specie1, tree_specie *specie2);
bool its_young_specie(tree_specie* specie, int age_oldest_tree);
bool has_cut(vector<tree_specie*> to_be_cut);

int main() {
  int species_amount, specie_total_trees;
  vector<tree_specie> species;

  //Obtém entrada.
  cin >> species_amount;
  for(int i = 0; i < species_amount; i++) {
    cin >> specie_total_trees;
    species.push_back(tree_specie());
    for(int j = 0; j < specie_total_trees; j++) {
      species[i].trees.push_back(new tree());
      cin >> species[i].trees[j]->age;
      species[i].trees[j]->marked = false;
    }
  }

  //Ordena os heaps auxiliares, um ordenado pelo 60% da especie, outro pelo max.
  vector<tree_specie*> heap_60_species;
  vector<tree_specie> oldest_species;
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

  //Realiza os cortes necessários.      all_trees, heap_60_species
  bool cut_happened = true;
  int age_oldest_tree = all_trees[0]->age;
  int oldest_tree_index = 0, cut_counter = 0;
  vector<int> to_be_cut;
  while(cut_happened && (oldest_tree_index < (int)all_trees.size())) {
    //Percorre heap de 60% em busca de especies velhas, salvando o endereço de
    //especies que terão árvores cortadas em to_be_cut.
    age_oldest_tree = all_trees[oldest_tree_index]->age;
    mark_trees(heap_60_species, 0, to_be_cut, age_oldest_tree);


    //Atualiza contador de cortes.
    cut_counter += (int) to_be_cut.size();
    if(to_be_cut.empty()) {
      cut_happened = false;
    }

    //Exclui arvores, atualizando o heap_60_species a cada iteração
    while(!to_be_cut.empty()) {
      heap_60_species[to_be_cut.back()]->trees.pop_back();
      if(heap_60_species[to_be_cut.back()]->trees.empty()) {
        remove_element_heap(heap_60_species, to_be_cut.back());
      }
      heapify_60(heap_60_species, to_be_cut.back());
      to_be_cut.pop_back();
    }

    //Atualiza arvore mais velha.
    while((oldest_tree_index < (int)all_trees.size()) && (all_trees[oldest_tree_index]->marked == true)) {
      oldest_tree_index++;
    }
  }


// cout << "==============================================================================teste\n";
//   cout << "TREES\n";
//   for(int i = 0; i < all_trees.size(); i++) {
//     cout << all_trees[i]->age << " ";
//   }
//   cout << "\n\nSPECIES\n";
//   for(int i = 0; i < species.size(); i++) {
//     for(int j = 0; j < species[i].trees.size(); j++) {
//       cout << species[i].trees[j]->age << " ";
//     }
//     cout << '\n';
//   }
//
//   cout << "\nSIXTY\n";
//   for(int i = 0; i < heap_60_species.size(); i++) {
//     for(int j = 0; j < heap_60_species[i]->trees.size(); j++) {
//       cout << heap_60_species[i]->trees[j]->age << " ";
//     }
//     cout << '\n';
//   }
//   cout << "\ncut_counter: " << cut_counter << '\n';
// cout << "\n==============================================================================\n";

  //Desaloca memória.
  // for(int i = 0; i < species_amount; i++) {
  //   species[i].trees.erase(species[i].trees.begin(), species[i].trees.end());
  //   oldest_species[i].trees.erase(oldest_species[i].trees.begin(), oldest_species[i].trees.end());
  // }
  // species.erase(species.begin(), species.end());
  cout << cut_counter << '\n';
  return 0;
}


void mark_trees(vector<tree_specie*> &heap_60_species, int index, vector<int> &to_be_cut, int age_oldest_tree) {
  //Só olha se o indice atual for válido.
  if(index < (int)  heap_60_species.size()) {
    //Se a especie atual for velha...
    if(!its_young_specie(heap_60_species[index], age_oldest_tree)) {
      to_be_cut.push_back(index);
      //... Chama a função para as espécies abaixo dela no heap...
      mark_trees(heap_60_species, 2*index + 1, to_be_cut, age_oldest_tree);
      mark_trees(heap_60_species, 2*index + 2, to_be_cut, age_oldest_tree);

      //... E marca a mesma para corte.
      heap_60_species[index]->trees[heap_60_species[index]->trees.size() - 1]->marked = true;

    }
  }
  return;
}

void heapify_60(vector<tree_specie*> &heap_60_species, int index) {
  int left_child = 2*index + 1;
  int right_child = 2*index + 2;
  int oldest_index;
  if((left_child < (int)heap_60_species.size()) && (compare_60_species(heap_60_species[index], heap_60_species[left_child]))) {

    oldest_index = left_child;
  } else {
    oldest_index = index;
  }
  if((right_child < (int)heap_60_species.size()) && (compare_60_species(heap_60_species[oldest_index], heap_60_species[right_child]))) {
    oldest_index = right_child;
  }
  if(oldest_index != index) {
    tree_specie* swap_aux;
    swap_aux = heap_60_species[index];
    heap_60_species[index] = heap_60_species[oldest_index];
    heap_60_species[oldest_index] = swap_aux;
    heapify_60(heap_60_species, oldest_index);
  }
}

void remove_element_heap (vector<tree_specie*> &heap_60_species, int index) {
  int last_element = (int) heap_60_species.size() - 1;
  tree_specie* swap_aux;
  swap_aux = heap_60_species[index];
  heap_60_species[index] = heap_60_species[last_element];
  heap_60_species[last_element] = swap_aux;
  heap_60_species.pop_back();
  heapify_60(heap_60_species, index);
}

bool compare_oldest_species(tree_specie specie1, tree_specie specie2) {
  return ((specie1).trees[(specie1).trees.size()-1]->age) < ((specie2).trees[(specie2).trees.size()-1]->age);
}

bool compare_60_species(tree_specie *specie1, tree_specie *specie2) {
  return ((*specie1).trees[(int) ceil(0.6 * (*specie1).trees.size()) - 1]->age) < ((*specie2).trees[(int) ceil(0.6 * (*specie2).trees.size()) - 1]->age);
}

bool its_young_specie(tree_specie* specie, int age_oldest_tree) {
  if(specie->trees[(int) ceil(0.6 * specie->trees.size()) - 1]->age <= (0.6 * age_oldest_tree)) {
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
