#pragma once

#include <cstdint>
#include <type_traits>

namespace screen
{
	namespace format
	{
		struct Hex{};
	}

	enum class BackgroundColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGrey = 7,
	};

	enum class ForegroundColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGrey = 7,
		DarkGrey = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		LightBrown = 14,
		White = 15,
	};

	void initialize();
	void putChar(int x, int y, char c,
		ForegroundColor fgColor = ForegroundColor::LightGrey,
		BackgroundColor bgColor = BackgroundColor::Black);
	void putChar(char c,
		ForegroundColor fgColor = ForegroundColor::LightGrey,
		BackgroundColor bgColor = BackgroundColor::Black);
	void write(const char* text,
		ForegroundColor fgColor = ForegroundColor::LightGrey,
		BackgroundColor bgColor = BackgroundColor::Black);

	void writeByte(int byte);
	void writePtr(const void* ptr);
	void writeInt(int64_t i);
	void writeUInt(uint64_t i);

	template<typename T>
	void write(const T* ptr)
	{
		writePtr(ptr);
	}

	void scroll(int amount);

	namespace impl
	{
		template<typename First, typename... Rest>
		void print(const First& first, const Rest&... rest);

		template<typename First, typename... Rest>
		void printHex(const First& first, const Rest&... rest)
		{
			//writePtr((const void*)first);
			writeInt((int64_t)first);
			if constexpr (sizeof...(Rest) > 0)
			{
				write(" ");
				print(rest...);
			}
		}

		template<typename First, typename... Rest>
		void print(const First& first, const Rest&... rest)
		{
			if constexpr(std::is_integral<First>::value)
			{
				writeInt(first);
			}
			else if constexpr(std::is_same<First, format::Hex>::value)
			{
				printHex(rest...);
			}
			else
			{
				write(first);
			}

			if constexpr (sizeof...(Rest) > 0)
			{
				write(" ");
				print(rest...);
			}
		}
	}

	template<typename... T>
	void print(const T&... args)
	{
		impl::print(args...);
	}

	template<typename... T>
	void printnl(const T&... args)
	{
		impl::print(args..., "\n");
	}
}
