#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <vector>

using namespace std;

typedef vector<int> vi;

class SegmentTree {

  private:
    vi st, A;
    int n;

    int left(int p);
    int right(int p);

    void build(int p, int L, int R);
    int query(int p, int L, int R, int i, int j);
    void update(int p, int L, int R, int i, int j);

  public:
    SegmentTree(const vi & _A);
    ~SegmentTree();
    int query(int i, int j);
    void update(int p, int val);
  
};

#endif