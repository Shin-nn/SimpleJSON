#pragma once

#include "Type.h"
#include "Number.h"
#include "Integer.h"

#include "../Value.h"

#include <string>

namespace SimpleJSON {
	namespace Type {

		class String : public Type {
			public:
				inline String(const std::string &string_=""): string(string_) {
				}

				inline String(const Number &number): string(std::to_string(number)) {
				}

				inline String(const Integer &number): string(std::to_string(number)) {
				}

				inline virtual std::string serialize(const std::string& prefix="") const override {
					return prefix+"\""+string+"\"";
				}

				inline virtual String* clone() const override {
					return new String(string);
				}

				inline operator const std::string& () const {
					return string;
				}

				inline operator std::string& () {
					return string;
				}

				bool operator==(const String &r) {
					return string == r.string;
				}
			private:
				std::string string;
		};

		inline bool operator==(const String &l, const std::string &r) {
			return l.operator const std::string&()==r;
		}

		inline bool operator==(const String &l, const char *r) {
			return l==std::string(r);
		}
	}

	template<>
	std::unique_ptr<Type::Type> Value::toValue<std::string>(const std::string &r) {
		return std::unique_ptr<Type::String>(new Type::String(r));
	}


/*	template<>
	std::unique_ptr<Type::Type> Value::toValue<char const*>(char const* &r) {
		return std::unique_ptr<Type::String>(new Type::String(r));
	}
*/
	template<>
	std::string& Value::as<std::string>() {
		return *dynamic_cast<Type::String*>(value);
	}
}