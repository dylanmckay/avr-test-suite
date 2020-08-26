// RUN: @cxx @cxxflags -mmcu=atmega328p @file -o @tempfile -O0 && avr-sim @tempfile -w OUTPUT_VALUE=u16

#include <avrlit/boilerplate/unit_test.h>

uint16_t OUTPUT_VALUE = 0xff;

template<typename A, typename B>
__attribute__ ((noinline)) uint16_t shift_left(volatile A a, volatile B b) {
  return a << b;
}

template<typename A, typename B>
__attribute__ ((noinline)) uint16_t shift_right(volatile A a, volatile B b) {
  return a >> b;
}

// This final check ensures that the assignment correctly updates the global variable.
void unit_test(void) {
  // u16-vs-u16

  // Shift left:
  // CHECK: changed(OUTPUT_VALUE) = 8192
  OUTPUT_VALUE = shift_left<uint16_t, uint16_t>(2, 12);
  // CHECK: changed(OUTPUT_VALUE) = 2040
  OUTPUT_VALUE = shift_left<uint16_t, uint16_t>(255, 3);
  // CHECK: changed(OUTPUT_VALUE) = 4
  OUTPUT_VALUE = shift_left<uint16_t, uint16_t>(1, 2);
  // CHECK: changed(OUTPUT_VALUE) = 65280
  OUTPUT_VALUE = shift_left<uint16_t, uint16_t>(0xffff, 8);

  // Shift right:
  // CHECK: changed(OUTPUT_VALUE) = 16383
  OUTPUT_VALUE = shift_right<uint16_t, uint16_t>(65535, 2);
  // CHECK: changed(OUTPUT_VALUE) = 1
  OUTPUT_VALUE = shift_right<uint16_t, uint16_t>(65535, 15); // shift everything out but one
  // CHECK: changed(OUTPUT_VALUE) = 511
  OUTPUT_VALUE = shift_right<uint16_t, uint16_t>(65535, 7);
  // CHECK: changed(OUTPUT_VALUE) = 132
  OUTPUT_VALUE = shift_right<uint16_t, uint16_t>(4235, 5);
}

