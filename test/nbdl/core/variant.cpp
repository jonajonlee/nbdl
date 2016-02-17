//
// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include<Variant.hpp>

#include<catch.hpp>
#include<string>

struct SomeTag {};

TEST_CASE("Unitialized variant should match Unresolved.", "[variant]") 
{
	using Number = nbdl::Variant<int, std::string, SomeTag>;
	Number number;
	CHECK(number.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](std::string) {
			return 1;
		},
		[](int value) {
			return value;
		},
		[](SomeTag) {
			return 3;
		}) == 56);
}

TEST_CASE("Assign a value to a variant and use the callback interface to retrieve it.", "[variant]") 
{
	using Number = nbdl::Variant<int, std::string, SomeTag>;
	
	Number number = 512;
	CHECK(number.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](std::string) {
			return 1;
		},
		[](int value) {
			return value;
		},
		[](SomeTag) {
			return 3;
		}) == 512);
}

TEST_CASE("Copy a variant value.", "[variant]") 
{
	using Number = nbdl::Variant<int, SomeTag>;
	Number number1, number2;
	number1 = 123;
	number2 = Number(number1);
	CHECK(number2.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](std::string) {
			return 1;
		},
		[](int value) {
			return value;
		},
		[](SomeTag) {
			return 3;
		}) == 123);
}

TEST_CASE("Use the catch all to catch an unspecified tag", "[variant]")
{
	using Number = nbdl::Variant<int, std::string, SomeTag>;
	
	Number number = 185;
	CHECK(number.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](std::string) {
			return 1;
		},
		[](SomeTag) {
			return 3;
		},
		[](auto) {
			return 123;
		}) == 123);
	number = 93;
	CHECK(number.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](std::string) {
			return 1;
		},
		//not last position
		[](auto) {
			return 25;
		},
		[](SomeTag) {
			return 9;
		}) == 25);
}
TEST_CASE("Catch should not be called if there is a valid match.", "[variant]")
{
	using Number = nbdl::Variant<int, std::string, SomeTag>;
	Number number = 185;

	CHECK(number.match(
		[](nbdl::Unresolved) {
			return 56;
		},
		[](int) {
			return 76;
		},
		[](auto) {
			return 25;
		}) == 76);
}

//todo perhaps a matchRef function could allow mutable values in variants
TEST_CASE("Modify a struct's member in a variant", "[variant]")
{
	struct Person {
		std::string name_first;
		std::string name_last;
	};
	using MyVar = nbdl::Variant<Person, int, std::string, SomeTag>;
	
	MyVar var = Person { "Jason", "Rice" };
	var.match(
		[&](Person person) {
			person.name_last = "Ricez";
			var = person;
		}, nbdl::noop);
	bool proof = var.match(
		[](Person person) {
			CHECK(person.name_last == "Ricez");
			return true;
		},
		[](auto) {
			return false;
		});
	CHECK(proof);
}