#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long A = (a<0)?-a:a;
	long long B = (b<0)?-b:b;
	long long tmp = A * B ;
	FLOAT f = (FLOAT)(tmp >> 16);
	if ((a < 0 && b > 0) || (a > 0 && b < 0))
		return -f;
	return f;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	long long A = Fabs(a);
	long long B = Fabs(b);
	A <<= 16;
	B <<= 16;
	FLOAT f = 0;
	int count = 16;
	while (A!=0) {
		if (A >= B) {
			A -= B;
			f |= (1<<count);
		}
		if (count == 0) 
			break;
		B >> 1;
		count--;
	}
	if ((a < 0 && b > 0) || (a > 0 && b < 0))
		return -f;
	return f;
}

FLOAT f2F(float a) {
	int d = *(int *)&a;
	int s,e,m;
	s = d >> 31;
	e = ((d >> 23) & 0xff) - 127;
	m = (d & 0x7fffff) | 0x800000;
	if (s==0)
		return m >> (7-e);
	return -(m >> (7-e));
}

FLOAT Fabs(FLOAT a) {
	if (a < 0)
		a = -a;
	return a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

