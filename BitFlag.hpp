#pragma once

class BitFlag
{
	unsigned char value;
public:
	constexpr BitFlag(unsigned char value) :value(value) {}
	constexpr BitFlag operator|(const BitFlag& t)const { return value | t.value; }
	constexpr bool operator&(const BitFlag& t)const { return value | t.value; }
	BitFlag& operator^=(const BitFlag& t) { return value ^= t.value, *this; }
	constexpr bool operator()(unsigned char bit)const { return value & (1 << bit); }
	BitFlag& change(unsigned char bit) { return value ^= (1 << bit), *this; }
	constexpr operator unsigned char()const { return value; }
};

