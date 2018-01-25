#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdint>

#include "BigInteger.hpp"

BigInteger::BigInteger()
{
    m_number = new std::uint8_t[4];
    m_sizeReserved = 4;
    m_digitCount = 0;

    for (int i = 0; i < m_sizeReserved; i++)
    {
        m_number[i] = 0;
    }
}

BigInteger::BigInteger(int x)

{
    m_digitCount = 0;
    int tmpX = x;

    if (tmpX == 0)
    {
        m_digitCount = 1;
    }
    while (tmpX > 0)
    {
        tmpX /= 10;
        m_digitCount++;
    }

    m_sizeReserved = m_digitCount;
    m_number = new std::uint8_t[m_sizeReserved];

    for (int i = 0; i < m_digitCount; i++)
    {
        m_number[i] = x % 10;
        x /= 10;
    }
}

BigInteger::BigInteger(const std::string& rString)
{
    m_digitCount = rString.length();
    m_sizeReserved = m_digitCount;
    m_number = new std::uint8_t[m_sizeReserved];

    for (int i = 0; i < m_digitCount; i++)
    {
        std::uint8_t num = rString[m_digitCount - i - 1] - '0';
        m_number[i] = num;
    }
}

BigInteger::BigInteger(const BigInteger& rOther)
{
    m_digitCount = rOther.m_digitCount;
    m_sizeReserved = rOther.m_sizeReserved;
    m_number = new std::uint8_t[m_sizeReserved];

    for (int i = 0; i < m_sizeReserved; i++)
    {
        m_number[i] = rOther.m_number[i];
    }
}

BigInteger::~BigInteger()
{
    delete [] m_number;
}

BigInteger BigInteger::operator=(const BigInteger& rOther)
{
    m_digitCount = rOther.m_digitCount;
    m_sizeReserved = rOther.m_sizeReserved;

    delete [] m_number;
    m_number = new std::uint8_t[m_sizeReserved];

    for (int i = 0; i < m_sizeReserved; i++)
    {
        m_number[i] = rOther.m_number[i];
    }

    return *this;
}

void BigInteger::display()
{
    for (unsigned int digit = m_digitCount; digit > 0; digit--)
    {
        std::cout << static_cast<int>(m_number[digit - 1]);
    }
}

// ------------------------------------------------------------------
//
// Returns the digit as the specified positon.  If the position is greater
// that the number representation, a 0 is returned.
//
// ------------------------------------------------------------------
std::uint8_t BigInteger::getDigit(unsigned int position) const
{
    if (position < m_digitCount)
    {
        return m_number[position];
    }

    return 0;
}

void BigInteger::setDigit(unsigned int position, std::uint8_t digit)
{
    if (m_sizeReserved < position + 1)
    {
        expandArray(position);
    }

    m_number[position] = digit;

    if (m_digitCount < position + 1)
    {
        int additionalDigits = (position + 1) - m_digitCount;
        m_digitCount += additionalDigits;
    }
}

void BigInteger::expandArray(int targetPosition)
{
    unsigned int newSize = m_sizeReserved;
    while (targetPosition > 0 && newSize < targetPosition + 1)
    {
        newSize *= 2;
    }

    std::uint8_t* newNumber = new std::uint8_t[newSize];

    for (int i = 0; i < m_digitCount; i++)
    {
        newNumber[i] = m_number[i];
    }

    for (int i = m_digitCount; i < newSize; i++)
    {
        newNumber[i] = 0;
    }

    delete [] m_number;

    m_sizeReserved = newSize;
    m_number = newNumber;
}

BigInteger BigInteger::operator+(const BigInteger& rOther)
{
    BigInteger result;
    unsigned int length = (this->m_digitCount > rOther.m_digitCount) ? this->m_digitCount : rOther.m_digitCount;

    int carry = 0;
    for (unsigned int digit = 0; digit < length; digit++)
    {
        int v1 = this->getDigit(digit);
        int v2 = rOther.getDigit(digit);
        int sum = v1 + v2 + carry;
        int single = sum % 10;
        carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

        result.setDigit(digit, single);
    }
    if (carry > 0)
    {
        result.setDigit(length, carry);
    }

    return result;
}

BigInteger BigInteger::operator+(const int other)
{
    BigInteger toAdd(other);
    BigInteger result = *this + toAdd;
    return result;
}

BigInteger BigInteger::operator+=(const BigInteger& rOther)
{
    *this = *this + rOther;
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    *this += 1;
}

BigInteger BigInteger::operator*(const BigInteger& rOther)
{
    BigInteger result;
    const BigInteger& b = (this->m_digitCount < rOther.m_digitCount) ? *this : rOther;
    const BigInteger& t = (this->m_digitCount < rOther.m_digitCount) ? rOther : *this;

    for (unsigned int bDigit = 0; bDigit < b.m_digitCount; bDigit++)
    {
        BigInteger temp(0);
        int v1 = b.getDigit(bDigit);
        int carry = 0;
        for (unsigned int tDigit = 0; tDigit < t.m_digitCount; tDigit++)
        {
            int v2 = t.getDigit(tDigit);
            int sum = v1 * v2 + carry;
            int single = sum % 10;
            carry = ((sum - single) > 0) ? (sum - single) / 10 : 0;

            temp.setDigit(bDigit + tDigit, single);
        }
        if (carry > 0)
        {
            temp.setDigit(bDigit + t.m_digitCount, carry);
        }
        result = result + temp;
    }

    return result;
}

BigInteger BigInteger::operator*=(const BigInteger& rOther)
{
    *this = *this * rOther;
    return *this;
}

bool BigInteger::operator<=(const BigInteger& rOther) const
{
    if (this->m_digitCount < rOther.m_digitCount) return true;
    if (this->m_digitCount > rOther.m_digitCount) return false;
    //
    // Have to go digit by digit
    for (int digit = m_digitCount - 1; digit >= 0; digit--)
    {
        if (this->m_number[digit] < rOther.m_number[digit])
        {
            return true;
        }
        if (this->m_number[digit] > rOther.m_number[digit])
        {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator==(const BigInteger& rOther) const
{
    if (m_digitCount != rOther.m_digitCount)
    {
        return false;
    }

    for (unsigned int i = 0; i < m_digitCount; i++)
    {
        if (m_number[i] != rOther.m_number[i])
        {
            return false;
        }
    }

    return true;
}

BigInteger::operator double() const
{
    double result = 0.0;

    for (unsigned int i = 0; i < m_digitCount; i++)
    {
        uint8_t currentDigit = m_number[i];
        result += currentDigit * pow(10, i);
    }

    return result;
}

std::ostream& BigInteger::operator<<(std::ostream& rOut) const
{
    for (unsigned int i = m_digitCount - 1; i >= 0; i--)
    {
        rOut << m_number[i];
    }

    return rOut;
}