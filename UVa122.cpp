/*
 * UVa122
 */
#include <iostream>
#include <vector>
// #include <cstdio>
// #include <algorithm>
#include <queue>
// #include <map>
// #include <stack>
// #include <utility>
#include <cstring>

// #include "./util.hpp"

using namespace std;

struct Node {
  int val;
  bool have_value;
  Node *left;
  Node *right;
  Node (int x = 0) : val(x), have_value(false), left(NULL), right(NULL) {}
};

const int MAXN = 256;

Node *root;
char str[MAXN];
bool failed;

void addnode (int val, char *s) {
  int n = strlen(s);
  Node *u = root;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'L') {
      if (u->left == NULL) 
        u->left = new Node();
      u = u->left;
    }
    else if (s[i] == 'R') {
      if (u->right == NULL)
        u->right = new Node();
      u = u->right;
    }
  }
  if (u->have_value) failed = true;
  u->val = val;
  u->have_value = true;
}

bool read_input () {
  root = new Node();
  failed = false;
  for (;;) {
    if (scanf("%s", str) != 1) return false;
    if (strcmp(str, "()") == 0) break;
    int val;
    sscanf(&str[1], "%d", &val);
    addnode(val, strchr(str, ',') + 1);
  }
  return true;
}

bool bfs (vector<int> &ans) {
  queue<Node *> q;
  ans.clear();
  q.push(root);
  while (!q.empty()) {
    Node *u = q.front();
    q.pop();
    if (!u->have_value) return false;
    ans.push_back(u->val);
    if (u->left != NULL) q.push(u->left);
    if (u->right != NULL) q.push(u->right);
  }
  return true;
}

int main () {
  while (read_input()) {
    vector<int> ans;
    if (failed || !bfs(ans)) {
      cout << "not complete\n";
      continue;
    }
    for (auto it = ans.begin(); it != ans.end() - 1; it++) {
      cout << *it << " ";
    }
    cout << *(ans.end() - 1) << endl;
  }
  return 0;
}
