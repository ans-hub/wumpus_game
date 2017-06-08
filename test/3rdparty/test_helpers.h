// test_helpers.h
// Anton Novoselov
// Description: structs and funcs that help to test cpp apps
// Version: 0.23

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>

namespace anshub {

// Struct that represent "mock_data" and "assume_data" pairs

template <typename T, typename N>
struct TestPairs
{
  typedef std::vector<std::pair<T,N>> Pairs;
  Pairs pairs_;

  ~TestPairs() { std::cout << std::setfill(' '); }
  void push_back(T const mock, N const assume) 
  {
    pairs_.push_back(std::make_pair(mock, assume));
  }
  void pop_back() { pairs_.pop_back(); }
  bool empty()    { return pairs_.empty(); }
  T back_mock()   { return pairs_.back().first; }
  N back_assume() { return pairs_.back().second; }
};

// Helper function to print message of test result

template <typename T, typename N>
void ResultMessage(int i, T const &assume, N const &fact)
{
  std::cout << std::setprecision(std::numeric_limits<double>::digits10)
            << std::setfill(' ')
            << std::setw(6)
            << std::right
            << "Case "
            << std::setw(3)
            << std::left
            << std::setfill('.')
            << i;
  std::cout << std::setw(6)
            << std::right
            << std::setfill('.');
  if (assume == fact){
    std::cout << "Ok\n";
  } else {
    std::cout << "Fail\n";
    std::cout << " Assume " << assume << "\n";
    std::cout << " Getted " << fact << "\n";
  }
  std::cout << std::setfill(' ');
}

}

#endif