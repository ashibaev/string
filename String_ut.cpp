#include "test_framework.h"

#include "String.h"

#include <sstream>

TEST_SUITE(StringTests) {
	TEST(EmptyConstructor) {
		String string;

		ASSERT_EQUAL(string.Size(), (size_t)0);
	}

	TEST(CStringConstructor) {
		String string("abc");

		ASSERT_EQUAL(string.Size(), (size_t)3);
		ASSERT_EQUAL(string[0], 'a');
		ASSERT_EQUAL(string[1], 'b');
		ASSERT_EQUAL(string[2], 'c');
	}

	TEST(CopyConstruct) {
		String first("abc");
		String second(first);

		ASSERT_EQUAL(first.Size(), second.Size());
		for (size_t i = 0; i < first.Size(); ++i) {
			ASSERT_EQUAL(first[i], second[i]);
		}

		first[0] = 'd';
		ASSERT_EQUAL(first[0], 'd');
		ASSERT_EQUAL(second[0], 'a');
	}

	TEST(MoveConstructor) {
		String string(std::move(String("abc")));

		ASSERT_EQUAL(string.Size(), (size_t)3);
		ASSERT_EQUAL(string[0], 'a');
		ASSERT_EQUAL(string[1], 'b');
		ASSERT_EQUAL(string[2], 'c');
	}

	TEST(AssignmentOperator) {
		String first;

		{
			first = "a";
			ASSERT_EQUAL(first.Size(), (size_t)1);
			ASSERT_EQUAL(first[0], 'a');
		}
		{
			String second("bc");
			first = second;
			ASSERT_EQUAL(first.Size(), (size_t)2);
			ASSERT_EQUAL(first[0], 'b');
			ASSERT_EQUAL(first[1], 'c');
		}
		{
			String second("def");
			first = std::move(second);
			ASSERT_EQUAL(first.Size(), (size_t)3);
			ASSERT_EQUAL(first[0], 'd');
			ASSERT_EQUAL(first[1], 'e');
			ASSERT_EQUAL(first[2], 'f');
		}
		{
			String second = first = "a";

			ASSERT_EQUAL(first.Size(), (size_t)1);
			ASSERT_EQUAL(first[0], 'a');

			ASSERT_EQUAL(second.Size(), (size_t)1);
			ASSERT_EQUAL(second[0], 'a');
		}
	}

	TEST(SelfAssignment) {
		{
			String first("a");
			first = first;

			ASSERT_EQUAL(first.Size(), (size_t)1);
			ASSERT_EQUAL(first[0], 'a');
		}
		{
			String first("a");
			first = std::move(first);

			ASSERT_EQUAL(first.Size(), (size_t)1);
			ASSERT_EQUAL(first[0], 'a');
		}
	}

	TEST(Clear) {
		String first("abc");
		first.Clear();
		ASSERT_EQUAL(first.Size(), (size_t)0);
	}

	TEST(Empty) {
		ASSERT_THAT(String().Empty());
		ASSERT_THAT_NOT(String("abc").Empty());
	}

	TEST(AppendChar) {
		String string("ab");
		
		string += 'c';

		ASSERT_EQUAL(string.Size(), (size_t)3);
		ASSERT_EQUAL(string[0], 'a');
		ASSERT_EQUAL(string[1], 'b');
		ASSERT_EQUAL(string[2], 'c');
	}

	TEST(AppendString) {
		String string("a");

		string += String("bc");

		ASSERT_EQUAL(string.Size(), (size_t)3);
		ASSERT_EQUAL(string[0], 'a');
		ASSERT_EQUAL(string[1], 'b');
		ASSERT_EQUAL(string[2], 'c');
	}

	TEST(AppendCString) {
		String string("a");

		string += "bc";
		ASSERT_EQUAL(string.Size(), (size_t)3);
		ASSERT_EQUAL(string[0], 'a');
		ASSERT_EQUAL(string[1], 'b');
		ASSERT_EQUAL(string[2], 'c');
	}

	TEST(LongString) {
		String string;
		size_t length = (size_t) 1e4;
		
		for (size_t i = 0; i < length; ++i) {
			string += 'a';
		}

		ASSERT_EQUAL(string.Size(), length);
		for (const auto& c : string) {
			ASSERT_EQUAL(c, 'a');
		}
	}

	TEST(SelfAdding) {
		{
			String string("a");
			string += string;

			ASSERT_EQUAL(string.Size(), (size_t)2);
			ASSERT_EQUAL(string[0], 'a');
			ASSERT_EQUAL(string[1], 'a');
		}
		{
			String string("aaaaaaaaaa"); // size is 10
			string += string;

			ASSERT_EQUAL(string.Size(), (size_t)20);
			for (const auto& c : string) {
				ASSERT_EQUAL(c, 'a');
			}
		}
	}

	TEST(EqualityOperator) {
		ASSERT_THAT(String("abc") == String("abc"));
		ASSERT_THAT(String("abc") != String("abcd"));
		ASSERT_THAT(String("abc") != String("ab"));
	}

	TEST(ReadStrings) {
		std::stringstream ss("abc def\n");
		String a, b;
		ss >> a >> b;

		ASSERT_EQUAL(a, String("abc"));
		ASSERT_EQUAL(b, String("def"));
	}

	TEST(WriteString) {
		std::stringstream ss;
		String a("abc");
		ss << a;

		ASSERT_EQUAL(ss.str(), std::string("abc"));
	}

	TEST(AddStrings) {
		{
			String a("ab");
			String b("cd");
			String c = a + b;
			ASSERT_EQUAL(c, String("abcd"));
		}
		{
			String a("ab");
			String b("cd");
			String c = std::move(a) + b;
			ASSERT_EQUAL(c, String("abcd"));
		}
	}
}