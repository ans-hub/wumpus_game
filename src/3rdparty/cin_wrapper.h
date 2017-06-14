// Package: cin_wrapper (v0.3)
// Description: https://github.com/ans-hub/cin_wrapper
// Author: Anton Novoselov, 2017
// File: implementations of cin_wrapper package

#ifndef CIN_WRAPPER_H
#define CIN_WRAPPER_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

namespace anshub {

const std::string E_TYPE  = "Inputed value is not required type";
const std::string E_RANGE = "Inputed value is out of range";
const std::string E_LIST  = "Inputed value is out of list";

// PRIMARY function: get user input and validate type
// Return: false - if input breaked with sentinel
//         true  - if input is valid type

template <typename T> bool cin_get(T &value, std::string msg)
{
  std::cin.sync_with_stdio(false);
  std::string err = "";

  while (true)
  {
    std::cout << err << msg;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
    std::string input = "";

    std::getline(std::cin, input);
    std::stringstream of_stream(input);

    if (input.empty()) {
      return false;
    }
    if (!(of_stream >> value)) {
      err = E_TYPE + "\n";
    } else {
      return true;
    }
  }
  return true;
}

// SECONDARY function: do all that do primary fx, but provides additional
// checks via lambdas functions - F valid
// Return: false - if input breaked with sentinel
//         true  - if input is valid type and callback validation is true

template <typename T, typename F> bool cin_get(T &value, std::string msg, F valid)
{
  std::string err {""};
  while (true)
  {
    std::cout << err;
    if (!cin_get(value, msg)) {
      return false;
    }
    if (valid(value, err)) {
      return true;
    }
  }
  return true;
}

// Wrapper to lambda ver. of cin_get function with range validation
// Return: false - if input breaked with sentinel
//         true  - if input is valid type and valid conditions

template <typename T> bool cin_get(T &value, std::string msg, T min, T max)
{
  return cin_get(value, msg,
  [min,max](T &value, std::string &err) {
   
  if ((value < min) || (value > max)){
    err = E_RANGE + "\n";
    return false;
  } else {
    return true;
  }

  });
}

// Wrapper lambda ver. of cin_get function with check by "check-list" 
// Return: false - if input breaked with sentinel
//         true  - if input is valid type and valid conditions

template <typename T> bool cin_get(T &value, std::string msg, std::vector<T> list)
{
  return cin_get(value, msg,
  [&list](T &value, std::string &err) {
    
  typename std::vector<T>::iterator it;
  it = find (list.begin(), list.end(), value);
  if (it == list.end()) {
    err = E_LIST + "\n";
    return false;
  } else {
    return true;
  }

  });
}

}  // namespace anshub

#endif  // CIN_WRAPPER_H