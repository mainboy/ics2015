#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long A = a;
	long long B = b;
	long long f = A * B ;
	return f >> 16;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	long long A = Fabs(a);
	long long B = Fabs(b);
	A *= 65536;
	B *= 65536;
	FLOAT f = 0;
	int count = 16;
	while (A!=0) {
		if (A >= B) {
			A -= B;
			switch (count) {
				case 0:f = f|1;break;
				case 1:f = f|2;break;
				case 2:f = f|4;break;
				case 3:f = f|8;break;
				case 4:f = f|16;break;
				case 5:f = f|32;break;
				case 6:f |= 64;break;
				case 7:f |= 128;break;
				case 8:f |= 256;break;
				case 9:f |= 512;break;
				case 10:f |= 1024;break;
				case 11:f |= 2048;break;
				case 12:f |= 4096;break;
				case 13:f |= 8192;break;
				case 14:f |= 16384;break;
				case 15:f |= 32768;break;
				case 16:f |= 65536;break;
				default: break;
			}
			//f |= (1<<count);
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

