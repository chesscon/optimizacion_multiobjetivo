#include <algorithm>
#include <iostream>
#include <limits>

#include "Dominancia.hpp"
#include "SegmentTree.hpp"

using namespace std;

// compara inds por Eval1, Eval2, Eval3
int Dominancia::comparaIndsEvals(Individuo *ind1, Individuo *ind2) {

  vector<double> evals1 = ind1->getEvals();
  vector<double> evals2 = ind2->getEvals();

  int res = 0;

  for(int i=0; i < evals1.size() && res == 0; i++ ) {
    if (evals1[i] < evals2[i]) {
      res = -1;
      // break;
    }
    if (evals1[i] > evals2[i]) {
      res = 1;
      // break;
    }
  }

  return res;
}

// Compara inds por Eval2, Eval3, Eval1
int Dominancia::comparaIndsEvals2(Individuo *ind1, Individuo *ind2) {
  vector<double> evals1 = ind1->getEvals();
  vector<double> evals2 = ind2->getEvals();

  int res = 0;

  for(int i=1; i < evals1.size(); i++ ) {
    if (evals1[i] < evals2[i]) {
      res = -1;
      break;
    }
    if (evals1[i] > evals2[i]) {
      res = 1;
      break;
    }
  }

  if (res == 0 && evals1[0] != evals2[0]) {
    res = evals1[0] < evals2[0] ? -1 : 1;
  }
  
  return res; 
}

bool Dominancia::comparador1(Individuo *ind1, Individuo *ind2) {
  return comparaIndsEvals(ind1, ind2) < 0;
}

bool Dominancia::comparador2(Individuo *ind1, Individuo *ind2) {
  return comparaIndsEvals2(ind1, ind2) < 0;
}

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

  int result = -2;

  if (numDominadosEst1 > 0 && numDominadosEst2 > 0) {
    return NO_DOMINADO;
  } else if (numDominados1 == evals1.size() && numDominadosEst1 > 0 ) {
    result = DOMINADO;
  } else 
    //if(numDominados2 == evals1.size() && numDominadosEst2 > 0) 
  {
    result = -DOMINADO;
  }

  return result;
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

// Algoritmo SPAN
vector<Individuo *> Dominancia::calcularNoDominados2D_span( vector<Individuo *> inds ) {
  vector<Individuo *> noDominados;

  // 1. Ordenar por la primera coordenada
  sort(inds.begin(), inds.end(), Dominancia::comparador1 );

  // Agregamos al mejor (en la primera coordenada) a los no dominados:
  noDominados.push_back(inds[0]);

  vector<double> evals = inds[0]->getEvals();
  double min2 = evals[1];

  for(int i=1; i < inds.size(); i++) {
    evals = inds[i]->getEvals();
    // Si supera al minimo obtenido, se actualiza:
    if (evals[1] < min2) {
      min2 = evals[1];
      noDominados.push_back(inds[i]);
    }
  }

  return noDominados;
}

vector<Individuo *> Dominancia::calcularNoDominados3D_span( vector<Individuo *> inds
//vector<Individuo *> & noDominados 
  ) {
  vector<Individuo *> noDominados;

  // 1. Ordenar por la primera coordenada
  sort(inds.begin(), inds.end(), Dominancia::comparador1 );

  // construimos un segment tree, 
  // la segunda coordenada es la pos, y la tercera es el valor.
  vector<int> A;
  A.assign(inds.size(), numeric_limits<int>::max());

  SegmentTree st(A);
  vector<double> evals = inds[0]->getEvals();

  noDominados.push_back(inds[0]);
  st.update((int) evals[1], (int) evals[2]);

  for(int i=1; i < inds.size(); i++) {
    evals = inds[i]->getEvals();

    if (evals[2] < st.query(0, (int)evals[1])) {
      noDominados.push_back(inds[i]);
      st.update((int)evals[1], (int) evals[2]);
    }
  }

  return noDominados;
}


// Algoritmo Divide y Venceras
vector<Individuo *> Dominancia::calcularNoDominados2D_DV( vector<Individuo *> inds ) {
  // 1. Ordenar por la primera coordenada
  sort(inds.begin(), inds.end(), Dominancia::comparador1 );  

  return Dominancia::auxNoDominados2D_DV(inds, 0, inds.size());
}

vector<Individuo *> Dominancia::auxNoDominados2D_DV( vector<Individuo *> & inds,
  int ini, int numElems ) {

  vector<Individuo *> noDominados;

  if (ini < 0 || ini >= inds.size() || numElems <= 0 || numElems > inds.size()) 
    return noDominados;

  if (numElems == 1) {
    noDominados.push_back(inds[ini]);
    return noDominados;
  }

  int mitad = (numElems)/2;

  vector<Individuo *> noDomIzq = Dominancia::auxNoDominados2D_DV(inds, ini, mitad);
  vector<Individuo *> noDomDer = Dominancia::auxNoDominados2D_DV(inds, ini + mitad, 
    (numElems - mitad) );

  // Los de la izquierda ya esta bien calculados, los agregamos:
  noDominados = noDomIzq;

  int min2 = noDominados.back()->getEvals()[1];

  vector<double> evals;

  for(int i=0; i < noDomDer.size(); i++) {
    evals = noDomDer[i]->getEvals();
    if (evals[1] < min2) {
      min2 = evals[1];
      noDominados.push_back(noDomDer[i]);
    }
  }

  return noDominados;
}

vector<Individuo *> Dominancia::calcularNoDominados3D_DV( vector<Individuo *> inds ) {

  vector<Individuo *> preSort = inds;  

  // 1. Ordenar por la primera coordenada
  sort(inds.begin(), inds.end(), Dominancia::comparador1 );
  for(int i=0; i < inds.size(); i++) {
    inds[i]->indOrd1 = i;
  }

  // 2. Ordenamos por la segunda coordenada
  sort(preSort.begin(), preSort.end(), Dominancia::comparador2 );

  vector<int> indPreSort(preSort.size());
  // Creamos arreglo
  // Actualizar indice del presort:
  for(int i=0; i < preSort.size(); i++) {
    indPreSort[i] = preSort[i]->indOrd1;
//    presort[i].indOrd2 = i;
  }  

  return Dominancia::auxNoDominados3D_DV(inds, indPreSort, 0, inds.size());
}

vector<Individuo *> Dominancia::auxNoDominados3D_DV( vector<Individuo *> & inds,
  vector<int> indPreSort, int ini, int numElems ) {

//  cout << "AuxDV 3D, ini: " << ini << ", numElems: " << numElems 
//  << ", preSort.size()=" << indPreSort.size() << "\n";

  vector<Individuo *> noDominados;

  if (ini < 0 || ini >= inds.size() || numElems <= 0 || numElems > inds.size()) 
    return noDominados;

  if (numElems == 1) {
    noDominados.push_back(inds[ini]);
    return noDominados;
  }

  int mitad = (numElems)/2;
  int valX = mitad > 0 ? inds[ini + mitad]->getEvals()[0]
    : inds[ini]->getEvals()[0];

  int indMitad = ini+mitad;

  vector<double> evals;

  vector<int> indPreSortIzq;
  vector<int> indPreSortDer;

  // Calculamos el Presort para cada lado:
  for(int i=0; i < numElems; i++) {
    evals = inds[ indPreSort[i] ]->getEvals();
    //if (indPreSort[i] < (ini + mitad) ) {
    //if (evals[0] < valX) {
    if ( indPreSort[i] < indMitad ) {
      indPreSortIzq.push_back(indPreSort[i]);
    } else {
      indPreSortDer.push_back(indPreSort[i]);
    }
  }

  vector<Individuo *> noDomIzq = Dominancia::auxNoDominados3D_DV(inds, 
    indPreSortIzq, ini, mitad);
  vector<Individuo *> noDomDer = Dominancia::auxNoDominados3D_DV(inds, 
    indPreSortDer, ini + mitad, (numElems - mitad) );

  // Combinamos resultados, y ordenamos por presort
  vector<int> filtrados(indPreSort.size(), 0); 
  // filtrados =  [ini, ini + num_elems] -> [0, num_elems]
  for(int i=0; i < noDomIzq.size(); i++) {
    filtrados[ noDomIzq[i]->indOrd1 - ini ] = 1;
  }
  for(int i=0; i < noDomDer.size(); i++) {
    filtrados[ noDomDer[i]->indOrd1 - ini ] = 1;
  }

//  vector<Individuo *> combinados = Dominancia::filtrar_elementos(presort, filtrados);
  vector<Individuo *> combinados;

  for(int i=0; i < filtrados.size(); i++) {
    if (filtrados[ indPreSort[i] - ini ] == 1) {
      combinados.push_back( inds[ indPreSort[i] ] );
    }
  }
  if (combinados.size() == 0) {
    return noDominados;
  }

  // Algoritmo SCAN para dos dimensiones, considerando (y, z)
  evals = combinados[0]->getEvals();
  double min3 = combinados[0]->indOrd1 < indMitad ? evals[2] : numeric_limits<double>::max();

  noDominados.push_back(combinados[0]);
//  cout << "\t\tIni,Agregando Punto: " << combinados[0]->evalsToString() << "\n";

  for(int i=1; i < combinados.size(); i++) {
    evals = combinados[i]->getEvals();
    // Si supera al minimo obtenido, se actualiza:
//    cout << "\tComparando min3: " << min3 << ", con pto[ " << combinados[i]->indOrd1 << " ]: " 
//    << combinados[i]->evalsToString() << ", mitad: " <<  indMitad << "\n";
    if (evals[2] < min3) {
      min3 = combinados[i]->indOrd1 < indMitad ? evals[2] : min3;
      noDominados.push_back(combinados[i]);
//      cout << "\t\tAgregando Punto: " << combinados[i]->evalsToString() << "\n";
    //} else if( combinados[i]->indOrd1 < ini + mitad) { //evals[0] < valX ) { // punto del lado izquierdo
    } else if ( combinados[i]->indOrd1 < indMitad ) {
      noDominados.push_back(combinados[i]);
//      cout << "\t\tAgregando Punto Izq: " << combinados[i]->evalsToString() << "\n";
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