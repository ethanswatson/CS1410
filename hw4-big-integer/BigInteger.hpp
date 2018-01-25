#ifndef _BIGINTEGER_HPP_
#define _BIGINTEGER_HPP_

#include <cstdint>
#include <iostream>
#include <string>

class TestCases;

class BigInteger
{
public:
	BigInteger();
    BigInteger(int x);
    BigInteger(const std::string& rString);
    BigInteger(const BigInteger& rOther);
    ~BigInteger();
    BigInteger operator=(const BigInteger& rOther);
    BigInteger operator+(const BigInteger& rOther);
    BigInteger operator+(const int other);
    BigInteger operator+=(const BigInteger& rOther);
    BigInteger operator++(int);
    BigInteger operator*(const BigInteger& rOther);
    BigInteger operator*=(const BigInteger& rOther);
    bool operator<=(const BigInteger& rOther) const;
    bool operator==(const BigInteger& rOther) const;
    operator double() const;
    std::ostream& operator<<(std::ostream& rOut) const;
	void display();

	friend TestCases; // TODO Have students do this first thing

private:
	std::uint8_t* m_number;		// Internal representation of the number.
	unsigned int m_sizeReserved;	// Total size of the allocated space used to internally store the number
	unsigned int m_digitCount;	// How many digits are in the number.

	std::uint8_t getDigit(unsigned int position) const;
	void setDigit(unsigned int position, std::uint8_t digit);
    void expandArray(int targetPosition);
};

#endif
