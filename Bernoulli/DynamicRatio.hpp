#ifndef DYNAMIC_RATIO_HPP_DEFINED__
#define DYNAMIC_RATIO_HPP_DEFINED__

#include <cstdint>
#include <iostream>
#include <cassert>

namespace DRatio {

std::uint64_t gcd(std::uint64_t a, std::uint64_t b);

struct DRatio
{
  std::int64_t num;
  std::uint64_t den;

  DRatio(std::int64_t n = 0, std::int64_t d = 1):num(n),den(d)
  {simplify();}
  
  DRatio& operator+=(const DRatio& rhs)
  {
    num=num*rhs.den+rhs.num*den;
    den*=rhs.den;
    simplify();
    return *this;
  }
  DRatio& operator+=(const DRatio&& rhs) {return *this+=rhs;}

  DRatio& operator-=(const DRatio& rhs)
  {
    num=num*rhs.den-rhs.num*den;
    den*=rhs.den;
    simplify();
    return *this;
  }
  DRatio& operator-=(const DRatio&& rhs) {return *this-=rhs;}

  DRatio& operator*=(const DRatio& rhs)
  {
    num*=rhs.num;
    den*=rhs.den;
    simplify();
    return *this;
  }
  DRatio& operator*=(const DRatio&&rhs) {return *this*=rhs;}
  
  DRatio& operator/=(const DRatio& rhs)
  {
    num*=rhs.den;
    den*=rhs.num;
    simplify();
    return *this;
  }
  DRatio& operator/=(const DRatio&& rhs) {return *this/=rhs;}

private:
  void simplify()
  {
    std::uint64_t div = num < 0 ? -num : num;
    div=gcd(div,den);
    num/=(std::int64_t)div;
    den/=div;
  }
}; // struct DRatio

static inline
const DRatio operator+(const DRatio&& lhs,const DRatio&& rhs)
{return DRatio(lhs)+=rhs;}

static inline
const DRatio operator-(const DRatio&& lhs,const DRatio&& rhs)
{return DRatio(lhs)-=rhs;}

static inline
const DRatio operator*(const DRatio&& lhs,const DRatio&& rhs)
{return DRatio(lhs)*=rhs;}

static inline
const DRatio operator/(const DRatio&& lhs,const DRatio&& rhs)
{return DRatio(lhs)/=rhs;}

static inline
std::ostream& operator<<(std::ostream& out, const DRatio& rhs)
{return out << rhs.num << '/' << rhs.den;}

} // namespace DRatio

#endif
