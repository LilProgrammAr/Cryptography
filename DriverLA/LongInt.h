#pragma once
#include "framework.h"

#include <vector>
#include <cstdint>
#include <string>

struct DRIVERLA_API std::_Container_base12;
EXTSPEC_TEMPLATE template struct DRIVERLA_API std::_Simple_types<std::int8_t>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::_Vector_val<std::_Simple_types<std::int8_t>>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::_Compressed_pair<std::allocator<std::int8_t>, std::_Vector_val<std::_Simple_types<std::int8_t>>, true>;
EXTSPEC_TEMPLATE template class DRIVERLA_API std::vector<std::int8_t>;
EXTSPEC_TEMPLATE template struct DRIVERLA_API std::pair<std::vector<std::int8_t>&&, std::vector<std::int8_t>&&>;

namespace LA
{

	class DRIVERLA_API LongInt
	{
	private:
		using Digits = std::vector<std::int8_t>;

		std::pair<Digits, Digits> makeEqualLengthDigits(const LongInt& other) const;
		LongInt(Digits&& n, bool isNegative);

		template <typename Stream>
		friend Stream& operator<<(Stream& str, const LA::LongInt& n);
		void fromString(const std::string& str);

	private:
		bool m_isNegative;
		Digits m_digits;
	public:
		LongInt();
		~LongInt() = default;
		LongInt(const std::initializer_list<std::int8_t>& list);
		LongInt(const std::string& str);
		LongInt(const char* str);
		LongInt(std::int64_t n);
		LongInt(std::int32_t n);
		LongInt(const LongInt& other);
		LongInt(LongInt&&) = default;

		LongInt& operator=(const LongInt& other);
		LongInt& operator=(LongInt&&) = default;

		LongInt operator-(const LongInt& rhs) const;
		LongInt operator+(const LongInt& rhs) const;
		LongInt operator*(const LongInt& rhs) const;
		LongInt operator/(const LongInt& rhs) const;

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

	LongInt sqrt_whole(const LongInt& n);


	template <typename Stream>
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
} // namespace LA

namespace std
{
	LA::LongInt abs(const LA::LongInt& n);
}
