#ifndef INDIVIDUO_HPP
#define INDIVIDUO_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Individuo {

  private:
    vector<double> evals;

  public:
    int indOrd;

  public:
    // Genera un ind aleatorio
    Individuo(int numEvals, int ini, int fin);
    
    Individuo();
    ~Individuo();

    vector<double> getEvals();
    void setEvals(vector<double> evals);

    string evalsToString();

    bool operator<(const Individuo &a) const;

};

#endif