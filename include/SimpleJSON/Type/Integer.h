#pragma once

#include "Type.h"

#include <string>

namespace SimpleJSON {
	namespace Type {

		class Integer : public Type {
			public:
				Integer(const int &number=0.0): num(number) {

				}

				virtual std::string serialize(const std::string& prefix="") const override {
					return prefix+std::to_string(num);
				}

				virtual Integer* clone() const override {
					return new Integer(num);
				}

				operator int() const {
					return num;
				}

				operator int&() {
					return num;
				}
			private:
				int num;
		};

	}

	template<>
	std::unique_ptr<Type::Type> Value::toValue< >(const int &r) {
		return std::unique_ptr<Type::Integer>(new Type::Integer(r));
	}

	template <>
	int& Value::as<int>() {
		return *dynamic_cast<Type::Integer*>(value);
	}

}