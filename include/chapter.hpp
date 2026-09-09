#pragma once
#include <string>

class Chapter {
    std::string idName;

  public:
    Chapter(std::string id_name);
    std::string name();
};
