#ifndef _BUG_HPP_
#define _BUG_HPP_

class Bug
{
public:
	Bug();
	Bug(unsigned int legs, unsigned int mass);

	int getLegs()		{ return m_legs; }
	int getMass()		{ return m_mass; }

	void print();
	void eat(unsigned int bites);
	void poop();

private:
	unsigned int m_legs;
	unsigned int m_mass;
};

#endif
