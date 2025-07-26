#ifndef DISTANCE_H
#define DISTANCE_H

#include <cassert>
#include <cmath>
#include <ostream>
#include <ratio>

namespace measurement {
class distance;

template <typename mult_, typename period_> class impl_;

template <class impl__> impl__ distance_cast(const distance &dist) {
  static_assert(std::is_base_of<distance, impl__>::value,
                "Must be a distance type");
  impl__ imp = dist;

  return imp;
}

} // namespace measurement

class measurement::distance {
protected:
  typedef double rep_;

public:
  rep_ count_;

public:
  distance() { count_ = 0; }

  distance(const distance &dist) { count_ = dist.count_; }

  distance &operator=(const distance &dist) {
    count_ = dist.count_;
    return *this;
  }

protected:
  distance(const decltype(count_) ct_) { count_ = ct_; }
};

template <typename mult_, typename period_>
class measurement::impl_ : public distance {
  static const mult_ multiplier;
  static const period_ period;

  constexpr static double mult_val_ =
      static_cast<double>(multiplier.num) / static_cast<double>(multiplier.den);
  constexpr static double period_val_ =
      static_cast<double>(period.num) / static_cast<double>(period.den);
  constexpr static double constant_mult_ = mult_val_ * period_val_;

public:
  impl_() : distance() {}
  impl_(rep_ count) : distance(to_rep(count)) {}
  impl_(const impl_ &imp) : distance(imp) {}
  impl_(const distance &dist) : distance(dist) {}

  rep_ count() const noexcept { return count_ / constant_mult_; }

  // operators
  impl_ &operator=(const distance &imp) noexcept {
    count_ = imp.count_;
    return *this;
  }

  impl_ &operator=(const rep_ ct_) noexcept { // adding a raw count will add in
                                              // same units as this
    count_ = impl_(ct_).count_;
    return *this;
  }

  // Addition operators
  impl_ operator+(const distance &dist) const noexcept {
    impl_ imp;

    imp.count_ = count_ + dist.count_;

    return imp;
  }

  impl_ operator+(const rep_ ct_)
      const noexcept { // adding a raw count will add in same units as this
    impl_ imp;
    imp.count_ = count_ + impl_(ct_).count_;

    return imp;
  }

  impl_ &operator++(int) noexcept {
    count_ += impl_(1).count_;
    return *this;
  }

  impl_ &operator+=(const distance &dist) noexcept {
    count_ += dist.count_;

    return *this;
  }

  impl_ &operator+=(const rep_ ct_) noexcept {
    count_ += impl_(ct_).count_;

    return *this;
  }

  impl_ &operator--(int) noexcept {
    count_ -= impl_(1).count_;
    return *this;
  }

  impl_ operator-(const distance &dist) const noexcept {
    impl_ imp;

    imp.count_ = count_ - dist.count_;

    return imp;
  }

  impl_ operator-(const rep_ ct_)
      const noexcept { // adding a raw count will add in same units as this
    impl_ imp;
    imp.count_ = count_ - impl_(ct_).count_;

    return imp;
  }

  impl_ &operator-=(const distance &dist) noexcept {
    count_ -= dist.count_;
    return *this;
  }

  impl_ &operator-=(const rep_ ct_) noexcept {
    count_ -= impl_(ct_).count_;
    return *this;
  }

  impl_ &operator--() {
    count_ -= impl_(1).count_;
    return *this;
  }

  impl_ operator*(const rep_ multiplier) const noexcept {
    impl_ imp;

    imp.count_ = count_ * multiplier;
    return imp;
  }

  impl_ operator/(const rep_ divisor) const noexcept {
    impl_ imp;

    imp.count_ = count_ / divisor;
    return imp;
  }

  bool operator==(const distance &dist) const noexcept {
    return (std::abs(count_ - dist.count_) <
            std::numeric_limits<double>::epsilon());
  }

  bool operator!=(const distance &dist) const noexcept {
    return (std::abs(count_ - dist.count_) >
            std::numeric_limits<double>::epsilon());
  }

  bool operator<(const distance &dist) const noexcept {
    return count_ < dist.count_;
  }

  bool operator>(const distance &dist) const noexcept {
    return count_ > dist.count_;
  }

  bool operator<=(const distance &dist) const noexcept {
    return count_ - dist.count_ < std::numeric_limits<double>::epsilon();
  }

  bool operator>=(const distance &dist) const noexcept {
    return count_ - dist.count_ > -std::numeric_limits<double>::epsilon();
  }

private:
  static rep_ to_rep(const rep_ ct) {
    //        assert(!(ct != 0 && constant_mult_ >
    //        std::numeric_limits<rep_>::max() / ct)); // `a * x` would overflow
    //        assert(!(ct != 0 && constant_mult_ <
    //        std::numeric_limits<rep_>::min() / ct)); // `a * x` would
    //        underflow

    return ct * constant_mult_;
  }
};

// Note how this is declared outside of the class body, so it is a free function
// instead of a memberfunction
template <typename mult_, typename period_>
inline std::ostream &operator<<(std::ostream &out,
                                const measurement::impl_<mult_, period_> &val) {
  out << val.count();
  return out;
}

namespace measurement {
namespace si {
using si_mult_ = std::ratio<1>;

using meters = impl_<si_mult_, std::ratio<1>>;
using attometers = impl_<si_mult_, std::atto>;
using femtometers = impl_<si_mult_, std::femto>;
using picometers = impl_<si_mult_, std::pico>;
using nanometers = impl_<si_mult_, std::nano>;
using micrometers = impl_<si_mult_, std::micro>;
using millimeters = impl_<si_mult_, std::milli>;
using centimeters = impl_<si_mult_, std::centi>;
using decimeters = impl_<si_mult_, std::deci>;
using decameters = impl_<si_mult_, std::deca>;
using hectometers = impl_<si_mult_, std::hecto>;
using kilometers = impl_<si_mult_, std::kilo>;
using megameters = impl_<si_mult_, std::mega>;
using gigameters = impl_<si_mult_, std::giga>;
using terameters = impl_<si_mult_, std::tera>;
using petameters = impl_<si_mult_, std::peta>;
using exameters = impl_<si_mult_, std::exa>;
} // namespace si

namespace imperial {
using feet = impl_<std::ratio<3048, 10000>, std::ratio<1>>;
using miles = impl_<std::ratio<160934, 100>, std::ratio<1>>;
using yards = impl_<std::ratio<9144, 10000>, std::ratio<1>>;
using inches = impl_<std::ratio<254, 10000>, std::ratio<1>>;
using nauticalmiles = impl_<std::ratio<1852>, std::ratio<1>>;
} // namespace imperial
} // namespace measurement

#endif // DISTANCE_H
