#pragma once

#include "Type.h"

#include <string>

namespace SimpleJSON {
	namespace Type {

		class Number : public Type {
			public:
				Number(const double &number=0.0): num(number) {

				}

				virtual std::string serialize(const std::string& prefix="") const override {
					return prefix+std::to_string(num);
				}

				virtual Number* clone() const override {
					return new Number(num);
				}

				operator double () const noexcept {
					return num;
				}

				operator double& () noexcept {
					return num;
				}

			private:
				double num;
		};

	}

	template<>
	std::unique_ptr<Type::Type> Value::toValue<double>(const double &r) {
		return std::unique_ptr<Type::Number>(new Type::Number(r));
	}

	template<>
	std::unique_ptr<Type::Type> Value::toValue<float>(const float &r) {
		return std::unique_ptr<Type::Number>(new Type::Number(r));
	}

	template <>
	double& Value::as<double>() {
		return *dynamic_cast<Type::Number*>(value);
	}
}