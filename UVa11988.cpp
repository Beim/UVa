/*
 * uva11988
 */
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <utility>

using namespace std;

struct node {
  char val;
  node *next;
  node (char c) : val(c), next(NULL) {}
};

int main () {
  char c;
  node *root = new node('1');
  node *pos, *first, *last;
  pos = first = last = root;
  while (scanf("%c", &c) > 0) {
    if (c == '[') {
      pos = first;
    }
    else if (c == ']') {
      pos = last;
    }
    else if (c == '\n') {
      node *temp = new node(c);
      last->next = temp;
      last = temp;
      pos = last;
      first = last;
    }
    else {
      node *temp = new node(c);
      temp->next = pos->next;
      pos->next = temp;
      pos = temp;

      if (pos->next == NULL) {
        last = pos;
      }
    }
  }
  pos = root->next;
  while (pos != NULL && pos->next != NULL) {
    cout << pos->val;
    pos = pos->next;
  }
  cout << endl;
  return 0;
}
