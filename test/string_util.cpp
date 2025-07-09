
#include <gtest/gtest.h>

#ifdef CUTIL_CPP17_SUPPORTED
#include <optional>
#endif

#include <cutil/cpp_string_utils.hpp>
#include <cutil/cpp_utils.hpp>

TEST(Compare, compare_ignore_case)
{
    std::string str1 = "PoKeMoN!";
    std::string str2 = "pokemon!";
    std::string str3 = "POKEMON";

    EXPECT_EQ(true, cutil::str::compare_ignore_case(str1, str2));
    EXPECT_EQ(false, cutil::str::compare_ignore_case(str1, str3));
    EXPECT_EQ(false, cutil::str::compare_ignore_case(str2, str3));
}

TEST(Compare, starts_with_str)
{
    EXPECT_EQ(true, cutil::str::starts_with("m_DiffuseTexture", "m_"));
    EXPECT_EQ(true, cutil::str::starts_with("This is a simple test case", "This "));
    EXPECT_EQ(true, cutil::str::starts_with("This is a simple test case", "This is a simple test case"));
    EXPECT_EQ(true, cutil::str::starts_with("", ""));

    EXPECT_EQ(false, cutil::str::starts_with("p_DiffuseTexture", "m_"));
    EXPECT_EQ(false, cutil::str::starts_with("This is a simple test case", "his "));
    EXPECT_EQ(false, cutil::str::starts_with("abc", "abc_"));
    EXPECT_EQ(false, cutil::str::starts_with("abc", "_abc"));

    EXPECT_EQ(false, cutil::str::starts_with("", "m_"));
}

TEST(Compare, starts_with_char)
{
    EXPECT_EQ(true, cutil::str::starts_with("m_DiffuseTexture", 'm'));
    EXPECT_EQ(true, cutil::str::starts_with("This is a simple test case", 'T'));

    EXPECT_EQ(false, cutil::str::starts_with("p_DiffuseTexture", 'm'));
    EXPECT_EQ(false, cutil::str::starts_with("This is a simple test case", 'h'));

    EXPECT_EQ(false, cutil::str::starts_with("", 'm'));
}

TEST(Compare, ends_with_str)
{
    EXPECT_EQ(true, cutil::str::ends_with("DiffuseTexture_m", "_m"));
    EXPECT_EQ(true, cutil::str::ends_with("This is a simple test case", " test case"));
    EXPECT_EQ(true, cutil::str::ends_with("This is a simple test case", "This is a simple test case"));
    EXPECT_EQ(true, cutil::str::ends_with("", ""));

    EXPECT_EQ(false, cutil::str::ends_with("DiffuseTexture_p", "_m"));
    EXPECT_EQ(false, cutil::str::ends_with("This is a simple test case", "test cas"));
    EXPECT_EQ(false, cutil::str::ends_with("abc", "_abc"));
    EXPECT_EQ(false, cutil::str::ends_with("abc", "abc_"));

    EXPECT_EQ(false, cutil::str::ends_with("", "_m"));
}

TEST(Compare, ends_with_char)
{
    EXPECT_EQ(true, cutil::str::ends_with("DiffuseTexture_m", 'm'));
    EXPECT_EQ(true, cutil::str::ends_with("This is a simple test case", 'e'));

    EXPECT_EQ(false, cutil::str::ends_with("DiffuseTexture_p", 'm'));
    EXPECT_EQ(false, cutil::str::ends_with("This is a simple test case", 's'));

    EXPECT_EQ(false, cutil::str::ends_with("", 'm'));
}

TEST(Compare, contains_str)
{
    EXPECT_EQ(true, cutil::str::contains("DiffuseTexture_m", "fuse"));
    EXPECT_EQ(true, cutil::str::contains("", ""));
    EXPECT_EQ(false, cutil::str::contains("DiffuseTexture_m", "fuser"));
    EXPECT_EQ(false, cutil::str::contains("abc", "abc_"));
    EXPECT_EQ(false, cutil::str::contains("", "abc"));
}

TEST(Compare, contains_char)
{
    EXPECT_EQ(true, cutil::str::contains("DiffuseTexture_m", 'f'));
    EXPECT_EQ(false, cutil::str::contains("DiffuseTexture_m", 'z'));
    EXPECT_EQ(false, cutil::str::contains("", 'z'));
}

TEST(Compare, matches)
{
    const std::regex check_mail("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+$");

    EXPECT_EQ(true, cutil::str::matches("jon.doe@somehost.com", check_mail));
    EXPECT_EQ(false, cutil::str::matches("jon.doe@", check_mail));
}

/*
 * Parsing tests
 */

TEST(Parsing, short_To_string)
{
    EXPECT_EQ("-255", cutil::str::to_string<short int>(-255));
}

TEST(Parsing, u_short_To_string)
{
    EXPECT_EQ("255", cutil::str::to_string<unsigned short int>(255));
}

TEST(Parsing, To_string)
{
    EXPECT_EQ("-255", cutil::str::to_string<int>(-255));
}

TEST(Parsing, u_To_string)
{
    EXPECT_EQ("255", cutil::str::to_string<unsigned int>(255));
}

TEST(Parsing, long_To_string)
{
    EXPECT_EQ("-255", cutil::str::to_string<long int>(-255));
}

TEST(Parsing, u_long_To_string)
{
    EXPECT_EQ("255", cutil::str::to_string<unsigned long int>(255));
}

TEST(Parsing, long_long_To_string)
{
    EXPECT_EQ("-255", cutil::str::to_string<long long int>(-255));
}

TEST(Parsing, u_long_long_To_string)
{
    EXPECT_EQ("255", cutil::str::to_string<unsigned long long int>(255));
}

TEST(Parsing, char_to_string)
{
    EXPECT_EQ("d", cutil::str::to_string<char>('d'));
}

TEST(Parsing, u_char_to_string)
{
    EXPECT_EQ("d", cutil::str::to_string<unsigned char>('d'));
}

TEST(Parsing, float_to_string)
{
    EXPECT_EQ("5.245", cutil::str::to_string<float>(5.245f));
}

TEST(Parsing, double_to_string)
{
    EXPECT_EQ("5.245", cutil::str::to_string<double>(5.245));
}

TEST(Parsing, long_double_to_string)
{
    EXPECT_EQ("-5.245", cutil::str::to_string<long double>(-5.245));
}

TEST(Parsing, bool_to_string)
{
    EXPECT_EQ("1", cutil::str::to_string<bool>(true));
}

TEST(Parsing, neg_bool_to_string)
{
    EXPECT_EQ("0", cutil::str::to_string<bool>(false));
}

TEST(Parsing, string_to_short_int)
{
    EXPECT_EQ(-255, cutil::str::parse_string<short int>("-255"));
    EXPECT_EQ(-255, cutil::str::to_number<int32_t>("-255"));
    EXPECT_EQ(-255, cutil::str::to_number<int64_t>("-255"));
#ifdef CUTIL_CPP17_SUPPORTED
    EXPECT_EQ(-255, cutil::str::to_number_opt<int32_t>("-255"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt<size_t>("aaa")); // failed
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt<int32_t>("99999999999999")); // overflow
    EXPECT_EQ(-2, cutil::str::to_number_opt<int8_t>("-2"));
    EXPECT_EQ(127, cutil::str::to_number_opt<int8_t>("127"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt<uint8_t>("-2"));
    
    EXPECT_EQ(-255, cutil::str::to_number_opt_legacy<int32_t>("-255"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt_legacy<size_t>("aaa")); // failed
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt_legacy<int32_t>("99999999999999")); // overflow
    EXPECT_EQ(-2, cutil::str::to_number_opt_legacy<int8_t>("-2"));
    EXPECT_EQ(127, cutil::str::to_number_opt_legacy<int8_t>("127"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt_legacy<uint8_t>("-2"));
#endif
}

TEST(Parsing, string_to_u_short_int)
{
    EXPECT_EQ(255, cutil::str::parse_string<unsigned short int>("255"));
}

TEST(Parsing, string_to_int)
{
    EXPECT_EQ(-255, cutil::str::parse_string<int>("-255"));
}

TEST(Parsing, string_to_u_int)
{
    EXPECT_EQ(255, cutil::str::parse_string<unsigned int>("255"));
}

TEST(Parsing, string_to_long_int)
{
    EXPECT_EQ(-255, cutil::str::parse_string<long int>("-255"));
}

TEST(Parsing, string_to_u_long_int)
{
    EXPECT_EQ(255, cutil::str::parse_string<unsigned long int>("255"));
}

TEST(Parsing, string_to_long_long_int)
{
    EXPECT_EQ(-255, cutil::str::parse_string<long long int>("-255"));
}

TEST(Parsing, string_to_u_long_long_int)
{
    EXPECT_EQ(255, cutil::str::parse_string<unsigned long long int>("255"));
}

TEST(Parsing, string_to_char)
{
    EXPECT_EQ('d', cutil::str::parse_string<char>("d"));
}

TEST(Parsing, string_to_u_char)
{
    EXPECT_EQ('d', cutil::str::parse_string<unsigned char>("d"));
}

TEST(Parsing, string_to_float)
{
    EXPECT_EQ(5.245f, cutil::str::parse_string<float>("5.245f"));
    EXPECT_EQ(-255.0f, cutil::str::to_number<float>("-255"));
    
#ifdef CUTIL_CPP17_SUPPORTED
    EXPECT_EQ(5.245f, cutil::str::to_number_opt<float>("5.245f"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt<float>("aaa")); // failed
    EXPECT_EQ(99999999999999.0f, cutil::str::to_number_opt<float>("99999999999999"));
    EXPECT_EQ(1e2f, cutil::str::to_number_opt<float>("1e2"));
    
    EXPECT_EQ(5.245f, cutil::str::to_number_opt_legacy<float>("5.245f"));
    EXPECT_EQ(std::nullopt, cutil::str::to_number_opt_legacy<float>("aaa")); // failed
    EXPECT_EQ(99999999999999.0f, cutil::str::to_number_opt_legacy<float>("99999999999999"));
    EXPECT_EQ(1e2f, cutil::str::to_number_opt_legacy<float>("1e2"));
#endif
}

TEST(Parsing, string_to_double)
{
    EXPECT_EQ(5.245, cutil::str::parse_string<double>("5.245"));
}

TEST(Parsing, string_to_long_double)
{
    EXPECT_EQ(-5.245L, cutil::str::parse_string<long double>("-5.245"));
}

TEST(Parsing, string_to_bool)
{
    EXPECT_EQ(true, cutil::str::parse_string<bool>("1"));
}

TEST(Parsing, string_to_neg_bool)
{
    EXPECT_EQ(false, cutil::str::parse_string<bool>("0"));
}

/*
* Splitting and tokenizing
*/

TEST(Splitting, split_char_delim)
{
    std::string str1 = "asdf;asdfgh;asdfghjk";
    std::vector<std::string> res = cutil::str::split(str1, ';');
    std::vector<std::string> expected = { "asdf", "asdfgh", "asdfghjk" };
    ASSERT_EQ(res.size(), expected.size()) << "Vectors are of unequal length";
    for (unsigned i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(expected[i], res[i]) << "Vectors differ at index " << i;
    }

    // Empty input => empty string
    res = cutil::str::split("", ';');
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "");

    // No matches => original string
    res = cutil::str::split(str1, ',');
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], str1);

    // Leading delimiter => leading empty string
    res = cutil::str::split(";abc", ';');
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "");
    EXPECT_EQ(res[1], "abc");

    // Trailing delimiter => trailing empty string
    res = cutil::str::split("abc;", ';');
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");

    // Repeated delimiters => repeated empty strings
    res = cutil::str::split("abc;;;def", ';');
    expected = { "abc", "", "", "def" };
    ASSERT_EQ(res.size(), expected.size());
    for (unsigned i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(expected[i], res[i]);
    }
}

TEST(Splitting, split_string_delim)
{
    std::string str1 = "asdf>=asdfgh>=asdfghjk";
    std::vector<std::string> res = cutil::str::split(str1, ">=");
    std::vector<std::string> expected = { "asdf", "asdfgh", "asdfghjk" };
    ASSERT_EQ(res.size(), expected.size()) << "Vectors are of unequal length";
    for (unsigned i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(expected[i], res[i]) << "Vectors differ at index " << i;
    }

    // Empty input => empty string
    res = cutil::str::split("", ">=");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "");

    // No matches => original string
    res = cutil::str::split(str1, "<>");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], str1);

    // Leading delimiter => leading empty string
    res = cutil::str::split(">=abc", ">=");
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "");
    EXPECT_EQ(res[1], "abc");

    // Trailing delimiter => trailing empty string
    res = cutil::str::split("abc>=", ">=");
    ASSERT_EQ(res.size(), 2);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");

    // Repeated delimiters => repeated empty strings
    res = cutil::str::split("abc>=>=>=def", ">=");
    expected = { "abc", "", "", "def" };
    ASSERT_EQ(res.size(), expected.size());
    for (unsigned i = 0; i < res.size(); ++i)
    {
        EXPECT_EQ(expected[i], res[i]);
    }
}

TEST(Splitting, split_any)
{
    std::vector<std::string> res;

    // Basic usage
    res = cutil::str::split_any("abc,def|ghi jkl", ",| ");
    ASSERT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "def");
    EXPECT_EQ(res[2], "ghi");
    EXPECT_EQ(res[3], "jkl");

    // Empty input => empty string
    ASSERT_EQ(cutil::str::split_any("", ",:")[0], "");

    // No matches => original string
    res = cutil::str::split_any("abc_123", ",; ");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "abc_123");

    // Empty delimiters => original string
    res = cutil::str::split_any("abc;def", "");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "abc;def");

    // Leading delimiters => leading empty string
    res = cutil::str::split_any(";abc", ",; ");
    ASSERT_EQ(res.size(), 2);
    ASSERT_EQ(res[0], "");
    ASSERT_EQ(res[1], "abc");

    // Trailing delimiters => trailing empty string
    res = cutil::str::split_any("abc;", ",; ");
    ASSERT_EQ(res.size(), 2);
    ASSERT_EQ(res[0], "abc");
    ASSERT_EQ(res[1], "");

    // Consecutive delimiters => repeated empty strings
    res = cutil::str::split_any("abc,;123", ",;");
    ASSERT_EQ(res.size(), 3);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "");
    EXPECT_EQ(res[2], "123");
}

TEST(Regexsplitting, regex_split)
{
    std::vector<std::string> res;

    // Basic usage
    res = cutil::str::regex_split("abc,abcd;abce.abcf?", "[,;\\.\\?]+");

    ASSERT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], "abc");
    EXPECT_EQ(res[1], "abcd");
    EXPECT_EQ(res[2], "abce");
    EXPECT_EQ(res[3], "abcf");

    // Empty input => empty string
    ASSERT_EQ(cutil::str::regex_split("", ",:")[0], "");

    // No matches => original string
    res = cutil::str::regex_split("abc_123", ",; ");
    ASSERT_EQ(res.size(), 1);
    EXPECT_EQ(res[0], "abc_123");

    // Empty delimiters => original string
    res = cutil::str::regex_split("abc;def", "");
    ASSERT_EQ(res.size(), 8);
    EXPECT_EQ(res[0], "");
    EXPECT_EQ(res[1], "a");
    EXPECT_EQ(res[2], "b");
    EXPECT_EQ(res[3], "c");
    EXPECT_EQ(res[4], ";");
    EXPECT_EQ(res[5], "d");
    EXPECT_EQ(res[6], "e");
    EXPECT_EQ(res[7], "f");

    // Leading delimiters => leading empty string
    res = cutil::str::regex_split(";abc", ",; ");
    ASSERT_EQ(res.size(), 1);
    ASSERT_EQ(res[0], ";abc");
}

TEST(Regexsplitting_map, regex_split_map)
{
    std::map<std::string, std::string> res = cutil::str::regex_split_map("[abc] name = 123; [abd] name = 123;[abe] name = 123;  ", "\\[[^\\]]+\\]");
    std::map<std::string, std::string> ans = {
        {"[abc]", "name = 123;"}, {"[abd]", "name = 123;"}, {"[abe]", "name = 123;"}
    };
    for (auto each: res) {
        ASSERT_EQ(ans.count(each.first), 1);
        if (ans.count(each.first) == 1)
        {
            auto str = each.second;
            cutil::str::trim(str);
            ASSERT_EQ(str, ans[each.first]);
        }
    }
}

TEST(SplittingVector, join)
{
    std::string str1 = "Col1;Col2;Col3";
    std::vector<std::string> tokens1 = { "Col1", "Col2", "Col3" };

    EXPECT_EQ(str1, cutil::str::join(tokens1, ";"));

    std::string str2 = "1|2|3";
    std::vector<unsigned> tokens2 = { 1, 2, 3 };

    EXPECT_EQ(str2, cutil::str::join(tokens2, "|"));
}

TEST(SplittingSet, join)
{
    std::string str1 = "Col1;Col2;Col3";
    std::set<std::string> tokens1 = { "Col1", "Col2", "Col3" };

    EXPECT_EQ(str1, cutil::str::join(tokens1, ";"));

    std::string str2 = "1|2|3";
    std::set<unsigned> tokens2 = { 1, 2, 3 };

    EXPECT_EQ(str2, cutil::str::join(tokens2, "|"));
}

TEST(SplittingDropEmptyVector, drop_empty)
{
    std::vector<std::string> tokens = { "t1", "t2", "", "t4", "" };
    cutil::str::drop_empty(tokens);
	
    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(tokens[0], "t1");
    ASSERT_EQ(tokens[1], "t2");
    ASSERT_EQ(tokens[2], "t4");
}

TEST(SplittingDropEmptyCopyVector, drop_empty_copy)
{
    std::vector<std::string> tokens = { "t1", "t2", "", "t4", "" };
    auto res = cutil::str::drop_empty_copy(tokens);
    ASSERT_EQ(res.size(), 3);
    ASSERT_EQ(res[0], "t1");
    ASSERT_EQ(res[1], "t2");
    ASSERT_EQ(res[2], "t4");
}

TEST(SplittingDropEmptySet, drop_empty)
{
    std::set<std::string> tokens = { "t1", "t2", "", "t4", ""};
    cutil::str::drop_empty_set(tokens);
    auto it = tokens.begin();

    ASSERT_EQ(tokens.size(), 3);
    ASSERT_EQ(*(  it), "t1");
    ASSERT_EQ(*(++it), "t2");
    ASSERT_EQ(*(++it), "t4");
}

TEST(SplittingDropEmptyCopySet, drop_empty_copy)
{
    std::set<std::string> tokens = { "t1", "t2", "", "t4", "" };
    auto res = cutil::str::drop_empty_set_copy(tokens);
    auto it  = res.begin();

    ASSERT_EQ(res.size(), 3);
    ASSERT_EQ(*(  it), "t1");
    ASSERT_EQ(*(++it), "t2");
    ASSERT_EQ(*(++it), "t4");
}

TEST(TestDropDuplicate, drop_duplicate)
{
    std::vector<std::string> str1 = { "t1", "t2", "", "t4", "", "t1"};
    cutil::str::drop_duplicate(str1);

    std::vector<std::string> str2 = { "", "t1", "t2", "t4"};

    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TestDropDuplicateCopy, drop_duplicate_copy)
{
    std::vector<std::string> str1 = { "t1", "t2", "", "t4", "", "t1"};
    auto str3 = cutil::str::drop_duplicate_copy(str1);
    
    std::vector<std::string> str2 = { "", "t1", "t2", "t4"};
    EXPECT_EQ(std::equal(str2.cbegin(), str2.cend(), str3.cbegin()), true);
}

/*
 * Text manipulation tests
 */

TEST(TextManip, to_lower)
{
    EXPECT_EQ("hello strutil", cutil::str::to_lower("HeLlo StRUTIL"));
}

TEST(TextManip, to_upper)
{
    EXPECT_EQ("HELLO STRUTIL", cutil::str::to_upper("HeLlo StRUTIL"));
    EXPECT_EQ("", cutil::str::to_upper(""));
}

TEST(TextManip, capitalize)
{
    EXPECT_EQ("HeLlo StRUTIL", cutil::str::capitalize("heLlo StRUTIL"));
    EXPECT_EQ("+ is an operator.", cutil::str::capitalize("+ is an operator."));
    EXPECT_EQ("", cutil::str::capitalize(""));
}

TEST(TextManip, capitalize_first_char)
{
    EXPECT_EQ("Hello strutil", cutil::str::capitalize_first_char("HeLlo StRUTIL"));
    EXPECT_EQ("+ is an operator.", cutil::str::capitalize_first_char("+ is an operator."));
    EXPECT_EQ("", cutil::str::capitalize_first_char(""));
}

TEST(TextManip, trim_left_in_place)
{
    std::string test = "   HeLlo StRUTIL";
    cutil::str::trim_left(test);

    EXPECT_EQ("HeLlo StRUTIL", test);
}

TEST(TextManip, trim_right_in_place)
{
    std::string test = "HeLlo StRUTIL    ";
    cutil::str::trim_right(test);

    EXPECT_EQ("HeLlo StRUTIL", test);
}

TEST(TextManip, trim_both_in_place)
{
    std::string test = "   HeLlo StRUTIL    ";
    cutil::str::trim(test);

    EXPECT_EQ("HeLlo StRUTIL", test);
}

TEST(TextManip, trim_left)
{
    EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_left_copy("     HeLlo StRUTIL"));
}

TEST(TextManip, trim_right)
{
    EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_right_copy("HeLlo StRUTIL       "));
}

TEST(TextManip, trim_both)
{
    EXPECT_EQ("HeLlo StRUTIL", cutil::str::trim_copy("    HeLlo StRUTIL      "));
}

TEST(TextManip, repeat)
{
    EXPECT_EQ("GoGoGoGo",   cutil::str::repeat("Go", 4));
    EXPECT_EQ("ZZZZZZZZZZ", cutil::str::repeat('Z', 10));
}

TEST(TextManip, replace_first)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_first(str1, "$name", "Jon Doe");

    EXPECT_EQ(true, res);
    EXPECT_EQ("This is Jon Doe and that is also $name.", str1);
}

TEST(TextManip, no_replace_first)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_first(str1, "$name$", "Jon Doe");

    EXPECT_EQ(false, res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_last)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_last(str1, "$name", "Jon Doe");

    EXPECT_EQ(true, res);
    EXPECT_EQ("This is $name and that is also Jon Doe.", str1);
}

TEST(TextManip, no_replace_last)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_last(str1, "$name$", "Jon Doe");

    EXPECT_EQ(false, res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_all)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_all(str1, "$name", "Jon Doe");

    EXPECT_EQ(true, res);
    EXPECT_EQ("This is Jon Doe and that is also Jon Doe.", str1);
}

TEST(TextManip, no_replace_all)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_last(str1, "$name$", "Jon Doe");

    EXPECT_EQ(false, res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextManip, replace_all_target_empty)
{
    std::string str1 = "This is $name and that is also $name.";
    bool res = cutil::str::replace_all(str1, "", "Jon Doe");

    EXPECT_EQ(false, res);
    EXPECT_EQ("This is $name and that is also $name.", str1);
}

TEST(TextSortAscending, sorting_ascending)
{
    std::vector<std::string> str1 = {"ABC", "abc", "bcd", "", "-", "  ", "123", "-100"};
    cutil::str::sorting_ascending(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};
    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextSortDescending, sorting_descending)
{
    std::vector<std::string> str1 = {"ABC", "abc", "bcd", "", "-", "  ", "123", "-100"};
    cutil::str::sorting_descending(str1);

    std::vector<std::string> str2 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};
    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextReverseInplace, reverse_inplace)
{
    std::vector<std::string> str1 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};

    cutil::str::reverse_inplace(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};

    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str2.cbegin()), true);
}

TEST(TextReverseCopy, reverse_copy)
{
    std::vector<std::string> str1 = {"bcd", "abc", "ABC", "123", "-100", "-", "  ", ""};
    std::vector<std::string> str3(str1.begin(), str1.end());

    auto str4 = cutil::str::reverse_copy(str1);

    std::vector<std::string> str2 = {"", "  ", "-", "-100", "123", "ABC", "abc", "bcd"};

    EXPECT_EQ(std::equal(str1.cbegin(), str1.cend(), str3.cbegin()), true);
    EXPECT_EQ(std::equal(str4.cbegin(), str4.cend(), str2.cbegin()), true);
}
TEST(TextReverseCopy, filename)
{
    EXPECT_EQ("a_bc123,.12", cutil::str::sanitize_filename_copy("a_bc123,.12"));
    EXPECT_EQ("abc defg", cutil::str::sanitize_filename_copy(" abc defg  ", '_'));
    EXPECT_EQ("abc defg", cutil::str::sanitize_filename_copy(" abc defg  "));
    EXPECT_EQ("abcdefg", cutil::str::sanitize_filename_copy(" a<b>:c>\\d\"e/f|g:** ? "));
    EXPECT_EQ("a_b__c__d_e_f_g___ _", cutil::str::sanitize_filename_copy(" a<b>:c>\\d\"e/f|g:** ? ", '_'));
}
