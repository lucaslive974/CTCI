#include "chapter.hpp"
#include <utils.hpp>

Chapter::Chapter(std::string name) : idName(std::move(name)) {};

std::string Chapter::name() { return this->idName; }