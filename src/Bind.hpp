#ifndef NBDL_BIND_HPP
#define NBDL_BIND_HPP

#include<type_traits>
#include "EntityTraits.hpp"
#include "MemberSet.hpp"

namespace nbdl {

namespace detail {

template<class Binder, class = void>
struct IsGnosticBinder : std::false_type {};

template<class Binder>
struct IsGnosticBinder<Binder, 
	typename Void<typename Binder::GnosticBinder>::type>
	: std::true_type {};

template<typename Binder, typename M, typename Enable = void>
struct BindMemberHelperGnostic
{
	static void call(Binder &binder, typename M::OwnerType &owner)
	{
		binder.template bindMember<M>(owner);
	}
};
template<typename Binder, typename M>
struct BindMemberHelperGnostic<Binder, M,
	typename std::enable_if<IsEntity<typename M::MemberType>::value>::type>
{
	static void call(Binder &binder, typename M::OwnerType &owner)
	{
		binder.template bindEntity<M>(owner);
	}
};

template<typename Binder, typename M, typename Enable = void>
struct BindMemberHelperAgnostic
{
	template<typename NameFormat>
	static void call(Binder &binder, typename M::OwnerType &owner, NameFormat)
	{
		binder.bindMember(MemberName<NameFormat, M>::value, owner.*M::ptr);
	}
};
template<typename Binder, typename M>
struct BindMemberHelperAgnostic<Binder, M,
	typename std::enable_if<IsEntity<typename M::MemberType>::value>::type>
{
	template<typename NameFormat>
	static void call(Binder &binder, typename M::OwnerType &owner, NameFormat)
	{
		binder.bindEntity(MemberName<NameFormat, M>::value, [&owner](Binder &binder) {
			bind(binder, owner.*M::ptr, NameFormat{});
		});
	}
};

template<typename M, typename Binder, class = void>
struct BindMember
{
	template<typename NameFormat>
	static void call(Binder &binder, typename M::OwnerType &owner, NameFormat)
	{
		BindMemberHelperAgnostic<Binder, M>::call(binder, owner, NameFormat{});
	}
};

template<typename M, typename Binder>
struct BindMember<M, Binder, 
	typename std::enable_if<IsGnosticBinder<Binder>::value>::type>
{
	template<typename NameFormat>
	static void call(Binder &binder, typename M::OwnerType &owner, NameFormat)
	{
		BindMemberHelperGnostic<Binder, M>::call(binder, owner);
	}
};

template<typename NameFormat, typename Binder, typename Entity, typename Mset, class = void>
struct BindMembers
{
	static void call(Binder &binder, typename Mset::Member::OwnerType &owner)
	{
		BindMember<typename Mset::Member, Binder>::call(binder, owner, NameFormat{});	
		BindMembers<NameFormat, Binder, Entity, typename Mset::Next>::call(binder, owner);
	}
};
template<typename NameFormat, typename Binder, typename Entity, typename Mset>
struct BindMembers<NameFormat, Binder, Entity, Mset, 
	typename std::enable_if<MemberSetIsLast<Mset>::value>::type>
{
	static void call(Binder &binder, Entity &owner) {}
};

}//detail

template<typename NameFormat, typename Binder, typename Entity>
void bind(Binder &binder, Entity &entity, NameFormat)
{
	detail::BindMembers<NameFormat, Binder, Entity, typename EntityTraits<Entity>::Members>::call(binder, entity);
}

template<typename Binder, typename Entity>
void bind(Binder &binder, Entity &entity)
{
	bind(binder, entity, DefaultNameFormat{});
}

}//nbdl
#endif