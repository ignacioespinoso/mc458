//Aluno: Ignácio Espinoso Ribeiro
//RA: 169767

/*Funcionamento do programa: O programa faz uso de um vetor de especies para
manter um registro fixo das árvores de cada espécie. A partir disso, são criados
dois heaps: Um de ponteiros para espécie, ordenado pelo elemento correspondente
ao 60% da espécie. Outro heap é temporário, contendo cópias das espécies (mas
ainda apontando pras árvores originais), ordenado pela árvore mais velha de cada
espécie.
  A passagem dos elementos do vetor de espécies original para os heaps se dá em
mlog(k), dado que uma árvore é inserida de cada vez num heap de espécies.
  Do heap de árvores mais velhas, geramos um vetor contendo todas as árvores do
problema, ordenado decrescentemente começando pela árvore mais velha. Essa
passagem ocorre em mlog(k).
  Posteriormente, ocorrem os cortes das espécies velhas propriamente ditas. A obten
ção da árvore mais velha de todas ocorre em O(1) pois temos o primeiro elemento
válido do vetor all_trees. O loop permanece rodando enquanto tiverem ocorrido
cortes na iteração passada e estivermos acessando uma posição válida.
  A primeira etapa do corte é a detecção das espécies velhas e, então a marcação
das árvores a serem excluidas do vetor de espécies original. Como o corte itera
sobre o heap de 60%, temos um tempo proporcional a .
  Por fim, depois da marcação realizamos efetivamente a remoção das árvores,
atualização do heap de árvores e da posição da árvore mais velha ainda não cortada.*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <new>
#include <algorithm>
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
bool compare_oldest_species(tree_specie *specie1, tree_specie *specie2);
bool compare_60_species(tree_specie *specie1, tree_specie *specie2);
bool its_young_specie(tree_specie *specie, int age_oldest_tree);

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
  vector<tree_specie*> oldest_species;
  for(int i = 0; i < species_amount; i++) {
    oldest_species.push_back(new tree_specie(species[i]));
    push_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    heap_60_species.push_back(&species[i]);
    push_heap(heap_60_species.begin(), heap_60_species.end(), compare_60_species);
  }

  //Utiliza o heap ordenado pelos maximos para obter um vetor decrescente de todas
  //as árvores ordenado pela idade.
  std::vector<tree*> all_trees;
  while(!oldest_species.empty()) {
    all_trees.push_back(oldest_species[0]->trees.back());
    pop_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    oldest_species[oldest_species.size() - 1]->trees.pop_back();
    if(oldest_species[oldest_species.size() - 1]->trees.empty()) {
      delete oldest_species.back();
      oldest_species.pop_back();
    } else {
      push_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);
    }
  }

  //Realiza os cortes necessários.
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

  cout << cut_counter << '\n';

  //Desaloca memoria alocada para as árvores.
  for(int i = 0; i < (int) all_trees.size(); i++) {
    delete all_trees[i];
  }
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

bool compare_oldest_species(tree_specie *specie1, tree_specie *specie2) {
  return ((*specie1).trees[(*specie1).trees.size()-1]->age) < ((*specie2).trees[(*specie2).trees.size()-1]->age);
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
