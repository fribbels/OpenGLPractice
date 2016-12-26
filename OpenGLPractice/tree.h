#ifndef TREE_H
#define TREE_H

#include "branch.h"
#include <iostream>

class Tree {
public:
    Tree(Branch root, int growth);
    vector<float> getVertices();
    void grow();
    int getSize();

private:
    vector<Branch> alive;
    vector<Branch> dead;
};

#endif