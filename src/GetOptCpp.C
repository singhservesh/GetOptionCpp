/*
Copyright (C) 2011  Free Software Foundation

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
 
#include <iostream>
#include <string>
#include "GetOptCpp.H"

int option::option_index = 0;

option::option( const char short_name, const char *long_name , const char *value )
{
    this->short_name  = short_name;
    this->long_name   = long_name;
    this->value	      = value;
    this->index       = option_index;
    option_index++;
}

OptionRules::OptionRules( const char short_name, const char *long_name ,bool is_optional, bool has_value, const char *default_value, const char* description)
{
    this->short_name  = short_name;
    this->long_name   = long_name;
    this->isOptional  = is_optional;
    this->description = description;
    this->has_value    = has_value;
    this->default_value = default_value;
};

bool OptionRules::is_option( const char *opt )
{
    size_t len = strlen( opt );
    if ( len > 3 )
    {
	if ( opt[0] != '-' ||  opt[1] != '-' )
	{
	    return false;
	}
	int i = 2;
	while( opt[i] != '\0' )
	{	    
	    if ( isalnum (opt [i]) == false )
	    {
		if ( opt[i] != '=' ) return false;
		return true;
	    }
	    i++;
	}
	return false;
    }
    if ( len != 2 || isalnum (opt[1]) == false || isdigit(opt[1]) == true || opt[0] != '-' )
    {
	return false;
    }
    return true;
}

void GetOptCpp::add_option( const char short_name, const char *long_name, bool optional, 
	bool has_value, const char *default_value, const char* description)
{
    if ( isalnum (short_name) == false || isdigit(short_name) == true )
    {
	std::cout << "Invalid short option given in" << __PRETTY_FUNCTION__ << std::endl;
	exit(1);
    }
    size_t i = 0;
    while( long_name[i] != '\0' )
    {	    
	if ( isalnum (long_name [i]) == false)
	{
	    std::cout << __PRETTY_FUNCTION__ <<" Invalid long option [" 
		<< long_name << "]" << std::endl;
	    exit(1);
	}
	i++;
    }
    rule_map.push_back( new OptionRules( short_name, long_name, optional, has_value, default_value, description ) );
};
int GetOptCpp::parse_options( const int argc, const char* argv[] )
{
    int i = 1;
    std::string name = "";
    bool opt_added = false;
    std::string value = "";

    if ( argc < 1 )
	return -1;

    while( i < argc ) // Parse option with value;
    {
	opt_added = false;
	name = argv[i];
	if ( false == OptionRules::is_option( name.c_str() ) )
	{
	    std::cout << "Invalid option [" << name << "] or value is [invalid or not provided].";
	    //TODO std::cout << help;
	    return -1;
	}
	if ( name.length() > 3 ) // parse long option
	{
	    size_t pos = name.find_first_of('=');
	    value = name.substr( pos+1 );
	    name.erase(pos);
	    for( size_t k=0, j=rule_map.size(); k < j; k++ )
	    {
		if ( rule_map[k]->long_name == (name.c_str()+2) )
		{
		    if ( rule_map[k]->has_value == true && value.length() != 0 )
		    {
			mArgv.push_back( new option( rule_map[k]->short_name, rule_map[k]->long_name.c_str(), value.c_str() ) );
			opt_added = true;
			break;
		    }
		}
	    }
	}
	else 
	{
	    i++;
	    if ( i == argc )
	    {
		std::cout << "Invalid option " << argv[i-1] << "  value is not provided.";
		exit(1);
	    }
	    if ( true == OptionRules::is_option( argv[i] ))
	    {
		std::cout << "Value missing for option " << argv[i] << ".";
		exit(1);
	    }
	    value = argv[i];
	    for( size_t k=0, j=rule_map.size(); k < j; k++ )
	    {
		if ( *(name.c_str()+1) == rule_map[k]->short_name )
		{
		    if ( true == rule_map[k]->has_value && value.length() != 0 )
		    {
			mArgv.push_back( new option( rule_map[k]->short_name, rule_map[k]->long_name.c_str(), value.c_str() ) );
			opt_added = true;
			break;
		    }
		}
	    }
	}
	if ( opt_added == true )
	{
	    i++;
	    continue;	    
	}
	std::cout << "Invalid option " << argv[i] << "  value is invalid or not provided.";
	exit(1);
    }
    return 0;
}

int GetOptCpp::get_option( char const **value, char short_name, size_t index )
{
    if ( index >= mArgv.size() )
	return -1;
    if ( index > 0 )
    {
	if ( short_name == mArgv[index]->short_name )
	{
	    *value = (mArgv[index]->value).c_str();
	    return index;
	}
	return -1;
    }
    for( size_t i = 0, j = mArgv.size(); i < j; i++ )
    {
	if ( short_name == mArgv[i]->short_name )
	{
	    *value = (mArgv[i]->value).c_str();
	    return i;
	}
    }
    return -1;
}

int GetOptCpp::get_option( char const **value, const char *long_name, size_t index )
{
    if ( index >= mArgv.size() )
	return -1;
    if ( index > 0 )
    {
	if (  mArgv[index]->long_name == long_name )
	{
	    *value = (mArgv[index]->value).c_str();
	    return index;
	}
	return -1;
    }
    for ( size_t i = index, j = mArgv.size(); i < j; i++ )
    {
	if ( mArgv[i]->long_name  == long_name )
	{
	    *value = (mArgv[i]->value).c_str();
	    return i;
	}
    }
    return -1;
}

GetOptCpp::~GetOptCpp()
{
    for ( size_t i = 0, j = mArgv.size(); i < j; i++ )
    {
	delete mArgv[i];
    }
    for ( size_t i = 0, j = rule_map.size(); i < j; i++ )
    {
	delete rule_map[i];
    }
}
