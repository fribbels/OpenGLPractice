#ifndef BRANCH_H
#define BRANCH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h> 
#include <iostream> 
#include <ctime>

using namespace glm;
using namespace std;

class Branch {
public:
    Branch(vec4 rootVec, vec4 pointVec, float baseWidth);
    vector<float> getVertices();
    vector<Branch> fork();

private:
    vec4 root;
    vec4 point;

    float base;
};

#endif