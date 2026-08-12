# MSR-Fuzzer

A minimal, high-throughput brute-force engine that searches MISC opcode sequences to find instructions yielding a specific target register state.

# Why

After learning the basics of C (I learned to program in Rust - self-taught), I decided to make a simple enough project in order to test what I learned. In two hours, I built a simple MISC opcode fuzzer of sorts, which will find a very simple program in a few nanoseconds. This program would match the expected output in the first register with the input, after running through 4 opcodes that get brute forced. This is all possible due to a MISC (Minimal Instruction Set), that fits within a 16bit number, making the whole brute-force engine work in nanoseconds.

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
