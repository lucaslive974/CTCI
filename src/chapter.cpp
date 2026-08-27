#include "chapter.hpp"
#include <memory>
#include <utils.hpp>

Chapter::Chapter(std::string id_name) : id_name(std::move(id_name)) {};

void Chapter::executeChapters(std::vector<std::shared_ptr<Chapter>> &chapters) {
    for (auto &chapter : chapters) {
        chapter->printChapterName();
        chapter->execute();
        CTCI::utils::breakLine();
    }
}

void Chapter::printChapterName() { CTCI::utils::printTitle(id_name); }

void Chapter::execute() {
    for (auto &task : tasks) {
        CTCI::utils::printTitle(task.first);
        task.second();
    }
}

#include "chapters.hpp"

auto Chapter::getAllChapters() -> std::vector<std::shared_ptr<Chapter>> {
    return std::vector<std::shared_ptr<Chapter>>{
#define CHAPTERS_LIST
#define REGISTER_CHAPTER(CLASSNAME) std::make_shared<CLASSNAME>(),
#include "chapters.hpp.inc"
    };
};
