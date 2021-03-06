#ifndef FIXEDMATH_H
#define FIXEDMATH_H

#ifdef _MSC_VER
#pragma comment(lib, "fixedmath.lib")
#endif

#include <stdint.h>

/**
 *  円周率は分割数の2分の1
 */
#define M_PI ((1U<<15)/2) /* 32768/2 */

#define FIXEDMATH_FRACT_BITS 16 /* 小数部は16ビット */

union fixed;
typedef union fixed Fixed;

#ifdef __cplusplus
extern "C" {
#endif

Fixed *fixed_set_int(Fixed *, int);
int fixed_get_int(const Fixed *);
Fixed *fixed_add_fixed(Fixed *, const Fixed *);
Fixed *fixed_add_int(Fixed *, int);
Fixed *fixed_sub_fixed(Fixed *, const Fixed *);
Fixed *fixed_sub_int(Fixed *, int);
Fixed *fixed_mul_fixed(Fixed *, const Fixed *);
Fixed *fixed_mul_int(Fixed *, int);
Fixed *fixed_div_int(Fixed *, int);

#ifdef __cplusplus
}
#endif

union fixed {
	int32_t fixedValue;
	struct {
		uint16_t fractValue;
		int16_t  intValue;
	};
#ifdef __cplusplus
	fixed &operator +=(const fixed &o) {
		fixedValue += o.fixedValue;
		return *this;
	}
	fixed operator +(const fixed &o) const {
		fixed tmp = *this;
		tmp += o;
		return tmp;
	}
	fixed &operator +=(int i) {
		intValue += i;
		return *this;
	}
	fixed operator +(int i) const {
		fixed tmp = *this;
		tmp += i;
		return tmp;
	}
	fixed &operator -=(const fixed &o) {
		fixedValue -= o.fixedValue;
		return *this;
	}
	fixed operator -(const fixed &o) const {
		fixed tmp = *this;
		tmp -= o;
		return tmp;
	}
	fixed &operator -=(int i) {
		intValue -= i;
		return *this;
	}
	fixed operator -(int i) const {
		fixed tmp = *this;
		tmp -= i;
		return tmp;
	}
	fixed &operator *=(const fixed &o) {
#if defined(INT64_MAX)
		fixedValue = (int32_t)((int64_t)fixedValue * o.fixedValue / (1<<FIXEDMATH_FRACT_BITS));
#else
		fixed_mul_fixed(this, &o);
#endif
		return *this;
	}
	fixed operator *(const fixed &o) const {
		fixed tmp = *this;
		tmp *= o;
		return tmp;
	}
	fixed &operator *=(int i) {
		fixedValue *= i;
		return *this;
	}
	fixed operator *(int i) const {
		fixed tmp = *this;
		tmp *= i;
		return tmp;
	}
	fixed &operator /=(int i) {
		fixedValue /= i;
		return *this;
	}
	fixed operator /(int i) const {
		fixed tmp = *this;
		tmp /= i;
		return tmp;
	}
	fixed &operator =(int i) {
		fixedValue = 0;
		intValue = i;
		return *this;
	}
	operator int() const {
		return intValue;
	}
#endif
};

#ifdef __cplusplus

class CFixed
{
private:
	fixed value;
public:
	CFixed() {
		value = 0;
	}
	CFixed(int i) {
		value = i;
	}
	CFixed(const CFixed &o) {
		value = o.value;
	}
	CFixed(const fixed &o) {
		value = o;
	}
	CFixed &operator +=(const CFixed &o) {
		value += o.value;
		return *this;
	}
	CFixed operator +(const CFixed &o) const {
		CFixed tmp = *this;
		tmp += o;
		return tmp;
	}
	CFixed &operator +=(int i) {
		value += i;
		return *this;
	}
	CFixed operator +(int i) const {
		CFixed tmp = *this;
		tmp += i;
		return tmp;
	}
	CFixed &operator -=(const CFixed &o) {
		value -= o.value;
		return *this;
	}
	CFixed operator -(const CFixed &o) const {
		CFixed tmp = *this;
		tmp -= o;
		return tmp;
	}
	CFixed &operator -=(int i) {
		value -= i;
		return *this;
	}
	CFixed operator -(int i) const {
		CFixed tmp = *this;
		tmp -= i;
		return tmp;
	}
	CFixed &operator *=(const CFixed &o) {
		value *= o.value;
		return *this;
	}
	CFixed operator *(const CFixed &o) const {
		CFixed tmp = *this;
		tmp *= o;
		return tmp;
	}
	CFixed &operator *=(int i) {
		value *= i;
		return *this;
	}
	CFixed operator *(int i) const {
		CFixed tmp = *this;
		tmp *= i;
		return tmp;
	}
	CFixed &operator /=(int i) {
		value /= i;
		return *this;
	}
	CFixed operator /(int i) const {
		CFixed tmp = *this;
		tmp /= i;
		return tmp;
	}
	CFixed &operator =(int i) {
		value = i;
		return *this;
	}
	CFixed &operator =(const CFixed &o) {
		value = o.value;
		return *this;
	}
	CFixed &operator =(const fixed &o) {
		value = o;
		return *this;
	}
	operator int() const {
		return int(value);
	}
	operator fixed() const {
		return value;
	}
};

extern "C" {
#endif

Fixed sin12(int x);
Fixed cos12(int x);
Fixed sin13(int x);
Fixed cos13(int x);
int atan20(int y, int x);
int atan21(int y, int x);

#ifdef __cplusplus
}
#endif
#endif
