/*
* File:   Log.h
* Author: Alberto Lepe <dev@alepe.com>
*
* Created on December 1, 2015, 6:00 PM
*/

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

enum typelog {
	T_DEBUG,
	T_INFO,
	T_WARN,
	T_ERROR
};

struct structlog {
	bool headers = true;
	typelog level = T_INFO;
};

extern structlog LOGCFG;

class LOG {
public:
	LOG() {}
	LOG(typelog type) {
		msglevel = type;
		if (LOGCFG.headers) {
			operator<<("[") << getLabel(type) << "] ";
		}
	}
	~LOG() {
		if (opened) {
			final_msg << endl;
			printf(final_msg.str().c_str());
		}
		opened = false;
	}
	template<class T>
	LOG &operator<<(const T &msg) {
		if (msglevel >= LOGCFG.level) {
			final_msg << msg;
			opened = true;
		}
		return *this;
	}
private:
	bool opened = false;
	typelog msglevel = T_DEBUG;
	ostringstream final_msg ;
	inline string getLabel(typelog type) {
		string label;
		switch (type) {
		case T_DEBUG: label = "DEBUG"; break;
		case T_INFO:  label = "INFO "; break;
		case T_WARN:  label = "WARN "; break;
		case T_ERROR: label = "ERROR"; break;
		}
		return label;
	}
};

#endif  /* LOG_H */