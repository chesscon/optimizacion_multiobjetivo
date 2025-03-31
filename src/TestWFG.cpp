#include <iostream>
#include <cmath>
#include <limits>
#include "TestWFG.hpp"

//// Toolkit includes. //////////////////////////////////////////////////////
#include "Toolkit/ExampleProblems.h"
#include "Toolkit/TransFunctions.h"

using namespace std;
using namespace WFG::Toolkit;
using namespace WFG::Toolkit::Examples;

/* Inicilizar variables estaticas */
int TestWFG::k = 4;
int TestWFG::M = 2;
string TestWFG::problem = "WFG1";
vector<double> TestWFG::w;
vector<double> TestWFG::f;
int TestWFG::tipoEval = 0;

namespace {
vector< double > problem_calc_fitness(const vector< double >& z, 
  const int k, const int M, string fn) {
      if ( "WFG1" == fn ) {
        return Problems::WFG1( z, k, M );
      } else if ( "WFG2" == fn ) {
        return Problems::WFG2( z, k, M );
      } else if ( "WFG3" == fn  ) {
        return Problems::WFG3( z, k, M );
      } else if ( "WFG4" == fn ) {
        return Problems::WFG4( z, k, M );
      } else if ( "WFG5" == fn ) {
        return Problems::WFG5( z, k, M );
      } else if ( "WFG6" == fn ) {
        return Problems::WFG6( z, k, M );
      } else if ( "WFG7" == fn ) {
        return Problems::WFG7( z, k, M );
      } else if ( "WFG8" == fn ) {
        return Problems::WFG8( z, k, M );
      } else if ( "WFG9" == fn ) {
        return Problems::WFG9( z, k, M );
      } else if ( "I1" == fn ) {
        return Problems::I1( z, k, M );
      } else if ( "I2" == fn ) {
        return Problems::I2( z, k, M );
      } else if ( "I3" == fn ) {
        return Problems::I3( z, k, M );
      } else if ( "I4" == fn ) {
        return Problems::I4( z, k, M );
      } else if ( "I5" == fn) {
        return Problems::I5( z, k, M );
      } else {
        cout << "Unknown problem " << fn <<  "\n";
        //assert( false );
        return vector< double >();
      }
  }
}


double TestWFG::evaluaWFG(double *x, int n) {

  vector< double > z;  // the decison vector
  for( int i = 0; i < n; i++ ) {
    z.push_back( x[i] * (2*(i+1)) );
  } 
  
  TestWFG::f = problem_calc_fitness( z, TestWFG::k, TestWFG::M, TestWFG::problem);

  double res = 0;
  if (tipoEval != res) {
    res = numeric_limits<double>::min();
  }

  for( int i = 0; i < f.size() && i < w.size(); i++ ) {
    if (tipoEval == 0) {
      res += f[i]*TestWFG::w[i]; // Suma de Pesos
    } else {
      res = f[i]*fabs(TestWFG::w[i]); // Tchebycheff (Considerando z* = (0,0))
    }
  } 

  return res;
}

void TestWFG::evaluaResWFG(double *x, int n, double *g, int m) {}

void TestWFG::setParams(int k, int M, string problem, int tipoEval) {
  TestWFG::k = k;
  TestWFG::M = M;
  TestWFG::problem = problem;
  TestWFG::f.resize(M);
  TestWFG::w.resize(M);
  TestWFG::tipoEval = tipoEval;
}

void TestWFG::setW(vector<double> & w) {
  TestWFG::w = w;
}

vector<double> TestWFG::getEvals() {
  return TestWFG::f;
}