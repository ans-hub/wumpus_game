
#ifndef MVC_SET_BUTTONS_COORDS
#define MVC_SET_BUTTONS_COORDS

#include <istream>
#include <ios>

namespace mvc_set {

struct RoomButtonCoords
{
  int num_;
  int x_;
  int y_;
  int w_;
  int h_;
};

inline std::istream& operator>>(std::istream& is, RoomButtonCoords& c)
{
  char ch1, ch2, ch3, ch4;
  int num, x, y, w, h;
  is >> num >> ch1 >> x >> ch2 >> y >> ch3 >> w >> ch4 >> h;
  if (!is) return is;
  if (ch1 != ',' || ch2 != ',' || ch3 != ',' || ch4 != ',') {
    is.clear(std::ios_base::failbit);
    return is;
  }
  c.x_ = x;
  c.y_ = y;
  c.w_ = w;
  c.h_ = h;
  c.num_ = num;
  return is;
}

}  // namespace mvc_set

#endif  // MVC_SET_BUTTONS_COORDS