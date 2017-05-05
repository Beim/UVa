#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;

typedef std::vector<std::string> vec_str;

void split_string (const std::string &s, std::vector<std::string> &v, const std::string &c) {
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while (std::string::npos != pos2) {
    v.push_back(s.substr(pos1, pos2 - pos1));
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if (pos1 != s.length())
    v.push_back(s.substr(pos1));
}

int getID (std::map<std::string, int> &hash, std::string &str, int &count) {
  if (hash[str]) {
    hash[str]++;
    return count;
  }
  else {
    hash[str] = count;
    return ++count;
  }
}

int travel (std::map<std::string, int> &hash, std::vector<vec_str> &db, int c1, int c2, int max, std::pair<int, int> &result) {
  int hasResult = 0;
  std::map<std::pair<int, int>, int> temp_hash;
  std::pair<int, int> temp_pair = std::make_pair(hash[db[0][c1]], hash[db[0][c2]]);
  temp_hash[temp_pair] = 0;
  for (int idx = 1; idx < max; idx++) {
    temp_pair = std::make_pair(hash[db[idx][c1]], hash[db[idx][c2]]);
    if (temp_hash.count(temp_pair)) {
      hasResult = 1;
      result = std::make_pair(temp_hash[temp_pair], idx);
      break;
    }
    else {
      temp_hash[temp_pair] = idx;
    }
  }
  return hasResult;
}

int main () {
  int n, m;
  std::map<std::string, int> h;
  while (cin >> n >> m) {
    getchar();
    std::vector<vec_str> db(n, vec_str(0));
    for (int i = 0; i < n; i++) {
      std::string line;
      std::getline(cin, line);
      split_string(line, db[i], std::string(","));
    }

    std::map<std::string, int> hash;
    int count = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        getID(hash, db[i][j], count);
      }
    }

    std::pair<int, int> result;
    int ret = 0;
    int c1, c2;
    for (c1 = 0; c1 < n; c1++) {
      for (c2 = c1 + 1; c2 < m; c2++) {
        ret = travel(hash, db, c1, c2, n, result); 
        if (ret) break;
      }
      if (ret) break;
    }
    if (ret) {
      printf("get result, col: %d,%d; row: %d,%d\n", c1, c2, result.first, result.second);
    }
    else {
      printf("no result\n");
    }
  }
}
