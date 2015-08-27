//
// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// name, member(type, name)
// N * 2 + 1
#define STRUCT(NAME, ...) \
struct NAME \
{ \
	STRUCT_MEMBERS(__VA_ARGS__) \
}; \

#define GET_STRUCT_MEMBERS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, MACRO, ...) MACRO
#define STRUCT_MEMBERS(...) GET_STRUCT_MEMBERS(__VA_ARGS__, \
	STRUCT_MEMBERS10, \
	STRUCT_MEMBERS9, \
	STRUCT_MEMBERS8, \
	STRUCT_MEMBERS7, \
	STRUCT_MEMBERS6, \
	STRUCT_MEMBERS5, \
	STRUCT_MEMBERS4, \
	STRUCT_MEMBERS3, \
	STRUCT_MEMBERS2 )(__VA_ARGS__)

#define STRUCT_MEMBERS10(TYPE, NAME, ...) \
	STRUCT_MEMBERS2(TYPE, NAME) STRUCT_MEMBERS8(__VA_ARGS__)
#define STRUCT_MEMBERS8(TYPE, NAME, ...) \
	STRUCT_MEMBERS2(TYPE, NAME) STRUCT_MEMBERS6(__VA_ARGS__)
#define STRUCT_MEMBERS6(TYPE, NAME, ...) \
	STRUCT_MEMBERS2(TYPE, NAME) STRUCT_MEMBERS4(__VA_ARGS__)
#define STRUCT_MEMBERS4(TYPE, NAME, ...) \
	STRUCT_MEMBERS2(TYPE, NAME) STRUCT_MEMBERS2(__VA_ARGS__)
#define STRUCT_MEMBERS2(TYPE, NAME) TYPE NAME;
	
STRUCT(Account, 
		int, age,
		int, sum,
		int, average,
		std::string, nameFirst,
		std::string, nameLast )
