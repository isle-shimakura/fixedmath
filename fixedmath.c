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
#if defined(INT64_MAX)
	this->fixedValue = (int32_t)((int64_t)this->fixedValue * o->fixedValue / (1<<FIXEDMATH_FRACT_BITS));
#else
	int32_t fixedValue;
	int32_t ah = this->intValue;
	int32_t al = this->fixedValue - ah * (1<<FIXEDMATH_FRACT_BITS);
	int32_t bh = o->intValue;
	int32_t bl = o->fixedValue - bh * (1<<FIXEDMATH_FRACT_BITS);
	fixedValue = al * bl / (1<<FIXEDMATH_FRACT_BITS);
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

Fixed *fixed_div_int(Fixed *this, int i)
{
	this->fixedValue /= i;
	return this;
}
