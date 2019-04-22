#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <string>

#define F(X) X
#define DEC 1
#define HEX 2

class SerialMock {
public:
  inline void print(const std::string &text) { std::cout << text; }
  inline void println(const std::string &text) { std::cout << text << "\n"; }
  inline void println() { std::cout << "\n"; }

  inline void print(unsigned char val) { std::cout << val; }
  inline void print(unsigned char val, int type) {
    if (type == HEX) {
      std::cout << static_cast<int>(val);
    } else if (type == DEC) {
      std::cout << static_cast<int>(val);
    } else {
      std::cout << static_cast<int>(val);
    }
  }

  inline void println(unsigned char val) {
    print(val);
    std::cout << "\n";
  }
  inline void println(unsigned char val, int type) {
    print(val, type);
    std::cout << "\n";
  }
};

SerialMock Serial;

#endif