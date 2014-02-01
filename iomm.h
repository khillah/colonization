#ifndef IOMM_H
#define IOMM_H

#include <cassert>
#include <fstream>
#include <stdexcept>
#include <cstdint>


namespace iomm{
	using std::ostream;
	using std::istream;
	using std::string;
	using std::size_t;
	
	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint = std::uint32_t;
	
	string read_chars(istream &f, uint n);
	size_t write_chars(ostream &f, const string &s);
	
	char read_byte(istream &f);
	uint8 read_uint8(istream &f);
	uint16 read_uint16(istream &f);
	uint32 read_uint32(istream &f);
	string read_string(istream &f);
	
	size_t write_byte(ostream &f, const char &x);
	size_t write_uint8(ostream &f, const uint8 &x);	
	size_t write_uint16(ostream &f, const uint16 &x);
	size_t write_uint32(ostream &f, const uint32 &x);
	size_t write_string(ostream &f, const string &s);
	
	template <class T>
	T read(istream &f);
	
	template <class T>
	size_t write(ostream &f, const T &t);
}

#endif