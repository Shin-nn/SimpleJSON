#pragma once

#include "../Value.h"

namespace SimpleJSON {
	namespace Type {

		class Object : public Type {
			public:
				inline Object() : map() {

				}

				inline Object(std::initializer_list<std::pair<std::string const, Value>> list) : map() {
					for(const auto&it :list) {
						map.insert(it);
					}
				}

				inline virtual std::string serialize(const std::string& prefix="") const override {
					std::string serialized="";
					for(auto it :map) {
						serialized+=(serialized.length() > 0? ", \"" : "\"")+it.first+ "\" : " +it.second.serialize();
					}
					return prefix+"{"+serialized+"}";
				}

				inline virtual Object* clone() const override {
					return new Object(*this);
				}

				inline auto find(const std::string &key) const {
					return map.find(key);
				}

				template <typename T>
				inline SimpleJSON::Value& operator[](T a) {
					return map[a];
				}

				template <typename T>
				inline const SimpleJSON::Value& operator[](T a) const {
					return map.find(a)->second;
				}

				inline auto end() const {
					return map.end();
				}
			private:
				std::map<std::string,SimpleJSON::Value> map;
		};

	}
}