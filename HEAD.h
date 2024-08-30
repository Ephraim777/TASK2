#pragma once

#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include <string>
#include <iostream>

class big_integer {
public:
    big_integer();
    big_integer(const std::string& str);
    big_integer(big_integer&& other) noexcept;
    big_integer& operator=(big_integer&& other) noexcept;

    big_integer operator+(const big_integer& other) const;
    big_integer operator*(int value) const;

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num);

private:
    std::vector<int> digits;
};

#endif