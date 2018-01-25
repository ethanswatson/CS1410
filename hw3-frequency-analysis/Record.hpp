#ifndef _RECORD_HPP_
#define _RECORD_HPP_

class Record
{
public:
	Record(unsigned int value, unsigned int frequency = 1)
	{
		m_number = value;
		m_frequency = frequency;
	}

	unsigned int getNumber() { return m_number; }
	unsigned int getFrequency() { return m_frequency; }

	void setNumber(unsigned int number) { m_number = number; }
	void incrementFrequency() { m_frequency++; }

private:
	unsigned int m_number;
	unsigned int m_frequency;
};

#endif // _RECORD_HPP_
