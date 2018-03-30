// -*- c++ -*-

#pragma once

#include <Arduino.h>


namespace kaleidoscope {

// I need to decide if this constant should be defined here or in Keyboard.h
constexpr byte total_keys = 64;
#define TOTAL_KEYS_STR "64"

// The Model01 has only 64 keys, and we only need one extra value to indicate an invalid
// key address, so that all fits in one byte.
// typedef byte KeyAddr;

// I mistakenly thought that there was a problem with reading from PROGMEM and/or EEPROM
// that would be solved by using a struct instead of a basic typedef, so I implemented all
// this operator overloading. Now that I've done it, I'm going to try it out anyway, even
// though it doesn't solve the problem I thought it would.
struct KeyAddr {

  byte addr;

  KeyAddr() = default;

  // The single-argument constructor is `explicit` to prevent automatic casting of
  // integers to KeyAddr objects, and constexpr to allow the creation of compile-time
  // constant KeyAddr objects.
  explicit constexpr
  KeyAddr(byte addr) : addr{addr} {}

  // This (row,col) constructor was conceived as a transitional helper, but should
  // probably just be removed, since the "row" and "col" values don't match the old ones.
  constexpr
  KeyAddr(byte row, byte col) : addr((row * 8) + col) {}

  // Read a KeyAddr from an address in PROGMEM. This should be useful for sparse layers,
  // which will contain (KeyAddr,Key) pairs.
  void readFromProgmem(const KeyAddr& pgm_key_addr) {
    addr = pgm_read_byte(&pgm_key_addr.addr);
  }

  
  // Comparison operators for use with other KeyAddr objects
  bool operator==(const KeyAddr& other) const {
    return this->addr == other.addr;
  }
  bool operator!=(const KeyAddr& other) const {
    return this->addr != other.addr;
  }
  bool operator>(const KeyAddr& other) const {
    return this->addr > other.addr;
  }
  bool operator<(const KeyAddr& other) const {
    return this->addr < other.addr;
  }
  bool operator>=(const KeyAddr& other) const {
    return this->addr >= other.addr;
  }
  bool operator<=(const KeyAddr& other) const {
    return this->addr <= other.addr;
  }

  // Assignment & arithmetic operators (KeyAddr)
  KeyAddr& operator=(const KeyAddr& other) {
    this->addr = other.addr;
    return *this;
  }
  KeyAddr& operator+=(const KeyAddr& other) {
    this->addr += other.addr;
    return *this;
  }
  KeyAddr& operator-=(const KeyAddr& other) {
    this->addr -= other.addr;
    return *this;
  }

  // Increment & decrement unary operators
  KeyAddr& operator++() { // prefix
    ++addr;
    return *this;
  }
  KeyAddr& operator--() { // prefix
    --addr;
    return *this;
  }
  KeyAddr operator++(int) { // postfix
    KeyAddr tmp(addr++);
    return tmp;
  }
  KeyAddr operator--(int) { // postfix
    KeyAddr tmp(addr--);
    return tmp;
  }

  // Maybe I should provide a cast operator to convert to LedAddr from KeyAddr?

};

inline KeyAddr getProgmemKeyAddr(const KeyAddr& pgm_key_addr) {
  return KeyAddr(pgm_read_byte(&pgm_key_addr.addr));
}

} // namespace kaleidoscope {
