#include <stdint.h>
#include <stdio.h>

// Instruction: [ Opcode: 3bits, dist/reg: 2bits, arg/reg, 2bits, 1bit ]
enum Opcode {
  AND = 0,
  NOT = 1,
  OR = 2,
  XOR = 3,
  SUB = 4,
  IMM = 5,
  SHR = 6,
  SHL = 7,
};

uint16_t run_search(uint16_t input[4], uint16_t expect[4]) {
  for (uint16_t i = 0; i < UINT16_MAX; i++) {
    // uint16_t registers[4] = input[4];
    uint16_t registers[4] = {input[0], input[1], input[2], input[3]};

    uint16_t opcodes[] = {i >> 13, (i << 3) >> 10, (i << 6) >> 7,
                          (i << 9) >> 4};

    uint16_t dist_reg[] = {i >> 13, (i << 3) >> 10, (i << 6) >> 7,
                           (i << 9) >> 4};

    uint16_t arg_reg[] = {i >> 13, (i << 3) >> 10, (i << 6) >> 7,
                          (i << 9) >> 4};

    for (int j = 0; j < 4; j++) {
      switch (opcodes[i]) {
      case 0: {
        registers[dist_reg[i]] = registers[dist_reg[i]] & registers[arg_reg[i]];
        break;
      }
      case 1: {
        registers[dist_reg[i]] = !registers[arg_reg[i]];
        break;
      }
      case 2: {
        registers[dist_reg[i]] = registers[dist_reg[i]] | registers[arg_reg[i]];
        break;
      }
      case 3: {
        registers[dist_reg[i]] = registers[dist_reg[i]] ^ registers[arg_reg[i]];
        break;
      }
      case 4: {
        registers[dist_reg[i]] = registers[dist_reg[i]] - registers[arg_reg[i]];
        break;
      }
      case 5: {
        registers[dist_reg[i]] = dist_reg[i] & arg_reg[i];
        break;
      }
      case 6: {
        registers[dist_reg[i]] =
            registers[dist_reg[i]] >> registers[arg_reg[i]];
        break;
      }
      case 7: {
        registers[dist_reg[i]] = registers[dist_reg[i]]
                                 << registers[arg_reg[i]];
        break;
      }
      }
    }

    if (registers == expect) {
      return i;
      break;
    }
  }
}

int main() {
  uint16_t input[4] = {4, 4, 0, 0};
  uint16_t expect[4] = {256, 0, 0, 0};

  uint16_t solution_seed = run_search(input, expect);

  printf("Solution at seed: %d\n", solution_seed);

  return 0;
}
