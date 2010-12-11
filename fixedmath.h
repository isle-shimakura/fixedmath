#ifndef FIXEDMATH_H
#define FIXEDMATH_H

#include <limits.h>

/**
 *  ‰~ü—¦‚Í•ªŠ„”‚Ì2•ª‚Ì1
 */
#define M_PI ((1U<<15)/2) /* 32768/2 */

union fixed;
typedef union fixed Fixed;

#ifdef __cplusplus
extern "C" {
#endif

Fixed *fixed_set_int(Fixed *, int);
int fixed_get_int(Fixed *);
Fixed *fixed_add_fixed(Fixed *, Fixed *);
Fixed *fixed_add_int(Fixed *, int);
Fixed *fixed_mul_fixed(Fixed *, Fixed *);
Fixed *fixed_mul_int(Fixed *, int);

#ifdef __cplusplus
}
#endif

union fixed {
	long fixedValue;
	struct {
#ifndef BIG_ENDIAN
		unsigned short fractValue;
		short intValue;
#else
		unsigned short fractValue;
		short intValue;
#endif
	};
#ifdef __cplusplus
	fixed &operator +=(const fixed &o) {
		fixedValue += o.fixedValue;
		return *this;
	}
	fixed operator +(const fixed &o) {
		fixed tmp = *this;
		tmp += o;
		return tmp;
	}
	fixed &operator *=(const fixed &o) {
#if defined(LLONG_MAX)
		fixedValue = (long)(((long long)fixedValue * o.fixedValue) >> (sizeof(short) * CHAR_BIT));
#else
		fixed_mul_fixed(this, &o);
#endif
		return *this;
	}
	fixed operator *(const fixed &o) {
		fixed tmp = *this;
		tmp *= o;
		return tmp;
	}
	fixed &operator *=(int i) {
		fixedValue *= i;
		return *this;
	}
	fixed operator *(int i) {
		fixed tmp = *this;
		tmp *= i;
		return tmp;
	}
	fixed &operator =(int i) {
		fixedValue = 0;
		intValue = i;
		return *this;
	}
	operator int() {
		return intValue;
	}
#endif
};

#ifdef __cplusplus
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
