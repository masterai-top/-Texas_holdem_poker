#ifndef __SYSTEM_INFO_CONFIG_DETAIL_H__
#define __SYSTEM_INFO_CONFIG_DETAIL_H__
class SystemInfoConfigDetailRequest
{
public:
	SystemInfoConfigDetailRequest(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		writer.StartObject();
		SERIALIZE_MEMBER(writer,id);

		writer.EndObject();
	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	void Deserialize(const string& json)
	{
		Document d;
		if (d.Parse(json.c_str()).HasParseError()){
			throw logic_error("parse json error. raw data : " + json);
		}
		SET_DOC_MEMBER(d,id);

	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
	    return 0;
	}
private:
	CInteger       	_id             ;  //主键

};
class SystemInfoConfigDetailResponse
{
public:
	SystemInfoConfigDetailResponse(const string& json) {
		this->Deserialize(json);
	}
	template <typename Writer>
	void Serialize(Writer& writer) const {
		writer.StartObject();
		SERIALIZE_MEMBER(writer,id);
		SERIALIZE_MEMBER(writer,area);
		SERIALIZE_MEMBER(writer,target);
		SERIALIZE_MEMBER(writer,nickName);
		SERIALIZE_MEMBER(writer,title);
		SERIALIZE_MEMBER(writer,content);
		SERIALIZE_MEMBER(writer,beginTime);
		SERIALIZE_MEMBER(writer,optUser);
		SERIALIZE_MEMBER(writer,createDate);

		writer.EndObject();
	}

	void toString(std::string& json) {
		StringBuffer sb;
		Writer<StringBuffer> writer(sb);
		Serialize(writer);
		json = sb.GetString();
	}

	void Deserialize(const string& json)
	{
		Document d;
		if (d.Parse(json.c_str()).HasParseError()){
			throw logic_error("parse json error. raw data : " + json);
		}
		SET_DOC_MEMBER(d,id);
		SET_DOC_MEMBER(d,area);
		SET_DOC_MEMBER(d,target);
		SET_DOC_MEMBER(d,nickName);
		SET_DOC_MEMBER(d,title);
		SET_DOC_MEMBER(d,content);
		SET_DOC_MEMBER(d,beginTime);
		SET_DOC_MEMBER(d,optUser);
		SET_DOC_MEMBER(d,createDate);

	}

	static tars::Int32 handler(const vector<tars::Char>& reqBuf, const map<std::string, std::string>& extraInfo, vector<tars::Char>& rspBuf)
	{
	    return 0;
	}
private:
	CInteger       	_id             ;  //主键
	CString        	_area           ;  //发送消息的地区：台湾、东南亚、欧洲、大陆等
	CString        	_target         ;  //发送目标（空代表所有人,用户ID代表个人）
	CString        	_nickName       ;  //昵称（发送所有人时，昵称为空）
	CString        	_title          ;  //配置标题，最多显示20个字符
	CString        	_content        ;  //配置内容，最多显示100个字符
	CString        	_beginTime      ;  //生效时间
	CString        	_optUser        ;  //操作者
	CString        	_createDate     ;  //创建时间

};
#endif