#include <stdint.h>
#include <stdio.h>

// Instruction: [ Opcode: 3bits, dist/reg: 2bits, arg/reg, 2bits]
enum op {
  AND = 0,
  NOT = 1,
  OR = 2,
  XOR = 3,
  SUB = 4,
  IMM = 5,
  SHR = 6,
  SHL = 7,
};

uint16_t run_search(uint16_t input[4], uint16_t expect) {
  for (uint16_t i = 0; i < UINT16_MAX; i++) {
    // uint16_t registers[4] = input[4];
    uint16_t registers[4] = {input[0], input[1], input[2], input[3]};

    uint16_t opcodes[4] = {i >> 13, (i & 0x1C00) >> 10, (i & 0xE0) >> 5,
                           (i & 0x1C) >> 2};

    uint16_t dist_reg[4] = {i >> 14, (i & 0x3000) >> 12, (i & 0xC00) >> 10,
                            (i & 0x300) >> 8};

    uint16_t arg_reg[4] = {(i & 0xC0) >> 6, (i & 0x30) >> 4, (i & 0xC) >> 2,
                           i & 0x3};

    for (int j = 0; j < 4; j++) {
      switch (opcodes[j]) {
      case AND:
        registers[dist_reg[j]] &= registers[arg_reg[j]];
        break;
      case NOT:
        registers[dist_reg[j]] = !registers[arg_reg[j]];
        break;
      case OR:
        registers[dist_reg[j]] |= registers[arg_reg[j]];
        break;
      case XOR:
        registers[dist_reg[j]] ^= registers[arg_reg[j]];
        break;
      case SUB:
        registers[dist_reg[j]] -= registers[arg_reg[j]];
        break;
      case IMM:
        registers[dist_reg[j]] = dist_reg[j] & arg_reg[j];
        break;
      case SHR:
        registers[dist_reg[j]] >>= registers[arg_reg[j]];
        break;
      case SHL:
        registers[dist_reg[j]] <<= registers[arg_reg[j]];
        break;
      }
    }

    if (registers[0] == expect) {
      return i;
      break;
    }
  }
  return 0;
}

void print_code(uint16_t seed) {
  uint16_t i = seed;
  uint16_t opcodes[4] = {i >> 13, (i & 0x1C00) >> 10, (i & 0xE0) >> 5,
                         (i & 0x1C) >> 2};

  uint16_t dist_reg[4] = {i >> 14, (i & 0x3000) >> 12, (i & 0xC00) >> 10,
                          (i & 0x300) >> 8};

  uint16_t arg_reg[4] = {(i & 0xC0) >> 6, (i & 0x30) >> 4, (i & 0xC) >> 2,
                         i & 0x3};

  for (int i = 0; i < 4; i++) {
    printf("OPCODE: %d, DIST_REG: %d, ARG_REG: %d\n", opcodes[i], dist_reg[i],
           arg_reg[i]);
  }
}

int main() {
  uint16_t input[4] = {4, 4, 0, 0};

  uint16_t solution_seed = run_search(input, 8);

  printf("Solution at seed: %d\n", solution_seed);
  print_code(solution_seed);

  return 0;
}
