#include "../include/expression_parser.hpp" // for public API & String typedef
#include "parser.hpp"                        // internal parser implementation
#include <sstream>
#include <iomanip>

namespace expression_parser {
	String evaluate(String expression) {
		double value = internal::parse_and_evaluate(expression);
		std::ostringstream oss;
		oss << std::setprecision(15) << std::showpoint << value;
		std::string s = oss.str();
		if(s.find('.') != std::string::npos) {
			while(!s.empty() && s.back() == '0') s.pop_back();
			if(!s.empty() && s.back() == '.') s.pop_back();
		}
		if(s.empty()) s = "0";
		return s;
	}
}
