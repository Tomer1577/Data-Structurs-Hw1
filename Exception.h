#ifndef WET1_EXCEPTION_H
#define WET1_EXCEPTION_H

#include <exception>

class Exception: public std::exception {};

class ItemNotFound: public Exception {};

class ItemFound: public Exception {};

class OutOfBounds: public Exception {};

#endif //WET1_EXCEPTION_H
