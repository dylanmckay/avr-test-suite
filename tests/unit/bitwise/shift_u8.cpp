// RUN: @cxx @cxxflags -mmcu=atmega328p @file -o @tempfile -O0 && avr-sim @tempfile -w OUTPUT_VALUE=u8

#include <avrlit/boilerplate/unit_test.h>

uint8_t OUTPUT_VALUE = 0xff;

template<typename A, typename B>
__attribute__ ((noinline)) uint8_t shift_left(volatile A a, volatile B b) {
  return a << b;
}

template<typename A, typename B>
__attribute__ ((noinline)) uint8_t shift_right(volatile A a, volatile B b) {
  return a >> b;
}

// This final check ensures that the assignment correctly updates the global variable.
void unit_test(void) {
  // u8-vs-u8

  // Shift left:
  // CHECK: changed(OUTPUT_VALUE) = 2
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 0);
  // CHECK: changed(OUTPUT_VALUE) = 4
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 1);
  // CHECK: changed(OUTPUT_VALUE) = 8
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 2);
  // CHECK: changed(OUTPUT_VALUE) = 16
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 3);
  // CHECK: changed(OUTPUT_VALUE) = 32
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 4);
  // CHECK: changed(OUTPUT_VALUE) = 64
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 5);
  // CHECK: changed(OUTPUT_VALUE) = 128
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(2, 6);
  // CHECK: changed(OUTPUT_VALUE) = 0
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(1, 8);
  // CHECK: changed(OUTPUT_VALUE) = 120
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(30, 2);
  // CHECK: changed(OUTPUT_VALUE) = 128
  OUTPUT_VALUE = shift_left<uint8_t, uint8_t>(1, 7);

  // Shift right:
  // CHECK: changed(OUTPUT_VALUE) = 127
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(255, 1);
  // CHECK: changed(OUTPUT_VALUE) = 12
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(100, 3);
  // CHECK: changed(OUTPUT_VALUE) = 0
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(50, 10); // shift completely out
  // CHECK: changed(OUTPUT_VALUE) = 50
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(200, 2);
  // CHECK: changed(OUTPUT_VALUE) = 128
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 0);
  // CHECK: changed(OUTPUT_VALUE) = 64
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 1);
  // CHECK: changed(OUTPUT_VALUE) = 32
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 2);
  // CHECK: changed(OUTPUT_VALUE) = 16
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 3);
  // CHECK: changed(OUTPUT_VALUE) = 8
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 4);
  // CHECK: changed(OUTPUT_VALUE) = 4
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 5);
  // CHECK: changed(OUTPUT_VALUE) = 2
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 6);
  // CHECK: changed(OUTPUT_VALUE) = 1
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 7);
  // CHECK: changed(OUTPUT_VALUE) = 0
  OUTPUT_VALUE = shift_right<uint8_t, uint8_t>(128, 8);
}

