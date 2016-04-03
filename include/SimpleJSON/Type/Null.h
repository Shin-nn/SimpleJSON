#pragma once

#include "Type.h"

namespace SimpleJSON {
	namespace Type {

		class Null : public Type {
			public:
				inline Null() {

				}

				inline virtual Null* clone() const override {
					return new Null();
				}

				inline virtual std::string serialize(const std::string& prefix="") const override {
					return prefix+"null";
				}
		};

	}
}