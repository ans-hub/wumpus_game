#ifndef RAND_TOOLKIT_H
#define RAND_TOOLKIT_H

#include <random>

namespace rand_toolkit {

// Returns reference to random_engine

inline std::default_random_engine & global_urng( )
{
  static std::default_random_engine u{};
  return u;
}

// Starts random_engine with random_device

inline void start_rand()
{
  static std::random_device rd{};
  global_urng().seed( rd() );
}

// Returns random int from the range

inline int get_rand(int from, int to)
{
  static std::uniform_int_distribution<> d{};
  using parm_t = decltype(d)::param_type;
  return d (global_urng(), parm_t{from, to});
}

// Returns random double form the range

inline double get_rand(double from, double to)
{
  static std::uniform_real_distribution<> d{};
  using parm_t = decltype(d)::param_type;
  return d (global_urng(), parm_t{from, to});
}

// Emulates coin toss (returns 0 or 1)

inline int coin_toss()
{
  return get_rand(0,1);
}

// Returns the count of first continuous sequences from the range
//    where `limits` is necessary for preventing endless loop if
//    errors will occur while gets random value

inline int get_sequence_count(int from, int to, int limits)
{
  int i{0};
  int val = get_rand(from, to);
  while (true) {
    int next = get_rand(from, to);
    if (++i >= limits) return i;
    if (next != val) return i;
    val = next;
  }
}

// Returns the count of first continuous sequences of tossed coin

inline int get_coin_sequence_count(int limits)
{
  return get_sequence_count(0, 1, limits);
}

} // namespace rand_toolkit

#endif  // RAND_TOOLKIT_H