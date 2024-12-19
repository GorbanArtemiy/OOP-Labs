#pragma once

#include <initializer_list>
#include <iostream>

class Three {
public:
  Three();
  Three(const size_t &n, unsigned char t = 0);
  Three(const std::initializer_list<unsigned char> &lst);
  Three(const std::string &str);
  Three(const Three &other);
  Three(Three &&other) noexcept;
  ~Three() noexcept;

  Three &operator=(const Three &other);
  Three &operator=(Three &&other) noexcept;
  Three &operator+=(const Three &other);
  Three &operator-=(const Three &other);
  friend Three operator+(const Three &a, const Three &b);
  friend Three operator-(const Three &a, const Three &b);

  friend bool operator==(const Three &a, const Three &b);
  friend bool operator!=(const Three &a, const Three &b);
  friend bool operator<(const Three &a, const Three &b);
  friend bool operator>(const Three &a, const Three &b);
  friend bool operator<=(const Three &a, const Three &b);
  friend bool operator>=(const Three &a, const Three &b);

  friend std::ostream &operator<<(std::ostream &os, const Three &num);

private:
  bool isInvalidDigit(unsigned char c);
  bool
  isValidThreeInitListOfStr(const std::initializer_list<unsigned char> &lst);
  bool isValidThreeString(const std::string &str);

private:
  size_t _sz;
  unsigned char *_arr;
};