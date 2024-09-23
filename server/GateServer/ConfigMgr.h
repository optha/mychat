#pragma once
#include "const.h"

struct SectionInfo {
	std::map<std::string, std::string> _section_datas;

	SectionInfo() {}
	SectionInfo(const SectionInfo& src) {
		_section_datas = src._section_datas;
	}
	~SectionInfo() { _section_datas.clear(); }

	// 重载赋值运算符
	SectionInfo& operator=(const SectionInfo& src) {
		if (&src == this) {
			return *this;
		}
		this->_section_datas = src._section_datas;
		return *this;
	}

	// 通过 map[key] 获取对应的 value
	std::string operator[](const std::string& key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		return _section_datas[key];
	}
};

class ConfigMgr
{
public:
	~ConfigMgr() {
		_config_map.clear();
	}

	ConfigMgr(const ConfigMgr& src) {
		_config_map = src._config_map;
	}
	ConfigMgr& operator=(const ConfigMgr& src) {
		if (&src == this) {
			return *this;
		}
		_config_map = src._config_map;
	}

	static ConfigMgr& Inst() {
		static ConfigMgr cfg_mgr;
		return cfg_mgr;
	}

	SectionInfo operator[](const std::string& section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}

private:
	ConfigMgr();
	std::map<std::string, SectionInfo> _config_map;
};

