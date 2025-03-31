#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <ctime>        // std::time

#include "Individuo.hpp"
#include "Dominancia.hpp"

using namespace std;

vector<Individuo *> generaPtosAleatorios(int numPtos, int numEvals);
vector<Individuo *> generaPtosNoDominados(int numPtos, int numEvals);
void imprimirPtos(vector<Individuo *> & inds);

int main(int argc, char const *argv[]) {

  unsigned int seed = time(NULL);
//  seed=1539305659;
//  seed=1540070295;
  srand(seed);  

  cout << "# SEED: " << seed << "\n";
  
  int numPtos = atoi(argv[1]);
  int numEvals = atoi(argv[2]);
  int metodo = argc > 3 ?  atoi(argv[3]) : 0;

  cout << "#Generando puntos.. \n";
  vector<Individuo *> inds = generaPtosAleatorios(numPtos, numEvals);
  //vector<Individuo *> inds = generaPtosNoDominados(numPtos, numEvals);

  cout << "#Total de Puntos generados: "<< inds.size() << "\n";
//  imprimirPtos(inds);

  clock_t tIni = clock();
  clock_t t = clock() - tIni;
  
  double time_searchAC = 0;
  double time_searchSP = 0;
  double time_searchDV = 0;

  cout << "# Calculando no noDominados, Alg Cuad \n";
  tIni = clock();
  vector<Individuo *> noDominados = Dominancia::calcularNoDominados(inds);
  t = clock() - tIni;
  time_searchAC = ((double)t)/(CLOCKS_PER_SEC);

  vector<Individuo *> noDomSpan;
  vector<Individuo *> noDomDV;
 

  cout << "#Alg Cuad, Puntos no Dominados: " << noDominados.size() << " \n";
  imprimirPtos(noDominados);


  cout << "#tamanio AlgCuadr AlgSpan AlgDV\n";
  cout << numPtos << " " << time_searchAC << "\n";

  for(int i=0; i < inds.size(); i++) {
    delete inds[i];
    inds[i] = NULL;
  }

  return 0;
}

vector<Individuo *> generaPtosAleatorios(int numPtos, int numEvals) {

  set<Individuo> datos;

  int numIntentos = 0;
  cout << "# \t ******  Generando puntos *** \n";
  while (datos.size() < numPtos) {
    Individuo ind(numEvals, 0, numPtos);
    datos.insert(ind);
    //printf("# Individuo %d generado:", numIntentos);
    //cout << ind.evalsToString() << "\n";
    
    numIntentos++;
  }

  cout << "# Total de Intentos: " << numIntentos << "\n";

  vector<Individuo *> inds(numPtos);

  int i=0;
  for(set<Individuo>::iterator it= datos.begin(); 
    i < numPtos && it != datos.end(); it++) {
    inds[i] = new Individuo();
    Individuo ind = *it;
    inds[i++]->setEvals( ind.getEvals() );
  }

  return inds;
}

vector<Individuo *> generaPtosNoDominados(int numPtos, int numEvals) {

  set<Individuo> datos;

  int numIntentos = 0;
  vector<double> evals(numEvals);
  while (datos.size() < numPtos && numIntentos < numPtos) {
//    cout << "intento: " << numIntentos << "\n";
    Individuo ind;
    for(int i=0; i < numEvals; i++) {
      switch(i) {
        case 0:
          evals[i] = numIntentos % numPtos;
          break;
        case 1:
          evals[i] = ( (numPtos-1) - datos.size()) % numPtos;
          break;
        default:
          evals[i] = rand() % numPtos;
      }
    }
    ind.setEvals(evals);
    datos.insert(ind);
    numIntentos++;
  }

  cout << "# Total de Intentos: " << numIntentos << "\n";

  vector<Individuo *> inds(numPtos);

  int i=0;
  for(set<Individuo>::iterator it= datos.begin(); 
    i < numPtos && it != datos.end(); it++) {
    inds[i] = new Individuo();
    Individuo ind = *it;
    inds[i++]->setEvals( ind.getEvals() );
  }

//  shuffle(inds, inds.begin(), inds.end());
  random_shuffle(inds.begin(), inds.end());

  return inds;
}

void imprimirPtos(vector<Individuo *> & inds) {
  for(int i=0; i < inds.size(); i++) {
    cout << "# " << inds[i]->evalsToString()  << "\n";
  }
}