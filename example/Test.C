
/* LICENSE NOTICE
 * *
 * *
 * */
#include <iostream>
#include <fstream>
#include "../src/GetOptCpp.H"

int main(int argc, const char *argv[])
{

    GetOptCpp options;

    options.add_option( 's', "author", true, true, "ServeshSingh" );/*this parameter mandatory, has value with tag, default value is Servesh*/
    options.add_option( 't' );
    options.add_option( 'W', "wow" );

    const char *author       = NULL;
    const char *t            = NULL;
    const char *wow          = NULL;

    if ( options.parse_options( argc, argv ) != 0 )
    {
        std::cerr << "Parse Error.";
        return 1;
    }


    int opt_index = -1;
    opt_index = options.get_option( &author, 's');
    if ( opt_index < 0 )
    {
        std::cerr << "option author not supplied or has some error: " <<  author  << std::endl;
    }
    opt_index = options.get_option( &t, "t");
    if ( opt_index < 0)
    {
        std::cerr << "option t error: Option error or not supplied." <<  t  << std::endl;
    }
    opt_index = options.get_option( &wow, "wow");
    if ( opt_index < 0)
    {
        std::cerr << "option t error: Option error or not supplied." <<  t  << std::endl;
    }
    std::cout <<std::endl;
    return 0;
}

