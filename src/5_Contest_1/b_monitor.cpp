#include <cstdio>
#include <cmath>

int highestCommonDeliter(int numerator, int denominator)
{
	return (denominator == 0) ? numerator : highestCommonDeliter(denominator, numerator % denominator);
}

class Fraction
{
public:
	Fraction(int numerator, int denominator) :
		m_numerator(numerator),
		m_denominator(denominator),
		m_reducedNumerator(numerator),
		m_reducedDenominator(denominator)
	{
	}

	bool isEmpty() const
	{
		return m_numerator == 0 || m_denominator == 0;
	}

	int getNumerator() const
	{
		return m_numerator;
	}

	int getDenominator() const
	{
		return m_denominator;
	}

	void setNumerator(int value)
	{
		m_numerator = value;
	}

	void setDenominator(int value)
	{
		m_denominator = value;
	}

	void reduce()
	{
		auto deliter = highestCommonDeliter(m_numerator, m_denominator);
		m_reducedNumerator = m_numerator / deliter;
		m_reducedDenominator = m_denominator / deliter;
	}

	float getValue()
	{
		return m_denominator != 0 ? (float)m_numerator / m_denominator : 0.0f;
	}

	bool operator=(const Fraction& other)
	{
		static float epsilan = 0.000001;
		return std::abs((float)m_numerator / m_denominator - (float)other.m_numerator / other.m_denominator) < epsilan;
		//return m_reducedNumerator == other.m_reducedNumerator && m_reducedDenominator == other.m_reducedDenominator;
	}

	bool operator!=(const Fraction& other)
	{
		return !operator=(other);
	}

private:
	int m_numerator;
	int m_denominator;

	int m_reducedNumerator;
	int m_reducedDenominator;
};

void doTask5B()
{
	int a;
	int b;
	int x;
	int y;
	scanf("%d %d %d %d", &a, &b, &x, &y);

	Fraction monitor(a, b);
	//monitor.reduce();

	Fraction ratio(x, y);
	//ratio.reduce();

	while (monitor != ratio && !monitor.isEmpty()) {
		if (monitor.getValue() > ratio.getValue()) {
			monitor.setNumerator(ratio.getValue() * monitor.getDenominator());
			//monitor.reduce();
		} else {
			monitor.setDenominator(monitor.getNumerator() / ratio.getValue());
			//monitor.reduce();
		}
	}

	if (monitor.isEmpty()) {
		printf("0 0\n");
	} else {
		printf("%d %d\n", monitor.getNumerator(), monitor.getDenominator());
	}

	//auto stop = 0;
	//scanf("%d", &stop);
}

//int main()
//{
//	doTask5B();
//	return 0;
//}
