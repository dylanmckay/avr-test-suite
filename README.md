# avr-test-suite

[![Crates.io](https://img.shields.io/crates/v/avr-test-suite.svg)](https://crates.io/crates/avr-test-suite)
[![Build Status](https://travis-ci.org/dylanmckay/avr-test-suite.svg?branch=master)](https://travis-ci.org/dylanmckay/avr-test-suite)
[![license](https://img.shields.io/github/license/dylanmckay/avr-test-suite.svg)]()

A standalone test-suite for AVR compilers.

Uses [simavr](https://github.com/buserror/simavr) under the hood.

# Usage

```bash
git clone https://github.com/dylanmckay/avr-test-suite.git
cd avr-test-suite

# Run all tests
./run-tests.sh
```

# Binaries

There are two binaries included in this crate.

## `avr-lit`

The test runner.

Usage

```bash
cd avr-test-suite

# Run all tests with avr-gcc
cargo run --bin avr-lit -- --avr-gcc

# Run specific test with avr-gcc
cargo run --bin avr-lit -- --avr-gcc tests/memory/copy-immediate-to-sram/copy_u32.cpp

# Run all tests with llvm
cargo run --bin avr-lit -- --llvm-sysroot /path/to/llvm/buildtree

# Run specific test with avr-gcc
cargo run --bin avr-lit -- --llvm-sysroot /path/to/llvm/buildtree tests/memory/copy-immediate-to-sram/copy_string.cpp
```

## `avr-sim`

An avr simulator that will flash binaries given to it onto an emulated
AVR and execute the program until it goes into indefinite sleep mode with
interrupts disabled.

It will also connect the simulated UART to standard output, which can
then be used by tests or other stuff.

Usage

```bash
cd avr-test-suite

# Run a program by loading it via disk
cargo run --bin avr-sim MyExecutable.elf

# Compile a file and pipe it directly into the simulator to run.
echo 'int main() { return 0; }' > main.c
avr-gcc main.c -mmcu=atmega328 -o /dev/stdout | cargo run --bin avr-sim MyExecutable
```

# Test format

Uses the [lit](https://crates.io/crates/lit) crate.

# Coverage

  * Basic copying of immediate integer values to SRAM
  * Memory copying from one chunk of RAM to another chunk

# Tests yet to be implemented

  * Calling convention tests
  * Interrupt handler tests
  * ... many more

