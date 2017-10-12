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
  int tree_amount;
};

void mark_trees(vector<tree_specie> &species, int index, vector<tree_specie*> &to_be_cut, int age_oldest_tree);
bool compare_oldest_species(tree_specie *specie1, tree_specie *specie2);
bool compare_60_species(tree_specie specie1, tree_specie specie2);
bool its_young_specie(tree_specie specie, int age_oldest_tree);
bool has_cut(vector<tree_specie*> to_be_cut);

int main() {
  int species_amount, species_trees;
  vector<tree_specie> species;
  vector<tree_specie*> oldest_species;
  //Obtém entrada.
  cin >> species_amount;
  for(int i = 0; i < species_amount; i++) {
    cin >> species_trees;
    species.push_back(tree_specie());
    species[i].tree_amount = species_trees;
    for(int j = 0; j < species_trees; j++) {
      species[i].trees.push_back(int());
      cin >> species[i].trees[j];
    }
  }

  for(int i = 0; i < species_amount; i++) {
    oldest_species.push_back(&(species[i]));
  }
  //Faz um heap com as árvores correspondentes ao 60% de cada especie.
  make_heap(species.begin(), species.end(), compare_60_species);

  //Faz heap de ponteiros para as espécies, ordenando de acordo com espécie com árvore mais velha.
  make_heap(oldest_species.begin(), oldest_species.end(), compare_oldest_species);

  //Realiza os cortes necessários.
//  bool cut_happened = true;
  int cut_counter = 0;
  int age_oldest_tree;
  vector<tree_specie*> to_be_cut;
//  while(cut_happened) {
    //Obtem arvore mais velha.
    age_oldest_tree = oldest_species[0]->trees[oldest_species[0]->tree_amount-1];
    //Percorre heap de 60% em busca de especies velhas, salvando o endereço de
    //especies que terão árvores cortadas em to_be_cut.
    mark_trees(species, 0, to_be_cut, age_oldest_tree);

    //Exclui arvores, atualiza o vetor ordenado de árvores mais velhas (oldest_species).

    //Atualiza contador de cortes.
  //  cut_happened = has_cut(to_be_cut);
  //  cut_counter += to_be_cut.size();
//  }


//==============================================================================teste
  cout << "===================================================================\n";
  cout << "PRIMEIROS CORTES" << cut_counter <<   '\n';
  cout << to_be_cut.size() << "   <-tamanho\n";
  for(int i = 0; i < (int)to_be_cut.size(); i++) {

    cout << to_be_cut[i]->trees[to_be_cut[i]->tree_amount-1] << '\n'; //
  }
  cout << "===================================================================\n";

  // cout <<"HEAP DE 60%: " << '\n';
  // for(int i = 0; i < species_amount; i++) {
  //   //cout << "Valores da especie " << i << " , de total "<<  species[i].tree_amount <<" e arvore mais velha "<< species[i].oldest_tree << " \n";
  //   cout << species[i].trees[(int) ceil(0.6 * species[i].tree_amount) - 1] << '\n';
  // //  cout << '\n';
  // }
  // cout <<"HEAP DE MAIS VELHAS: " << '\n';
  // for(int i = 0; i < species_amount; i++) {
  //   //cout << "Valores da especie " << i << " , de total "<<  species[i].tree_amount <<" e arvore mais velha "<< species[i].oldest_tree << " \n";
  //   cout << oldest_species[i]->trees[oldest_species[i]->tree_amount-1] << '\n';
  // //  cout << '\n';
  // }
  // cout << "cut_counter: " << cut_counter << '\n';
  cout << "===================================================================\n";
//==============================================================================

  //Desaloca memória.
  for(int i = 0; i < species_amount; i++) {
    species[i].trees.erase(species[i].trees.begin(), species[i].trees.end());
  }
  species.erase(species.begin(), species.end());
  return 0;
}


void mark_trees(vector<tree_specie> &species, int index, vector<tree_specie*> &to_be_cut, int age_oldest_tree) {
  //Só olha se o indice atual for válido.
  if(index < (int)  species.size()) {
    //Se a especie atual for velha...
    if(!its_young_specie(species[index], age_oldest_tree)) {
      cout << "XABLAU: " << species[index].trees[species[index].tree_amount -1] << '\n';
      //... Marca a mesma para corte...
      to_be_cut.push_back(&(species[index]));
      //... e chama a função para as espécies abaixo dela no heap.
      mark_trees(species, 2*index + 1, to_be_cut, age_oldest_tree);
      mark_trees(species, 2*index + 2, to_be_cut, age_oldest_tree);
    }
  }
  return;
}

bool compare_oldest_species(tree_specie *specie1, tree_specie *specie2) {
  return (*specie1).trees[(*specie1).tree_amount-1] < (*specie2).trees[(*specie2).tree_amount-1];
}

bool compare_60_species(tree_specie specie1, tree_specie specie2) {
  return specie1.trees[(int) ceil(0.6 * specie1.tree_amount) - 1] < specie2.trees[(int) ceil(0.6 * specie2.tree_amount) - 1];
}

bool its_young_specie(tree_specie specie, int age_oldest_tree) {
  if(specie.trees[(int) ceil(0.6 * specie.tree_amount) - 1] <= (0.6 * age_oldest_tree)) {
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
