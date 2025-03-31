#ifndef DOMINANCIA_HPP
#define DOMINANCIA_HPP

#define PRIMERO_DOMINA -2
#define SEGUNDO_DOMINA 2
#define IGUALES 0
#define SIN_DOMINANCIA -1

#include <vector>

using namespace std;

#include "Individuo.hpp"

class Dominancia {

  public:
    static int comparaIndsDominancia(Individuo *ind1, Individuo *ind2);

    // Algoritmo Cuadratico
    static vector<Individuo *> calcularNoDominados(vector<Individuo *> inds);

    static vector<Individuo *> filtrar_elementos(vector<Individuo *> v, 
      vector<int> filtro);
};

#endif