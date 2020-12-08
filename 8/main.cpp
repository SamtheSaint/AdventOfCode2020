#include <vector>
#include <string.h>
#include <iostream>

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


int main(int argc, char const* argv[])
{
  unsigned int pc = 0;
  int acc = 0;
  vector<Instruction> mem;

  char _opcode[3];
  int _data;
  while (cin >> _opcode >> _data) {
    mem.push_back(Instruction(_opcode, _data));
  }

  bool executed[mem.size()];
  for (int i = 0; i < mem.size(); i++) executed[i] = false;

  while (pc < mem.size()) {
    Instruction cur = mem[pc];
    printf("PC: %d, ACC: %d, OPCODE: %s, DATA: %d\n", pc, acc, cur.opcode, cur.data);
    if (executed[pc] == true) break;

    if (strcmp("nop", cur.opcode) == 0) { executed[pc] = true; pc++; }
    else if (strcmp("acc", cur.opcode) == 0) { acc += cur.data; executed[pc] = true; pc++; }
    else if (strcmp("jmp", cur.opcode) == 0) { executed[pc] = true; pc += cur.data; }
    else {
      cerr << "Unknown Instruction: " << cur.opcode;
      exit(1);
    }
  }

  return 0;
}


