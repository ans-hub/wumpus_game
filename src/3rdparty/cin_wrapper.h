// Novoselov Ans @ 2017

#ifndef CIN_WRAPPER_H
#define CIN_WRAPPER_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

namespace anshub {

const std::string E_TYPE  = "Input value is not required type";
const std::string E_RANGE = "Input value is out of range";
const std::string E_LIST  = "Input value is out of list";

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