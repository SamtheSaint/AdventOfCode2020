#include <vector>
#include <string.h>
#include <iostream>
#include <set>

using namespace std;

struct Instruction
{
  char opcode[3];
  int data;

  Instruction(char _opcode[3], int _data) {
    strcpy(opcode, _opcode);
    data = _data;
  }
};

int simulate(const vector<Instruction>& mem, const int swap) {
  unsigned int pc = 0;
  int acc = 0;

  bool executed[mem.size()];
  for (int i = 0; i < mem.size(); i++) executed[i] = false;


  while (pc < mem.size()) {
    Instruction cur = mem[pc];
    if (pc == swap) strcpy(cur.opcode, strcmp("jmp", cur.opcode) == 0 ? "nop" : "jmp");
    printf("PC: %d, ACC: %d, OPCODE: %s, DATA: %d\n", pc, acc, cur.opcode, cur.data);
    if (executed[pc] == true) return -1;

    if (strcmp("nop", cur.opcode) == 0) { executed[pc] = true; pc++; }
    else if (strcmp("acc", cur.opcode) == 0) { acc += cur.data; executed[pc] = true; pc++; }
    else if (strcmp("jmp", cur.opcode) == 0) { executed[pc] = true; pc += cur.data; }
    else {
      cerr << "Unknown Instruction: " << cur.opcode;
      exit(1);
    }
  }

  return acc;
}

int main(int argc, char const* argv[])
{
  vector<Instruction> mem;
  vector<int> jmp_nop;

  char _opcode[3];
  int _data;

  while (cin >> _opcode >> _data) {
    mem.push_back(Instruction(_opcode, _data));
    if ((strcmp("jmp", _opcode) == 0) || (strcmp("nop", _opcode) == 0)) jmp_nop.push_back(mem.size() - 1);
  }

  for (const int swap : jmp_nop) {
    int res = simulate(mem, swap);
    if (res == -1) continue;
    cout << res << endl;
    break;
  }

  return 0;
}


