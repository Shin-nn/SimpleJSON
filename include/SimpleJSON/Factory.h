#pragma once

#include <SimpleJSON.h>

#include <memory>
#include <functional>
#include <iostream>

#define SIMPLEJSON_REGISTER(FACTORY,NAME,FUNCTION) private: static const bool __SIMPLE_JSON_REGISTERED;

#define SIMPLEJSON_REGISTER_FINISH(FACTORY,NAME,FUNCTION) const bool NAME::__SIMPLE_JSON_REGISTERED = FACTORY::registerCreator( #NAME ,FUNCTION);

namespace SimpleJSON {

	template <typename T, bool DEBUG = false>
	/**
	 * @brief Factory for creating objects
	 */
	class Factory {
		public:

			class Exception : public std::exception {
				public:
					Exception(const std::string& what) : what_(what) {

					}
					virtual const char* what() const noexcept {
						return what_.c_str();
					}
				protected:
					std::string what_;
			};

			class Redefined : public Exception {
				public:
					Redefined(const std::string& className) : Exception("Constructor for "+ className+" redefined") {

					}
			};

			class ClassNotFound : public Exception {
				public:
					ClassNotFound(const std::string& className) : Exception("Class \""+className+"\" can not be destringified.") {

					}
			};

			typedef std::function<std::unique_ptr<T>(const SimpleJSON::Type::Object&) > CreatorFunction;

			Factory(const Factory&) = delete;

			static bool registerCreator(const std::string &className, CreatorFunction c) {
				return instance().registerCreator_(className, c);
			}

			static std::unique_ptr<T> deserialize(const std::string &str) {
				SimpleJSON::Value v = SimpleJSON::parse(str);
				return instance().deserialize_(v.as<Type::Object>());
			}

			static std::unique_ptr<T> deserialize(const SimpleJSON::Type::Object& object) {
				return instance().deserialize_(object);
			}

			// Thread safe as of C++11
			static Factory<T,DEBUG>& instance() {
				static Factory<T,DEBUG> fact;
				return fact;
			}

		private:

			inline bool registerCreator_(const std::string &className, CreatorFunction f);

			inline std::unique_ptr<T> deserialize_ (const SimpleJSON::Type::Object& object);

			Factory(): creators() {

			}

			std::map<std::string,CreatorFunction> creators;
	};
}

template<typename T, bool DEBUG>
bool SimpleJSON::Factory<T,DEBUG>::registerCreator_(const std::string &className, CreatorFunction f) {
	const auto& creator=creators.find(className);
	if(creator != creators.end()) {
		throw Redefined(className);
	}

	if(DEBUG) {
		std::cerr << "REGISTERED " << className << "\n";
	}

	creators[className] = f;
	return true;
}

template<typename T, bool DEBUG>
std::unique_ptr<T> SimpleJSON::Factory<T,DEBUG>::deserialize_(const SimpleJSON::Type::Object& object) {
	std::string className = object["class"].as<std::string>();

	if(DEBUG) {
		std::cerr << "DESERIALIZING " << className << "\n";
	}

	const auto& creator=creators.find(className);
	if(creator == creators.end()) {
		throw ClassNotFound(className);
	}

	return creator->second(object);
}