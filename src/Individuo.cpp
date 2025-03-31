#include <iostream>
#include <cstdlib>
#include "Individuo.hpp"

using namespace std;

Individuo::Individuo(int numEvals, int ini, int fin) {
  this->evals.resize(numEvals);
  for(int i=0; i < numEvals; i++) {
    this->evals[i] = ini + (rand() % ((fin - ini)));
  }
}

Individuo::Individuo() {
}


Individuo::~Individuo() {
}

vector<double> Individuo::getEvals() {
  return this->evals;
}


void Individuo::setEvals(vector<double> evals) {
  this->evals = evals;
}

string Individuo::evalsToString() {

  string res="(";

  for(int i=0; i < evals.size(); i++) {
    res = res + to_string(evals[i]) + ", ";
  }
  res = res + ")";

  return res;
}

bool Individuo::operator<(const Individuo &a) const {
      
  int res = 0;

  for(int i=0; i < evals.size() && res == 0; i++ ) {
    if (evals[i] < a.evals[i]) {
      res = -1;
      // break;
    }
    if (evals[i] > a.evals[i]) {
      res = 1;
      // break;
    }
  }
      return res < 0;
}