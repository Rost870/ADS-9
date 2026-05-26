// Copyright 2025 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "tree.h"

static void printPerm(const std::vector<char>& p) {
  for (char c : p) std::cout << c;
  std::cout << "\n";
}

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::vector<char> small = {'1', '2', '3'};
  PMTree demo(small);

  std::cout << "=== All permutations of {1,2,3} ===\n";
  std::vector<std::vector<char>> all = getAllPerms(demo);
  for (size_t i = 0; i < all.size(); i++) printPerm(all[i]);

  std::cout << "\n--- getPerm1 ---\n";
  for (int i = 1; i <= static_cast<int>(all.size()); ++i) {
    std::cout << "perm1[" << i << "] = ";
    printPerm(getPerm1(demo, i));
  }

  std::cout << "\n--- getPerm2 ---\n";
  for (int i = 1; i <= static_cast<int>(all.size()); ++i) {
    std::cout << "perm2[" << i << "] = ";
    printPerm(getPerm2(demo, i));
  }

  std::cout << "\n=== Timing experiment (microseconds) ===\n";
  std::cout << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";

  for (int n = 2; n <= 9; ++n) {
    std::vector<char> elems;
    for (int i = 0; i < n; ++i)
      elems.push_back(static_cast<char>('1' + i));
    PMTree t(elems);
    int total = 1;
    for (int i = 2; i <= n; ++i) total *= i;
    int rnum = (std::rand() % total) + 1;

    auto t0 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    getPerm1(t, rnum);
    auto t3 = std::chrono::high_resolution_clock::now();
    auto t4 = std::chrono::high_resolution_clock::now();
    getPerm2(t, rnum);
    auto t5 = std::chrono::high_resolution_clock::now();

    typedef std::chrono::microseconds us_t;
    int64_t d1 = std::chrono::duration_cast<us_t>(t1 - t0).count();
    int64_t d2 = std::chrono::duration_cast<us_t>(t3 - t2).count();
    int64_t d3 = std::chrono::duration_cast<us_t>(t5 - t4).count();

    std::cout << n << "\t" << d1 << "\t\t"
              << d2 << "\t\t" << d3 << "\n";
  }

  return 0;
}
