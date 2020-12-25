/*
	olcPixelGameEngine.h

	+-------------------------------------------------------------+
	|           OneLoneCoder Pixel Game Engine v2.09              |
	|  "What do you need? Pixels... Lots of Pixels..." - javidx9  |
	+-------------------------------------------------------------+

	What is this?
	~~~~~~~~~~~~~
	olc::PixelGameEngine is a single file, cross platform graphics and userinput
	framework used for games, visualisations, algorithm exploration and learning.
	It was developed by YouTuber "javidx9" as an assistive tool for many of his
	videos. The goal of this project is to provide high speed graphics with
	minimal project setup complexity, to encourage new programmers, younger people,
	and anyone else that wants to make fun things.

	However, olc::PixelGameEngine is not a toy! It is a powerful and fast utility
	capable of delivering high resolution, high speed, high quality applications
	which behave the same way regardless of the operating system or platform.

	This file provides the core utility set of the olc::PixelGameEngine, including
	window creation, keyboard/mouse input, main game thread, timing, pixel drawing
	routines, image/sprite loading and drawing routines, and a bunch of utility
	types to make rapid development of games/visualisations possible.

	License (OLC-3)
	~~~~~~~~~~~~~~~

	Copyright 2018 - 2020 OneLoneCoder.com

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.

	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.

	Links
	~~~~~
	YouTube:	https://www.youtube.com/javidx9
				https://www.youtube.com/javidx9extra
	Discord:	https://discord.gg/WhwHUMV
	Twitter:	https://www.twitter.com/javidx9
	Twitch:		https://www.twitch.tv/javidx9
	GitHub:		https://www.github.com/onelonecoder
	Homepage:	https://www.onelonecoder.com
	Patreon:	https://www.patreon.com/javidx9
	Community:  https://community.onelonecoder.com

	Compiling in Linux
	~~~~~~~~~~~~~~~~~~
	You will need a modern C++ compiler, so update yours!
	To compile use the command:

	g++ -o YourProgName YourSource.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

	On some Linux configurations, the frame rate is locked to the refresh
	rate of the monitor. This engine tries to unlock it but may not be
	able to, in which case try launching your program like this:

	vblank_mode=0 ./YourProgName

	Compiling in Code::Blocks on Windows
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Well I wont judge you, but make sure your Code::Blocks installation
	is really up to date - you may even consider updating your C++ toolchain
	to use MinGW32-W64.

	Guide for installing recent GCC for Windows:
	https://www.msys2.org/
	Guide for configuring code::blocks:
	https://solarianprogrammer.com/2019/11/05/install-gcc-windows/
	https://solarianprogrammer.com/2019/11/16/install-codeblocks-gcc-windows-build-c-cpp-fortran-programs/

	Add these libraries to "Linker Options":
	user32 gdi32 opengl32 gdiplus Shlwapi dwmapi stdc++fs

	Set these compiler options: -std=c++17

	Compiling on Mac - EXPERIMENTAL! PROBABLY HAS BUGS
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Yes yes, people use Macs for C++ programming! Who knew? Anyway, enough
	arguing, thanks to Mumflr the PGE is now supported on Mac. Now I know nothing
	about Mac, so if you need support, I suggest checking out the instructions
	here: https://github.com/MumflrFumperdink/olcPGEMac

	clang++ -arch x86_64 -std=c++17 -mmacosx-version-min=10.15 -Wall -framework OpenGL -framework GLUT -lpng YourSource.cpp -o YourProgName

	Using stb_image.h
	~~~~~~~~~~~~~~~~~
	The PGE will load png images by default (with help from libpng on non-windows systems).
	However, the excellent "stb_image.h" can be used instead, supporting a variety of
	image formats, and has no library dependence - something we like at OLC studios ;)
	To use stb_image.h, make sure it's in your code base, and simply:

	#define OLC_IMAGE_STB

	Before including the olcPixelGameEngine.h header file. stb_image.h works on many systems
	and can be downloaded here: https://github.com/nothings/stb/blob/master/stb_image.h

	Ports
	~~~~~
	olc::PixelGameEngine has been ported and tested with varying degrees of
	success to: WinXP, Win7, Win8, Win10, Various Linux, Raspberry Pi,
	Chromebook, Playstation Portable (PSP) and Nintendo Switch. If you are
	interested in the details of these ports, come and visit the Discord!

	Thanks
	~~~~~~
	I'd like to extend thanks to Bispoo, Eremiell, slavka, gurkanctn, Phantim, IProgramInCPP
	JackOJC, KrossX, Huhlig, Dragoneye, Appa, JustinRichardsMusic, SliceNDice, dandistine
	Ralakus, Gorbit99, raoul, joshinils, benedani, Moros1138, Alexio, SaladinAkara & MagetzUb
	for advice, ideas and testing, and I'd like to extend my appreciation to the
	200K YouTube followers,	80+ Patreons and 10K Discord server members who give me
	the motivation to keep going with all this :D

	Significant Contributors: @Moros1138, @SaladinAkara, @MaGetzUb, @slavka,
								@Dragoneye, @Gorbit99 & @Mumflr

	Special thanks to those who bring gifts!
	GnarGnarHead.......Domina
	Gorbit99...........Bastion, Ori & The Blind Forest, Terraria
	Marti Morta........Gris
	Danicron...........Terraria
	SaladinAkara.......Aseprite
	AlterEgo...........Final Fantasy XII - The Zodiac Age
	SlicEnDicE.........Noita

	Special thanks to my Patreons too - I wont name you on here, but I've
	certainly enjoyed my tea and flapjacks :D

	Author
	~~~~~~
	David Barr, aka javidx9, �OneLoneCoder 2018, 2019, 2020

	2.01: Made renderer and platform static for multifile projects
	2.02: Added Decal destructor, optimised Pixel constructor
	2.03: Added FreeBSD flags, Added DrawStringDecal()
	2.04: Windows Full-Screen bug fixed
	2.05: +DrawPartialWarpedDecal() - draws a warped decal from a subset image
			+DrawPartialRotatedDecal() - draws a rotated decal from a subset image
	2.06: +GetTextSize() - returns area occupied by multiline string
			+GetWindowSize() - returns actual window size
			+GetElapsedTime() - returns last calculated fElapsedTime
			+GetWindowMouse() - returns actual mouse location in window
			+DrawExplicitDecal() - bow-chikka-bow-bow
			+DrawPartialDecal(pos, size) - draws a partial decal to specified area
			+FillRectDecal() - draws a flat shaded rectangle as a decal
			+GradientFillRectDecal() - draws a rectangle, with unique colour corners
			+Modified DrawCircle() & FillCircle() - Thanks IanM-Matrix1 (#PR121)
			+Gone someway to appeasing pedants
	2.07: +GetPixelSize() - returns user specified pixel size
			+GetScreenPixelSize() - returns actual size in monitor pixels
			+Pixel Cohesion Mode (flag in Construct()) - disallows arbitrary window scaling
			+Working VSYNC in Windows windowed application - now much smoother
			+Added string conversion for olc::vectors
			+Added comparator operators for olc::vectors
			+Added DestroyWindow() on windows platforms for serial PGE launches
			+Added GetMousePos() to stop TarriestPython whinging
	2.08: Fix SetScreenSize() aspect ratio pre-calculation
			Fix DrawExplicitDecal() - stupid oversight with multiple decals
			Disabled olc::Sprite copy constructor
			+olc::Sprite Duplicate() - produces a new clone of the sprite
			+olc::Sprite Duplicate(pos, size) - produces a new sprite from the region defined
			+Unary operators for vectors
			+More pedant mollification - Thanks TheLandfill
			+ImageLoader modules - user selectable image handling core, gdi+, libpng, stb_image
			+Mac Support via GLUT - thanks Mumflr!
	2.09: Fix olc::Renderable Image load error - Thanks MaGetzUb & Zij-IT for finding and moaning about it
			Fix file rejection in image loaders when using resource packs
			Tidied Compiler defines per platform - Thanks slavka
			+Pedant fixes, const correctness in parts
			+DecalModes - Normal, Additive, Multiplicative blend modes
			+Pixel Operators & Lerping
			+Filtered Decals - If you hate pixels, then erase this file
			+DrawStringProp(), GetTextSizeProp(), DrawStringPropDecal() - Draws non-monospaced font

*/

//////////////////////////////////////////////////////////////////////////////////////////

// O------------------------------------------------------------------------------O
// | Example "Hello World" Program (main.cpp)                                     |
// O------------------------------------------------------------------------------O
/*

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name you application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}

*/

#ifndef OLC_PGE_DEF
#define OLC_PGE_DEF

// O------------------------------------------------------------------------------O
// | STANDARD INCLUDES                                                            |
// O------------------------------------------------------------------------------O
#include <cmath>
#include <cstdint>
#include <string>
#include <iostream>
#include <streambuf>
#include <sstream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <fstream>
#include <map>
#include <functional>
#include <algorithm>
#include <array>
#include <cstring>

// O------------------------------------------------------------------------------O
// | COMPILER CONFIGURATION ODDITIES                                              |
// O------------------------------------------------------------------------------O
#define USE_EXPERIMENTAL_FS

#if defined(_WIN32)
#if _MSC_VER >= 1920 && _MSVC_LANG >= 201703L
#undef USE_EXPERIMENTAL_FS
#endif
#endif

#if defined(__linux__) || defined(__MINGW32__) || defined(__EMSCRIPTEN__) || defined(__FreeBSD__) || defined(__APPLE__)
#if __cplusplus >= 201703L
#undef USE_EXPERIMENTAL_FS
#endif
#endif

#if defined(__APPLE__)
#define PGE_USE_CUSTOM_START
#endif

#if defined(USE_EXPERIMENTAL_FS) || defined(FORCE_EXPERIMENTAL_FS)
// C++14
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace _gfs = std::experimental::filesystem::v1;
#else
	// C++17
#include <filesystem>
namespace _gfs = std::filesystem;
#endif

#if defined(UNICODE) || defined(_UNICODE)
#define olcT(s) L##s
#else
#define olcT(s) s
#endif

#define UNUSED(x) (void)(x)

// O------------------------------------------------------------------------------O
// | PLATFORM SELECTION CODE, Thanks slavka!                                      |
// O------------------------------------------------------------------------------O

// Platform
#if !defined(OLC_PLATFORM_WINAPI) && !defined(OLC_PLATFORM_X11) && !defined(OLC_PLATFORM_GLUT)
#if defined(_WIN32)
#define OLC_PLATFORM_WINAPI
#endif
#if defined(__linux__) || defined(__FreeBSD__)
#define OLC_PLATFORM_X11
#endif
#if defined(__APPLE__)
#define OLC_PLATFORM_GLUT
#endif
#endif

// Renderer
#if !defined(OLC_GFX_OPENGL10) || !defined(OLC_GFX_OPENGL33) && !defined(OLC_GFX_DIRECTX10)
#define OLC_GFX_OPENGL10
#endif

// Image loader
#if !defined(OLC_IMAGE_STB) && !defined(OLC_IMAGE_GDI) && !defined(OLC_IMAGE_LIBPNG)
#if defined(_WIN32)
#define	OLC_IMAGE_GDI
#endif
#if defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#define	OLC_IMAGE_LIBPNG
#endif
#endif

// O------------------------------------------------------------------------------O
// | PLATFORM-SPECIFIC DEPENDENCIES                                               |
// O------------------------------------------------------------------------------O
#if defined(OLC_PLATFORM_WINAPI)
#define _WINSOCKAPI_ // Thanks Cornchipss

//#if !defined(WIN32_LEAN_AND_MEAN) // Removes something GDI requires
//	#define WIN32_LEAN_AND_MEAN
//#endif
#if !defined(VC_EXTRALEAN)
#define VC_EXTRALEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif

// In Code::Blocks
#if !defined(_WIN32_WINNT)
#ifdef HAVE_MSMF
#define _WIN32_WINNT 0x0600 // Windows Vista
#else
#define _WIN32_WINNT 0x0500 // Windows 2000
#endif
#endif

#include <windows.h>

#undef _WINSOCKAPI_
#endif

#if defined(OLC_PLATFORM_X11)
namespace X11
{
#include <X11/X.h>
#include <X11/Xlib.h>
}
#endif

#if defined(OLC_PLATFORM_GLUT)
#define PGE_USE_CUSTOM_START
#if defined(__linux__)
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#if defined(__APPLE__)
#include <GLUT/glut.h>
#endif
#endif

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INTERFACE DECLARATION                                     |
// O------------------------------------------------------------------------------O
namespace olc
{
	class PixelGameEngine;
	class Sprite;

	// Pixel Game Engine Advanced Configuration
	constexpr uint8_t nMouseButtons = 5;
	constexpr uint8_t nDefaultAlpha = 0xFF;
	constexpr uint32_t nDefaultPixel = (nDefaultAlpha << 24);

	enum rcode { FAIL = 0, OK = 1, NO_FILE = -1 };

	// O------------------------------------------------------------------------------O
	// | olc::Pixel - Represents a 32-Bit RGBA colour                                 |
	// O------------------------------------------------------------------------------O
	struct Pixel
	{
		union
		{
			uint32_t n = nDefaultPixel;

			struct
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
		};

		enum Mode { NORMAL, MASK, ALPHA, CUSTOM };

		Pixel();
		Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = nDefaultAlpha);
		Pixel(uint32_t p);
		Pixel& operator =(const Pixel& v) = default;
		bool operator ==(const Pixel& p) const;
		bool operator !=(const Pixel& p) const;
		Pixel operator *(float i) const;
		Pixel operator /(float i) const;
		Pixel& operator *=(float i);
		Pixel& operator /=(float i);
		Pixel operator +(const Pixel& p) const;
		Pixel operator -(const Pixel& p) const;
		Pixel& operator +=(const Pixel& p);
		Pixel& operator -=(const Pixel& p);
		Pixel inv() const;
	};

	Pixel PixelF(float red, float green, float blue, float alpha = 1.0f);
	Pixel PixelLerp(const Pixel& p1, const Pixel& p2, float t);

	// O------------------------------------------------------------------------------O
	// | USEFUL CONSTANTS                                                             |
	// O------------------------------------------------------------------------------O
	static const Pixel
		GREY(192, 192, 192), DARK_GREY(128, 128, 128), VERY_DARK_GREY(64, 64, 64),
		RED(255, 0, 0), DARK_RED(128, 0, 0), VERY_DARK_RED(64, 0, 0),
		YELLOW(255, 255, 0), DARK_YELLOW(128, 128, 0), VERY_DARK_YELLOW(64, 64, 0),
		GREEN(0, 255, 0), DARK_GREEN(0, 128, 0), VERY_DARK_GREEN(0, 64, 0),
		CYAN(0, 255, 255), DARK_CYAN(0, 128, 128), VERY_DARK_CYAN(0, 64, 64),
		BLUE(0, 0, 255), DARK_BLUE(0, 0, 128), VERY_DARK_BLUE(0, 0, 64),
		MAGENTA(255, 0, 255), DARK_MAGENTA(128, 0, 128), VERY_DARK_MAGENTA(64, 0, 64),
		WHITE(255, 255, 255), BLACK(0, 0, 0), BLANK(0, 0, 0, 0);

	// Thanks to scripticuk and others for updating the key maps
	// MOTE: The GLUT platform will need updating, open to contributions ;)
	enum Key
	{
		NONE,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		K0,
		K1,
		K2,
		K3,
		K4,
		K5,
		K6,
		K7,
		K8,
		K9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		SPACE,
		TAB,
		SHIFT,
		CTRL,
		INS,
		DEL,
		HOME,
		END,
		PGUP,
		PGDN,
		BACK,
		ESCAPE,
		RETURN,
		ENTER,
		PAUSE,
		SCROLL,
		NP0,
		NP1,
		NP2,
		NP3,
		NP4,
		NP5,
		NP6,
		NP7,
		NP8,
		NP9,
		NP_MUL,
		NP_DIV,
		NP_ADD,
		NP_SUB,
		NP_DECIMAL,
		PERIOD,
		EQUALS,
		COMMA,
		MINUS,
		OEM_1,
		OEM_2,
		OEM_3,
		OEM_4,
		OEM_5,
		OEM_6,
		OEM_7,
		OEM_8,
		CAPS_LOCK,
		ENUM_END
	};

	// O------------------------------------------------------------------------------O
	// | olc::vX2d - A generic 2D vector type                                         |
	// O------------------------------------------------------------------------------O
#if !defined(OLC_IGNORE_VEC2D)
	template <class T>
	struct v2d_generic
	{
		T x = 0;
		T y = 0;

		v2d_generic() : x(0), y(0)
		{
		}

		v2d_generic(T _x, T _y) : x(_x), y(_y)
		{
		}

		v2d_generic(const v2d_generic& v) : x(v.x), y(v.y)
		{
		}

		v2d_generic& operator=(const v2d_generic& v) = default;
		T mag() const { return T(std::sqrt(x * x + y * y)); }
		T mag2() const { return x * x + y * y; }

		v2d_generic norm() const
		{
			T r = 1 / mag();
			return v2d_generic(x * r, y * r);
		}

		v2d_generic perp() const { return v2d_generic(-y, x); }
		T dot(const v2d_generic& rhs) const { return this->x * rhs.x + this->y * rhs.y; }
		T cross(const v2d_generic& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
		v2d_generic operator +(const v2d_generic& rhs) const { return v2d_generic(this->x + rhs.x, this->y + rhs.y); }
		v2d_generic operator -(const v2d_generic& rhs) const { return v2d_generic(this->x - rhs.x, this->y - rhs.y); }
		v2d_generic operator *(const T& rhs) const { return v2d_generic(this->x * rhs, this->y * rhs); }
		v2d_generic operator *(const v2d_generic& rhs) const { return v2d_generic(this->x * rhs.x, this->y * rhs.y); }
		v2d_generic operator /(const T& rhs) const { return v2d_generic(this->x / rhs, this->y / rhs); }
		v2d_generic operator /(const v2d_generic& rhs) const { return v2d_generic(this->x / rhs.x, this->y / rhs.y); }

		v2d_generic& operator +=(const v2d_generic& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}

		v2d_generic& operator -=(const v2d_generic& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}

		v2d_generic& operator *=(const T& rhs)
		{
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}

		v2d_generic& operator /=(const T& rhs)
		{
			this->x /= rhs;
			this->y /= rhs;
			return *this;
		}

		v2d_generic operator +() const { return {+x, +y}; }
		v2d_generic operator -() const { return {-x, -y}; }
		bool operator ==(const v2d_generic& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
		bool operator !=(const v2d_generic& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }

		const std::string str() const
		{
			return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
		}

		friend std::ostream& operator <<(std::ostream& os, const v2d_generic& rhs)
		{
			os << rhs.str();
			return os;
		}

		operator v2d_generic<int32_t>() const { return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y)}; }
		operator v2d_generic<float>() const { return {static_cast<float>(this->x), static_cast<float>(this->y)}; }
		operator v2d_generic<double>() const { return {static_cast<double>(this->x), static_cast<double>(this->y)}; }
	};

	// Note: joshinils has some good suggestions here, but they are complicated to implement at this moment,
	// however they will appear in a future version of PGE
	template <class T>
	v2d_generic<T> operator *(const float& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs * static_cast<float>(rhs.x)),
		                      static_cast<T>(lhs * static_cast<float>(rhs.y)));
	}

	template <class T>
	v2d_generic<T> operator *(const double& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs * static_cast<double>(rhs.x)),
		                      static_cast<T>(lhs * static_cast<double>(rhs.y)));
	}

	template <class T>
	v2d_generic<T> operator *(const int& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs * static_cast<int>(rhs.x)), static_cast<T>(lhs * static_cast<int>(rhs.y)));
	}

	template <class T>
	v2d_generic<T> operator /(const float& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs / static_cast<float>(rhs.x)),
		                      static_cast<T>(lhs / static_cast<float>(rhs.y)));
	}

	template <class T>
	v2d_generic<T> operator /(const double& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs / static_cast<double>(rhs.x)),
		                      static_cast<T>(lhs / static_cast<double>(rhs.y)));
	}

	template <class T>
	v2d_generic<T> operator /(const int& lhs, const v2d_generic<T>& rhs)
	{
		return v2d_generic<T>(static_cast<T>(lhs / static_cast<int>(rhs.x)), static_cast<T>(lhs / static_cast<int>(rhs.y)));
	}

	typedef v2d_generic<int32_t> vi2d;
	typedef v2d_generic<uint32_t> vu2d;
	typedef v2d_generic<float> vf2d;
	typedef v2d_generic<double> vd2d;
#endif

	// O------------------------------------------------------------------------------O
	// | olc::HWButton - Represents the state of a hardware button (mouse/key/joy)    |
	// O------------------------------------------------------------------------------O
	struct HWButton
	{
		bool bPressed = false; // Set once during the frame the event occurs
		bool bReleased = false; // Set once during the frame the event occurs
		bool bHeld = false; // Set true for all frames between pressed and released events
	};

	// O------------------------------------------------------------------------------O
	// | olc::ResourcePack - A virtual scrambled filesystem to pack your assets into  |
	// O------------------------------------------------------------------------------O
	struct ResourceBuffer : public std::streambuf
	{
		ResourceBuffer(std::ifstream& ifs, uint32_t offset, uint32_t size);
		std::vector<char> vMemory;
	};

	class ResourcePack : public std::streambuf
	{
	public:
		ResourcePack();
		~ResourcePack();
		bool AddFile(const std::string& sFile);
		bool LoadPack(const std::string& sFile, const std::string& sKey);
		bool SavePack(const std::string& sFile, const std::string& sKey);
		ResourceBuffer GetFileBuffer(const std::string& sFile);
		bool Loaded();
	private:
		struct sResourceFile
		{
			uint32_t nSize;
			uint32_t nOffset;
		};

		std::map<std::string, sResourceFile> mapFiles;
		std::ifstream baseFile;
		std::vector<char> scramble(const std::vector<char>& data, const std::string& key);
		std::string makeposix(const std::string& path);
	};

	class ImageLoader
	{
	public:
		ImageLoader() = default;
		virtual ~ImageLoader() = default;
		virtual rcode LoadImageResource(Sprite* spr, const std::string& sImageFile, ResourcePack* pack) = 0;
		virtual rcode SaveImageResource(Sprite* spr, const std::string& sImageFile) = 0;
	};

	// O------------------------------------------------------------------------------O
	// | olc::Sprite - An image represented by a 2D array of olc::Pixel               |
	// O------------------------------------------------------------------------------O
	class Sprite
	{
	public:
		Sprite();
		Sprite(const std::string& sImageFile, ResourcePack* pack = nullptr);
		Sprite(int32_t w, int32_t h);
		Sprite(const Sprite&) = delete;
		~Sprite();

	public:
		rcode LoadFromFile(const std::string& sImageFile, ResourcePack* pack = nullptr);
		rcode LoadFromPGESprFile(const std::string& sImageFile, ResourcePack* pack = nullptr);
		rcode SaveToPGESprFile(const std::string& sImageFile);

	public:
		int32_t width = 0;
		int32_t height = 0;

		enum Mode { NORMAL, PERIODIC };

		enum Flip { NONE = 0, HORIZ = 1, VERT = 2 };

	public:
		void SetSampleMode(Mode mode = NORMAL);
		Pixel GetPixel(int32_t x, int32_t y) const;
		bool SetPixel(int32_t x, int32_t y, Pixel p);
		Pixel GetPixel(const vi2d& a) const;
		bool SetPixel(const vi2d& a, Pixel p);
		Pixel Sample(float x, float y) const;
		Pixel SampleBL(float u, float v) const;
		Pixel* GetData();
		Sprite* Duplicate();
		Sprite* Duplicate(const vi2d& vPos, const vi2d& vSize);
		Pixel* pColData = nullptr;
		Mode modeSample = NORMAL;

		static std::unique_ptr<ImageLoader> loader;
	};

	// O------------------------------------------------------------------------------O
	// | olc::Decal - A GPU resident storage of an olc::Sprite                        |
	// O------------------------------------------------------------------------------O
	class Decal
	{
	public:
		Decal(Sprite* spr, bool filter = false);
		virtual ~Decal();
		void Update();

	public: // But dont touch
		int32_t id = -1;
		Sprite* sprite = nullptr;
		vf2d vUVScale = {1.0f, 1.0f};
	};

	enum class DecalMode
	{
		NORMAL,
		ADDITIVE,
		MULTIPLICATIVE,
		STENCIL,
		ILLUMINATE,
	};

	// O------------------------------------------------------------------------------O
	// | olc::Renderable - Convenience class to keep a sprite and decal together      |
	// O------------------------------------------------------------------------------O
	class Renderable
	{
	public:
		Renderable() = default;
		rcode Load(const std::string& sFile, ResourcePack* pack = nullptr, bool filter = false);
		void Create(uint32_t width, uint32_t height, bool filter = false);
		Decal* Decal() const;
		Sprite* Sprite() const;

	private:
		std::unique_ptr<olc::Sprite> pSprite = nullptr;
		std::unique_ptr<olc::Decal> pDecal = nullptr;
	};

	// O------------------------------------------------------------------------------O
	// | Auxilliary components internal to engine                                     |
	// O------------------------------------------------------------------------------O

	struct DecalInstance
	{
		Decal* decal = nullptr;
		vf2d pos[4] = {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
		vf2d uv[4] = {{0.0f, 0.0f}, {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}};
		float w[4] = {1, 1, 1, 1};
		Pixel tint[4] = {WHITE, WHITE, WHITE, WHITE};
		DecalMode mode = DecalMode::NORMAL;
	};

	struct DecalTriangleInstance
	{
		vf2d points[3];
		vf2d texture[3];
		Pixel colours[3];
		Decal* decal = nullptr;
	};

	struct LayerDesc
	{
		vf2d vOffset = {0, 0};
		vf2d vScale = {1, 1};
		bool bShow = false;
		bool bUpdate = false;
		Sprite* pDrawTarget = nullptr;
		uint32_t nResID = 0;
		std::vector<DecalInstance> vecDecalInstance;
		Pixel tint = WHITE;
		std::function<void()> funcHook = nullptr;
	};

	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		virtual void PrepareDevice() = 0;
		virtual rcode CreateDevice(std::vector<void*> params, bool bFullScreen, bool bVSYNC) = 0;
		virtual rcode DestroyDevice() = 0;
		virtual void DisplayFrame() = 0;
		virtual void PrepareDrawing() = 0;
		virtual void SetDecalMode(const DecalMode& mode) = 0;
		virtual void DrawLayerQuad(const vf2d& offset, const vf2d& scale, Pixel tint) = 0;
		virtual void DrawDecalQuad(const DecalInstance& decal) = 0;
		virtual uint32_t CreateTexture(uint32_t width, uint32_t height, bool filtered = false) = 0;
		virtual void UpdateTexture(uint32_t id, Sprite* spr) = 0;
		virtual uint32_t DeleteTexture(uint32_t id) = 0;
		virtual void ApplyTexture(uint32_t id) = 0;
		virtual void UpdateViewport(const vi2d& pos, const vi2d& size) = 0;
		virtual void ClearBuffer(Pixel p, bool bDepth) = 0;
		static PixelGameEngine* ptrPGE;
	};

	class Platform
	{
	public:
		virtual ~Platform() = default;
		virtual rcode ApplicationStartUp() = 0;
		virtual rcode ApplicationCleanUp() = 0;
		virtual rcode ThreadStartUp() = 0;
		virtual rcode ThreadCleanUp() = 0;
		virtual rcode CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const vi2d& vViewPos, const vi2d& vViewSize) = 0;
		virtual rcode CreateWindowPane(const vi2d& vWindowPos, vi2d& vWindowSize, bool bFullScreen) = 0;
		virtual rcode SetWindowTitle(const std::string& s) = 0;
		virtual rcode StartSystemEventLoop() = 0;
		virtual rcode HandleSystemEvent() = 0;
		static PixelGameEngine* ptrPGE;
	};

	static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<Platform> platform;
	static std::map<size_t, uint8_t> mapKeys;

	// O------------------------------------------------------------------------------O
	// | olc::PixelGameEngine - The main BASE class for your application              |
	// O------------------------------------------------------------------------------O
	class PixelGameEngine
	{
	public:
		PixelGameEngine();
		virtual ~PixelGameEngine();
	public:
		rcode Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
		                bool full_screen = false, bool vsync = false, bool cohesion = false);
		rcode Start();

	public: // User Override Interfaces
		// Called once on application startup, use to load your resources
		virtual bool OnUserCreate();
		// Called every frame, and provides you with a time per frame value
		virtual bool OnUserUpdate(float fElapsedTime);
		// Called once on application termination, so you can be one clean coder
		virtual bool OnUserDestroy();

	public: // Hardware Interfaces
		// Returns true if window is currently in focus
		bool IsFocused() const;
		// Get the state of a specific keyboard button
		HWButton GetKey(Key k) const;
		// Get the state of a specific mouse button
		HWButton GetMouse(uint32_t b) const;
		// Get Mouse X coordinate in "pixel" space
		int32_t GetMouseX() const;
		// Get Mouse Y coordinate in "pixel" space
		int32_t GetMouseY() const;
		// Get Mouse Wheel Delta
		int32_t GetMouseWheel() const;
		// Get the mouse in window space
		const vi2d& GetWindowMouse() const;
		// Gets the mouse as a vector to keep Tarriest happy
		const vi2d& GetMousePos() const;

	public: // Utility
		// Returns the width of the screen in "pixels"
		int32_t ScreenWidth() const;
		// Returns the height of the screen in "pixels"
		int32_t ScreenHeight() const;
		// Returns the width of the currently selected drawing target in "pixels"
		int32_t GetDrawTargetWidth() const;
		// Returns the height of the currently selected drawing target in "pixels"
		int32_t GetDrawTargetHeight() const;
		// Returns the currently active draw target
		Sprite* GetDrawTarget() const;
		// Resize the primary screen sprite
		void SetScreenSize(int w, int h);
		// Specify which Sprite should be the target of drawing functions, use nullptr
		// to specify the primary screen
		void SetDrawTarget(Sprite* target);
		// Gets the current Frames Per Second
		uint32_t GetFPS() const;
		// Gets last update of elapsed time
		float GetElapsedTime() const;
		// Gets Actual Window size
		const vi2d& GetWindowSize() const;
		// Gets pixel scale
		const vi2d& GetPixelSize() const;
		// Gets actual pixel scale
		const vi2d& GetScreenPixelSize() const;

	public: // CONFIGURATION ROUTINES
		// Layer targeting functions
		void SetDrawTarget(uint8_t layer);
		void EnableLayer(uint8_t layer, bool b);
		void SetLayerOffset(uint8_t layer, const vf2d& offset);
		void SetLayerOffset(uint8_t layer, float x, float y);
		void SetLayerScale(uint8_t layer, const vf2d& scale);
		void SetLayerScale(uint8_t layer, float x, float y);
		void SetLayerTint(uint8_t layer, const Pixel& tint);
		void SetLayerCustomRenderFunction(uint8_t layer, std::function<void()> f);

		std::vector<LayerDesc>& GetLayers();
		uint32_t CreateLayer();

		// Change the pixel mode for different optimisations
		// olc::Pixel::NORMAL = No transparency
		// olc::Pixel::MASK   = Transparent if alpha is < 255
		// olc::Pixel::ALPHA  = Full transparency
		void SetPixelMode(Pixel::Mode m);
		Pixel::Mode GetPixelMode();
		// Use a custom blend function
		void SetPixelMode(std::function<Pixel(int x, int y, const Pixel& pSource, const Pixel& pDest)> pixelMode);
		// Change the blend factor form between 0.0f to 1.0f;
		void SetPixelBlend(float fBlend);

	public: // DRAWING ROUTINES
		// Draws a single Pixel
		virtual bool Draw(int32_t x, int32_t y, Pixel p = WHITE);
		bool Draw(const vi2d& pos, Pixel p = WHITE);
		// Draws a line from (x1,y1) to (x2,y2)
		void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, Pixel p = WHITE, uint32_t pattern = 0xFFFFFFFF);
		void DrawLine(const vi2d& pos1, const vi2d& pos2, Pixel p = WHITE, uint32_t pattern = 0xFFFFFFFF);
		// Draws a circle located at (x,y) with radius
		void DrawCircle(int32_t x, int32_t y, int32_t radius, Pixel p = WHITE, uint8_t mask = 0xFF);
		void DrawCircle(const vi2d& pos, int32_t radius, Pixel p = WHITE, uint8_t mask = 0xFF);
		// Fills a circle located at (x,y) with radius
		void FillCircle(int32_t x, int32_t y, int32_t radius, Pixel p = WHITE);
		void FillCircle(const vi2d& pos, int32_t radius, Pixel p = WHITE);
		// Draws a rectangle at (x,y) to (x+w,y+h)
		void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = WHITE);
		void DrawRect(const vi2d& pos, const vi2d& size, Pixel p = WHITE);
		// Fills a rectangle at (x,y) to (x+w,y+h)
		void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, Pixel p = WHITE);
		void FillRect(const vi2d& pos, const vi2d& size, Pixel p = WHITE);
		// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
		void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = WHITE);
		void DrawTriangle(const vi2d& pos1, const vi2d& pos2, const vi2d& pos3, Pixel p = WHITE);
		// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
		void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, Pixel p = WHITE);
		void FillTriangle(const vi2d& pos1, const vi2d& pos2, const vi2d& pos3, Pixel p = WHITE);
		// Draws an entire sprite at well location (x,y)
		void DrawSprite(int32_t x, int32_t y, Sprite* sprite, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
		void DrawSprite(const vi2d& pos, Sprite* sprite, uint32_t scale = 1, uint8_t flip = Sprite::NONE);
		// Draws an area of a sprite at location (x,y), where the
		// selected area is (ox,oy) to (ox+w,oy+h)
		void DrawPartialSprite(int32_t x, int32_t y, Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h,
		                       uint32_t scale = 1, uint8_t flip =
			                       Sprite::NONE);
		void DrawPartialSprite(const vi2d& pos, Sprite* sprite, const vi2d& sourcepos, const vi2d& size, uint32_t scale = 1,
		                       uint8_t flip =
			                       Sprite::NONE);

		// Decal Quad functions
		void SetDecalMode(const DecalMode& mode);
		// Draws a whole decal, with optional scale and tinting
		void DrawDecal(const vf2d& pos, Decal* decal, const vf2d& scale = {1.0f, 1.0f}, const Pixel& tint = WHITE);
		// Draws a region of a decal, with optional scale and tinting
		void DrawPartialDecal(const vf2d& pos, Decal* decal, const vf2d& source_pos, const vf2d& source_size,
		                      const vf2d& scale = {1.0f, 1.0f}, const
		                      Pixel& tint = WHITE);
		void DrawPartialDecal(const vf2d& pos, const vf2d& size, Decal* decal, const vf2d& source_pos,
		                      const vf2d& source_size, const
		                      Pixel& tint = WHITE);
		// Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
		void DrawExplicitDecal(Decal* decal, const vf2d* pos, const vf2d* uv, const Pixel* col);
		// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
		void DrawWarpedDecal(Decal* decal, const vf2d (&pos)[4], const Pixel& tint = WHITE);
		void DrawWarpedDecal(Decal* decal, const vf2d* pos, const Pixel& tint = WHITE);
		void DrawWarpedDecal(Decal* decal, const std::array<vf2d, 4>& pos, const Pixel& tint = WHITE);
		// As above, but you can specify a region of a decal source sprite
		void DrawPartialWarpedDecal(Decal* decal, const vf2d (&pos)[4], const vf2d& source_pos, const vf2d& source_size,
		                            const
		                            Pixel& tint = WHITE);
		void DrawPartialWarpedDecal(Decal* decal, const vf2d* pos, const vf2d& source_pos, const vf2d& source_size, const
		                            Pixel& tint = WHITE);
		void DrawPartialWarpedDecal(Decal* decal, const std::array<vf2d, 4>& pos, const vf2d& source_pos,
		                            const vf2d& source_size, const
		                            Pixel& tint = WHITE);
		// Draws a decal rotated to specified angle, wit point of rotation offset
		void DrawRotatedDecal(const vf2d& pos, Decal* decal, float fAngle, const vf2d& center = {0.0f, 0.0f},
		                      const vf2d& scale = {1.0f, 1.0f}, const
		                      Pixel& tint = WHITE);
		void DrawPartialRotatedDecal(const vf2d& pos, Decal* decal, float fAngle, const vf2d& center,
		                             const vf2d& source_pos, const
		                             vf2d& source_size, const vf2d& scale = {1.0f, 1.0f}, const Pixel& tint = WHITE);
		// Draws a multiline string as a decal, with tiniting and scaling
		void DrawStringDecal(const vf2d& pos, const std::string& sText, Pixel col = WHITE,
		                     const vf2d& scale = {1.0f, 1.0f});
		void DrawStringPropDecal(const vf2d& pos, const std::string& sText, Pixel col = WHITE,
		                         const vf2d& scale = {1.0f, 1.0f});
		// Draws a single shaded filled rectangle as a decal
		void FillRectDecal(const vf2d& pos, const vf2d& size, Pixel col = WHITE);
		// Draws a corner shaded rectangle as a decal
		void GradientFillRectDecal(const vf2d& pos, const vf2d& size, Pixel colTL, Pixel colBL, Pixel colBR, Pixel
		                           colTR);

		// Draws a single line of text - traditional monospaced
		void DrawString(int32_t x, int32_t y, const std::string& sText, Pixel col = WHITE, uint32_t scale = 1);
		void DrawString(const vi2d& pos, const std::string& sText, Pixel col = WHITE, uint32_t scale = 1);
		vi2d GetTextSize(const std::string& s);

		// Draws a single line of text - non-monospaced
		void DrawStringProp(int32_t x, int32_t y, const std::string& sText, Pixel col = WHITE, uint32_t scale = 1);
		void DrawStringProp(const vi2d& pos, const std::string& sText, Pixel col = WHITE, uint32_t scale = 1);
		vi2d GetTextSizeProp(const std::string& s);

		// Clears entire draw target to Pixel
		void Clear(Pixel p);
		// Clears the rendering back buffer
		void ClearBuffer(Pixel p, bool bDepth = true);

	public: // Branding
		std::string sAppName;

	private: // Inner mysterious workings
		Sprite* pDrawTarget = nullptr;
		Pixel::Mode nPixelMode = Pixel::NORMAL;
		float fBlendFactor = 1.0f;
		vi2d vScreenSize = {256, 240};
		vf2d vInvScreenSize = {1.0f / 256.0f, 1.0f / 240.0f};
		vi2d vPixelSize = {4, 4};
		vi2d vScreenPixelSize = {4, 4};
		vi2d vMousePos = {0, 0};
		int32_t nMouseWheelDelta = 0;
		vi2d vMousePosCache = {0, 0};
		vi2d vMouseWindowPos = {0, 0};
		int32_t nMouseWheelDeltaCache = 0;
		vi2d vWindowSize = {0, 0};
		vi2d vViewPos = {0, 0};
		vi2d vViewSize = {0, 0};
		bool bFullScreen = false;
		vf2d vPixel = {1.0f, 1.0f};
		bool bHasInputFocus = false;
		bool bHasMouseFocus = false;
		bool bEnableVSYNC = false;
		float fFrameTimer = 1.0f;
		float fLastElapsed = 0.0f;
		int nFrameCount = 0;
		Sprite* fontSprite = nullptr;
		Decal* fontDecal = nullptr;
		Sprite* pDefaultDrawTarget = nullptr;
		std::vector<LayerDesc> vLayers;
		uint8_t nTargetLayer = 0;
		uint32_t nLastFPS = 0;
		bool bPixelCohesion = false;
		DecalMode nDecalMode = DecalMode::NORMAL;
		std::function<Pixel(int x, int y, const Pixel&, const Pixel&)> funcPixelMode;
		std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
		std::vector<vi2d> vFontSpacing;

		// State of keyboard
		bool pKeyNewState[256] = {false};
		bool pKeyOldState[256] = {false};
		HWButton pKeyboardState[256] = {false};

		// State of mouse
		bool pMouseNewState[nMouseButtons] = {false};
		bool pMouseOldState[nMouseButtons] = {false};
		HWButton pMouseState[nMouseButtons] = {false};

		// The main engine thread
		void EngineThread();

		// At the very end of this file, chooses which
		// components to compile
		void olc_ConfigureSystem();

		// If anything sets this flag to false, the engine
		// "should" shut down gracefully
		static std::atomic<bool> bAtomActive;

	public:
		// "Break In" Functions
		void olc_UpdateMouse(int32_t x, int32_t y);
		void olc_UpdateMouseWheel(int32_t delta);
		void olc_UpdateWindowSize(int32_t x, int32_t y);
		void olc_UpdateViewport();
		void olc_ConstructFontSheet();
		void olc_CoreUpdate();
		void olc_PrepareEngine();
		void olc_UpdateMouseState(int32_t button, bool state);
		void olc_UpdateKeyState(int32_t key, bool state);
		void olc_UpdateMouseFocus(bool state);
		void olc_UpdateKeyFocus(bool state);
		void olc_Terminate();

		// NOTE: Items Here are to be deprecated, I have left them in for now
		// in case you are using them, but they will be removed.
		// olc::vf2d	vSubPixelOffset = { 0.0f, 0.0f };

		friend class PGEX;
	};

	// O------------------------------------------------------------------------------O
	// | PGE EXTENSION BASE CLASS - Permits access to PGE functions from extension    |
	// O------------------------------------------------------------------------------O
	class PGEX
	{
		friend class PixelGameEngine;
	protected:
		static PixelGameEngine* pge;
	};
}

#endif // OLC_PGE_DEF
