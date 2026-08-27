#pragma once
#include <memory>
#include <string>
#include <vector>

class Chapter {
    std::string id_name;

  public:
    Chapter(std::string id_name);
    virtual ~Chapter() = default;
    virtual void execute() = 0;
    static void executeChapters(std::vector<std::shared_ptr<Chapter>> &chapters);
    static auto getAllChapters() -> std::vector<std::shared_ptr<Chapter>>;
    void printChapterName();
};
