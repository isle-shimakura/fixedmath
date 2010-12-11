#include "fixedmath.h"

Fixed *fixed_set_int(Fixed *this, int i)
{
	this->fixedValue = 0;
	this->intValue = i;
	return this;
}

int fixed_get_int(Fixed *this)
{
	return this->intValue;
}

Fixed *fixed_add_fixed(Fixed *this, Fixed *o)
{
	this->fixedValue += o->fixedValue;
	return this;
}

Fixed *fixed_add_int(Fixed *this, int i)
{
	this->intValue += i;
	return this;
}

Fixed *fixed_mul_fixed(Fixed *this, Fixed *o)
{
#if defined(LLONG_MAX)
	this->fixedValue = (long)((long long)this->fixedValue * o->fixedValue / (USHRT_MAX + 1));
#else
	long fixedValue;
	int minus = 0;
	if (this->fixedValue < 0) {
		minus++;
		this->fixedValue = -this->fixedValue;
	}
	if (o->fixedValue < 0) {
		minus++;
		o->fixedValue = -o->fixedValue;
	}
	fixedValue = (this->fractValue * o->fractValue) >> (sizeof(short) * CHAR_BIT);
	fixedValue += this->intValue * o->fractValue;
	fixedValue += this->fixedValue * o->intValue;
	if (minus & 1) {
		fixedValue = -fixedValue;
	}
	this->fixedValue = fixedValue;
#endif
	return this;
}

Fixed *fixed_mul_int(Fixed *this, int i)
{
	this->fixedValue *= i;
	return this;
}
