#include <algorithm>
#include <iostream>
#include <limits>

#include "Dominancia.hpp"

using namespace std;

int Dominancia::comparaIndsDominancia(Individuo *ind1, Individuo *ind2) {

  vector<double> evals1 = ind1->getEvals();
  vector<double> evals2 = ind2->getEvals();

  int numDominadosEst1 = 0;
  int numDominados1 = 0;

  int numDominadosEst2 = 0;
  int numDominados2 = 0;

  for(int i=0; i < evals1.size(); i++) {
    if (evals1[i] <= evals2[i]) numDominados1++;
    if (evals1[i] < evals2[i]) numDominadosEst1++;
    
    if (evals2[i] <= evals1[i]) numDominados2++;
    if (evals2[i] < evals1[i]) numDominadosEst2++;
  }


  if (numDominados1 == evals1.size() && numDominados2 == evals1.size() && numDominadosEst1 == 0 && numDominadosEst2 == 0 ) {
    return IGUALES;
  } else if (numDominados1 == evals1.size() && numDominadosEst1 > 0 ) {
    return PRIMERO_DOMINA;
  } else if(numDominados2 == evals1.size() && numDominadosEst2 > 0) 
  {
    return SEGUNDO_DOMINA;
  }

  // numDominadosEst1 > 0 && numDominadosEst2 > 0
  return SIN_DOMINANCIA;
}

// Algoritmo Cuadratico
vector<Individuo *> Dominancia::calcularNoDominados(vector<Individuo *> inds) {
  vector<Individuo *> noDominados;

  bool dominado = false;

  for(int i=0; i < inds.size(); i++) {
    dominado = false;
    for(int j=0; j < inds.size() && !dominado; j++) {
      if (i==j) continue;

      dominado = dominado ||
        (Dominancia::comparaIndsDominancia(inds[i], inds[j]) > 0);

    }
    if (!dominado) {
      noDominados.push_back(inds[i]);
    }
  }

  return noDominados;
}

vector<Individuo *> Dominancia::filtrar_elementos(vector<Individuo *> v, 
  vector<int> filtro) {

  vector<Individuo *> resultado;

  // Marcamos los elementos que se deben regresar:
  for(int i=0; i < v.size(); i++) {
    if (filtro[i] == 1) {
      resultado.push_back(v[i]);
    }
  }

  return resultado;
}