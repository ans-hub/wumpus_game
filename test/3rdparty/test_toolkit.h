// Package: test_toolkit (v0.34)
// Description: https://github.com/ans-hub/test_toolkit
// Author: Anton Novoselov, 2017
// File: interface and implementation of test_toolkit

#ifndef TEST_TOOLKIT_H
#define TEST_TOOLKIT_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>

namespace test_toolkit {

// Represents "mock" data and "assume" data joined in pairs

template <typename T, typename N>
class TestPairs
{
public:
  typedef std::vector<std::pair<T,N>> Pairs;
  ~TestPairs() { std::cerr << std::setfill(' '); }
  
  void push_back(T const mock, N const assume);
  void pop_back() { pairs_.pop_back(); }
  bool empty() const { return pairs_.empty(); }
  T back_mock() const { return pairs_.back().first; }
  N back_assume() const { return pairs_.back().second; }

private:
  Pairs pairs_;
};

template <typename T, typename N>
void TestPairs<T,N>::push_back(T const mock, N const assume) 
{
  pairs_.push_back(std::make_pair(mock, assume));
}

// Compares two variables and prints results in depending of eq or not eq
//    of `assume` and `actual` values. Returns not bool but integer value
//    since its needs to be consistent with returned type of main() for
//    possible auto testing purposes

template <typename T, typename N>
int result_message(int i, T const &assume, N const &actual)
{
  std::cerr << std::setprecision(std::numeric_limits<double>::digits10)
            << std::setfill(' ')
            << std::setw(7)
            << std::right
            << "Case "
            << std::setw(3)
            << std::left
            << std::setfill('.')
            << i;
  std::cerr << std::setw(6)
            << std::right
            << std::setfill('.');
  if (assume == actual){
    std::cerr << "Ok\n";
    std::cerr << std::setfill(' ');
    return 0;
  }
  else {
    std::cerr << "Fail\n";
    std::cerr << "  assume " << assume << "\n";
    std::cerr << "  actual " << actual << "\n";
    std::cerr << std::setfill(' ');
    return 1;
  }
}

// Short alias for "bool result_message(...)"

template <typename T, typename N>
int message(int i, T const &assume, N const &actual)
{
  return result_message(i, assume, actual);
}

} // namespace anshub

#endif  // TEST_TOOLKIT_H