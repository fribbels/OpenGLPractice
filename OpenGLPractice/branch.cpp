#include "branch.h"

vector<vec4> get2DPerpendicularVectors(vec4 orig, float base);
float degToRad(float deg);
float randomFloat(float a, float b);

Branch::Branch(vec4 rootVec, vec4 pointVec, float baseWidth) {
    root = rootVec;
    point = pointVec;
    base = baseWidth;
}

vector<float> Branch::getVertices() {
    vec4 dir = root-point;
    vector<vec4> perpVecs = get2DPerpendicularVectors(dir, base);
    vec4 perp1 = perpVecs.at(0);
    vec4 perp2 = perpVecs.at(1);

    float arr[] = {perp1.x+root.x, perp1.y+root.y, 0,
                                perp2.x+root.x, perp2.y+root.y, 0,
                                point.x, point.y, 0};
    vector<float> vertices(arr, arr + sizeof(arr) / sizeof(arr[0]));

    return vertices;
}

vector<Branch> Branch::fork() {
    vector<Branch> result;

    for (int i = 0; i < 3; i++) {
        float theta = degToRad(randomFloat(-80.0f, 80.0f));
        vec4 dir = point-root;
        float x = dir.x*cos(theta) - dir.y*sin(theta);
        float y = dir.x*sin(theta) + dir.y*cos(theta);
    
        float norm = sqrt(dir.y * dir.y + dir.x * dir.x);
        float hShrink = 0.8f;
        float bShrink = 0.6f;
        dir = vec4(x, y, 0, 0) * hShrink;
        Branch newBranch(point, dir+point, bShrink*base);
        result.push_back(newBranch);
    }
    return result;
}

vector<vec4> get2DPerpendicularVectors(vec4 orig, float base) {
    vector<vec4> result;
    float norm = sqrt(orig.y * orig.y + orig.x * orig.x);
    float scale = 1/norm*base/2;
    result.push_back(vec4(-orig.y, orig.x, 0, 0)*scale);
    result.push_back(vec4(orig.y, -orig.x, 0, 0)*scale);

    return result;
}

float degToRad(float deg) {
    return deg * 0.0174533f;
}

float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}