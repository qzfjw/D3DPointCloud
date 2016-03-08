#include "stdafx.h"
#include "DXUTmisc.h"

float frand(float fmin,float fmax)
{
	return (fmin + (fmax - fmin)*rand()/(RAND_MAX+1.0));
}