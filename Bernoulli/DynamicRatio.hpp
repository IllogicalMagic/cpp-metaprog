#ifndef DYNAMIC_RATIO_HPP_DEFINED__
#define DYNAMIC_RATIO_HPP_DEFINED__

#include <cstdint>
#include <iostream>

struct DRatio
{
  std::int64_t num;
  std::uint64_t den;

  DRatio(std::int64_t n = 0, std::int64_t d = 1):num(n),den(d) {}
  
  DRatio& operator+=(const DRatio& rhs)
  {
    num=num*rhs.den+rhs.num*den;
    den*=rhs.den;
    return *this;
  }
  DRatio& operator+=(const DRatio&& rhs) {return *this+=rhs;}

  DRatio& operator-=(const DRatio& rhs)
  {
    num=num*rhs.den-rhs.num*den;
    den*=rhs.den;
    return *this;
  }
  DRatio& operator-=(const DRatio&& rhs) {return *this-=rhs;}

  DRatio& operator*=(const DRatio& rhs)
  {
    num*=rhs.num;
    den*=rhs.den;
    return *this;
  }
  DRatio& operator*=(const DRatio&&rhs) {return *this*=rhs;}
  
  DRatio& operator/=(const DRatio& rhs)
  {
    num*=rhs.den;
    den*=rhs.num;
    return *this;
  }
  DRatio& operator/=(const DRatio&& rhs) {return *this/=rhs;}

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

#endif
