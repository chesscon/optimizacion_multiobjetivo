#ifndef TEST_WFG_HPP
#define TEST_WFG_HPP

#include <vector>
#include <string>

using namespace std;

class TestWFG {
  public:
    static vector<double> w; // pesos
    static int k; // Numero de parametros de posicion
    static int M; // Numero de Objetivos
    static string problem;
    static vector<double> f;
    static int tipoEval; // Funcion de escalizacion 

    /* Funciones */
    static double evaluaWFG(double *x, int n);
    static void evaluaResWFG(double *x, int n, double *g, int m);

    static void setParams(int k, int M, string problem, int tipoEval);
    static void setW(vector<double> & w);
    static vector<double> getEvals();

};

#endif