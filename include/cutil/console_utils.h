/* UTF-8 encoding
* Project URL: 	https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		9 JUL 2025
  License:		MIT License
* Do not include this header in header files.
* If libs like fmtlib or Qt also included in source file, pls #include their headers FIRST, then #include this header.
	引用说明: 若源文件使用了 fmtlib 或 Qt 等库, 请先 #include 这些头文件, 最后再 #include 此头文件.
*/
#ifndef CUTIL_CONSOLE_UTILS_H__
#define CUTIL_CONSOLE_UTILS_H__
#include <cutil/base.h>

//* ==== customize parameters:
#ifndef CUTIL_ANSI_ESCAPE_UNSUPPORTED
	#define CUTIL_ANSI_ESCAPE_UNSUPPORTED		0	// set 0 to disable style changing, espeacially before Windows 10 1511
#endif
#if defined(CUTIL_ANSI_ESCAPE_UNSUPPORTED) && (! CUTIL_OS_WINDOWS)
	#undef CUTIL_ANSI_ESCAPE_UNSUPPORTED // not Windows, enable Ansi Escape Codes
#endif

#if defined(__cplusplus)
	#include <cutil/cpp_base.hpp>
	#include <iostream>
	#include <string>
#endif

_CUTIL_NAMESPACE_BEGIN

//====================== CONSOLE FORMAT/CUSTOMIZING MACROS =========================
//* reference:    https://en.wikipedia.org/wiki/ANSI_escape_code
			   // https://zh.wikipedia.org/wiki/ANSI%E8%BD%AC%E4%B9%89%E5%BA%8F%E5%88%97
			   
//* WARNING:  Windows built-in command-line tools in versions prior to Windows 10 1511 (WINVER >= 0x0A00) do not support this feature.
//		If font or color customizing features is needed in Windows 7 or prior system, pls use SetConsoleTextAttribute() function.
#if CUTIL_ANSI_ESCAPE_UNSUPPORTED == 1
	#define CAnsiEsc(_STR)		""			// disable Ansi Escape Codes
	#define CAnsiEscStr(_STR)	""			//  raw C++ Ansi EScape Code Strings
#else // default
	#define CAnsiEsc(_STR)		"\033[" _STR //* C++ Ansi Escape Codes with prefix
	#define CAnsiEscStr(_STR)	_STR 		 //  raw C++ Ansi EScape Code Strings
#endif

//* RESET color formatting and font styles to DEFAULT, you must add this after customizing font color
	#define CReset 			CAnsiEsc("0m")
	#define CRst			CReset 		// shorter alias
	#define CStyle(_STYLE, _STR)	_STYLE _STR CReset
	// example: printf(FYellow BBlue "yellow text" CRst);

//* font foreground colors
// dark font color series
	#define FBlack			CAnsiEsc("30m")
	#define FRed 			CAnsiEsc("31m")
	#define FGreen 			CAnsiEsc("32m")
	#define FYellow			CAnsiEsc("33m")	// in some terminals, it renders like brown.
	#define FBlue			CAnsiEsc("34m")
	#define FMagenta		CAnsiEsc("35m")
	#define FCyan			CAnsiEsc("36m")
	#define FWhite			CAnsiEsc("37m")
	
// light font color series
	#define FLBlack			CAnsiEsc("90m")	// it's gray.
	#define FLRed 			CAnsiEsc("91m")
	#define FLGreen 		CAnsiEsc("92m")
	#define FLYellow 		CAnsiEsc("93m")
	#define FLBlue 			CAnsiEsc("94m")
	#define FLMagenta 		CAnsiEsc("95m")
	#define FLCyan 			CAnsiEsc("96m")
	#define FLWhite 		CAnsiEsc("97m")
	#define FGray			FLBlack 	// equals to "CLBlack"
	#define FGrey			FLBlack
	
// font color: custom RGB values CRGB
	#define FRgb(R, G, B)	CAnsiEsc("38;2;" #R ";" #G ";" #B "m")
	#define FCode(C)		CAnsiEsc("38;5;"#C"m") // 8-bit color code, supports 0-15, 16-231, 232-255
	#define FDefault		CAnsiEsc("39m") 	// default foreground color

//* font background colors, can be combined with foreground colors
// dark font background color series
	#define BBlack			CAnsiEsc("40m")
	#define BRed 			CAnsiEsc("41m")
	#define BGreen 			CAnsiEsc("42m")
	#define BYellow			CAnsiEsc("43m")
	#define BBlue			CAnsiEsc("44m")
	#define BMagenta		CAnsiEsc("45m")
	#define BCyan			CAnsiEsc("46m")
	#define BWhite			CAnsiEsc("47m")
	
// light font background color series
	#define BLBlack			CAnsiEsc("100m")  // actually it's gray
	#define BLRed 			CAnsiEsc("101m")
	#define BLGreen 		CAnsiEsc("102m")
	#define BLYellow		CAnsiEsc("103m")
	#define BLBlue			CAnsiEsc("104m")
	#define BLMagenta		CAnsiEsc("105m")
	#define BLCyan			CAnsiEsc("106m")
	#define BLWhite			CAnsiEsc("107m")
	#define BGray			BLBlack	 // equals to "BLBlack"
	#define BGrey			BLBlack
	
// font background color: custom RGB values
	#define BRgb(R, G, B)	CAnsiEsc("48;2;" #R ";" #G ";" #B "m")
	#define BColor(C)		CAnsiEsc("48;5;"#C"m") // 8-bit color code, supports 0-15, 16-231, 232-255
	#define BDefault		CAnsiEsc("49m") 	// default background color

//* font styles
	#define CBold			CAnsiEsc("1m")	// Bold
	#define CWeak			CAnsiEsc("2m")	// Dimmed, Darker, or Faint
	#define CItalic			CAnsiEsc("3m")	// Italic
	#define CUnderLine		CAnsiEsc("4m")	// Underline
	#define CFlash			CAnsiEsc("5m")	// Flashing
	#define CQFlash			CAnsiEsc("6m")	// Quick flashing
	#define CInvert			CAnsiEsc("7m")	// Swap foreground and background colors
	#define CHide			CAnsiEsc("8m")	// Hide or Conceal
	// actually, "\033[1;31m" means bold and red text, these props can be stacked in this way.
	
	#define CDblUnderline	CAnsiEsc("21m")
	#define CNotUnderline	CAnsiEsc("24m")
	
	
//* ==== specific foreground and background color combinations
	#define CTurn 			CAnsiEsc("107;30m")		// white text on a black background
	#define CLYelBold 		CAnsiEsc("1;93m")		// bold, and light yellow
	#define CInvLYel		CAnsiEsc("1;30;103m")
	#define CLRedBold		CAnsiEsc("1;91m")
	#define CLightBold		CAnsiEsc("1;97;100m")
	#define CInvBold		CAnsiEsc("1;30;107m")

//* ============
//* Cursor control
	#define CUp(n)			CAnsiEsc(#n"A") // cursor Up:   Moves the cursor n (default 1) cells in the given direction.
	#define CDown(n)		CAnsiEsc(#n"B") // cursor Down: e.g. std::cout << CDown("2") // moves cursor 2 cells down
	#define CForward(n)		CAnsiEsc(#n"C") // cursor Forward:
	#define CBack(n)		CAnsiEsc(#n"D") // cursor Back
	#define CFwd(n)			CForward(n)  	// aliases
	#define CRight(n)		CForward(n)
	#define CLeft(n)		CBack(n)

	#define CNextLn(n)		CAnsiEsc(#n"E") // Moves cursor to beginning of the line n (default 1) lines down
	#define CPrevLn(n)		CAnsiEsc(#n"F") // Moves cursor to beginning of the line n (default 1) lines up.
	#define CHorzPos(n)		CAnsiEsc(#n"G") // Moves the cursor to column n (default 1, absolute).

	#define CCursorPos(x, y) CAnsiEsc(#x";"#y"H") 	// Moves the cursor to row n, column m
	#define CPos(x, y) 		 CCursorPos(x, y) 		// shorter alias

//* clear the screen or line
	#define CClear(n)		CAnsiEsc(#n"J") //  If the cursor is already at the edge of the screen, this has no effect.
	#define CClearAfter		CClear(0)   // clear from cursor to end of screen
	#define CClearBefore	CClear(1)   // clear from cursor to beginning of the screen
	#define CClearScr		CClear(2) 	// clear screen(console), and moves cursor to upper left on DOS ANSI.SYS.
	#define CClearAll		CClear(3) 	// erase screen(console), and delete all lines saved in the scrollback buffer


	#define CEraseLn(n)		CAnsiEsc(#n"K") // Erases part of the line. Cursor position does not change.
	#define CEraseLnAfter	CEraseLn(0)  // clear from cursor to the end of the line
	#define CEraseLnBefore	CEraseLn(1)  // clear from cursor to beginning of the line
	#define CEraseLnAll		CEraseLn(2)  // clear entire line

//* scroll control
	#define CScrollUp(n)	CAnsiEsc(#n"S") // Scroll whole page up by n (default 1) lines. New lines are added at the bottom.
	#define CScrollDn(n)	CAnsiEsc(#n"T") // Scroll whole page down by n (default 1) lines. New lines are added at the top.
	
	#define CSaveCursorPos	CAnsiEsc("s")
	#define CReadCursorPos  CAnsiEsc("u")
	
	#define CShowCursor		CAnsiEscStr("\033?25h")
	#define CHideCursor		CAnsiEscStr("\033?25l")

//* macros for text color formatting

#if CUTIL_ANSI_ESCAPE_UNSUPPORTED == 1
	#define _CUTIL_COLOR_OPT(_COLOR)	""
	#define _CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED()	return
#else // default
	#define _CUTIL_COLOR_OPT(_COLOR)	_COLOR
	#define _CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED()
#endif

//* ==============================================================


//* macros for console window/application and streams
#if CUTIL_OS_WINDOWS == 1 // in Windows
	#if CUTIL_WINAPI_INCLUDED == 1
		#define CUTIL_CHCP_ENCODING(_NUM)	\
			do {_CUTIL_DBL_COLON SetConsoleCP(_NUM); _CUTIL_DBL_COLON SetConsoleOutputCP(_NUM); \
			system("chcp "#_NUM);} while(0)
		#define CUTIL_CONSOLE_SIZE(COL, ROW)	\
			do {_CUTIL_DBL_COLON CONSOLE_SCREEN_BUFFER_INFO bufInfo; \
				_CUTIL_DBL_COLON GetConsoleScreenBufferInfo(_CUTIL_DBL_COLON GetStdHandle(STD_OUTPUT_HANDLE), &bufInfo); \
				bufInfo.dwSize.X = (COL); bufInfo.dwSize.Y = (ROW); \
				_CUTIL_DBL_COLON SetConsoleScreenBufferSize(_CUTIL_DBL_COLON GetStdHandle(STD_OUTPUT_HANDLE), bufInfo.dwSize); \
			} while(0)
	#else // in windows system, but without <windows.h> winapi
		#define CUTIL_CHCP_ENCODING(_NUM)	system("chcp "#_NUM)	// custom chcp encoding (number) in Windows
		#define CUTIL_CONSOLE_SIZE(X, Y) 	system("mode con cols=" #X "lines=" #Y) // set console window size
	#endif
	
	#define CUTIL_CONSOLE_CLEAR()			system("cls")			// clear the screen (console)
	#define CUTIL_CONSOLE_PAUSE()			system("pause")			// pause the console application
	
#else 	// in Linux/MacOS
	#define CUTIL_CHCP_ENCODING(_NUM)
	
	#define CUTIL_CONSOLE_CLEAR()			system("clear") 		// clear the screen (console)
	#define CUTIL_CONSOLE_SIZE(X, Y)		_CUTIL_COLOR_OPT(printf("\033[8;%d;%dt", (Y), (X)))
	#define CUTIL_CONSOLE_PAUSE()			getchar()				// pause the console application
	
#endif


//* features with win32api
#if CUTIL_WINAPI_INCLUDED == 1
	#define CUTIL_CONSOLE_TITLE(_STR)			_CUTIL_DBL_COLON SetConsoleTitle(_STR)  // set console title in windows by winapi, (_A/_W?)
	#define CUTIL_CONSOLE_TITLE_A(_STR)			_CUTIL_DBL_COLON SetConsoleTitleA(_STR)
	#define CUTIL_CONSOLE_TITLE_W(_WSTR)		_CUTIL_DBL_COLON SetConsoleTitleW(_WSTR)
	
	#define CUTIL_CONSOLE_CURSOR_POS(x, y)	\
		do {_CUTIL_DBL_COLON COORD pos; pos.X=x; pos.Y=y; \
			_CUTIL_DBL_COLON SetConsoleCursorPosition(_CUTIL_DBL_COLON GetStdHandle(STD_OUTPUT_HANDLE), pos); \
		} while(0)
	#define CUTIL_CONSOLE_ATTR(_ATTR)	\
		_CUTIL_DBL_COLON SetConsoleTextAttribute(_CUTIL_DBL_COLON GetStdHandle(STD_OUTPUT_HANDLE), (_ATTR))
	#define CUTIL_CONSOLE_RESET_STYLE()			CUTIL_CONSOLE_ATTR(0)
	#define CUTIL_ENABLE_VIRTUAL_TERMINAL()	\
		do {_CUTIL_DBL_COLON HANDLE handle = _CUTIL_DBL_COLON GetStdHandle(STD_OUTPUT_HANDLE); \
			_CUTIL_DBL_COLON DWORD mode; _CUTIL_DBL_COLON GetConsoleMode(handle, &mode); \
			mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; _CUTIL_DBL_COLON SetConsoleMode(handle, mode); \
		} while(0)
	//? 据说上面的函数在设置时只需要设置一次就可以自动适配到 STD_OUTPUT_HANDLE(stdout) 和 STD_ERROR_HANDLE(stderr) ?
	
#else // without win32api, or in Linux
	#define CUTIL_CONSOLE_TITLE(_STR)			_CUTIL_COLOR_OPT(printf("\033]0;%s\007", _STR)) // set console title in linux
	#define CUTIL_CONSOLE_TITLE_A(_STR)			CUTIL_CONSOLE_TITLE(_STR)
	#define CUTIL_CONSOLE_TITLE_W(_WSTR)		_CUTIL_COLOR_OPT(wprintf(L"\033]0;%ls\007", _WSTR))
	
	#define CUTIL_CONSOLE_CURSOR_POS(x, y)		_CUTIL_COLOR_OPT(printf("\033[%u;%uH", x, y))
	#define CUTIL_CONSOLE_ATTR(_ATTR)
	#define CUTIL_CONSOLE_RESET_STYLE()			_CUTIL_COLOR_OPT(printf(CReset))
	#define CUTIL_ENABLE_VIRTUAL_TERMINAL()
#endif


//* Flush the input buffer to ensure that subsequent "scanf()" or "cin" calls receive valid input.
#define CUTIL_CONSOLE_FLUSH_INPUTBUFFER()	do {char ch; while((ch = getchar()) != '\n') continue;} while(0)
	// 吸收输入缓存区内的其余字符, 以便下次 scanf 或 cin 时能够获取到正确的输入内容

//* Set Console Encoding by "chcp" command in Windows
#define CUTIL_CHCP_ENCODING_UTF8()       CUTIL_CHCP_ENCODING(65001)		//* set console encoding to UTF-8 in windows
#define CUTIL_CHCP_ENCODING_GB2312()     CUTIL_CHCP_ENCODING(936)		//  Simp. Chinese, or 54936 for GB18030
#define CUTIL_CHCP_ENCODING_BIG5()       CUTIL_CHCP_ENCODING(950)		//  Trad. Chinese
#define CUTIL_CHCP_ENCODING_KOR()        CUTIL_CHCP_ENCODING(949)		//  Korean
#define CUTIL_CHCP_ENCODING_JIS()        CUTIL_CHCP_ENCODING(932)		//  Shift_JIS,
#define CUTIL_CHCP_ENCODING_LATIN1()     CUTIL_CHCP_ENCODING(850)		//  Latin 1 multilingual (West European)
#define CUTIL_CHCP_ENCODING_LATIN2()     CUTIL_CHCP_ENCODING(852)		//  Latin 2 multilingual (East European / Slavic)
#define CUTIL_CHCP_ENCODING_CYR()        CUTIL_CHCP_ENCODING(855)		//  Cyrillic / Russian
#define CUTIL_CHCP_ENCODING_WIN1250()    CUTIL_CHCP_ENCODING(1250)		//  windows 1250, Central European
#define CUTIL_CHCP_ENCODING_WIN1251()    CUTIL_CHCP_ENCODING(1251)		//  windows 1251, Cyrillic
#define CUTIL_CHCP_ENCODING_WIN1252()    CUTIL_CHCP_ENCODING(1252)		//  windows 1252, western European

//* set execution locale
#define CUTIL_LOCALE_UTF8()				setlocale(LC_ALL, ".UTF-8")
#define CUTIL_LOCALE_DEFAULT()			setlocale(LC_ALL, "")
#define CUTIL_LOCALE_UTF8_PRINT()		do {char* pLocale = setlocale(LC_ALL, ".UTF-8");	\
											if(pLocale == NULL){ \
												printf(_CUTIL_COLOR_OPT(FLRed) "  setlocale(): unknown locale!\n" _CUTIL_COLOR_OPT(CRst)); \
											}else{	\
												printf(_CUTIL_COLOR_OPT(FLGreen) "  setlocale(): locale set to %s" _CUTIL_COLOR_OPT(CRst), pLocale); \
											}		\
											printf("\n"); \
										} while(0)
/*
* Instruction (C):
	#include <locale.h>
	#include <stdio.h>
	#include <windows.h>		// include other headers first
	#include <fmt/core.h>		// include other headers first
	
	#include <cutil/console_utils.h> 	// include this header at last
	
	int main(int argc, char* argv[]){
		CUTIL_CHCP_ENCODING_UTF8(); 		// switch console encoding to UTF-8 (windows)
		CUTIL_LOCALE_UTF8_PRINT();			// set locale to UTF-8, and print the current locale
		CUTIL_ENABLE_VIRTUAL_TERMINAL(); 	// enable virtual terminal processing in Windows console, so that ANSI escape codes can be used.
		CUTIL_CONSOLE_TITLE(_TEXT("MyProject")); 	// set console window title
		CUTIL_CONSOLE_SIZE(100, 30);		// set console window size to with of 30 chars and height of 30 lines.
		CUTIL_CONSOLE_CLEAR();				// clear console (system("cls"))
		
		CUTIL_PRINT_ARGV(argc, argv);		// print all argc and argv[n] of main() function
		
		printf(FLGreen "Hello World!\n" CRst);   	// print "Hello World" with light yellow console color formatting
														you should put "CRst" at the end of string to RESET console font color to DEFAULT
		printf(CStyle(FLGreen, "Hello World!\n")); 	// Equivalent
		
		fprintf(stderr, FLRed "ERROR\n" CRst);  	// print "ERROR" with font color light red, "CRst" is also needed to revert font color to default
		fprintf(stderr, CStyle(FLRed, "ERROR\n"));	// Equivalent
		
		printf(BRed FGreen CQFlash "test\n" CRst);  // Print text with green font and red background, and quickly flashing
		printf(CStyle(BRed FGreen CQFlash, "test\n"));// Equivalent
		
		printf(CForward(2)); 					// move thr cursor 2 characters right, equals to `CRight(2)` or `CFwd(2)`.
		
		CUTIL_ERROR_MESSAGE("error occured!"); 	// print an error message with filename, function name and line number ATTACHED.
		
		CUTIL_CONSOLE_PAUSE(); 			 		// system("pause");
		return 0;
	}

-------------------------
* Instruction (C++):
	#include <clocale>
	#include <iostream>
	#include <fmt/core.h> // optional
	#include <windows.h>  // windows only
	#include <cutil/console_utils.h> 	// include this header at last
	
	int main(int argc, char* argv[]){
		cutil::console::set_locale_utf8(); 			// set locale to UTF-8
		cutil::console::set_chcp_encoding(cutil::console::Encodings::UTF8); // set console encoding to UTF-8, you can also use `set_chcp_encoding_utf8()`
		cutil::console::enable_virtual_terminal();	// enable virtual terminal processing in Windows console, so that ANSI escape codes can be used.
		cutil::console::set_title("MyProject"); 	// set console window title
		cutil::console::set_size(100, 30); 			// set console window size to with of 30 chars and height of 30 lines.
		cutil::console::clear(); 					// clear console (system("cls"))
		
		cutil::console::print_argv(argc, argv); 	// print all argc and argv[n] of main() function
		
		fmt::println(FLGreen "Hello World!" CRst); 	// print "Hello World" with light green console color formatting
		fmt::println(stderr, FLRed "ERROR" CRst); 	// print "ERROR" with font color light red
		
		fmt::println(BRed FGreen CQFlash "test" CRst); // Print text with green font and red background, and quickly flashing
		
		cutil::console::pause(); 					// system("pause");
		return 0;
	}
*/


//============= PROGRAM DEBUGGING: Print Args/Error Messages ===============

//* fmt::println redirection
#if defined(__cplusplus) && (CUTIL_FMT_INCLUDED == 1) // fmt::print(), fmt::println()
	// note: "##__VA_ARGS__" is supported in gnu C++, and MSVC for version >= VS2015 update 3
	#define CUTIL_PRINTLN_SUPPORTED 1
	#define CUTIL_PRINT(_STR, ...)			fmt::print(_STR,   ##__VA_ARGS__)
	#define CUTIL_PRINTLN(_STR, ...)		fmt::println(_STR, ##__VA_ARGS__)
	// #define CUTIL_FMT_STREAMED(_VAR)		fmt::streamed(_VAR)
#elif defined(CUTIL_CPP23_SUPPORTED) // C++23 std::print(), std::println()
	#if __has_include(<print>) // C++17 support, && (defined(_PRINT_) || defined(_GLIBCXX_PRINT)
		#define CUTIL_PRINTLN_SUPPORTED 1
		#define CUTIL_PRINT(_STR, ...)		std::print(_STR,   ##__VA_ARGS__)
		#define CUTIL_PRINTLN(_STR, ...)	std::println(_STR, ##__VA_ARGS__)
	#else // no fmtlib, and after C++23
		#define CUTIL_PRINT(_STR, ...)
		#define CUTIL_PRINTLN(_STR, ...)
	#endif
#else // no fmtlib, and before C++23
	#define CUTIL_PRINT(_STR, ...)
	#define CUTIL_PRINTLN(_STR, ...)
#endif // _PRINT_


//* variable print
#define CUTIL_COUT_VAR(_VAR)				std::cout << #_VAR " = " << _VAR << '\n';
#if CUTIL_PRINTLN_SUPPORTED
	#define CUTIL_PRINT_VAR(_VAR)			CUTIL_PRINTLN(#_VAR " = {}", _VAR)
#else
	#define CUTIL_PRINT_VAR(_VAR)			CUTIL_COUT_VAR(_VAR)
#endif


//* error message print
#define CUTIL_PRINT_ERR(_STR, ...)		CUTIL_PRINT(stderr,   _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
#define CUTIL_PRINTLN_ERR(_STR, ...)	CUTIL_PRINTLN(stderr, _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
#define CUTIL_PRINTF_ERR(_STR, ...)		fprintf(stderr, _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
#define CUTIL_PRINTFLN_ERR(_STR, ...)	fprintf(stderr, _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst) "\n", ##__VA_ARGS__)
#define CUTIL_COUT_ERR(_STR, ...)		std::cerr << _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst)
#define CUTIL_COUTLN_ERR(_STR, ...)		std::cerr << _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst) << '\n'


//* macros for print something ONLY IN DEBUG BUILD
#if CUTIL_DEBUG_BUILD // Only Print in Debug Build
	#define CUTIL_DEBUG_PRINT(_STR, ...)		CUTIL_PRINT(_STR, ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTLN(_STR, ...)		CUTIL_PRINTLN(_STR, ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)	CUTIL_PRINT(stderr, _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)	CUTIL_PRINTLN(stderr, _CUTIL_COLOR_OPT(FLRed) _STR _CUTIL_COLOR_OPT(CRst), ##__VA_ARGS__)
	
	#define CUTIL_DEBUG_COUT(...)				std::cout << __VA_ARGS__
	#define CUTIL_DEBUG_COUTLN(...)				std::cout << __VA_ARGS__ << '\n'
	#define CUTIL_DEBUG_CERR(...)				CUTIL_COUT_ERR(__VA_ARGS__)
	#define CUTIL_DEBUG_CERRLN(...)				CUTIL_COUTLN_ERR(__VA_ARGS__)
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)		printf(_STR, ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)		printf(_STR "\n", ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTF_ERR(_STR, ...)	CUTIL_PRINTF_ERR(_STR, ##__VA_ARGS__)
	#define CUTIL_DEBUG_PRINTFLN_ERR(_STR, ...)	CUTIL_PRINTFLN_ERR(_STR, ##__VA_ARGS__)
	
	#define CUTIL_DEBUG_PRINT_ARGV(_argc, _argv) 	CUTIL_PRINT_ARGV(_argc, _argv)
	
#else // Do Nothing in Release Build
	#define CUTIL_DEBUG_PRINT(_STR, ...)
	#define CUTIL_DEBUG_PRINTLN(_STR, ...)
	#define CUTIL_DEBUG_PRINT_ERR(_STR, ...)
	#define CUTIL_DEBUG_PRINTLN_ERR(_STR, ...)
	
	#define CUTIL_DEBUG_COUT(...)
	#define CUTIL_DEBUG_COUTLN(...)
	#define CUTIL_DEBUG_CERR(...)
	#define CUTIL_DEBUG_CERRLN(...)
	
	#define CUTIL_DEBUG_PRINTF(_STR, ...)
	#define CUTIL_DEBUG_PRINTFLN(_STR, ...)
	#define CUTIL_DEBUG_PRINTF_ERR(_STR, ...)
	#define CUTIL_DEBUG_PRINTFLN_ERR(_STR, ...)
	
	#define CUTIL_DEBUG_PRINT_ARGV(_argc, _argv)
	
#endif // CUTIL_DEBUG_BUILD
/* instruction:
	if you want to print some debug message to console, and only do this in DEBUG BUILD,
	use these macros above, they will do nothing in release build.
* example:
	CUTIL_DEBUG_COUT("this is: " << 5); // expand to std::cout in debug build, and nothing in release build
	CUTIL_DEBUG_COUTLN("");             // with a line break ( << '\n')
	CUTIL_DEBUG_PRINTLN("this is {}", 5); // expand to fmt::println(if you include fmtlib headers above
										this header include), or std::println(C++23)
	CUTIL_DEBUG_PRINTF("this is %d", 5); // expand to printf in debug build
	
	CUTIL_DEBUG_PRINTLN_ERR("err: cannot ...!"); // print to stderr
	CUTIL_DEBUG_PRINTLN(stderr, "err: cannot ...!"); // equivalent
	CUTIL_DEBUG_CERR("err: cannot ... !" << 2 << std::endl);
*/


//* print all argc and argv[n] arguments for main(int argc, char* argv[]) function
#define CUTIL_PRINT_ARGV(_argc, _argv) do { \
		printf(_CUTIL_COLOR_OPT(CRst) "\n"); \
		printf(_CUTIL_COLOR_OPT(FLCyan CBold) \
			"====== Print Program params for `int main(int " \
			_CUTIL_COLOR_OPT(FLWhite) "argc" _CUTIL_COLOR_OPT(FLCyan) ", char* " \
			_CUTIL_COLOR_OPT(FLYellow) "argv[]" _CUTIL_COLOR_OPT(FLCyan) ")` =====" \
			_CUTIL_COLOR_OPT(CRst) "\n");						\
		printf(_CUTIL_COLOR_OPT(FLWhite) _CUTIL_COLOR_OPT(CBold) \
			"  argc: " _CUTIL_COLOR_OPT(FLWhite) "%d" _CUTIL_COLOR_OPT(CRst) "\n", (_argc)); \
		printf(_CUTIL_COLOR_OPT(FLGreen)   		"    argv[  0]: " \
			_CUTIL_COLOR_OPT(FLBlue) "%.256s\n", (_argv)[0]); \
		for(int i = 1; i < (_argc); i++) { \
			printf(_CUTIL_COLOR_OPT(FLYellow) 	"    argv[%3d]: " \
			_CUTIL_COLOR_OPT(FLGreen) "%.256s\n", i, (_argv)[i]); \
		} \
		printf(_CUTIL_COLOR_OPT(CRst) "\n"); \
	} while (0)


//* print an error message with filename, function name and line number ATTACHED.
#define CUTIL_ERROR_MESSAGE(_REASON) \
	fprintf(stderr, _CUTIL_COLOR_OPT(CRst FLRed CBold)	"\n=============== ERROR MESSAGE: " \
					_CUTIL_COLOR_OPT(FLWhite) _REASON _CUTIL_COLOR_OPT(CRst) "\n" \
			_CUTIL_COLOR_OPT(FRed) "    file: " _CUTIL_COLOR_OPT(FCyan)  __FILE__ "\n" \
			_CUTIL_COLOR_OPT(FRed) "    func: " _CUTIL_COLOR_OPT(FCyan) "%s\n" \
			_CUTIL_COLOR_OPT(FRed) "    line: " _CUTIL_COLOR_OPT(FCyan) "%d\n" \
			_CUTIL_COLOR_OPT(CRst) "\n" , _CUTIL_FUNC_NAME, __LINE__ \
	)

//* print an warning message with filename, function name and line number ATTACHED.
#define CUTIL_WARNING_MESSAGE(_REASON) \
	fprintf(stderr, _CUTIL_COLOR_OPT(CRst FLYellow) "\n=============== WARNING MESSAGE: " \
	 				_CUTIL_COLOR_OPT(FLWhite) _REASON _CUTIL_COLOR_OPT(CRst) "\n" \
			_CUTIL_COLOR_OPT(FYellow) "    file: " _CUTIL_COLOR_OPT(FCyan)  __FILE__ "\n" \
			_CUTIL_COLOR_OPT(FYellow) "    func: " _CUTIL_COLOR_OPT(FCyan) "%s\n" \
			_CUTIL_COLOR_OPT(FYellow) "    line: " _CUTIL_COLOR_OPT(FCyan) "%d\n" \
			_CUTIL_COLOR_OPT(CRst) "\n" , _CUTIL_FUNC_NAME, __LINE__ \
	)


//* print an error message, and force ABORT application.
#define CUTIL_ABORT_ERR(_REASON) 	 	do {CUTIL_ERROR_MESSAGE(_REASON); exit(-1);} while(0)
#define CUTIL_ABORT_ERR_ASM(_REASON) 	do {CUTIL_ERROR_MESSAGE(_REASON); asm("exit");} while(0)


//* print if the application is in debug or release build
#if CUTIL_DEBUG_BUILD
	#define CUTIL_PRINT_BUILD_TYPE()	printf(_CUTIL_COLOR_OPT(FLGreen) "  build type: `Debug`\n" _CUTIL_COLOR_OPT(CRst))
#else // release
	#define CUTIL_PRINT_BUILD_TYPE()	printf(_CUTIL_COLOR_OPT(FLGreen) "  build type: `Release`\n" _CUTIL_COLOR_OPT(CRst))
#endif


//========================== C++ versions ========================
#ifdef __cplusplus
namespace console {
	enum class Encodings : uint32_t {
		UTF8 		= 65001,	//* UTF-8
		GB2312 		= 936,		//  Simp. Chinese, or 54936 for GB18030
		GBK 		= GB2312,
		Big5 		= 950,		//  Trad. Chinese
		Korean 		= 949,		//  Korean
		JIS 		= 932,		//  Shift_JIS, Japanese
		Latin1 		= 850,		//  Latin 1 multilingual (West European)
		Latin2 		= 852,		//  Latin 2 multilingual (East European / Slavic)
		Cyrillic 	= 855,		//  Cyrillic / Russian
		Win1250 	= 1250,		//  windows 1250, Central European
		Win1251 	= 1251,		//  windows 1251, Cyrillic
		Win1252 	= 1252		//  windows 1252, western European
	};
	//* set console title, encoding, size, and other properties
	_CUTIL_FUNC_STATIC inline void set_title(const std::string& title) {
		CUTIL_CONSOLE_TITLE_A(title.data());
	}
	_CUTIL_FUNC_STATIC inline void set_title(const std::wstring& title) {
		CUTIL_CONSOLE_TITLE_W((title.data()));
	}
	
	
	_CUTIL_FUNC_STATIC inline void set_attr(uint16_t attr) {
		CUTIL_CONSOLE_ATTR(attr);
	}
	_CUTIL_FUNC_STATIC inline void reset_style() {
		CUTIL_CONSOLE_RESET_STYLE();
	}
	_CUTIL_FUNC_STATIC inline void enable_virtual_terminal() {
		CUTIL_ENABLE_VIRTUAL_TERMINAL();
	}
	
	//* set console encoding by "chcp" command in Windows
	_CUTIL_FUNC_STATIC inline void set_chcp_encoding(uint16_t codepage) {
	#if CUTIL_OS_WINDOWS == 1
		#if CUTIL_WINAPI_INCLUDED == 1
			::SetConsoleCP(codepage);
			::SetConsoleOutputCP(codepage);
		#else
			char buf[32];
			sprintf(buf, "chcp %u", codepage);
			system(buf);
		#endif
	#endif
	// in Linux/MacOS, do nothing
	}
	_CUTIL_FUNC_STATIC inline void set_chcp_encoding(Encodings encoding) {
		cutil::console::set_chcp_encoding(static_cast<uint32_t>(encoding));
	}
	_CUTIL_FUNC_STATIC inline void set_chcp_encoding_utf8() {
		cutil::console::set_chcp_encoding(cutil::console::Encodings::UTF8);
	}
	
	//* set size of console window in Windows
	_CUTIL_FUNC_STATIC inline void set_size(uint16_t cols, uint16_t rows) {
	#if CUTIL_OS_WINDOWS == 1
		#if CUTIL_WINAPI_INCLUDED == 1
			::CONSOLE_SCREEN_BUFFER_INFO bufInfo;
			::GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufInfo);
			bufInfo.dwSize.X = (cols);
			bufInfo.dwSize.Y = (rows);
			::SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufInfo.dwSize);
		#else
			char buf[64];
			sprintf(buf, "mode con cols=%u lines=%u", cols, rows);
			system(buf);
		#endif
	#else
		_CUTIL_COLOR_OPT(printf("\033[8;%d;%dt", rows, cols))
	#endif
	// in Linux/MacOS, do nothing
	}
	
	//* clear console screen
	_CUTIL_FUNC_STATIC inline void clear() {
		CUTIL_CONSOLE_CLEAR();
	}
	
	//* pause the program by `getchar()` or `system::pause()`
	_CUTIL_FUNC_STATIC inline void pause() {
		CUTIL_CONSOLE_PAUSE();
	}
	
	//* flush input buffer
	_CUTIL_FUNC_STATIC inline void flush_input_buffer() {
		int c;
		while((c = getchar()) != '\n' && c != EOF) continue;
		if(std::cin.fail()) {
			std::cin.clear();
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	
	//* set locale (and print if succeed)
	_CUTIL_FUNC_STATIC inline void set_locale(const std::string& locale, bool isPrint = true) {
		char* pLocale = std::setlocale(LC_ALL, locale.data());
		if(isPrint) {
			if(pLocale == nullptr) {
				printf(_CUTIL_COLOR_OPT(FLRed) "  setlocale(): unknown locale!\n" _CUTIL_COLOR_OPT(CRst));
			} else {
				printf(_CUTIL_COLOR_OPT(FLGreen) "  setlocale(): locale set to %s" _CUTIL_COLOR_OPT(CRst), pLocale);
			}
			printf("\n");
		}
	}
	_CUTIL_FUNC_STATIC inline void set_locale_utf8(bool isPrint = true) {
		cutil::console::set_locale(".UTF-8", isPrint);
	}
	_CUTIL_FUNC_STATIC inline void set_locale_default() {
		cutil::console::set_locale("", false);
	}
	
	
	//*--------- cursor controling through ANSI escape symbols -------------
	/*   NOTICE:
		In Windows, the top-left corner of the console is (1, 1), not (0, 0).
		In Linux, the top-left corner of the console is (0, 0)
	*/
	//* move cursor to (col, row)
	_CUTIL_FUNC_STATIC inline void set_cursor_pos(uint16_t col, uint16_t row) {
		CUTIL_CONSOLE_CURSOR_POS(col, row);
	}
	
	_CUTIL_FUNC_STATIC inline void move_cursor_col(int16_t d_col) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(d_col == 0) return;
		if(d_col > 0){
			printf("\033[%dC", d_col); // move cursor right
		}else if(d_col < 0){
			printf("\033[%dD", -d_col); // move cursor left
		}
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void move_cursor_row(int16_t d_row) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(d_row == 0) return;
		if(d_row > 0){
			printf("\033[%dB", d_row); // move cursor down
		}else if(d_row < 0){
			printf("\033[%dA", -d_row); // move cursor up
		}
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void move_cursor_pos(int16_t d_col, int16_t d_row) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		cutil::console::move_cursor_col(d_col);
		cutil::console::move_cursor_row(d_row);
	}
	
	//* move cursor to next/previous line
	_CUTIL_FUNC_STATIC inline void move_cursor_next_line(int16_t n = 1) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(n == 0) return;
		printf("\033[%dE", n); // move cursor to next line
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void move_cursor_prev_line(int16_t n = 1) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(n == 0) return;
		printf("\033[%dF", n); // move cursor to previous line
		fflush(stdout);
	}
	
	//* move cursor to horizontal position
	_CUTIL_FUNC_STATIC inline void move_cursor_horz_pos(uint16_t col) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[%dG", col); // move cursor to horizontal position
		fflush(stdout);
	}
	
	//* clear text
	_CUTIL_FUNC_STATIC inline void clear_after_cursor() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[0J"); // clear from cursor to end of screen
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void clear_before_cursor() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[1J"); // clear from cursor to beginning of screen
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void clear_screen_and_cursor() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[2J"); // clear screen(console), and moves cursor to upper left on DOS ANSI.SYS.
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void clear_screen() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[3J"); // erase screen(console), and delete all lines saved in the scrollback buffer
		fflush(stdout);
	}
	
	//* clear line
	_CUTIL_FUNC_STATIC inline void clear_line_after_cursor() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[0K"); // clear from cursor to end of line
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void clear_line_before_cursor() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[1K"); // clear from cursor to beginning of line
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void clear_line() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[2K"); // clear entire line
		fflush(stdout);
	}

	//* scroll control
	_CUTIL_FUNC_STATIC inline void scroll_up(int16_t n = 1) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(n <= 0) return;
		printf("\033[%dS", n); // scroll up
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void scroll_down(int16_t n = 1) {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		if(n <= 0) return;
		printf("\033[%dT", n); // scroll down
		fflush(stdout);
	}
	
	//* save and restore cursor position
	_CUTIL_FUNC_STATIC inline void save_cursor_pos() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[s"); // save cursor position
		fflush(stdout);
	}
	_CUTIL_FUNC_STATIC inline void restore_cursor_pos() {
		_CUTIL_RETURN_IF_ANSI_ESCAPE_UNSUPPORTED();
		printf("\033[u"); // restore cursor position
		fflush(stdout);
	}
	
	//* print all argc and argv[n] arguments for main(int argc, char* argv[]) function
	 _CUTIL_FUNC_STATIC inline void print_argv(int argc, char* argv[]) {
		CUTIL_PRINT_ARGV(argc, argv);
	}
	
	
} // namespace console
#endif // __cplusplus

_CUTIL_NAMESPACE_END
#endif // CUTIL_CONSOLE_UTILS_H__
