#include "pch.h"
#include "LongInt.h"
#include <tuple>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iterator>
#include <exception>

bool LA::LongInt::operator<(const LongInt& rhs) const
{
	Digits a, b;
	std::tie(a, b) = makeEqualLengthDigits(rhs);
	for (std::int64_t i = a.size() - 1; i >= 0; --i)
	{
		if (b[i] > a[i])
		{
			return true;
		}
		else if (a[i] > b[i])
		{
			return false;
		}
	}
	return false;
}

bool LA::LongInt::operator>(const LongInt& rhs) const
{
	Digits a, b;
	std::tie(a, b) = makeEqualLengthDigits(rhs);
	for (std::int64_t i = a.size() - 1; i >= 0; --i)
	{
		if (b[i] < a[i])
		{
			return true;
		}
		else if (a[i] < b[i])
		{
			return false;
		}
	}
	return false;
}

bool LA::LongInt::operator<=(const LongInt& rhs) const
{
	return !operator>(rhs);
}

bool LA::LongInt::operator>=(const LongInt& rhs) const
{
	return !operator<(rhs);
}

bool LA::LongInt::operator==(const LongInt& rhs) const
{
	Digits a, b;
	std::tie(a, b) = makeEqualLengthDigits(rhs);

	for (size_t i = 0u; i < a.size(); ++i)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

bool LA::LongInt::operator!=(const LongInt& rhs) const
{
	return !operator==(rhs);
}

LA::LongInt LA::LongInt::operator-() const
{
	LongInt res(*this);
	res.m_isNegative = !res.m_isNegative;
	return res;
}

bool LA::LongInt::isNegative() const
{
	return m_isNegative;
}

void LA::LongInt::setNegative(bool negative)
{
	m_isNegative = negative;
}

std::pair<LA::LongInt::Digits, LA::LongInt::Digits>  LA::LongInt::makeEqualLengthDigits(const LongInt& other) const
{
	Digits lhs = m_digits;
	Digits rhs = other.m_digits;

	auto size = std::max(lhs.size(), rhs.size());

	for (auto i = lhs.size(); i <= size; ++i)
	{
		lhs.push_back(std::int8_t(0));
	}
	for (auto i = rhs.size(); i <= size; ++i)
	{
		rhs.push_back(std::int8_t(0));
	}

	return std::make_pair<Digits, Digits>(std::move(lhs), std::move(rhs));
}

LA::LongInt::LongInt(Digits&& n, bool isNegative)
	: m_digits(std::move(n))
	, m_isNegative(isNegative)
{
}

void LA::LongInt::fromInteger(std::int64_t integer)
{
	integer = std::abs(integer);
	while (integer > 0)
	{
		m_digits.insert(m_digits.begin(), integer % 10);
		integer /= 10;
	}
	std::reverse(m_digits.begin(), m_digits.end());
	m_digits.push_back(0);
}

void LA::LongInt::fromString(const std::string& str)
{
	m_digits.reserve(str.size() + 1);
	auto rhead = str.crbegin();
	for (; rhead != --str.crend(); ++rhead)
	{
		if (*rhead < '0' || *rhead > '9')
		{
			throw std::logic_error("Expected digit!");
		}
		m_digits.push_back(*rhead - '0');
	}
	if (*rhead == '-')
	{
		m_isNegative = true;
	}
	else
	{
		m_isNegative = false;
		if (*rhead >= '0' && *rhead <= '9')
		{
			m_digits.push_back(*rhead - '0');
		}
	}

}

void LA::LongInt::removeZeros()
{
	if (!m_digits.empty())
	{
		size_t i = m_digits.size() - 1;
		for (; i != 0 && m_digits[i] == 0; --i)
		{
			m_digits.erase(std::next(m_digits.begin(), i));
		}
		if (m_digits[i] == 0)
		{
			m_digits.erase(std::next(m_digits.begin(), i));
		}
		m_digits.push_back(0);
	}
}

LA::LongInt::LongInt()
	: m_digits(1, 0)
	, m_isNegative(false)
{
}

LA::LongInt::LongInt(const std::initializer_list<std::int8_t>& list)
	: m_isNegative(false)
{
	m_digits.reserve(list.size());
	std::copy(list.begin(), list.end(), std::back_inserter(m_digits));
	std::reverse(m_digits.begin(), m_digits.end());
}

LA::LongInt::LongInt(const std::string& str)
{
	fromString(str);
}

LA::LongInt::LongInt(const char* str)
{
	fromString(str);
}

//LA::LongInt::LongInt(std::int64_t n)
//	: m_isNegative(n < 0)
//{
//	n = n < 0 ? -n : n;
//	while (n > 0)
//	{
//		m_digits.insert(m_digits.begin(), n % 10);
//		n /= 10;
//	}
//	std::reverse(m_digits.begin(), m_digits.end());
//	m_digits.push_back(0);
//}
//
//LA::LongInt::LongInt(std::int32_t n)
//	: m_isNegative(n < 0)
//{
//	n = n < 0 ? -n : n;
//	while (n > 0)
//	{
//		m_digits.insert(m_digits.begin(), n % 10);
//		n /= 10;
//	}
//	std::reverse(m_digits.begin(), m_digits.end());
//	m_digits.push_back(0);
//}

LA::LongInt::LongInt(const LongInt& other)
	: m_isNegative(other.m_isNegative)
	, m_digits(other.m_digits)
{
}

LA::LongInt& LA::LongInt::operator=(const LA::LongInt& other)
{
	m_digits = other.m_digits;
	m_isNegative = other.m_isNegative;
	return *this;
}

LA::LongInt LA::LongInt::operator-(const LongInt& rhs) const
{
	if (m_isNegative && !rhs.m_isNegative)
	{
		return operator-().operator+(rhs).operator-();
	}
	if (!m_isNegative && rhs.m_isNegative)
	{
		return operator+(rhs.operator-());
	}
	if (m_isNegative && rhs.m_isNegative)
	{
		return operator-().operator+(rhs.operator-()).operator-();
	}
	if (operator<(rhs))
	{
		return rhs.operator-(*this).operator-();
	}

	Digits a, b;
	std::tie(a, b) = makeEqualLengthDigits(rhs);

	for (auto i = 0llu; i < a.size() - 1; ++i)
	{
		if (a[i] < b[i])
		{
			a[i] += 10;
			--a[i + 1];
		}
		a[i] -= b[i];
	}
	LongInt res(std::move(a), false);
	res.removeZeros();
	return res;
}

LA::LongInt LA::LongInt::operator+(const LA::LongInt& rhs) const
{
	if (m_isNegative && !rhs.m_isNegative)
	{
		return rhs.operator-(*this);
	}
	if (!m_isNegative && rhs.m_isNegative)
	{
		return operator-(rhs);
	}
	if (m_isNegative && rhs.m_isNegative)
	{
		return -operator+(rhs);
	}

	Digits a, b;
	std::tie(a, b) = makeEqualLengthDigits(rhs);

	for (auto i = 0llu; i < a.size() - 1; ++i)
	{
		a[i] += b[i];
		a[i + 1] += a[i] / 10;
		a[i] %= 10;
	}

	LongInt res(std::move(a), false);
	res.removeZeros();
	return res;
}

LA::LongInt LA::LongInt::operator*(const LongInt& rhs) const
{
	bool resNegative = (m_isNegative || rhs.m_isNegative) && !(m_isNegative && rhs.m_isNegative);

	const Digits& a = m_digits;
	const Digits& b = rhs.m_digits;

	Digits res(a.size() + b.size(), 0);

	for (auto i = 0llu; i < a.size(); ++i)
	{
		std::uint8_t carry = 0;

		for (auto j = 0llu; j < b.size() || carry; ++j)
		{
			auto cur = res[i + j] + a[i] * (j < b.size() ? b[j] : 0) + carry;

			res[i + j] = cur % 10;
			carry = cur / 10;
		}
	}

	LongInt resInt(std::move(res), resNegative);
	resInt.removeZeros();
	return resInt;
}

LA::LongInt LA::LongInt::operator/(const LongInt& rhs) const
{
	if (operator<(rhs))
	{
		return LongInt(0ll);
	}
	if (operator==(rhs))
	{
		return LongInt(1ll);
	}
	if (operator==(LongInt(0ll)))
	{
		return LongInt(1ll);
	}
	if (rhs.operator==(LongInt(0ll)))
	{
		throw std::logic_error("Zero division!");
	}

	bool resNegative = (m_isNegative || rhs.m_isNegative) && !(m_isNegative && rhs.m_isNegative);
	Digits digits = m_digits;
	while (digits.back() == 0)
	{
		digits.pop_back();
	}
	Digits res(digits.size(), 0);
	LongInt current_value(0);
	for (int i = 0; i < digits.size(); ++i)
	{
		current_value *= 10;
		current_value.m_digits[0] = digits[digits.size() - 1 - i];

		int x = 0;
		int left_index = 0;
		int right_index = 10;

		while (left_index <= right_index)
		{
			int middle = (left_index + right_index) >> 1;

			LongInt cur = std::abs(rhs) * middle;

			if (std::abs(cur) <= std::abs(current_value))
			{
				x = middle;
				left_index = middle + 1;
			}
			else
			{
				right_index = middle - 1;
			}
		}

		res[res.size() - 1 - i] = x;
		current_value = current_value - std::abs(rhs) * x;
	}

	LongInt resInt(std::move(res), resNegative);
	resInt.removeZeros();

	return resInt;
}

LA::LongInt& LA::LongInt::operator-=(const LongInt& rhs)
{
	return operator=(operator-(rhs));
}

LA::LongInt& LA::LongInt::operator+=(const LongInt& rhs)
{
	return operator=(operator+(rhs));
}

LA::LongInt& LA::LongInt::operator*=(const LongInt& rhs)
{
	return operator=(operator*(rhs));
}

LA::LongInt& LA::LongInt::operator/=(const LongInt& rhs)
{
	return operator=(operator/(rhs));
}

LA::LongInt& LA::LongInt::operator--()
{
	operator-=(1ll);
	return *this;
}

LA::LongInt LA::LongInt::operator--(int)
{
	LongInt res(*this);
	operator-=(1ll);
	return res;
}

LA::LongInt& LA::LongInt::operator++()
{
	operator+=(1ll);
	return *this;
}

LA::LongInt LA::LongInt::operator++(int)
{
	LongInt res(*this);
	operator+=(1ll);
	return res;
}

LA::LongInt LA::LongInt::operator%(const LongInt& rhs) const
{
	return operator-(rhs.operator*(operator/(rhs)));
}

LA::LongInt std::abs(const LA::LongInt& n)
{
	return n < 0 ? -n : n;
}

LA::LongInt std::pow(const LA::LongInt& n, const LA::LongInt& pow)
{
	LA::LongInt res = n;
	for (LA::LongInt i = 1; i < pow; ++i)
	{
		res *= n;
	}
	return res;
}

DRIVERLA_API LA::LongInt std::sqrt(const LA::LongInt& n)
{
	if (n == 0 || n == 1)
	{
		return n;
	}
	LA::LongInt start = 1, end = n, ans = -1;
	while (start <= end)
	{
		LA::LongInt mid = (start + end) / 2;
		if (mid * mid == n)
		{
			return mid;
		}
		if (mid * mid < n)
		{
			start = mid + 1;
			ans = mid;
		}
		else
		{
			end = mid - 1;
		}
	}
	return ans;
}
