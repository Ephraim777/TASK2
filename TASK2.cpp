#include "HEAD.h"
#include <algorithm>


big_integer::big_integer() : digits() {}


big_integer::big_integer(const std::string& str) {
    for (char ch : str) {
        if (isdigit(ch)) {
            digits.push_back(ch - '0');
        }
    }
}


big_integer::big_integer(big_integer&& other) noexcept : digits(std::move(other.digits)) {}

big_integer& big_integer::operator=(big_integer&& other) noexcept {
    if (this != &other) {
        digits = std::move(other.digits);
    }
    return *this;
}


big_integer big_integer::operator+(const big_integer& other) const {
    big_integer result;
    int carry = 0;
    size_t max_size = std::max(digits.size(), other.digits.size());
    result.digits.resize(max_size);

    for (size_t i = 0; i < max_size; ++i) {
        int digit1 = (i < digits.size()) ? digits[digits.size() - 1 - i] : 0;
        int digit2 = (i < other.digits.size()) ? other.digits[other.digits.size() - 1 - i] : 0;
        int sum = digit1 + digit2 + carry;
        result.digits[max_size - 1 - i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0) {
        result.digits.insert(result.digits.begin(), carry);
    }

    return result;
}


big_integer big_integer::operator*(int value) const {
    big_integer result;
    int carry = 0;

    result.digits.resize(digits.size());
    for (size_t i = digits.size(); i-- > 0;) {
        int product = digits[i] * value + carry;
        result.digits[i] = product % 10;
        carry = product / 10;
    }


    while (carry > 0) {
        result.digits.insert(result.digits.begin(), carry % 10);
        carry /= 10;
    }

    return result;
}


std::ostream& operator<<(std::ostream& os, const big_integer& num) {
    for (int digit : num.digits) {
        os << digit;
    }
    return os;
}

int main() {
    big_integer number1("117575");
    big_integer number2("465");
    big_integer result = number1 + number2;
    std::cout << result << std::endl;

    big_integer result2 = number1 * 2;
    std::cout << result2 << std::endl;

    return 0;
}