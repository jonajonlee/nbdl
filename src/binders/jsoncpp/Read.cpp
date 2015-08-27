//
// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include<stdexcept>
#include "Read.hpp"

namespace nbdl {
namespace binders {
namespace jsoncpp {

Read::Read(const Json::Value &value) :
	jsonVal(value)
{
	if (!jsonVal.isObject())
		throw std::runtime_error("JSON Object expected");
}

void Read::bind(const std::string name, bool &field)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isBool())
		throw std::runtime_error("JSON Boolean expected");
	field = obj.asBool();
}

void Read::bind(const std::string name, unsigned int &field)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isIntegral())
		throw std::runtime_error("JSON Integral expected");
	field = obj.asUInt();
}

void Read::bind(const std::string name, int &field)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isIntegral())
		throw std::runtime_error("JSON Integral expected");
	field = obj.asInt();
}

void Read::bind(const std::string name, double &field)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isNumeric())
		throw std::runtime_error("JSON Number expected");
	field = obj.asDouble();
}

void Read::bind(const std::string name, std::string &field)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isString())
		throw std::runtime_error("JSON String expected");
	field = obj.asString();
}

Read Read::createObjectReader(const std::string name)
{
	const Json::Value &obj = jsonVal[name];
	if (!obj.isObject())
		throw std::runtime_error("JSON Object expected");
	return Read(obj);
}

/* i'm getting rid of 'lists' for now but will need this code
void Read::bind(const std::string name, EntityListBase &list)
{
	const Json::Value &array = jsonVal[name];
	if (!array.isArray())
		throw std::runtime_error("JSON Array expected");
	list.initWithSize(array.size());
	int listSize = list.size();
	int i = 0;
	for (auto &obj : array)
	{
		Read reader(obj);
		list.getRef(i++).bindMembers(reader);
		if (i >= listSize)
			break;
	}
}
*/

}//jsoncpp
}//binders
}//nbdl
