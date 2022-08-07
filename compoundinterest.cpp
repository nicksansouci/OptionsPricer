#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "elements.h"


void compoundInterest::calculate_interest() {
		std::cout << "What is the principal investment?" << '\n';
		std::cin >> principal;
		std::cout << "What is the interest rate?" << '\n';
		std::cin >> interestrate;
		if (interestrate > 1)
			interestrate *= 0.01;
		std::cout << "How many periods will the investment be compounding interest (years)?" << '\n';
		std::cin >> periods;

		double compoundedinterest = (principal * pow((1 + interestrate), periods) - principal);
		double compoundedprincipal = (principal * pow((1 + interestrate), periods));

		std::cout << std::fixed << std::setprecision(2);
		std::cout << "Your compounded interest = " << compoundedinterest << '\n';
		std::cout << "Your principal + compound interest = " << compoundedprincipal << '\n';
	}




