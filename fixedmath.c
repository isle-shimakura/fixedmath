#include "fixedmath.h"

Fixed *fixed_set_int(Fixed *this, int i)
{
	this->fixedValue = 0;
	this->intValue = i;
	return this;
}

int fixed_get_int(const Fixed *this)
{
	return this->intValue;
}

Fixed *fixed_add_fixed(Fixed *this, const Fixed *o)
{
	this->fixedValue += o->fixedValue;
	return this;
}

Fixed *fixed_add_int(Fixed *this, int i)
{
	this->intValue += i;
	return this;
}

Fixed *fixed_sub_fixed(Fixed *this, const Fixed *o)
{
	this->fixedValue -= o->fixedValue;
	return this;
}

Fixed *fixed_sub_int(Fixed *this, int i)
{
	this->intValue -= i;
	return this;
}

Fixed *fixed_mul_fixed(Fixed *this, const Fixed *o)
{
#if defined(LLONG_MAX)
	this->fixedValue = (long)((long long)this->fixedValue * o->fixedValue / (USHRT_MAX + 1));
#else
	long fixedValue;
	long ah = this->intValue;
	long al = this->fixedValue - ah * (USHRT_MAX + 1);
	long bh = o->intValue;
	long bl = o->fixedValue - bh * (USHRT_MAX + 1);
	fixedValue = al * bl / (USHRT_MAX + 1);
	fixedValue += ah * bl;
	fixedValue += this->fixedValue * bh;
	this->fixedValue = fixedValue;
#endif
	return this;
}

Fixed *fixed_mul_int(Fixed *this, int i)
{
	this->fixedValue *= i;
	return this;
}
