#pragma once

#include <SimpleJSON/Type/Boolean.h>
#include <SimpleJSON/Type/Integer.h>
#include <SimpleJSON/Type/Number.h>
#include <SimpleJSON/Type/Object.h>
#include <SimpleJSON/Type/String.h>
#include <SimpleJSON/Type/Array.h>
#include <SimpleJSON/Value.h>

#include <string>
#include <memory>

namespace SimpleJSON {
	class JSONParser {
		public:

			static Value parse(const std::string& str) {
				std::string tmp =str;
				return std::move(parseValue(tmp));
			}
		public:
			static bool isFloat(const std::string &s) {
				std::size_t i =0;
				while(1) {
					if(std::isdigit(s[i]) || s[i]=='-') {
						i++;
					}else if(s[i]=='.') { // TODO
						return true;
					}else {
						return false;
					}
				}
			}
			static void removeWhiteSpaces(std::string&str) {
				std::size_t ind =0;
				while(std::isspace(str[ind])) {
					ind++;
				}
				if(ind > 0) {
					str=std::string(str.begin()+ind,str.end());
				}
			}

			inline static SimpleJSON::Type::Object parseObject(std::string& str);

			inline static SimpleJSON::Type::Array parseArray(std::string& str);

			inline static SimpleJSON::Type::String parseString(std::string& str);

			inline static SimpleJSON::Type::Number parseNumber(std::string& str);

			inline static SimpleJSON::Type::Null parseNull(std::string& str);

			inline static SimpleJSON::Type::Boolean parseBool(std::string& str);

			inline static Value parseValue(std::string& str);

			inline static SimpleJSON::Type::Integer parseInteger(std::string &str);
	};

	inline Value parse(const std::string &str) {
		return std::move(JSONParser::parse(str));
	}

	SimpleJSON::Type::Object JSONParser::parseObject(std::string& str) {
		Type::Object obj;
		bool inObject=true;
		removeWhiteSpaces(str);
		str=std::string(str.begin()+1,str.end());
		do {
			removeWhiteSpaces(str);
			if(str[0] == '}') {
				inObject=false;
				str = std::string(str.begin()+1,str.end());
			}else {
				if(str[0]==',') {
					str=std::string(str.begin()+1,str.end());
				}
				std::string key = parseString(str);
				removeWhiteSpaces(str);
				str = std::string(str.begin()+1,str.end());
				obj[key] = parseValue(str);
			}
		}
		while(inObject);
		return std::move(obj);
	}

	SimpleJSON::Type::Array JSONParser::parseArray(std::string& str) {
		std::vector<Value> array;
		bool inArray=true;
		do {
			removeWhiteSpaces(str);
			if(str[0]==']') {
				str=std::string(str.begin()+1,str.end());
				inArray=false;
			}else {
				str=std::string(str.begin()+1,str.end()); // jump "," and "["
				array.push_back(parseValue(str));
			}
		}while(inArray);
		return std::move(array);
	}

	SimpleJSON::Type::String JSONParser::parseString(std::string& str) {
		removeWhiteSpaces(str);

		std::size_t end=1;
		while(str[end]!= '"') {
			if(str[end]=='\\') { // TODO: http://www.json.org/
				end+=2;
			}else {
				end++;
			}
		}

		std::string tmp;
		for(std::size_t i=1;i<end;i++) {
			if(str[i]=='\\') { // TODO
				tmp+=str[i+1];
				i++;
			} else {
				tmp+=str[i];
			}
		}
		str=std::string(str.begin()+end+1,str.end());
		return tmp;
	}

	SimpleJSON::Type::Number JSONParser::parseNumber(std::string& str) {
		removeWhiteSpaces(str);
		std::size_t nextChar=0;
		double ret=std::stod(str,&nextChar);

		str=std::string(str.begin()+nextChar,str.end());
		return ret;
	}

	SimpleJSON::Type::Integer JSONParser::parseInteger(std::string &str) {
		removeWhiteSpaces(str);
		std::size_t nextChar=0;
		int ret=std::stoi(str,&nextChar);

		str=std::string(str.begin()+nextChar,str.end());
		return ret;
	}

	SimpleJSON::Type::Null JSONParser::parseNull(std::string& str) {
		removeWhiteSpaces(str);
		if(str.length() >= 4) {
			str=std::string(str.begin()+4, str.end());
		}
		return {};
	}

	SimpleJSON::Type::Boolean JSONParser::parseBool(std::string& str) {
		removeWhiteSpaces(str);
		if(str.length() >= 4 && str.substr(0,4) == "true") {
				str=std::string(str.begin()+4, str.end());
				return true;
		} else {
			str=std::string(str.begin()+5, str.end());
			return false;
		}
	}

	Value JSONParser::parseValue(std::string &str) {
		removeWhiteSpaces(str);
		if(str[0] == '{') {
			return std::move(parseObject(str));
		}else if(str[0] == '[') {
			return std::move(parseArray(str));
		}else if(str[0] == '\"') {
			return std::move(parseString(str));
		}else if(std::isdigit(str[0]) || str[0]=='-' || str[0]=='.') { // TODO init
			if(isFloat(str)) {
				return std::move(parseNumber(str));
			}else {
				return std::move(parseInteger(str));
			}

		}else if( str[0]=='n') {
			return std::move(parseNull(str));
		}else {
			return std::move(parseBool(str));
		}
	}


}
