#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <cstring>

typedef std::vector<int> int_vec;
typedef std::vector<int>::iterator it_intvec;

typedef std::vector<long long int> llint_vec;
typedef std::vector<long long int>::iterator it_llintvec;

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