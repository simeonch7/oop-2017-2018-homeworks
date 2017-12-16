#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

long greatest_common_divisor(long x, long y);

class Exception {
	string err;
	public:

	Exception(string msg) : err(msg) {}
	string get_err() {
		return err;
	}
};

class Rational {
	long num_;
	long denum_;

	public:
	
	Rational(long num = 1, long denum = 1) 
	: num_(num), denum_(denum) {}
	
	void reduction() {
		long divisor = greatest_common_divisor(num_, denum_);
		num_ = num_ / divisor;
		denum_ = denum_ / divisor; 
	}



	long get_num() const{
		return num_;
	}

	long get_denum() const{
		return denum_;
	}

	Rational& set_num(long num) {
		num_ = num;
		return *this;
	}

	Rational& set_denum(long denum) {
		denum_ = denum;
		return *this;
	}

	Rational& sumator(const Rational& helper) {
		num_ = num_ * helper.denum_ + denum_ * helper.num_;
		denum_ = denum_ * helper.denum_;
		return *this;
	}

	Rational& multiplier(const Rational& helper) {
		num_ = num_ * helper.num_;
		denum_ = denum_ * helper.denum_;
		return *this;
	}

	Rational& subtractor(const Rational& helper) {
		num_ = num_ * helper.denum_ - denum_ * helper.num_;
		denum_ = denum_ * helper.denum_;
		return *this;
	}
	
	Rational& divider(const Rational& helper) {
		num_ = num_ * helper.denum_;
		denum_ = denum_ * helper.num_;
		return *this;
	}
};


Rational operator+(const Rational& num, const Rational& num1) {
	Rational result(num.get_num(), num.get_denum());
	result.sumator(num1);
	return result;
}

Rational operator*(const Rational& num, const Rational& num1) {
	Rational result(num.get_num(), num.get_denum());
	result.multiplier(num1);
	return result;
}

Rational operator-(const Rational& num, const Rational& num1) {
	Rational result(num.get_num(), num.get_denum());
	result.subtractor(num1);
	return result;
}

Rational operator/(const Rational& num, const Rational& num1) {
	Rational result(num.get_num(), num.get_denum());
	result.divider(num1);
	return result;
}

istream& operator>>(istream& inputter, Rational& n) {
	long num;
	long denum;
	char operation;

	inputter >> operation;
	if(operation != '(') {
		inputter.clear(ios_base::badbit);
		return inputter;
	} 

	inputter >> num >> operation;

	if(operation != '/') {
		inputter.clear(ios_base::badbit);
		return inputter;
	}

	inputter >> denum >> operation;

	if(operation != ')') {
		inputter.clear(ios_base::badbit);
		return inputter;
	}

	if(inputter.good()) {
		n.set_num(num);
		n.set_denum(denum);
	}

	return inputter;
}

ostream& operator<<(ostream& outputter, const Rational& n) {
	outputter << "(" << n.get_num() << "/" << n.get_denum() << ")";
	return outputter;
}

int main() {

	string input;
	while(1) {

		char operation;
		cout << "> ";
		getline(cin, input);
	
		if(input == "q")break;

		istringstream inputter(input);
		Rational solution, number;
		inputter >> solution;
		if(inputter.fail()) {
			throw Exception("OOOPS!!! The number should be ratonal!");
		}
		inputter >> operation;
		while(operation != '=') { 
			inputter >> number;
			if(inputter.fail()) {
				throw Exception("OOOPS!!! The number should be ratonal!");	
			}

			switch(operation){
			case '+':
			solution = solution + number;
			break;
                   	 case '*':
                        solution = solution * number;
                        break;
                   	 case '-':
                        solution = solution - number;
                        break;
                   	 case '/':
                        solution = solution / number;
                        break;
			}

			inputter >> operation;	
		}

		if(solution.get_num() != 0 
			&& solution.get_denum() != 0) {
			solution.reduction();
		} 
		else {	
			solution.set_num(0);
			solution.set_denum(1);
		}

		cout << solution << endl;
	}	
	return 0;
}

long greatest_common_divisor(long x, long y) {
	long divisor;
	if(x > y) {
		divisor = y;
	}
	else {
		divisor = x;
	}

	if(divisor < 0) {
		divisor = divisor * -1;
	}

	while (x % divisor != 0 || y % divisor != 0) {
		divisor--;
    	}	
    
    return divisor;
}
