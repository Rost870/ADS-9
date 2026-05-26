// Copyright 2025 NNTU-CS
#include <vector>
#include "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.allPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = tree.allPerms();
  if (num < 1 || num > static_cast<int>(all.size()))
    return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  PNode* rt = tree.getRoot();
  int n = static_cast<int>(rt->children.size());
  if (n == 0) return {};
  int total = 1;
  for (int i = 2; i <= n; i++) total *= i;
  if (num < 1 || num > total) return {};
  std::vector<char> result;
  int idx = num - 1;
  PNode* cur = rt;
  for (int depth = 0; depth < n; ++depth) {
    int branch = 1;
    for (int i = 2; i <= n - depth - 1; i++) branch *= i;
    int childIdx = idx / branch;
    idx %= branch;
    cur = cur->children[childIdx];
    result.push_back(cur->val);
  }
  return result;
}
