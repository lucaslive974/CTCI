#include "chapters.hpp"
#include <limits>

using namespace CTCI;

auto III::sortStack(Stack<int> &stack) -> void {
    if (stack.empty())
        return;

    Stack<int> tmp;
    while (!stack.empty()) {
        int val = stack.peek();
        stack.pop();

        while (!tmp.empty() && val < tmp.peek()) {
            int tmpVal = tmp.peek();
            tmp.pop();

            stack.push(tmpVal);
        }

        tmp.push(val);
    }

    while (!tmp.empty()) {
        stack.push(tmp.peek());
        tmp.pop();
    }
};

using AnimalShelter = III::AnimalShelter;

void AnimalShelter::enqueue(UniquePtr<Animal> &&ptr) {
    auto entry = AnimalStorage{.animal = std::move(ptr), .seq = seq};

    if (auto *pt = dynamic_cast<Dog *>(entry.animal.get()))
        dogs.push(std::move(entry));
    else
        cats.push(std::move(entry));

    ++seq;
}

auto AnimalShelter::dequeueAny() -> UniquePtr<AnimalShelter::Animal> {
    if (empty())
        return nullptr;

    size_t dseq = dogs.empty() ? std::numeric_limits<size_t>::max() : dogs.front().seq;
    size_t cseq = cats.empty() ? std::numeric_limits<size_t>::max() : cats.front().seq;

    auto &queue = dseq < cseq ? dogs : cats;
    auto entry = std::move(queue.front());
    queue.pop();

    return std::move(entry.animal);
};

template <typename Ty>
    requires(std::same_as<Ty, AnimalShelter::Dog> || std::same_as<Ty, AnimalShelter::Cat>)
CTCI::UniquePtr<Ty> dequeueAnimalOfType(CTCI::Queue<AnimalShelter::AnimalStorage> &queue) {
    if (queue.empty())
        return nullptr;

    auto entry = std::move(queue.front());
    queue.pop();

    auto ret = CTCI::UniquePtr<Ty>(static_cast<Ty *>(entry.animal.get()));
    entry.animal.release();
    return std::move(ret);
}

auto AnimalShelter::dequeueDog() -> UniquePtr<AnimalShelter::Dog> { return std::move(dequeueAnimalOfType<Dog>(dogs)); }

auto AnimalShelter::dequeueCat() -> UniquePtr<AnimalShelter::Cat> { return std::move(dequeueAnimalOfType<Cat>(cats)); }

bool AnimalShelter::empty() { return dogs.empty() && cats.empty(); }
