#pragma once

#include <SimpleJSON/Type/Boolean.h>
#include <SimpleJSON/Type/Integer.h>
#include <SimpleJSON/Type/Number.h>
#include <SimpleJSON/Type/Object.h>
#include <SimpleJSON/Type/String.h>
#include <SimpleJSON/Type/Array.h>
#include <SimpleJSON/Value.h>

#include <string>
#include <memory>

namespace SimpleJSON {
	inline std::unique_ptr<Value> parse(const std::string &) {
		return std::unique_ptr<Value>(nullptr);//new Value(Type::Object()));
	}
}
