#pragma once
#include "framework.h"

#include <string>
#include <type_traits>

namespace LA
{

	class DRIVERLA_API LongInt
	{
	private:
		using Digits = std::vector<std::int8_t>;

		std::pair<Digits, Digits> makeEqualLengthDigits(const LongInt& other) const;
		LongInt(Digits&& n, bool isNegative);

		template <class Stream>
		friend Stream& operator<<(Stream& str, const LA::LongInt& n);

		void fromInteger(std::int64_t integer);
		void fromString(const std::string& str);
		void removeZeros();

	private:
		bool m_isNegative;
		Digits m_digits;
	public:
		LongInt();
		~LongInt() = default;
		LongInt(const std::initializer_list<std::int8_t>& list);
		LongInt(const std::string& str);
		LongInt(const char* str);

		template <class T>
		LongInt(T n);

		LongInt(const LongInt& other);
		LongInt(LongInt&&) = default;

		LongInt& operator=(const LongInt& other);
		LongInt& operator=(LongInt&&) = default;

		LongInt operator-(const LongInt& rhs) const;
		LongInt operator+(const LongInt& rhs) const;
		LongInt operator*(const LongInt& rhs) const;
		LongInt operator/(const LongInt& rhs) const;

		LongInt& operator-=(const LongInt& rhs);
		LongInt& operator+=(const LongInt& rhs);
		LongInt& operator*=(const LongInt& rhs);
		LongInt& operator/=(const LongInt& rhs);

		LongInt& operator--();
		LongInt operator--(int);
		LongInt& operator++();
		LongInt operator++(int);

		LongInt operator%(const LongInt& rhs) const;

		bool operator<(const LongInt& rhs) const;
		bool operator>(const LongInt& rhs) const;
		bool operator<=(const LongInt& rhs) const;
		bool operator>=(const LongInt& rhs) const;

		bool operator==(const LongInt& rhs) const;
		bool operator!=(const LongInt& rhs) const;

		LongInt operator-() const;

		bool isNegative()const;
		void setNegative(bool negative);
	};

	template <class Stream>
	Stream& operator<<(Stream& str, const LA::LongInt& n)
	{
		if (n.m_isNegative)
		{
			str << '-';
		}
		auto rhead = n.m_digits.crbegin();
		auto crend = n.m_digits.crend();
		while (rhead != crend && *rhead == 0)
		{
			rhead++;
		}
		if (rhead == crend)
		{
			str << 0;
		}
		else
		{
			while (rhead != crend)
			{
				str << static_cast<std::int32_t>(*(rhead++));
			}
		}
		return str;
	}

	LongInt operator""_lint(unsigned long long n)
	{
		return LongInt(n);
	}

	template<class T>
	inline LongInt::LongInt(T n) 
		: m_isNegative(n < 0)
	{
		fromInteger(static_cast<std::int64_t>(n));
	}
} // namespace LA

namespace std
{
	DRIVERLA_API LA::LongInt abs(const LA::LongInt& n);
	DRIVERLA_API LA::LongInt pow(const LA::LongInt& n, const LA::LongInt& pow);
	DRIVERLA_API LA::LongInt sqrt(const LA::LongInt& n);
}
