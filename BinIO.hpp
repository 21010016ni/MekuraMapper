#pragma once
#include <stdexcept>
#include <fstream>

class BinIO
{
public:
	std::fstream fst;

	BinIO(const char* s, std::ios_base::openmode mode) :fst(s, mode | std::ios::binary) {}
	BinIO(const std::string& s, std::ios_base::openmode mode) :fst(s, mode | std::ios::binary) {}
	template<class T> void write(T value)
	{
		fst.write(reinterpret_cast<char*>(&value), sizeof(value));
	}
	template<class T> T read()
	{
		T ret;
		fst.read(reinterpret_cast<char*>(&ret), sizeof(ret));
		if (fst.fail())
			throw std::runtime_error("file read error");
		return ret;
	}
};

