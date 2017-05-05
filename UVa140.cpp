/*
 * UVa140 accept
 */
#include <iostream>
// #include <sstream>
#include <vector>
// #include <cstdio>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
// #include <utility>
#include <cstring>
// #include <cstdlib>

// #include "./util.hpp"

using namespace std;

struct LinkNode {
    int idx;
    LinkNode *next;
    LinkNode(int i = -1, LinkNode *n = NULL) {
        idx = i;
        next = n;
    }
    ~LinkNode() {
        idx = 0;
        next = NULL;
    }
};

struct Input {
    char *input_str = NULL;
    int pos = 0;
    char getNext() {
        return input_str[pos++];
    }
    void reset(char *input_str = NULL) {
        this->input_str = input_str;
        pos = 0;
    }
};

struct Permu {
    vector<int> *vec;
    int *permu_arr;
    int get(int i) { return (*vec)[permu_arr[i]]; }
    int size() { return vec->size(); }
    Permu (vector<int> *v) { vec = v; }
};

const int MAXN = 200;

LinkNode *nodes[26]; // 记录输入节点
map<int, int> nodes_map; // 记录出现过的节点
vector<int> vec; // 记录出现过的节点
vector<int> vec_ans; // 结果排列
int permu_arr[26]; // 辅助获得全排列
char input_str[MAXN]; // 按行获取输入
Permu permu(&vec); // 辅助获得全排列
int imin; // 记录所有排列的最大距离的最小值

void free_nodes() {
    for (int i = 0; i < 26; i++) {
        if (nodes[i]) {
            LinkNode *temp = nodes[i];
            while (temp) {
                LinkNode *temp1 = temp;
                temp = temp->next;
                free(temp1);
            }
        }
    }
}

void find_max() {
    int one_max = 0;
    for (int i = 0; i < permu.size(); i++) {
        int j = permu.get(i); // A -> F B   j -> node->idx node->idx
        int k = 0;
        LinkNode *node = nodes[j];
        if (node) {
            while (node) {
                for (int p = 0; p < permu.size(); p++) {
                    if (permu.get(p) == node->idx) {
                        int distance = p > i ? p-i : i-p;
                        k = distance > k ? distance : k;
                        break;
                    }
                }
                node = node->next;
            }
        }
        if (k >= imin && imin > 0) return;
        one_max = k > one_max ? k : one_max;
    }
    if (imin < 0 || imin > one_max) {
        imin = one_max;
        vec_ans.clear();
        for (int i = 0; i < permu.size(); i++) {
            vec_ans.push_back(permu.get(i));
        }
    }
}

void permutation(int cur) {
    int n = vec.size();
    if (cur == n) {
        permu.permu_arr = permu_arr;
        find_max();
        return;
    }
    for (int i = 0; i < n; i++) {
        permu_arr[cur] = i;
        int ok = 1;
        for (int j = 0; j < cur; j++) {
            if (permu_arr[j] == i) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            permutation(cur+1);
        }
    }
}

int main(void) {
    Input input;
    while (scanf("%s", input_str) && input_str[0] != '#') {
        nodes_map.clear();
        vec.clear();
        imin = -1;
        free_nodes();
        memset(nodes, 0, sizeof(nodes));
        input.reset(input_str);
        int len = strlen(input_str);
        int flag = 0;
        int pos = 0;

        while (input.pos < len) {
            char c = input.getNext();
            if (c == ':') {
               flag = 1; 
            }
            else if (c == ';') {
                flag = 0;
            }
            else {
                nodes_map[c-'A'] = 1;
                if (flag == 0) {
                    pos = c - 'A';
                }
                else {
                    if (nodes[pos] == NULL) {
                        nodes[pos] = new LinkNode(c-'A');
                    }
                    else {
                        LinkNode *temp = nodes[pos];
                        nodes[pos] = new LinkNode(c-'A', temp);
                    }
                }
            }
        }
        for (auto it = nodes_map.begin(); it != nodes_map.end(); it++) {
            vec.push_back(it->first);
        }
        permutation(0);
        for (auto it = vec_ans.begin(); it != vec_ans.end(); it++) {
            printf("%c ", *it + 'A');
        }
        printf("-> %d\n", imin);
    }
    return 0;
}
