#pragma once

#include "Type.h"
#include "../Value.h"

#include <string>

namespace SimpleJSON {
	namespace Type {

		class Boolean : public Type {
			public:
				Boolean(const bool &val=false): value(val) {

				}

				virtual std::string serialize(const std::string& prefix="") const override {
					return prefix+std::to_string(value);
				}

				virtual Boolean* clone() const override {
					return new Boolean(value);
				}

				operator bool() const {
					return value;
				}

				operator bool&() {
					return value;
				}
			private:
				bool value;
		};

	}

	template<>
	inline std::unique_ptr<Type::Type> Value::toValue<bool>(const bool &r) {
		return std::unique_ptr<Type::Boolean>(new Type::Boolean(r));
	}

	template <>
	inline bool& Value::as<bool>() {
		return *dynamic_cast<Type::Boolean*>(value);
	}

}