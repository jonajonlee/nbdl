//
// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef NBDL_MEMBER_NAMES

#include "VFUNC.hpp"

#define NBDL_MEMBER_NAMES(...) VFUNC(NBDL_MEMBER_NAMES, __VA_ARGS__)

#define NBDL_MEMBER_NAMES63(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
 NBDL_MEMBER_NAMES62(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES62(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES61(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES61(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES60(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES60(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES59(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES59(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES58(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES58(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES57(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES57(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES56(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES56(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES55(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES55(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES54(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES54(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES53(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES53(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES52(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES52(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES51(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES51(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES50(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES50(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES49(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES49(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES48(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES48(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES47(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES47(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES46(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES46(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES45(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES45(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES44(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES44(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES43(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES43(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES42(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES42(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES41(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES41(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES40(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES40(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES39(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES39(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES38(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES38(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES37(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES37(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES36(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES36(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES35(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES35(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES34(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES34(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES33(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES33(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES32(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES32(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES31(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES31(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES30(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES30(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES29(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES29(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES28(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES28(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES27(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES27(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES26(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES26(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES25(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES25(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES24(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES24(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES23(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES23(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES22(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES22(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES21(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES21(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES20(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES20(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES19(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES19(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES18(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES18(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES17(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES17(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES16(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES16(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES15(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES15(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES14(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES14(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES13(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES13(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES12(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES12(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES11(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES11(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES10(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES10(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES9(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES9(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES8(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES8(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES7(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES7(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES6(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES6(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES5(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES5(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES4(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES4(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES3(NAME, __VA_ARGS__)
#define NBDL_MEMBER_NAMES3(NAME, MNAME, ...) NBDL_MEMBER_NAMES2(NAME, MNAME) \
	 NBDL_MEMBER_NAMES2(NAME, __VA_ARGS__)

#define NBDL_MEMBER_NAMES2(NAME, MNAME) NBDL_MEMBER_NAME(NAME, MNAME);

#endif
