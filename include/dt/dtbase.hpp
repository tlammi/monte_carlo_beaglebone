#ifndef _DT_DTBASE_HPP
#define _DT_DTBASE_HPP

#include <cmath>
#include <cstdint>
#include <tuple>

namespace dt {
namespace dtbase {

enum Base10UnitType { TIME, DISTANCE };

template <typename T, int64_t O, Base10UnitType U>
class Base10Unit {
        T _val;

        template <typename, int64_t, Base10UnitType>
        friend class Base10Unit;

        constexpr static T pow10(int64_t order) { return std::pow(10, order); }

        template <typename T2, int64_t O2>
        static std::tuple<T, T2> normalize(const Base10Unit<T, O, U>& u0,
                                           const Base10Unit<T2, O2, U>& u1) {
                auto order0 = O;
                auto order1 = O2;
                auto min_order = std::min(order0, order1);

                return std::make_tuple(
                    u0._val * Base10Unit::pow10(order0 - min_order),
                    u1._val * Base10Unit::pow10(order1 - min_order));
        }

 public:
        Base10Unit(const T val) : _val(val) {}

        template <typename T2, int64_t O2>
        Base10Unit(Base10Unit<T2, O2, U> u) {
                auto order_diff = O2 - O;
                _val = u._val * std::pow(10, order_diff);
        }

        template <typename T2, int64_t O2>
        bool operator==(const Base10Unit<T2, O2, U>& other) const {
                T val;
                T2 val2;
                std::tie(val, val2) = Base10Unit::normalize(*this, other);

                return val == val2;
        }

        bool operator==(const T val) const { return _val == val; }

        template <typename T2, int64_t O2>
        bool operator!=(const Base10Unit<T2, O2, U>& other) const {
                return !(*this == other);
        }

        bool operator!=(const T val) const { return _val != val; }

        template <typename T2, int64_t O2>
        void operator+=(const Base10Unit<T2, O2, U>& other) {
                auto order_diff = O2 - O;
                _val += other._val * Base10Unit::pow10(order_diff);
        }

        void operator+=(T val) { _val += val; }
        T val() const { return _val; }

        template <typename T2, int64_t O2>
        Base10Unit<T, O, U> operator+(
            const Base10Unit<T2, O2, U>& other) const {
                auto res = Base10Unit<T, O, U>(_val);
                res += other;
                return res;
        }
        Base10Unit<T, O, U> operator+(const T val) {
                return Base10Unit<T, O, U>(_val + val);
        }

        template <typename T2, int64_t O2>
        void operator-=(const Base10Unit<T2, O2, U>& other) {
                auto order_diff = O2 - O;
                _val -= other._val * Base10Unit::pow10(order_diff);
        }

        void operator-=(const T val) { _val -= val; }

        template <typename T2, int64_t O2>
        Base10Unit<T, O, U> operator-(
            const Base10Unit<T2, O2, U>& other) const {
                auto res = Base10Unit<T, O, U>(_val);
                res -= other;
                return res;
        }

        Base10Unit<T, O, U> operator-(const T val) {
                return Base10Unit<T, O, U>(_val + val);
        }

        template <typename T2, int64_t O2>
        bool operator>(const Base10Unit<T2, O2, U>& other) const {
                T val;
                T2 val2;
                std::tie(val, val2) = Base10Unit::normalize(*this, other);
                return val > val2;
        }

        bool operator>(T val) const { return _val > val; }

        template <typename T2, int64_t O2>
        bool operator<(const Base10Unit<T2, O2, U>& other) const {
                T val;
                T2 val2;
                std::tie(val, val2) = Base10Unit::normalize(*this, other);
                return val < val2;
        }

        bool operator<(T val) const { return _val < val; }

        template <typename T2, int64_t O2>
        bool operator<=(const Base10Unit<T2, O2, U>& other) const {
                auto res = Base10Unit::normalize(*this, other);
                return res[0] <= res[1];
        }

        bool operator<=(T val) { return _val <= val; }

        template <typename T2, int64_t O2>
        bool operator>=(const Base10Unit<T2, O2, U>& other) const {
                auto res = Base10Unit::normalize(*this, other);
                return res[0] >= res[1];
        }

        bool operator>=(T val) { return _val >= val; }

        T raw() const { _val; }
};

}  // namespace dtbase
}  // namespace dt

#endif