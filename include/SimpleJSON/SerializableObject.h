#pragma once

#include <SimpleJSON.h>

#include <sstream>

namespace SimpleJSON {
	class SerializableObject {
		public:

			inline virtual ~SerializableObject() {
			}

			virtual SimpleJSON::Type::Object serialize() const = 0;

			inline virtual std::string stringify() const final;
	};

	inline static std::ostream& operator<<(std::ostream& stream, const SerializableObject &object) {
		//const SimpleJSON::Type::Object obj=object.serialize();
		//stream << obj.serialize();

		return stream;
	}
}

std::string SimpleJSON::SerializableObject::stringify() const{
	std::ostringstream s;
	operator<<(s,*this);
	return s.str();
}