#pragma once

#include "../Value.h"

#include <vector>

namespace SimpleJSON {
	namespace Type {

		class Array : public Type {
			public:
				inline Array() : array() {

				}

				inline Array(const std::initializer_list<SimpleJSON::Value> &list) : array(list) {

				}

				template<typename T>
				inline Array(const std::vector<T> &arr) : array(arr.begin(),arr.end()) {

				}

				inline virtual std::string serialize(const std::string& prefix="") const override {
					std::string serialized="";
					for(std::size_t i=0;i<array.size();i++) {
						serialized+=(serialized.length() > 0? ", \"" : "\"")+ std::to_string(i) + "\" : " +array[i].serialize();
					}
					return prefix+"["+serialized+"]";
				}

				inline virtual Array* clone() const override {
					return new Array(array);
				}

				inline SimpleJSON::Value& operator[](std::size_t index) noexcept {
					return array[index];
				}

				inline const SimpleJSON::Value& operator[](std::size_t index) const noexcept {
					return array[index];
				}

			private:
				std::vector<SimpleJSON::Value> array;
		};

	}
}