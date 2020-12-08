#ifndef WET1_EXCEPTION_H
#define WET1_EXCEPTION_H

#include <bits/exception.h>

class Exception: public std::exception {};

class ItemNotFound: public Exception {};

class ItemFound: public Exception {};

class OutOfBound: public Exception {};

#endif //WET1_EXCEPTION_H
