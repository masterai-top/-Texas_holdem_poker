// Serialize example
// This example shows writing JSON string with writer directly.
#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "rapidjson/writer.h" // for stringify JSON
#include "rapidjson/document.h"

#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include "globe.h"

using namespace rapidjson;
using namespace std;

class CString;
class CInteger;

template<typename T>
std::string toString(T t)
{
	ostringstream os;
	os << t;
	return os.str();
}
template<typename T, typename... Args>
std::string toString(T head, Args... args)
{
	ostringstream os;
	os << head;
	return os.str() + toString(args...);
}

class CString {
public:
	CString() { this->_isNull = true; }

	CString(const std::string& str) {
		this->_data = str;
		this->_isNull = false;
	}
	std::string toString() {
		if (isNull()) {
			throw logic_error("CString is NULL");
		}
		return this->_data;
	}
	void assign(const std::string& str) {
		this->_data = str;
		this->_isNull = false;
	}

	void assign(const CString& rhs){
		this->_data = rhs._data;
		this->_isNull = rhs._isNull;
	}

	operator std::string()const {
		if (isNull()) {
			throw logic_error("CString is NULL");
		}
		return this->_data;
	}

	bool isNull()const { return this->_isNull; }
private:
	std::string _data;
	bool _isNull;
};

class CInteger {
public:
	CInteger() { this->_isNull = true; }

	CInteger(int64_t value) {
		this->_data = value;
		this->_isNull = false;
	}
	std::string toString() {
		if (isNull()) {
			throw logic_error("CInteger is NULL");
		}
		return TC_Common::tostr<int64_t>(this->_data);
	}
	void assign(int64_t newValue) {
		this->_data = newValue;
		this->_isNull = false;
	}

	void assign(const  CInteger& newValue) {
		this->_data = newValue._data;
		this->_isNull = newValue._isNull;
	}

	void assign(const string& newValue) {
		int64_t intValue = S2L(newValue);
		this->_data = intValue;
		this->_isNull = false;
	}

	operator int64_t() const {
		if (isNull()) {
			throw logic_error("CInteger is NULL");
		}
		return this->_data;
	}

	bool isNull()const { return this->_isNull; }
private:
	int64_t _data;
	bool _isNull;
};

// 管理后台请求状态码
const static int64_t RESULT_CODE_SUCCESS	= 1;
const static int64_t RESULT_CODE_FAIL		= 0;
#define INSERT_ASSIGN_STATEMENT(member) req.data[#member] = request._##member.toString()
#define UPDATE_ASSIGN_STATEMENT(member) 			if (request._##member.isNull() == false) \
													{ \
														req.data[#member] = request._##member.toString(); \
													}
#define SERIALIZE_MEMBER(writer, member) serializeMember(writer,#member,_##member)
#define SET_DOC_MEMBER(document, member) setDocMember(document, #member, _##member);
#define SET_RESPONSE_MEMBER(member) 				if (key == #member) { \
													response._##member.assign(value); \
													}
template <typename Writer>
void serializeMember(Writer& writer, const CString& content) {
	if (content.isNull()){
		writer.Null();
	}else{
		std::string str = content;
		writer.String(str.c_str(), (SizeType)str.length());
	}
}

template <typename Writer>
void serializeMember(Writer& writer, const CInteger& content) {
	if (content.isNull()) {
		writer.Null();
	}else{
		writer.Int64(content);
	}
}

template <typename Writer, typename MemberType>
void serializeMember(Writer& writer, const string& keyName, const MemberType& member) {
	writer.String(keyName.c_str());
	serializeMember(writer, member);
}

static void setDocMember(const Document& d, const std::string& keyName, CString& member){
	if (
		d.HasMember(keyName.c_str()) == false ||
		(d[keyName.c_str()].IsString() == false && d[keyName.c_str()].IsNull() == false)
		){
		throw logic_error("json Type error!");
	}
	if (d[keyName.c_str()].IsString()) {
		member.assign(d[keyName.c_str()].GetString());
	}
}

static void setDocMember(const Document& d, const std::string& keyName, CInteger& member) {
	if (
		d.HasMember(keyName.c_str()) == false ||
		(d[keyName.c_str()].IsInt64() == false && d[keyName.c_str()].IsNull() == false)
		){
		throw logic_error("json Type error!");
	}
	if (d[keyName.c_str()].IsInt64()) {
		member.assign(d[keyName.c_str()].GetInt64());
	}
}

#endif // !__DEFINE_H