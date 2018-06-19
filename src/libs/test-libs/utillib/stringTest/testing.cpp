/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include <string>
#include <algorithm>
#include "utillib.h"
#include "testing.h"

//------------------------------------------------------------------------
class CThisTest : public testing::Test {
public:
                 CThisTest(void) : Test() {}
    virtual void SetUp    (void) {}
    virtual void TearDown (void) {}
};

//------------------------------------------------------------------------
#ifdef NATIVE
#define strVal(a) a
#else
#define strVal(a) a.c_str()
#endif

//------------------------------------------------------------------------
TEST_F(CThisTest, TestRelational) {
    string foo = "alpha"; string_q xfoo(foo.c_str());
    string bar = "beta";  string_q xbar(bar.c_str());

    cout << "Running " << testName << "\n";
    cout << "\tc-string  -- foo:  " << foo  << " bar: " << bar << "\n";
    cout << "\tqb-string -- xfoo: " << xfoo << " xbar: " << xbar << "\n\n";

    ASSERT_NOT_EQ("c-string non-equality",        foo,  bar      );
    ASSERT_NOT_EQ("qb-string non-equality",       xfoo, xbar     );
    ASSERT_EQ    ("string equality",              foo.c_str(), xfoo);
    ASSERT_TRUE  ("c-string less than",           (foo < bar)    );
    ASSERT_TRUE  ("qb-string less than",          (xfoo < xbar)  );
    ASSERT_FALSE ("c-string greater than",        (foo > bar)    );
    ASSERT_FALSE ("qb-string greater than",       (xfoo > xbar)  );
    ASSERT_TRUE  ("c-string less than or eq",     (foo <= bar)   );
    ASSERT_TRUE  ("qb-string less than or eq",    (xfoo <= xbar) );
    ASSERT_FALSE ("c-string greater than or eq",  (foo >= bar)   );
    ASSERT_FALSE ("qb-string greater than or eq", (xfoo >= xbar) );
    ASSERT_FALSE ("c-string min",                 (min(foo, bar) == bar) );
    ASSERT_TRUE  ("c-string max",                 (max(foo, bar) == bar) );
    ASSERT_FALSE ("qb-string min",                (min(xfoo, xbar) == xbar) );
    ASSERT_TRUE  ("qb-string max",                (max(xfoo, xbar) == xbar) );

    return true;
}}

//------------------------------------------------------------------------
TEST_F(CThisTest, TestCompare) {
    string str1("green apple"); string_q xstr1("green apple");
    string str2("red apple");   string_q xstr2("red apple");

    cout << "Running " << testName << "\n";
    cout << "\tc-string  -- str1:  " <<  str1  << " str2: "  << str2  << "\n";
    cout << "\tqb-string -- xstr1: " << xstr1 << " xstr2: " << xstr2 << "\n\n";

    ASSERT_NOT_EQ("c-string compare",             str1.compare( str2 ), 0);
    ASSERT_NOT_EQ("qb-string compare",           xstr1.compare( xstr2), 0);
    ASSERT_NOT_EQ("c-string compare",             str1.compare( str2 ), 0);
    ASSERT_NOT_EQ("qb-string compare",           xstr1.compare( xstr2), 0);
    ASSERT_EQ    ("c-string partial compare",     str1.compare( 6, 5,"apple"),  0);
    ASSERT_EQ    ("qb-string partial compare",   xstr1.compare( 6, 5,"apple"),  0);
    ASSERT_EQ    ("c-string partial compare 2",   str2.compare( str2.size()-5,  5, "apple"), 0);
    ASSERT_EQ    ("qb-string partial compare 2", xstr2.compare( str2.size()-5,  5, "apple"), 0);
    ASSERT_EQ    ("c-string double partial",      str1.compare( 6, 5,  str2, 4, 5), 0);
    ASSERT_EQ    ("qb-string double partial",    xstr1.compare( 6, 5, xstr2, 4, 5), 0);

    return true;
}}

//------------------------------------------------------------------------
TEST_F(CThisTest, TestAssignment) {
    string str1("Test string: "), str2, str3;
    string_q xstr1("Test string: "), xstr2, xstr3;

    str2 = 'x';
    xstr2 = 'x';

     str3 =  str1 +  str2;
    xstr3 = xstr1 + xstr2;

    cout << "Running " << testName << "\n";

    ASSERT_TRUE("c-string set1",   str1 == "Test string: ");
    ASSERT_TRUE("qb-string set1", xstr1 == "Test string: ");
    ASSERT_TRUE("c-string set2",   str2 == "x");
    ASSERT_TRUE("qb-string set2", xstr2 == "x");
    ASSERT_TRUE("c-string set3",   str3 == "Test string: x");
    ASSERT_TRUE("qb-string set3", xstr3 == "Test string: x");
    ASSERT_TRUE("set1 equal",      str1 == strVal(xstr1));
    ASSERT_TRUE("set2 equal",      str2 == strVal(xstr2));
    ASSERT_TRUE("set3 equal",      str3 == strVal(xstr3));
    return true;
}}

//------------------------------------------------------------------------
TEST_F(CThisTest, TestCStr) {

    cout << "Running " << testName << "\n";

    char str[] = "Please split this sentence into tokens";
    char *token;
    char *rest = str;
    while ((token = strtok_r(rest, " ", &rest)))
        cout << TESTID("tokenize",15) << padRight(token,8,' ') << "\t" << (rest ? rest : "") << "\n";
    cout << "\n";

    string_q str1 = "Please|split|that|sentence|into|tokens";
    while (!str1.empty())
        cout << TESTID("nextTokClr",15) << padRight(nextTokenClear(str1,'|'),8,' ') << "\t" << str1 << "\n";
    cout << "\n";

    string_q text1 = "This isthe_thing\tthat matters\tand is_upperCase lower case";
    cout << TESTID("base case",15) << text1 << "\n";
    cout << TESTID("toLower",15) << toLower(text1) << "\n";
    cout << TESTID("toUpper",15) << toUpper(text1) << "\n";
    cout << TESTID("toProper",15) << toProper(text1) << "\n";
    cout << "\n";

    string_q text2 = "This isthe_thing\tthat matters\tand is_upperCase lower case";
    cout << TESTID("base case",15) << text2 << "\n";
    cout << TESTID("toLower",15) << toLower(text2) << "\n";
    cout << TESTID("toUpper",15) << toUpper(text2) << "\n";
    cout << TESTID("toProper",15) << toProper(text2) << "\n";
    cout << "\n";

    string_q strip1 = " tab[\t]AxBBBxBxA tab:\t";
    cout << TESTID("base case",15)   << "|" << strip1 << "|\n";
    cout << TESTID("trim",15)        << "|" << trim(strip1) << "|\n";
    cout << TESTID("trim lead",15)   << "|" << trimLeading(strip1) << "|\n";
    cout << TESTID("trim tail",15)   << "|" << trimTrailing(strip1, '\t') << "|\n";
    cout << TESTID("trim ws",15)     << "|" << trimWhitespace(strip1) << "|\n";
    cout << TESTID("trim ws ext",15) << "|" << trimWhitespace(strip1, "tab:[]") << "|\n";
    cout << "\n";

    string_q strip2 = " tab[\t]AxBBBxBxA tab:\t";
    cout << TESTID("base case",15)   << "|" << strip2 << "|\n";
    cout << TESTID("trim",15)        << "|" << trim(strip2) << "|\n";
    cout << TESTID("trim lead",15)   << "|" << trimLeading(strip2) << "|\n";
    cout << TESTID("trim tail",15)   << "|" << trimTrailing(strip2, '\t') << "|\n";
    cout << TESTID("trim ws",15)     << "|" << trimWhitespace(strip2) << "|\n";
    cout << TESTID("trim ws ext",15) << "|" << trimWhitespace(strip2, "tab:[]") << "|\n";
    cout << "\n";

    cout << TESTID("countOf",15) << "There are " << countOf(strip2, 'B') << " 'Bs' in '|" << strip2 << "|'\n";
    cout << TESTID("countOf",15) << "There are " << countOf(text2,  'i') << " 'is' in '" << substitute(text1, "\t"," ") << "'\n";
    cout << "\n";

    string_q thing = "This is the thing";
    cout << TESTID("base case",15)      << thing << "\n";
    cout << TESTID("find is",15)        << thing.find("is") << "\n";
    cout << TESTID("contains is",15)    << contains(thing, "is") << "\n";
    cout << TESTID("find not this",15)  << thing.find("ThiNG") << "\n";
    cout << TESTID("not there this",15) << contains(thing, "ThiNG") << "\n";
//    cout << TESTID("findI not this",15) << thing.findI("ThiNG") << "\n";
    cout << TESTID("there this",15)     << containsI(thing, "ThiNG") << "\n";
    cout << "\n";

    string_q target = "Target1|Target2|Target3|Target4";
    cout << TESTID("base case",15) << target << "\n";
    while (target.find("get") != string::npos) {
        replaceReverse(target, "get", "tan");
        cout << TESTID("rev replace",15) << target << "\n";
    }
    cout << "\n";

    string_q target1 = "Target1|Target2|Target3|Target4";
    cout << TESTID("base case",15) << target1 << "\n";
    replaceAny(target1, "get", "XXX");
    cout << TESTID("rep any",15) << target1 << "\n";
    replaceAny(target1, "|", " |  ");
    cout << TESTID("rep any",15) << target1 << "\n";
    replaceAny(target1, " ", "-");
    cout << TESTID("rep any",15) << target1 << "\n";
    replaceAll(target1, "X", "");
    replaceAny(target1, " -", "");
    cout << TESTID("rep any",15) << target1 << "\n";
    cout << "\n";

    string_q revTarget = ".desrever gnirts eht si sihT";  cout << TESTID("base case",15) << revTarget << "\n";
    reverse(revTarget);                                   cout << TESTID("reversed", 15) << revTarget << "\n";
    cout << "\n";

    string_q target3 = "Target1|Target2|Target3|Target4"; cout << TESTID("base case",15) << target3 << "\n";
    replace(target3, "Target1", "");                   cout << TESTID("replace",15)   << target3 << "\n";
    replace(target3, "Target2", "");                   cout << TESTID("replace",15)   << target3 << "\n";
    replace(target3, "Target3", "");                   cout << TESTID("replace",15)   << target3 << "\n";
    replace(target3, "Target4", "");                   cout << TESTID("replace",15)   << target3 << "\n";
    cout << "\n";

    string es1;
    ASSERT_TRUE("es1 is empty", es1.empty())
    ASSERT_TRUE("es1 == \"\"", es1 == "");
    ASSERT_TRUE("es1 == EMPTY", es1 == strVal(EMPTY));
    ASSERT_TRUE("es1 == nullStr", es1 == nullStr);

    string_q es2;
    ASSERT_TRUE("es2 is empty", es2.empty())
    ASSERT_TRUE("es2 == \"\"", es2 == "");
    ASSERT_TRUE("es2 == EMPTY", es2 == EMPTY);
    ASSERT_TRUE("es2 == nullStr", es2 == nullStr);

    return true;
}}

#include "options.h"
//------------------------------------------------------------------------
int main(int argc, const char *argv[]) {

    COptions options;
    if (!options.prepareArguments(argc, argv))
        return 0;

    while (!options.commandList.empty()) {
        string_q command = nextTokenClear(options.commandList, '\n');
        if (!options.parseArguments(command))
            return 0;

        switch (options.testNum) {
            case 0: LOAD_TEST(TestRelational); break;
            case 1: LOAD_TEST(TestCompare);    break;
            case 2: LOAD_TEST(TestAssignment); break;
            case 3: LOAD_TEST(TestCStr);       break;
        }
    }

    return RUN_ALL_TESTS();
}
