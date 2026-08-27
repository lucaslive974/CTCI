#include "chapter.hpp"

int main(int argc, char **argv) {
    auto chapters = Chapter::getAllChapters();
    Chapter::executeChapters(chapters);
}
