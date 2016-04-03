#pragma once

#include <string>

namespace SimpleJSON {
	namespace Type {
		class Type {
			public:
				inline virtual ~Type() {

				}

				virtual Type* clone() const=0;

				virtual std::string serialize(const std::string& prefix="") const=0;
		};

	}
}