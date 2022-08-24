// Copyright 2021, 2022 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/system/error_code.hpp>
#include <boost/system/error_condition.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/config.hpp>

#if !defined(BOOST_SYSTEM_HAS_SYSTEM_ERROR)

BOOST_PRAGMA_MESSAGE( "BOOST_SYSTEM_HAS_SYSTEM_ERROR not defined, test will be skipped" )
int main() {}

#else

#include <system_error>

namespace sys = boost::system;

enum my_errc
{
    enomem_c = ENOMEM
};

enum my_errn
{
    enomem_n = ENOMEM
};

namespace std {

template<> struct is_error_code_enum<my_errc>
{
    static const bool value = true;
};

template<> struct is_error_condition_enum<my_errn>
{
    static const bool value = true;
};

} // namespace std

std::error_code make_error_code( my_errc e )
{
    return std::error_code( e, std::generic_category() );
}

std::error_condition make_error_condition( my_errn e )
{
    return std::error_condition( e, std::generic_category() );
}

int main()
{
    sys::error_code ec = make_error_code( sys::errc::not_enough_memory );
    sys::error_condition en( sys::errc::not_enough_memory );

    BOOST_TEST_EQ( ec, en );
    BOOST_TEST_EQ( en, ec );

    BOOST_TEST_EQ( ec, enomem_c );
    BOOST_TEST_EQ( enomem_c, ec );

    BOOST_TEST_EQ( ec, enomem_n );
    BOOST_TEST_EQ( enomem_n, ec );

    // BOOST_TEST_EQ( en, enomem_c );
    // BOOST_TEST_EQ( enomem_c, en );

    // BOOST_TEST_EQ( en, enomem_n );
    // BOOST_TEST_EQ( enomem_n, en );

    return boost::report_errors();
}

#endif
