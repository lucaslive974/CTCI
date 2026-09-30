#include "chapters.hpp"

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

void AnimalShelter::enqueue(std::unique_ptr<Animal> &&ptr) { animals.append(std::move(ptr)); }

auto AnimalShelter::dequeueAny() -> std::unique_ptr<AnimalShelter::Animal> {
    if (empty())
        return nullptr;

    auto tmp = animals.head;
    animals.popFront();

    return std::move(tmp->val);
};

auto AnimalShelter::dequeueDog() -> std::unique_ptr<AnimalShelter::Animal> {
    return dequeueAnimalOfType<AnimalShelter::Dog>();
}
auto AnimalShelter::dequeueCat() -> std::unique_ptr<AnimalShelter::Animal> {
    return dequeueAnimalOfType<AnimalShelter::Cat>();
}

bool AnimalShelter::empty() { return animals.empty(); }
