# MSR-Fuzzer

A minimal, high-throughput brute-force engine that searches MISC opcode sequences to find instructions yielding a specific target register state.

# Why

After learning the basics of C (I learned to program in Rust - self-taught), I decided to make a simple enough project in order to test what I learned. In two hours, I built a simple MISC opcode fuzzer of sorts, which will find a very simple program in a few nanoseconds. This program would match the expected output in the first register with the input, after running through 4 opcodes that get brute forced. This is all possible due to a MISC (Minimal Instruction Set), that fits within a 16bit number, making the whole brute-force engine work in nanoseconds.

# Overview

MSR-Fuzzer is a micro-virtual machine and brute-force instruction synthesizer written in C. It encodes short Minimal Instruction Set Computer (MISC) instruction streams into a single 16-bit scalar integer (seed).By bounding the entire execution payload to 16 bits, the total program search space is limited to $2^{16}$ (65,536) total candidate programs. This design allows exhaustive iteration over every possible 4-instruction combination in nanoseconds without heap allocations or pointer indirection.

# Specifications

Register File:

* Registers: 4 general-purpose 16-bit registers (registers[0] through registers[3]).
* Target Register: registers[0] serves as the output accumulator evaluated against the target value.

# Instruction Set Architecture (ISA)

| Opcode | Encoding | Mnemonic | C Equivalent Operation | Description |
| :---: | :---: | :---: | :--- | :--- |
| `0` | `000` | `AND` | `registers[dist_reg] &= registers[arg_reg]` | Bitwise AND of target register and argument register |
| `1` | `001` | `NOT` | `registers[dist_reg] = !registers[arg_reg]` | Logical NOT of argument register (results in `0` or `1`) |
| `2` | `010` | `OR`  | `registers[dist_reg] |= registers[arg_reg]` | Bitwise OR of target register and argument register |
| `3` | `011` | `XOR` | `registers[dist_reg] ^= registers[arg_reg]` | Bitwise XOR of target register and argument register |
| `4` | `100` | `SUB` | `registers[dist_reg] -= registers[arg_reg]` | Integer subtraction of argument register from target register |
| `5` | `101` | `IMM` | `registers[dist_reg] = dist_reg & arg_reg` | Immediate mask combining register index values directly |
| `6` | `110` | `SHR` | `registers[dist_reg] >>= registers[arg_reg]` | Bitwise logical right-shift by value in argument register |
| `7` | `111` | `SHL` | `registers[dist_reg] <<= registers[arg_reg]` | Bitwise logical left-shift by value in argument register |

# API Reference

`run_search`

```
uint16_t run_search(uint16_t input[4], uint16_t expect);
```

Executes an exhaustive linear search across all $2^{16}$ integer seeds.input: Initial 4-element 16-bit array copied into registers[0..3]. expect: Target value required in registers[0] upon completion of the 4th instruction. Returns: The first uint16_t seed value matching the condition, or 0 if no candidate satisfies expect.

`print_code`

```void print_code(uint16_t seed, uint16_t input[4]);```

Decodes and executes a solution seed step-by-step, logging disassembly and live CPU register views to standard output. seed: The synthesized 16-bit program payload. input: Initial register state array.

Example Execution Trace

For an input array of {2194, 100, 0, 0} and target 2094, run_search evaluates execution paths and disassembles the synthesized binary:

```
Solution at seed: 2097
OPCODE: (AND), DIST_REG: (0), ARG_REG: (0), RegView: (2194)(100)(0)(0)
OPCODE: (OR ), DIST_REG: (0), ARG_REG: (3), RegView: (2194)(100)(0)(0)
OPCODE: (NOT), DIST_REG: (2), ARG_REG: (0), RegView: (2194)(100)(0)(0)
OPCODE: (SUB), DIST_REG: (0), ARG_REG: (1), RegView: (2094)(100)(0)(0)
```

#### License

<sup>
Licensed under either of <a href="LICENSE-APACHE">Apache License, Version
2.0</a> or <a href="LICENSE-MIT">MIT license</a> at your option.
</sup>

<br>

<sub>
Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in this crate by you, as defined in the Apache-2.0 license, shall
be dual licensed as above, without any additional terms or conditions.
</sub>
