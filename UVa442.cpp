/*
 * uva442
 */
#include <iostream>
#include <vector>
// #include <cstdio>
// #include "./util.hpp"
// #include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <utility>

using namespace std;

int multi_time (pair<int, int> &p1, pair<int, int> &p2) {
  if (p1.second == p2.first) {
    return p1.first * p1.second * p2.second;
  }
  else {
    return 0;
  }
}

int count_time (const string &str, map<char, int[2]> &hash) {
  int times = 0;
  if (str.length() <= 1) return 0;
  stack<pair<int, int>> st;
  auto it = str.begin();
  while (it != str.end()) {
    if (*it == '(') {
      it++;
    }
    else if (*it == ')') {
      pair<int, int> p1(st.top());
      st.pop();
      pair<int, int> p2(st.top());
      st.pop();
      int t = multi_time(p2, p1);
      if (!t) return -1;
      times += t;
      st.push(make_pair(p2.first, p1.second));
      it++;
    }
    else {
      st.push(make_pair(hash[*it][0], hash[*it][1]));
      it++;
    }
  }
  while (st.size() > 1) {
    pair<int, int> p1(st.top());
    st.pop();
    pair<int, int> p2(st.top());
    st.pop();
    int t = multi_time(p2, p1);
    if (!t) return -1;
    times += t;
    st.push(make_pair(p2.first, p1.second));
  }
  return times;
}

int main () {
  int cases;
  cin >> cases;
  map<char, int [2]> hash;
  char c; int arr[2];
  for (int i = 0; i < cases; i++) {
    cin >> c >> arr[0] >> arr[1];
    hash[c][0] = arr[0];
    hash[c][1] = arr[1];
  }
  getchar();
  string str;
  while (getline(cin, str)) {
    int t = count_time(str, hash);
    if (t >= 0) {
      cout << t << endl;
    }
    else {
      cout << "error\n";
    }
  }
  return 0;
}
