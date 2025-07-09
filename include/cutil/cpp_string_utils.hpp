 /**
 ******************************************************************************
 *
 *  @mainpage strutil v1.1.0 - header-only string utility library documentation
 *  @see https://github.com/Shot511/strutil
 *
 *  @copyright  Copyright (C) 2024 Tomasz Galaj
 *  @file       strutil.h
 *  @brief      Library public interface header
 *
 *  @subsection Thank you all for your contributions!!
 *
 ******************************************************************************
 * Modified by BH2WFR for cutil project at 7 JUL 2025.
 */
#ifndef CUTIL_CPP_STRING_UTIL_HPP__
#define CUTIL_CPP_STRING_UTIL_HPP__
#include <cutil/base.h>
#include <cutil/cpp_base.hpp>

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif


#include <cstdint>
#include <cstdlib>
#include <type_traits>
#include <algorithm>
#include <cctype>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#ifndef CUTIL_STRINGUTIL_DO_NOT_USE_PARALLEL
	#define CUTIL_STRINGUTIL_DO_NOT_USE_PARALLEL	0
#endif

#if defined(CUTIL_CPP17_SUPPORTED) && !CUTIL_STRINGUTIL_DO_NOT_USE_PARALLEL
	#define _CUTIL_STRINGUTIL_USE_PARALLEL //* use std::execution::par for some algorithms (>=C++17)
	#include <execution>
#endif
#ifdef CUTIL_CPP17_SUPPORTED
	#include <optional>
	#include <charconv>
#endif


_CUTIL_NAMESPACE_BEGIN
namespace str
{
	namespace internal{
		template<typename T, typename Compare>
		inline void sort(std::vector<T>& vec, Compare comp = std::less<T>()) {
		#ifdef _CUTIL_STRINGUTIL_USE_PARALLEL
			std::sort(std::execution::par_unseq, vec.begin(), vec.end(), comp);
		#else
			std::sort(vec.begin(), vec.end(), comp);
		#endif
		}
		
		template <typename T>
		struct is_arithmetic : std::integral_constant<bool, std::is_arithmetic<T>::value && !std::is_same<T, bool>::value> {};
		
		template <typename T>
		struct is_integral : std::integral_constant<bool, std::is_integral<T>::value && !std::is_same<T, bool>::value> {};
		
		template <typename T>
		struct is_floating_point : std::integral_constant<bool, std::is_floating_point<T>::value> {};
	}
	
	
	/**
	 * @brief Converts any datatype into std::string.
	 *        Datatype must support << operator.
	 * @tparam T
	 * @param value - will be converted into std::string.
	 * @return Converted value as std::string.
	 */
	template<typename T> _CUTIL_FUNC_STATIC
	inline std::string to_string(T value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	/**
	 * @brief Converts std::string into any datatype.
	 *        Datatype must support << operator.
	 * @tparam T
	 * @param str - std::string that will be converted into datatype T.
	 * @return Variable of datatype T.
	 */
	template<typename T> _CUTIL_FUNC_STATIC
	inline T parse_string(const std::string & str)
	{
		T result;
		std::istringstream(str) >> result;
		return result;
	}
/*
	EXPECT_EQ(-255, cutil::str::parse_string<long int>("-255"));
	EXPECT_EQ("5.245", cutil::str::to_string<float>(5.245f));
*/
	
	
	/**
	 * @brief Converts std::string to lower case.
	 * @param str - std::string that needs to be converted.
	 * @return Lower case input std::string.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string to_lower(const std::string & str)
	{
		auto result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](uint8_t c) -> uint8_t
		{
			return static_cast<uint8_t>(std::tolower(c));
		});
		return result;
	}

	/**
	 * @brief Converts std::string to upper case.
	 * @param str - std::string that needs to be converted.
	 * @return Upper case input std::string.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string to_upper(const std::string & str)
	{
		auto result = str;
		std::transform(result.begin(), result.end(), result.begin(), [](uint8_t c) -> uint8_t
		{
			return static_cast<uint8_t>(std::toupper(c));
		});
		return result;
	}

	/**
	 * @brief Converts the first character of a string to uppercase letter and lowercases all other characters, if any.
	 * @param str - input string to be capitalized.
	 * @return A string with the first letter capitalized and all other characters lowercased. It doesn't modify the input string.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string capitalize(const std::string & str)
	{
		auto result = str;
		if (!result.empty())
		{
			result.front() = static_cast<char>(std::toupper(result.front()));
		}
		return result;
	}

	/**
	 * @brief Converts only the first character of a string to uppercase letter, all other characters stay unchanged.
	 * @param str - input string to be modified.
	 * @return A string with the first letter capitalized. All other characters stay unchanged. It doesn't modify the input string.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string capitalize_first_char(const std::string & str)
	{
		auto result = to_lower(str);
		if (!result.empty())
		{
			result.front() = static_cast<char>(std::toupper(result.front()));
		}
		return result;
	}
/*
	EXPECT_EQ("hello strutil", cutil::str::to_lower("HeLlo StRUTIL"));
	EXPECT_EQ("HELLO STRUTIL", cutil::str::to_upper("HeLlo StRUTIL"));
	EXPECT_EQ("HeLlo StRUTIL", cutil::str::capitalize("heLlo StRUTIL"));
	EXPECT_EQ("Hello strutil", cutil::str::capitalize_first_char("HeLlo StRUTIL"));
*/



	/**
	 * @brief Checks if input std::string str contains specified substring.
	 * @param str - std::string to be checked.
	 * @param substring - searched substring.
	 * @return True if substring was found in str, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool contains(const std::string & str, const std::string & substring)
	{
		return str.find(substring) != std::string::npos;
	}

	/**
	 * @brief Checks if input std::string str contains specified character.
	 * @param str - std::string to be checked.
	 * @param character - searched character.
	 * @return True if character was found in str, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool contains(const std::string & str, const char character)
	{
		return contains(str, std::string(1, character));
	}
/*
	EXPECT_EQ(true, cutil::str::contains("Hello StrUtil", "Str"));
	EXPECT_EQ(true, cutil::str::contains("Hello StrUtil", 'S'));
*/


	/**
	 * @brief Compares two std::strings ignoring their case (lower/upper).
	 * @param str1 - std::string to compare
	 * @param str2 - std::string to compare
	 * @return True if str1 and str2 are equal, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool compare_ignore_case(const std::string & str1, const std::string & str2)
	{
		return to_lower(str1) == to_lower(str2);
	}
/*
	std::string str1 = "POKEMON";
	std::string str2 = "pokemon";
	std::string str3 = "POKEMON";
	EXPECT_EQ(true, cutil::str::compare_ignore_case(str1, str2));
	EXPECT_EQ(true, cutil::str::compare_ignore_case(str1, str3));
	EXPECT_EQ(true, cutil::str::compare_ignore_case(str2, str3));
*/
	
	
	
	/**
	 * @brief Trims (in-place) white spaces from the left side of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	_CUTIL_FUNC_STATIC inline
	void trim_left(std::string & str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) { return !std::isspace(ch); }));
	}

	/**
	 * @brief Trims (in-place) white spaces from the right side of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	_CUTIL_FUNC_STATIC inline
	void trim_right(std::string & str)
	{
		str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) { return !std::isspace(ch); }).base(), str.end());
	}

	/**
	 * @brief Trims (in-place) white spaces from the both sides of std::string.
	 *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	 * @param str - input std::string to remove white spaces from.
	 */
	_CUTIL_FUNC_STATIC inline
	void trim(std::string & str)
	{
		trim_left(str);
		trim_right(str);
	}

	 /**
	  * @brief Trims white spaces from the left side of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string trim_left_copy(const std::string& str)
	{
		std::string result = str;
		trim_left(result);
		return result;
	}

	/**
	  * @brief Trims white spaces from the right side of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string trim_right_copy(const std::string& str)
	{
		std::string result = str;
		trim_right(result);
		return result;
	}

	/**
	  * @brief Trims white spaces from the both sides of std::string.
	  *        Taken from: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring.
	  * @param str - input std::string to remove white spaces from.
	  * @return Copy of input str with trimmed white spaces.
	  */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string trim_copy(const std::string& str)
	{
		std::string result = str;
		trim(result);
		return result;
	}
/*
	EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_left_copy("   HeLlo StRUTIL"));
	EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_right_copy("HeLlo StRUTIL    "));
	EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_copy("    HeLlo StRUTIL      "));
	
	std::string test = "   HeLlo StRUTIL";
	cutil::str::trim_left(test);
	EXPECT_EQ("HeLlo StRUTIL", test);
*/


	/**
	 * @brief Replaces (in-place) the first occurrence of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	_CUTIL_FUNC_STATIC inline
	bool replace_first(std::string & str, const std::string & target, const std::string & replacement)
	{
		const size_t start_pos = str.find(target);
		if (start_pos == std::string::npos)
		{
			return false;
		}
		str.replace(start_pos, target.length(), replacement);
		return true;
	}

	/**
	 * @brief Replaces (in-place) last occurrence of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	_CUTIL_FUNC_STATIC inline
	bool replace_last(std::string & str, const std::string & target, const std::string & replacement)
	{
		size_t start_pos = str.rfind(target);
		if (start_pos == std::string::npos)
		{
			return false;
		}
		str.replace(start_pos, target.length(), replacement);
		return true;
	}

	/**
	 * @brief Replaces (in-place) all occurrences of target with replacement.
	 *        Taken from: http://stackoverflow.com/questions/3418231/c-replace-part-of-a-string-with-another-string.
	 * @param str - input std::string that will be modified.
	 * @param target - substring that will be replaced with replacement.
	 * @param replacement - substring that will replace target.
	 * @return True if replacement was successfull, false otherwise.
	 */
	_CUTIL_FUNC_STATIC inline
	bool replace_all(std::string & str, const std::string & target, const std::string & replacement)
	{
		if (target.empty())
		{
			return false;
		}
		size_t start_pos = 0;
		const bool found_substring = str.find(target, start_pos) != std::string::npos;
		while ((start_pos = str.find(target, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, target.length(), replacement);
			start_pos += replacement.length();
		}
		return found_substring;
	}
/*
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_last(str1, "$name$", "Jon Doe");
    EXPECT_EQ(false, res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
	
	std::string str2 = "This is $name and that is also $name.";
	bool res2 = cutil::str::replace_all(str1, "$name", "Jon Doe");
	EXPECT_EQ(true, res2);
	EXPECT_EQ("This is Jon Doe and that is also Jon Doe.", str2);
*/





	/**
	 * @brief Checks if std::string str ends with specified suffix.
	 * @param str - input std::string that will be checked.
	 * @param suffix - searched suffix in str.
	 * @return True if suffix was found, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool ends_with(const std::string & str, const std::string & suffix)
	{
		const auto suffix_start = str.size() - suffix.size();
		const auto result = str.find(suffix, suffix_start);
		return (result == suffix_start) && (result != std::string::npos);
	}

	/**
	 * @brief Checks if std::string str ends with specified character.
	 * @param str - input std::string that will be checked.
	 * @param suffix - searched character in str.
	 * @return True if ends with character, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool ends_with(const std::string & str, const char suffix)
	{
		return !str.empty() && (str.back() == suffix);
	}

	/**
	 * @brief Checks if std::string str starts with specified prefix.
	 * @param str - input std::string that will be checked.
	 * @param prefix - searched prefix in str.
	 * @return True if prefix was found, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool starts_with(const std::string & str, const std::string & prefix)
	{
		return str.rfind(prefix, 0) == 0;
	}

	/**
	 * @brief Checks if std::string str starts with specified character.
	 * @param str - input std::string that will be checked.
	 * @param prefix - searched character in str.
	 * @return True if starts with character, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool starts_with(const std::string & str, const char prefix)
	{
		return !str.empty() && (str.front() == prefix);
	}
/*
	EXPECT_EQ(true, cutil::str::ends_with("DiffuseTexture_m", "_m"));
	EXPECT_EQ(true, cutil::str::ends_with("DiffuseTexture_m", 'm'));
	EXPECT_EQ(true, cutil::str::starts_with("DiffuseTexture_m", "Diffuse"));
	EXPECT_EQ(true, cutil::str::starts_with("DiffuseTexture_m", 'D'));
*/



	/**
	 * @brief Splits input std::string str according to input delim.
	 * @param str - std::string that will be splitted.
	 * @param delim - the delimiter.
	 * @return std::vector<std::string> that contains all splitted tokens.
	 * @note If input str is empty, the output vector will contain one empty string.
	 * 	 If input str ends with delim, the output vector will contain one empty string at the end.
	 * 	 If input str is empty and ends with delim, the output vector will contain two empty strings.
	 *   If delim is not found in str, the output vector will contain one string equal to input str.
	 *   If delim is repeated in str, the output vector will contain empty strings for each repeated occurrence.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::vector<std::string> split(const std::string & str, const char delim, size_t vectorReserve = 0)
	{
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;
		if(vectorReserve > 0){
			tokens.reserve(vectorReserve);
		}
		while(std::getline(ss, token, delim))
		{
			tokens.push_back(token);
		}
		// Match semantics of split(str,str)
		if (str.empty() || ends_with(str, delim)) {
			tokens.emplace_back();
		}
		return tokens;
	}

	/**
	 * @brief Splits input std::string str according to input std::string delim.
	 *        Taken from: https://stackoverflow.com/a/46931770/1892346.
	 * @param str - std::string that will be split.
	 * @param delim - the delimiter.
	 * @return std::vector<std::string> that contains all splitted tokens.
	 * @note If input str is empty, the output vector will contain one empty string.
	 * 	 If input str ends with delim, the output vector will contain one empty string at the end.
	 * 	 If input str is empty and ends with delim, the output vector will contain two empty strings.
	 *   If delim is not found in str, the output vector will contain one string equal to input str.
	 *   If delim is repeated in str, the output vector will contain empty strings for each repeated occurrence.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::vector<std::string> split(const std::string & str, const std::string & delim, size_t vectorReserve = 0)
	{
		size_t pos_start = 0, pos_end, delim_len = delim.length();
		std::string token;
		std::vector<std::string> tokens;
		if(vectorReserve > 0){
			tokens.reserve(vectorReserve);
		}
		while ((pos_end = str.find(delim, pos_start)) != std::string::npos)
		{
			token = str.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			tokens.push_back(token);
		}
		tokens.push_back(str.substr(pos_start));
		return tokens;
	}

	/**
	 * @brief Splits input string using any delimiter in the given set.
	 * @param str - std::string that will be split.
	 * @param delims - the set of delimiter characters.
	 * @return vector of resulting tokens.
	 * @note If input str is empty, the output vector will contain one empty string.
	 * 	 If input str ends with delim, the output vector will contain one empty string at the end.
	 * 	 If input str is empty and ends with delim, the output vector will contain two empty strings.
	 *   If delim is not found in str, the output vector will contain one string equal to input str.
	 *   If delim is repeated in str, the output vector will contain empty strings for each repeated occurrence.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::vector<std::string> split_any(const std::string & str, const std::string & delims, size_t vectorReserve = 0)
	{
		std::string token;
		std::vector<std::string> tokens;
		if(vectorReserve > 0){
			tokens.reserve(vectorReserve);
		}
		size_t pos_start = 0;
		for (size_t pos_end = 0; pos_end < str.length(); ++pos_end)
		{
			if (contains(delims, str[pos_end]))
			{
				token = str.substr(pos_start, pos_end - pos_start);
				tokens.push_back(token);
				pos_start = pos_end + 1;
			}
		}
		tokens.push_back(str.substr(pos_start));
		return tokens;
	}
	
	
	/**
	 * @brief Splits input string using regex as a delimiter.
	 * @param src - std::string that will be split.
	 * @param rgx_str - the set of delimiter characters.
	 * @return vector of resulting tokens.
	 * @note If input str is empty, the output vector will contain one empty string.
	 * 	 If input str ends with delim, the output vector will contain one empty string at the end.
	 * 	 If input str is empty and ends with delim, the output vector will contain two empty strings.
	 *   If delim is not found in str, the output vector will contain one string equal to input str.
	 *   If delim is repeated in str, the output vector will contain empty strings for each repeated occurrence.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::vector<std::string> regex_split(const std::string& src, const std::string& rgx_str, size_t vectorReserve = 0)
	{
		std::vector<std::string> elems;
		if(vectorReserve > 0){
			elems.reserve(vectorReserve);
		}
		const std::regex rgx(rgx_str);
		std::sregex_token_iterator iter(src.begin(), src.end(), rgx, -1);
		std::sregex_token_iterator end;
		while (iter != end)
		{
			elems.push_back(*iter);
			++iter;
		}
		return elems;
	}

	/**
	 * @brief Splits input string using regex as a delimiter.
	 * @param src - std::string that will be split.
	 * @param dest - map of matched delimiter and those being splitted.
	 * @param rgx_str - the set of delimiter characters.
	 * @return True if the parsing is successfully done.
	 * @note space around the delimiter will be trimmed.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::map<std::string, std::string> regex_split_map(const std::string& src, const std::string& rgx_str)
	{
		std::map<std::string, std::string> dest;
		std::string tstr = src + " ";
		std::regex rgx(rgx_str);
		std::sregex_token_iterator niter(tstr.begin(), tstr.end(), rgx);
		std::sregex_token_iterator viter(tstr.begin(), tstr.end(), rgx, -1);
		std::sregex_token_iterator end;
		++viter;
		while (niter != end)
		{
			dest[*niter] = *viter;
			++niter;
			++viter;
		}
		return dest;
	}

/*
	std::vector<std::string> res;
	res = cutil::str::split("asdf;asdfgh;asdfghjk", ';'); //* char
	// -> { "asdf", "asdfgh", "asdfghjk" }
	
	res = cutil::str::split("asdf>=asdfgh>=asdfghjk", ">="); //* string
	// -> { "asdf", "asdfgh", "asdfghjk" }
	
	res = cutil::str::split_any("abc,def|ghi jkl", ",| "); //* any of the delimiters
	// -> { "abc", "def", "ghi", "jkl" }
	
	res = cutil::str::regex_split("abc,abcd;abce.abcf?", "[,;\\.\\?]+"); //* regex
	// -> { "abc", "abcd", "abce", "abcf" }
	
	std::map<std::string, std::string> res_map;
	res_map = cutil::str::regex_split_map( //* regex map
						"[abc] name = 123; [abd]  name = 123;[abe] name = 123;  "
					  , "\\[[^\\]]+\\]" // starts with '[' and ends with ']', contains without ']'
					  );
	);
	// -> { "[abc]" : "name = 123;", "[abd]" : "name = 123;", "[abe]" : "name = 123;" }
	
	
	//* edge cases
	res = cutil::str::split("", ';'); 			// -> { "" }
	res = cutil::str::split("abcdef", ';'); 	// -> { "abcdef" }
	res = cutil::str::split("abcdef;", ';'); 	// -> { "abcdef", "" }
	res = cutil::str::split("abcdef;;", ';'); 	// -> { "abcdef", "", "" }
	res = cutil::str::split(";abcdef", ';'); 	// -> { "", "abcdef" }
	res = cutil::str::split("abc;;;def", ";"); 	// -> { "abc", "", "", "def" }
	
*/







    /**
     * @brief Joins all elements of a container of arbitrary datatypes
     *        into one std::string with delimiter delim.
     * @tparam Container - container type. (std::vector, std::set, std::list, ...)
     * @param tokens - container of tokens.
     * @param delim - the delimiter.
     * @return std::string with joined elements of container tokens with delimiter delim.
     */
    template<typename Container> _CUTIL_FUNC_STATIC
    inline std::string join(const Container & tokens, const std::string & delim)
    {
        std::ostringstream result;
        for(auto it = tokens.begin(); it != tokens.end(); ++it)
        {
            if(it != tokens.begin())
            {
                result << delim;
            }

            result << *it;
        }

        return result.str();
    }
/*
	std::vector<std::string> tokens = { "abc", "def", "ghi" };
	EXPECT_EQ("abc,def,ghi", cutil::str::join(tokens, ","));
	
	std::set<std::string> tokens_set = { "abc", "def", "ghi" };
	EXPECT_EQ("abc,def,ghi", cutil::str::join(tokens_set, ","));
*/



	/**
	 * @brief Inplace removal of all empty strings in a container of strings
	 * @tparam Container - container type, like std::vector, std::set, std::list, ...
	 * @param tokens - container of strings.
	 */
	template<template<typename, typename...> typename Container, typename... E> _CUTIL_FUNC_STATIC
	inline void drop_empty(Container<std::string, E...> & tokens)
	{
	#ifdef CUTIL_CPP20_SUPPORTED // C++20, use erase_if
		auto last = std::erase_if(tokens, [](auto& s){ return s.empty(); });
	#else // C++11
		auto it = std::remove_if(tokens.begin(), tokens.end(), [](const std::string& s){return s.empty();});
		tokens.erase(it, tokens.end());
	#endif
	}
	
	template<template<typename, typename...> typename Container, typename... E> _CUTIL_FUNC_STATIC
	inline void drop_empty_set(Container<std::string, E...> & tokens) // versions for std::set<std::string>
	{
	#ifdef CUTIL_CPP20_SUPPORTED // C++20, use erase_if
		auto last = std::erase_if(tokens, [](auto& s){ return s.empty(); });
	#else // C++11
		for(auto it = tokens.begin(); it != tokens.end(); ){
			if(it->empty()){
				it = tokens.erase(it);
			}else{
				++it;
			}
		}
	#endif
	}

	/**
	 * @brief Inplace removal of all empty strings in a container of strings
	 * @tparam container - container type.
	 * @param tokens - container of strings.
	 * @return container of non-empty tokens.
	 */
	template<template<typename, typename...> typename Container, typename... E> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline Container<std::string> drop_empty_copy(const Container<std::string, E...>& tokens)
	{
		auto result = tokens;
		drop_empty(result);
		return result;
	}
	template<template<typename, typename...> typename Container, typename... E> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline Container<std::string> drop_empty_set_copy(const Container<std::string, E...>& tokens)
	{
		auto result = tokens;
		drop_empty_set(result);
		return result;
	}
/*
	std::vector<std::string> tokens = { "t1", "t2", "", "t4", "" };
	cutil::str::drop_empty(tokens);
		// -> { "t1", "t2", "t4" }
	
	std::set<std::string> tokens_set = { "t1", "t2", "", "t4", "" };
	cutil::str::drop_empty_set(tokens_set);
		// -> { "t1", "t2", "t4" }
	
	auto new_set = cutil::str::drop_empty_set_copy(tokens_set);
		// -> { "t1", "t2", "t4" }
*/


	/**
	 * @brief Inplace removal of all duplicate strings in a vector<string> where order is not to be maintained
	 *        Taken from: C++ Primer V5
	 * @tparam T - arbitrary datatype.
	 * @param tokens - vector of strings.
	 * @return vector of non-duplicate tokens.
	 */
	template<typename T> _CUTIL_FUNC_STATIC
	inline void drop_duplicate(std::vector<T> &tokens)
	{
		internal::sort(tokens, std::less<T>());
		auto end_unique = std::unique(tokens.begin(), tokens.end());
		tokens.erase(end_unique, tokens.end());
	}

	/**
	 * @brief Removal of all duplicate strings in a vector<string> where order is not to be maintained
	 *        Taken from: C++ Primer V5
	 * @tparam T - arbitrary datatype.
	 * @param tokens - vector of strings.
	 * @return vector of non-duplicate tokens.
	 */
	template<typename T> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline std::vector<T> drop_duplicate_copy(const std::vector<T>& tokens)
	{
		std::vector<T> result = tokens;
		internal::sort(result, std::less<T>());
		auto end_unique = std::unique(result.begin(), result.end());
		result.erase(end_unique, result.end());
		return result;
	}
/*
	std::vector<std::string> str1 = { "t1", "t2", "", "t4", "", "t1"};
    cutil::str::drop_duplicate(str1);
		// -> { "", "t1", "t2", "t4" }
*/



	/**
	 * @brief Creates new std::string with repeated n times substring str.
	 * @param str - substring that needs to be repeated.
	 * @param n - number of iterations.
	 * @return std::string with repeated substring str.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string repeat(const std::string & str, size_t n)
	{
		std::string result;
		result.reserve(str.size() * n);
		for(size_t i = 0; i < n; ++i)
		{
			result += str;
		}
		return result;
	}

	/**
	 * @brief Creates new std::string with repeated n times char c.
	 * @param c - char that needs to be repeated.
	 * @param n - number of iterations.
	 * @return std::string with repeated char c.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string repeat(char c, size_t n)
	{
		return std::string(n, c);
	}
/*
	EXPECT_EQ("GoGoGoGo",   cutil::str::repeat("Go", 4));
	EXPECT_EQ("ZZZZZZZZZZ", cutil::str::repeat('Z', 10));
*/



	/**
	 * @brief Checks if input std::string str matches specified reular expression regex.
	 * @param str - std::string to be checked.
	 * @param regex - the std::regex regular expression.
	 * @return True if regex matches str, false otherwise.
	 */
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	bool matches(const std::string & str, const std::regex & regex)
	{
		return std::regex_match(str, regex);
	}



	/**
	 * @brief Sort input std::vector<std::string> strs in ascending order.
	 * @param strs - std::vector<std::string> to be checked.
	 */
	template<typename T> _CUTIL_FUNC_STATIC
	inline void sorting_ascending(std::vector<T> &strs)
	{
		// std::sort(std::execution::par_unseq, strs.begin(), strs.end());
		internal::sort(strs, std::less<T>());
	}

	/**
	 * @brief Sorted input std::vector<std::string> strs in descending order.
	 * @param strs - std::vector<std::string> to be checked.
	 */
	template<typename T> _CUTIL_FUNC_STATIC
	inline void sorting_descending(std::vector<T> &strs)
	{
		// std::sort(std::execution::par_unseq, strs.begin(),strs.end(), std::greater<T>());
		internal::sort(strs, std::greater<T>());
	}

	/**
	 * @brief Reverse input container strs.
	 * @param strs - container to be checked.
	 */
	template<typename Container> _CUTIL_FUNC_STATIC
	inline void reverse_inplace(Container &strs)
	{
		std::reverse(strs.begin(), strs.end());
	}

	/**
	 * @brief Reverse input container strs.
	 * @param strs - container to be checked.
	 */
	template<typename Container> _CUTIL_NODISCARD _CUTIL_FUNC_STATIC
	inline Container reverse_copy(const Container& strs)
	{
		Container result = strs;
		std::reverse(result.begin(), result.end());
		return result;
	}

	
	//* modify input string to valid filename by replace invalid characters
	// if `(replace == '\0')`, invalid characters will be removed; otherwise there will be replaced by `replace`
	_CUTIL_FUNC_STATIC inline
	void sanitize_filename(std::string& str, char replace = '\0')
	{
		std::string invalid_chars = "<>:\"/\\|?*";
	#ifdef _CUTIL_STRINGUTIL_USE_PARALLEL
		if(replace == '\0'){
			str.erase(std::remove_if(std::execution::par, str.begin(), str.end(), [&invalid_chars](char c){
				return invalid_chars.find(c) != std::string::npos;
			}), str.end());
		}else{
			std::replace_if(std::execution::par, str.begin(), str.end(), [&invalid_chars](char c){
				return invalid_chars.find(c) != std::string::npos;
			}, replace);
		}
	#else
		if(replace == '\0'){
			str.erase(std::remove_if(str.begin(), str.end(), [&invalid_chars](char c){
				return invalid_chars.find(c) != std::string::npos;
			}), str.end());
		}else{
			std::replace_if(str.begin(), str.end(), [&invalid_chars](char c){
				return invalid_chars.find(c) != std::string::npos;
			}, replace);
		}
	#endif
		cutil::str::trim(str);
	}
	
	//* get valid filename from the input string by replace invalid characters
	// if `(replace == '\0')`, invalid characters will be removed; otherwise there will be replaced by `replace`
	_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	std::string sanitize_filename_copy(const std::string& str, char replace = '\0')
	{
		std::string result = str;
		cutil::str::sanitize_filename(result, replace);
		return result;
	}
/*
	EXPECT_EQ("abcdefg", cutil::str::sanitize_filename_copy(" a<b>:c>\\d\"e/f|g:** ? "));
    EXPECT_EQ("a_b__c__d_e_f_g___ _", cutil::str::sanitize_filename_copy(" a<b>:c>\\d\"e/f|g:** ? ", '_'));
*/
	
	
	
	//* convert string to the specified type, like int, float, double, etc.
	//  if failed, it throws exception
	//  these functions are only the wrappers of std::stoi, std::stol, std::stof, etc.
	//  if you want to use std::stringstream, use `cutil::str::parse_string()`
	//  do not support non-arithmetic types
	//  2nd param `base` is not available for `float`, `double`, `long double`
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_arithmetic<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	Ret to_number(const std::string& str, int base = 10){ // for `uint8_t`, `int8_t`, `uint16_t`, `int16_t`, `unsigned int`
		int64_t ret = std::stoll(str, nullptr, base);
		if(ret < std::numeric_limits<Ret>::min() || ret > std::numeric_limits<Ret>::max()){
			throw std::out_of_range("to_number: value out of range for type " + std::string(typeid(Ret).name()));
		}
		return static_cast<Ret>(ret);
	}
	template<> _CUTIL_NODISCARD
	inline int to_number<int>(const std::string& str, int base){
		return std::stoi(str, nullptr, base); // `int` is 16-bit in some 8bit or 16 bit embedded systems
	}
	template<> _CUTIL_NODISCARD
	inline long to_number<long>(const std::string& str, int base){
		return std::stol(str, nullptr, base); // `long` is 32-bit in Windows x64, but 64-bit in Linux x64
	}
	template<> _CUTIL_NODISCARD
	inline unsigned long to_number<unsigned long>(const std::string& str, int base){
		return std::stoul(str, nullptr, base);
	}
	template<> _CUTIL_NODISCARD
	inline long long to_number<long long>(const std::string& str, int base){
		return std::stoll(str, nullptr, base);
	}
	template<> _CUTIL_NODISCARD
	inline unsigned long long to_number<unsigned long long>(const std::string& str, int base){
		return std::stoull(str, nullptr, base);
	}
	template<> _CUTIL_NODISCARD
	inline float to_number<float>(const std::string& str, int base){
		return std::stof(str);
	}
	template<> _CUTIL_NODISCARD
	inline double to_number<double>(const std::string& str, int base){
		return std::stod(str);
	}
	template<> _CUTIL_NODISCARD
	inline long double to_number<long double>(const std::string& str, int base){
		return std::stold(str);
	}
	
	
	//* convert string to the specified type, like int, float, double, etc.
	//  if failed, it returns default_value
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_arithmetic<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	Ret to_number(const std::string& str, Ret default_value, int base = 10){
		try {
			return to_number<Ret>(str, base);
		} catch (...) {
			return default_value;
		}
	}
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_arithmetic<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	auto to_number_pair(const std::string& str, int base = 10) -> std::pair<bool, Ret>
	{
		try {
			return {true, to_number<Ret>(str, base)};
		} catch (...) {
			return {false, Ret()};
		}
	}
#ifdef CUTIL_CPP17_SUPPORTED
	//* convert string to the specified type, like int, float, double, etc.
	//  if failed, it returns std::nullopt
	//  `std::from_chars()` is more recommended for C++17 and later
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_arithmetic<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	auto to_number_opt_legacy(const std::string& str, int base = 10) -> std::optional<Ret>
	{
		try {
			return to_number<Ret>(str, base);
		} catch (...) {
			return std::nullopt;
		}
	}
	
	//* convert string to the specified type, like int, float, double, etc.
	//  if failed, it returns std::nullopt
	//  this function uses `std::from_chars()` for C++17 and later
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_integral<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	auto to_number_opt(std::string_view str, int base = 10) -> std::optional<Ret>
	{
		Ret ret;
		const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), ret, base);
		if(ec == std::errc() /*&& ptr == str.data() + str.size()*/){
			return ret;
		}
		return std::nullopt;
	}
	template<typename Ret, typename std::enable_if<cutil::str::internal::is_floating_point<Ret>::value, bool>::type = false>
		_CUTIL_NODISCARD _CUTIL_FUNC_STATIC inline
	auto to_number_opt(std::string_view str) -> std::optional<Ret>
	{
		Ret ret;
		const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), ret);
		if(ec == std::errc() /*&& ptr == str.data() + str.size()*/){
			return ret;
		}
		return std::nullopt;
	}
	
#endif


} // namespace

_CUTIL_NAMESPACE_END
#endif /* CUTIL_CPP_STRING_UTIL_HPP__ */
