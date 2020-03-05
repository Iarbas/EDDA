// ========================================== max. 120 symbols in one line ============================================
/**
 * @par Project
 * EDDA - Evaluative Data-driven Design Application
 *
 * @file    readConfig.hpp
 * @author  Andre Alexander Pieper
 * @version 1.0
 * @date    2019-12-08
 *
 * @brief   Header file to read the configuration file.
 *
 * This program part is responsible for reading the configuration file and returns the requested information.
 */
// --------------------------------------------------------------------------------------------------------------------

#ifndef HEADER_READER_HPP_AP_08122019
#define HEADER_READER_HPP_AP_08122019

#include <string>
#include <vector>


namespace EDDAmisc
{
/** @class ReadConfig
 *  @brief Header file to read the configuration file.
 *
 *  This program part is responsible for reading the configuration file and returns
 *  the requested information.
 */
class ReadConfig
{
public:
	ReadConfig(std::string config_file_name);
	virtual ~ReadConfig();				// Virtual Destructor.
        void get_parameter(std::string int_value_name, int &int_value);
        void get_parameter(std::string str_value_name, std::string &str_value);

private:
	void Init();
        void check_data_size();
        bool data_size_tested;
        bool data_size_ok;
	std::string remove_comments(std::string &buffer);
	std::string _config_file_name;
        std::vector<std::string> split(const std::string& s, std::string delimiter, std::string delete_chars);
        std::vector<std::string> raw_config;
};
}

#endif // HEADER_READER_HPP_AP_08122019
