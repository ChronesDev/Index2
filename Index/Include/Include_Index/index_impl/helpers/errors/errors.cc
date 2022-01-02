#pragma once

#include <exception>

//#define INDEX_THROW(...) throw std::runtime_error(__VA_ARGS__)
#define INDEX_THROW(...) throw std::exception()

#define INDEX_THROW_NOT_IMPLEMENTED() throw std::runtime_error("index: not implemented.")