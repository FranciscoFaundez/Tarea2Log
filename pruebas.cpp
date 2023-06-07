#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;
using ll = long long;

int main(){

    vector<int> v(10);
     v = {1,2,3,4,5,6,7,8,9,10};
    v.push_back(11);
    //printeo el vector
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    return 0;
}