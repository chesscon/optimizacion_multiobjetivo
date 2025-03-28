#ifndef DOMINANCIA_HPP
#define DOMINANCIA_HPP

#define DOMINADO -1
#define NO_DOMINADO 0

#include <vector>

using namespace std;

#include "Individuo.hpp"

class Dominancia {

  public:
    static int comparaIndsEvals(Individuo *ind1, Individuo *ind2);
    static int comparaIndsEvals2(Individuo *ind1, Individuo *ind2);

    static bool comparador1(Individuo *ind1, Individuo *ind2);
    static bool comparador2(Individuo *ind1, Individuo *ind2);

    static int comparaIndsDominancia(Individuo *ind1, Individuo *ind2);

    // Algoritmo Cuadratico
    static vector<Individuo *> calcularNoDominados(vector<Individuo *> inds);

    // Algoritmo SPAN
    static vector<Individuo *> calcularNoDominados2D_span( vector<Individuo *> inds );
    static vector<Individuo *> calcularNoDominados3D_span( vector<Individuo *> inds ); //,
//        vector<Individuo *> & noDominados);

    // Algoritmo Divide y Venceras
    static vector<Individuo *> calcularNoDominados2D_DV( vector<Individuo *> inds );
    static vector<Individuo *> calcularNoDominados3D_DV( vector<Individuo *> inds );    

    static vector<Individuo *> filtrar_elementos(vector<Individuo *> v, vector<int> f);

  private:
    static vector<Individuo *> auxNoDominados2D_DV( vector<Individuo *> & inds,
      int ini, int numElems );

    static vector<Individuo *> auxNoDominados3D_DV( vector<Individuo *> & inds,
      vector<int> indPreSort, int ini, int numElems);
};

#endif