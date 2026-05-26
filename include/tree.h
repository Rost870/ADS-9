// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

struct PNode {
  char val;
  std::vector<PNode*> children;
  explicit PNode(char v) : val(v) {}
};

class PMTree {
 private:
  PNode* root;

  void build(PNode* node, std::vector<char> remain) {
    std::sort(remain.begin(), remain.end());
    for (char c : remain) {
      PNode* child = new PNode(c);
      node->children.push_back(child);
      std::vector<char> next;
      for (char x : remain)
        if (x != c) next.push_back(x);
      build(child, next);
    }
  }

  void collect(PNode* node, std::vector<char>& path,
               std::vector<std::vector<char>>& result) const {
    path.push_back(node->val);
    if (node->children.empty()) {
      result.push_back(path);
    } else {
      for (PNode* ch : node->children)
        collect(ch, path, result);
    }
    path.pop_back();
  }

  void destroy(PNode* node) {
    for (PNode* ch : node->children) destroy(ch);
    delete node;
  }

 public:
  explicit PMTree(const std::vector<char>& elems) {
    root = new PNode('\0');
    build(root, elems);
  }

  ~PMTree() { destroy(root); }

  PNode* getRoot() const { return root; }

  std::vector<std::vector<char>> allPerms() const {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    for (PNode* ch : root->children)
      collect(ch, path, result);
    return result;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
