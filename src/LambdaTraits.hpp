//
// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef NBDL_LAMBDA_TRAITS_HPP
#define NBDL_LAMBDA_TRAITS_HPP

#include<tuple>

namespace nbdl {

template<typename T>
struct LambdaTraits
{
	using Traits = LambdaTraits<decltype(&T::operator())>;
	using ReturnType = typename Traits::ReturnType;

	template<std::size_t i>
	using Arg = typename Traits::template Arg<i>;

	static const std::size_t arity = Traits::arity;
};
template<typename ClassType, typename Return, typename... Args>
struct LambdaTraits<Return(ClassType::*)(Args...) const>
{
	using ReturnType = Return;

	template<std::size_t i>
	using Arg = typename std::tuple_element<i, std::tuple<Args...>>::type;

	static const std::size_t arity = sizeof...(Args);
};

}//nbdl

#endif
