#include "SegmentTree.hpp"
#include <limits>
#include <iostream>

using namespace std;

SegmentTree::SegmentTree(const vi & _A) {
  A = _A;
  n = (int) A.size();
  st.assign(4*n, 0);
  build(1, 0, n-1);
}

SegmentTree::~SegmentTree() {
}

int SegmentTree::left(int p) {
  return p << 1; // 2*p
}

int SegmentTree::right (int p) {
  return (p<<1) + 1; // 2*p + 1
}

void SegmentTree::build(int p, int L, int R) {
  if (L==R)
    st[p] = L;
  else {
    build(left(p), L, (L+R)/2);
    build(right(p), (L+R)/2 + 1, R);

    int p1 = st[left(p)], p2 = st[right(p)];
    st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  }
}

int SegmentTree::query(int p, int L, int R, int i, int j) {

  if (i > R || j < L) return -1; // segmento actual fuera de rango
  if (L >= i && R <= j) return st[p]; // segmento actual contenido en el rango

  // Calculamos el minimo en l parte izq y der del intervalo:
  int p1 = query(left(p), L, (L+R)/2, i, j);
  int p2 = query(right(p), (L+R)/2 + 1, R, i, j);

  if (p1 == -1) return p2;
  if (p2 == -1) return p1;

  return (A[p1] <= A[p2]) ? p1 : p2;
}

void SegmentTree::update(int p, int L, int R, int pos, int val) {
  if (L == R) { // Estamos en una hoja
    // Llegamos al nodo que queremos actualizar
    A[pos] = val;
  } else {
    if (pos <= (L+R)/2 )
      update(left(p), L, (L+R)/2, pos, val);
    else 
      update(right(p), (L+R)/2 + 1, R, pos, val);
    // Calculamos el minimo en l parte izq y der del intervalo:
    int p1 = st[left(p)], p2 = st[right(p)];
    st[p] = (A[p1] <= A[p2]) ? p1 : p2;  
  }
}

int SegmentTree::query(int i, int j) {
  int res = query(1, 0, n-1, i, j);

  return (res >= 0) && (res <= n-1) ? 
    A[res] : numeric_limits<int>::max();
}

void SegmentTree::update(int pos, int val) {
  update(1, 0, n-1, pos, val);
}