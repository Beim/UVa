/*
 * UVa210
 * https://uva.onlinejudge.org/external/2/210.pdf
 */
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAX_PROCESS = 100;

int config[6];
vector<string> instr; // 指令
int instr_pos[MAX_PROCESS]; // 每个程序指令执行到的位置
deque<int> wait_queue; // 运行的程序队列
queue<int> block_queue; // 阻止的队列
map<char, int> var;

void next_tick (int pid, int &quota) {
  wait_queue.pop_front();
  wait_queue.push_back(pid);
  quota = config[5];
}

void run () {
  int lock = false;
  int quota = config[5];
  while (!wait_queue.empty()) {
    int pid = wait_queue.front(); // 正在执行的进程
    int ip = instr_pos[pid]; // 正在执行的指令数目
    string str = instr[ip]; // 正在执行的指令
    switch (str[2]) {
      case '=': // a = 1
        if (config[0] <= quota) { // 可以执行这条指令
          quota -= config[0];
          // var[pid][str[0]] = atoi(str.substr(4).c_str()); // 存变量
          var[str[0]] = atoi(str.substr(4).c_str()); // 存变量
          instr_pos[pid]++;
          if (quota == 0) {
            next_tick(pid, quota);
          }
        }
        else { // 不能执行这条指令
          next_tick(pid, quota);
        }
        break;
      case 'i': // print a
        if (config[1] <= quota) {
          quota -= config[1];
          cout << pid + 1 << ": "
            << var[str[6]] << endl;
          instr_pos[pid]++;
          if (quota == 0) {
            next_tick(pid, quota);
          }
        }
        else {
          next_tick(pid, quota);
        }
        break;
      case 'c': // lock
        if (lock) { // 锁住
          wait_queue.pop_front();
          block_queue.push(pid);
          quota = config[5];
        }
        else if (config[2] <= quota) { // 没有锁，quota足够执行
          quota -= config[2];
          lock = true;
          instr_pos[pid]++;
          if (quota == 0) {
            next_tick(pid, quota);
          }
        }
        else { // 没有锁，但是quota不足
          next_tick(pid, quota);
        }
        break;
      case 'l': // unlock
        if (config[3] <= quota) {
          quota -= config[3];
          lock = false;
          instr_pos[pid]++;
          if (!block_queue.empty()) {
            int npid = block_queue.front();
            block_queue.pop();
            wait_queue.insert(wait_queue.begin() + 1, npid);
          }
          if (quota == 0) {
            next_tick(pid, quota);
          }
        }
        else {
          next_tick(pid, quota);
        }
        break;
      case 'd': // end;
        if (config[4] <= quota) {
          quota = config[5];
          wait_queue.pop_front();
        }
        else {
          next_tick(pid, quota);
        }
        break;
    }
  }
}

int main () {
  int cases;
  cin >> cases;
  while (cases--) {
    for (int i = 0; i < MAX_PROCESS; i++)
      instr_pos[i] = 0;
    instr.clear();
    wait_queue.clear();
    block_queue = queue<int>();
    var.clear();

    int process_num;
    cin >> process_num;
    for (int i = 0; i < 6; i++)
      cin >> config[i];
    getchar();

    int pid = -1;
    while (process_num--) {
      pid++;
      instr_pos[pid] = (int)instr.size();
      string str;
      while (true) {
        getline(cin, str);
        instr.push_back(str);
        if (str == "end") {
          wait_queue.push_back(pid);
          break;
        }
      }
    }
    run();
  }
  return 0;
}
