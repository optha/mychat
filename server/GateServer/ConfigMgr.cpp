#include "ConfigMgr.h"
ConfigMgr::ConfigMgr() {
	// C++14 文件处理
	boost::filesystem::path current_path = boost::filesystem::current_path();
	boost::filesystem::path config_path = current_path / "config.ini";
	std::cout << "读取配置文件config.ini path: " << config_path << std::endl;

	// 处理 ini 文件
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(config_path.string(), pt);

	for (const auto& section_pair : pt) {
		// config.ini [] 如 [GateServer]
		const ::std::string& section_name = section_pair.first;

		// 对于每个section，遍历其所有的key-value对  
		const boost::property_tree::ptree& section_tree = section_pair.second;	// Port = 8080
		std::map<std::string, std::string> section_config;
		for (const auto& key_value_pair : section_tree) {
			const std::string& key = key_value_pair.first;	// Port
			const std::string& value = key_value_pair.second.get_value<std::string>();	// 8080
			section_config[key] = value;
		}

		SectionInfo sectionInfo;
		sectionInfo._section_datas = section_config;
		// 将section的key-value对保存到config_map中  
		_config_map[section_name] = sectionInfo;
	}

	// 输出所有的 section 和 key-value
	for (const auto& section_entry : _config_map) {
		const std::string& section_name = section_entry.first;
		SectionInfo section_config = section_entry.second;
		std::cout << "[" << section_name << "]" << std::endl;
		for (const auto& key_value_pair : section_config._section_datas) {
			std::cout << key_value_pair.first << "=" << key_value_pair.second << std::endl;
		}
	}
}