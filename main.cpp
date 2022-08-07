#define _USE_MATH_DEFINES


#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <thread>


   //There are two probability factors in the Black Scholes Model
//D1 and D2
//D1 = (ln(S/K) + (r + stddev^2/2)t)/ stddev(volatility) * sqrt(t))
//D2 = D1 - stddev(volatility) * sqrt(t)\

    double d_12(const int& j, const double& s, const double& k, const double& r, const double& v, const double& t) {
        return (log(s / k) + (r + (pow(-1, j - 1)) * 0.5 * v * v) * t) / (v * (pow(t, 0.5)));
    }

    //Normal probability function
    double normal_pdf(const double& x) {
        return (1.00 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x);
    }

    double option_delta(const double& present, const double& initialval, const double& nU, const double& iU) {
        return (present - initialval) / (nU - iU);
    }

    double normal_cdf(const double& x) {
        double k = 1.0 / (1.00 + 0.2316419 * x);
        double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

        if (x >= 0.0) {
            return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
        }


        else {
            return 1.0 - normal_cdf(-x);
        }
    }


    //Use reference for each variable to make sure they aren't changed by the functions
    double put_price(const double& s, const double& k, const double& r, const double& v, const double& t) {
        return -s * normal_cdf(-d_12(1, s, k, r, v, t)) + k * exp(-r * t) * normal_cdf(-d_12(2, s, k, r, v, t));
    }

    double call_price(const double& s, const double& k, const double& r, const double& v, const double& t) {
        return s * normal_cdf(d_12(1, s, k, r, v, t)) - k * exp(-r * t) * normal_cdf(d_12(2, s, k, r, v, t));
    }

    




int main() {


    
    
    //underlying asset price
    double s = 56.89;
    //strike price 
    double k = 58.00;
    //interest rate/risk free rate
    double r = 0.05;
    //volatility/std devation
    double v = 0.2;
    //time to expiration in years
    double t = 0.5;




    double callP = call_price(s, k, r, v, t);
    double putP = put_price(s, k, r, v, t);

    double present = callP; //New price of option contract
    double initialval = 5.0; //Initial price of option contract
    double nU = s; //New value of the stock
    double iU = 50.0; // Initial value of the stock
    double delta = option_delta(present, initialval, nU, iU);
    //Will be adding other option greeks soon

    //Output all variables, call price, put price, and delta.
    std::cout << "Underlying Asset Price: " << s << std::endl;
    std::cout << "Strike Price: " << k << std::endl;
    std::cout << "Risk Free Rate: " << r << "(" << r * 100 << "%)" << std::endl;
    std::cout << "Volatility: " << v  << "("  << v*100 << "%)" << std::endl;
    std::cout << "Years Until Expiration: " << t << std::endl;
    std::cout << "Theoretical Call Price: " << callP << std::endl;
    std::cout << "Theoretical Put Price: " << putP << std::endl;
    std::cout << "Delta: " << delta << std::endl;

    if (k >= s && putP < callP) {
        std::cout << "\n";
        std::cout << "The put contracts are undervalued, if you have a bearish conviction." << std::endl;
    }


    return 0;
}



