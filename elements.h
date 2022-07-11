#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

class compoundInterest
{
public:
	double principal;
	double interestrate;
	int periods;
	compoundInterest() : principal{}, interestrate{}, periods{} {}
	void calculate_interest();
	double black_scholes_merton();
};
