/**
	@file		Math.cpp
	@brief		”ŠwƒNƒ‰ƒX
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#include "stdafx.h"
#include "MathUtil.h"

void MathUtil::Srand(void)
{
	srand((unsigned)time(NULL));
}

double MathUtil::Rand(void)
{
	return rand() / (double)RAND_MAX;
}