// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.allPerms();
}
 
std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = tree.allPerms();
  if (num < 1 || num > static_cast<int>(all.size()))
    return {};
  return all[num - 1];
}
 
std::vector<char> getPerm2(PMTree& tree, int num) {
  PNode* rt = tree.getRoot();
  int n = static_cast<int>(rt->children.size());
  if (n == 0) return {};
 
  auto fact = [](int k) -> int {
    int f = 1;
    for (int i = 2; i <= k; i++) f *= i;
    return f;
  };
 
  int total = fact(n);
  if (num < 1 || num > total) return {};
 
  std::vector<char> result;
  int idx = num - 1;
  PNode* cur = rt;
 
  for (int depth = 0; depth < n; ++depth) {
    int branchSize = fact(n - depth - 1);
    int childIdx = idx / branchSize;
    idx %= branchSize;
    cur = cur->children[childIdx];
    result.push_back(cur->val);
  }
  return result;
}
