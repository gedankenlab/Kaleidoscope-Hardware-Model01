// -*- c++ -*-

#pragma once

// The only real question here is namespaces, and which file this belongs in. KeyAddr
// needs to have a particular name (e.g. kaleidoscope::hardware::KeyAddr, so the danger is
// having an alternate hardware library that comes first in the build search path. I guess
// this file should really just be a note that explains where to find the typedef.

namespace kaleidoscope {
namespace keyaddr {

typedef byte KeyAddr;

constexpr KeyAddr UNKNOWN_KEY_ADDR = TOTAL_KEYS;

// Everything past this point should be unnecessary, but could possibly be helpful for
// plugins that want to affect whole rows or columns. Note that this code defines 8 rows &
// 8 columns, which is probably not what a user wants on a Model01 (the last four rows are
// on the right half of the keyboard.

constexpr KeyAddr ROW_BITS = B00111000;
constexpr KeyAddr COL_BITS = B00000111;

// Conversion functions to help with back-compat and user addressing
constexpr byte row(KeyAddr key_addr) {
  return (key_addr & ROW_BITS) >> 3;
}

constexpr byte col(KeyAddr key_addr) {
  return (key_addr & COL_BITS);
}

constexpr KeyAddr addr(byte row, byte col) {
  // shift row by the number of col bits
  return ((row << 3) | col);
}

} // namespace keyaddr {
} // namespace kaleidoscope {
