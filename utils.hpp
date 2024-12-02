#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

typedef std::vector<int> int_vec;
typedef std::vector<int>::iterator it_intvec;

class ThrowError : public std::exception {
	private:
			std::string	_err_msg;
	public:
			ThrowError( std::string const err_msg ) {
				_err_msg = err_msg;
			}
			virtual ~ThrowError( void ) throw() {};
			virtual const char	*what( void ) const throw() {
				return _err_msg.c_str();
			}
};

#endif