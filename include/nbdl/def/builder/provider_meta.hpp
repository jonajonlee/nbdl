//
// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef NBDL_DEF_PROVIDER_META_HPP
#define NBDL_DEF_PROVIDER_META_HPP

#include <mpdef/list.hpp>
#include <mpdef/MPDEF_METASTRUCT.hpp>

#include <boost/hana.hpp>

namespace nbdl_def {
namespace builder {

namespace hana = boost::hana;

MPDEF_METASTRUCT(
  provider_meta
  , provider
  , name
  , access_points
);

}//builder
}//nbdl_def
#endif
