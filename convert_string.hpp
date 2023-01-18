#pragma once
#include <string>

namespace ext
{
	// 主にUTF-8(char8_t)型と通常の文字型(char)との相互変換をサポートする関数群です
	// 一部の関数は（STL標準でも！）未だにbasic_string<char>しか受け取らない場合があるため、その辺の調整を行う目的です
	// 特徴として、Shift-JISなどの文字列をUTF-8に変換するのではなく、あくまでC++上での型を変換するだけとなっています

	// 指定した型のポインタ文字列に解釈変換
	template<class T, class U>
	const T* to(const std::basic_string<U,std::char_traits<U>,std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	// 指定した型のポインタ文字列に解釈変換
	template<class T, class U>
	const T* to(const U* v)
	{
		return reinterpret_cast<const T*>(v);
	}

	// 指定した型を扱うbasic_stringに解釈変換
	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> convert(const std::basic_string<U, std::char_traits<U>, std::allocator<U>>& v)
	{
		return reinterpret_cast<const T*>(v.c_str());
	}

	// 数値を指定した型のポインタ文字列に解釈変換 多分floatやdoubleでも動く
	template<class T, class U>
	std::basic_string<T, std::char_traits<T>, std::allocator<T>> vto(U v)
	{
		return convert<T>(std::to_string(v));
	}
};

