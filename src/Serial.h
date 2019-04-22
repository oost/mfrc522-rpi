#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <string>

#define F(X) X
#define DEC 1
#define HEX 2

class Serial {
public:
  static void print(const std::string &text) { std::cout << text; }
  static void println(const std::string &text) { std::cout << text << "\n"; }
  static void println() { std::cout << "\n"; }

  static void print(unsigned char val) { std::cout << val; }
  static void print(unsigned char val, int type) {
    if (type == HEX) {
      std::cout << static_cast<int>(val);
    } else if (type == DEC) {
      std::cout << static_cast<int>(val);
    } else {
      std::cout << static_cast<int>(val);
    }
  }

  static void println(unsigned char val) {
    print(val);
    std::cout << "\n";
  }
  static void println(unsigned char val, int type) {
    print(val, type);
    std::cout << "\n";
  }
};

#endif