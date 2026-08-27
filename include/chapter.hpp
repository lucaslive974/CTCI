#pragma once
#include <memory>
#include <string>
#include <vector>

using Task = std::pair<std::string, void (*)()>;

class Chapter {
    std::string id_name;

  protected:
    std::vector<Task> tasks;

  public:
    Chapter(std::string id_name);
    virtual ~Chapter() = default;
    static void executeChapters(std::vector<std::shared_ptr<Chapter>> &chapters);
    static auto getAllChapters() -> std::vector<std::shared_ptr<Chapter>>;
    void printChapterName();
    void execute();
};
