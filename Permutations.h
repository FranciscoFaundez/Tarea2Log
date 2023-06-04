#ifndef PERMUTATIONS_H_INCLUDED
#define PERMUTATIONS_H_INCLUDED

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

std::vector<int> PermutationEqui(int n_max, int seed);
std::vector<int> PermutationSkew(int n_max, int seed, float alpha);

#endif // PERMUTATIONS_H_INCLUDED
