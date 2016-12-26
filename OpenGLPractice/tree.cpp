#include "tree.h"

template<typename T>
vector<T> vectorAppend(vector<T> first, vector<T> second) {
    for (int i = 0; i < second.size(); i++) {
        first.push_back(second[i]);
    }
    return first;
}

Tree::Tree(Branch root, int growth) {
    alive.push_back(root);
    for (int i = 0; i < growth; i++) {
        grow();
    }
}

void Tree::grow() {
    std::cout << "GROW\n";
    vector<Branch> newBranches;
    for(int i = 0; i < alive.size(); i++) {
        Branch branch = alive[i];
        newBranches = vectorAppend(newBranches, branch.fork());
    }

    dead = vectorAppend(dead, alive);
    alive = newBranches;
}

vector<float> Tree::getVertices() {
    vector<float> result;

    for (int i = 0; i < dead.size(); i++) {
        vector<float> vertices = dead.at(i).getVertices();
        result = vectorAppend(result, vertices);
    }

    return result;
}

int Tree::getSize() {
    return dead.size();
}