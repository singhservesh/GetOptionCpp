
/*This class GetOptCpp can be used for parsing command line arguments similar to GNU getopt.
Copyright (C) 2011  Free Software Foundation

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __GETOPTCPP
#define __GETOPTCPP

#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

class option
{
    private:
	static int option_index;
    public:
	option( char short_name, const char *long_name , const char *value );
	char short_name;
	std::string long_name;
	std::string value;
	size_t index;
};

class OptionRules
{
    public:
	OptionRules ( const char short_name, const char *long_name ,
		bool optional, bool has_value, const char *default_value, const char* description);
	static bool is_option( const char *arg );/*check if string is in option format i.e. -h, --help,*/
	char short_name;
	std::string long_name;
	bool isOptional;
	bool has_value;
	std::string default_value;
	std::string description;
};

class GetOptCpp
{
    public:
	~GetOptCpp();
	GetOptCpp(){};
	void add_option( const char short_name, const char *long_name = "", bool optional = false, bool has_value=true, const char *default_value="",
		const char* description = "");
	int parse_options( const int argc, const char* argv[] );
	int get_option( char const **value, char short_name, size_t index = 0 );
	int get_option( char const **value, const char *long_name, size_t index = 0);
	void addHelp( const char* );
	std::vector < OptionRules* > rule_map;
	std::vector < option* > mArgv;
};
#endif //__GETOPTCPP
