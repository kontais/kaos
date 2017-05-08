#include "screen.h"
#include <stdint.h>
#include <stddef.h>


//using namespace screen;
//using uint16_t = unsigned short;

constexpr size_t VGA_WIDTH = 80;
constexpr size_t VGA_HEIGHT = 25;

static uint16_t* screenBuf = (uint16_t*) 0xB8000;
static size_t terminalColumn = 0;
static size_t terminalRow = 0;

static void copyMem(void* destP, void* srcP, size_t amount)
{
	auto dest = static_cast<char*>(destP);
	auto src = static_cast<char*>(srcP);

	for(size_t i = 0; i < amount; ++i)
	{
		dest[i]=src[i];
	}
}

static uint16_t combine(char c, screen::ForegroundColor fgColor, screen::BackgroundColor bgColor)
{
	const char color = static_cast<uint16_t>(fgColor) |
					   static_cast<uint16_t>(bgColor) << 4;
	return static_cast<uint16_t>(color) << 8 | c;
}

static void newLine()
{
	terminalColumn = 0;
	terminalRow++;

	if(terminalRow >= VGA_HEIGHT)
	{
		screen::scroll(1);
		terminalRow--;
	}
}

void screen::initialize()
{
	for (size_t y = 0; y < VGA_HEIGHT; y++)
	{
		for (size_t x = 0; x < VGA_WIDTH; x++)
		{
			const size_t index = y * VGA_WIDTH + x;
			screenBuf[index] = combine(' ', ForegroundColor::White, BackgroundColor::Black);
		}
	}
}

void screen::putChar(int x, int y, char c, ForegroundColor fgColor, BackgroundColor bgColor)
{
	screenBuf[x + y * 80] = combine(c, fgColor, bgColor);
}

void screen::putChar(char c, ForegroundColor fgColor, BackgroundColor bgColor)
{
	putChar(terminalColumn, terminalRow, c, fgColor, bgColor);

	terminalColumn++;
	if(terminalColumn >= VGA_WIDTH)
	{
		newLine();
	}
}

void screen::write(const char* text, ForegroundColor fgColor, BackgroundColor bgColor)
{
	for(auto c = text; c != nullptr && *c != 0; ++c)
	{
		if(*c == '\n')
			newLine();
		else
			putChar(*c, fgColor, bgColor);
	}
}

void screen::writePtr(const void* ptr)
{
	putChar('0');
	putChar('x');
	for(int i=15;i>=0;--i)
	{
		char c = (reinterpret_cast<uint64_t>(ptr) >> (i*4)) & 0xf;
		if(c>9)
		{
			c += 'A' - 10;
		}
		else
		{
			c += '0';
		}
		putChar(c);
	}
}

void screen::writeInt(int64_t i)
{
	auto div = 1;
	if(i<0)
	{
		putChar('-');
		i = -i;
	}
	else if(i == 0)
	{
		putChar('0');
		return;
	}

	while(div <= i)
	{
		div *= 10;
	}

	div /= 10;
	while(div > 0)
	{
		auto pos = i / div;
		putChar(static_cast<char>(pos+'0'));
		i -= pos * div;
		div /= 10;
	}
}

void screen::scroll(int amount)
{
	if(amount > 0)
	{
		for (size_t y = 1; y < VGA_HEIGHT; y++)
		{
			copyMem(&screenBuf[(y-1)*VGA_WIDTH], &screenBuf[y*VGA_WIDTH], VGA_WIDTH * 2);
		}
		for(size_t n = 0; n < VGA_WIDTH; ++n)
		{
			putChar(n, VGA_HEIGHT - 1, ' ');
		}
	}
	else if(amount < 0)
	{

	}
}
