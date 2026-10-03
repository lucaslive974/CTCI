#include "chapters.hpp"
#include "testing_utils.hpp"
#include <gtest/gtest.h>

using StacksInt = CTCI::III::SetOfStacks<int>;

TEST(III, SET_OF_STACKS_PUSH) {
    StacksInt stacks(/*threshold=*/3);

    stacks.push({1, 2, 3});
    EXPECT_EQ(stacks.numberOfStacks(), 1);

    stacks.push(4);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(III, SET_OF_STACKS_POP) {
    StacksInt stacks(/*list=*/{1, 2, 3, 4, 5}, /*threshold=*/3);
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(III, SET_OF_STACKS_SIZE) {
    StacksInt stacks({1, 2, 3, 4, 5, 6});
    EXPECT_EQ(stacks.size(), 6);
}

TEST(III, SET_OF_STACKS_SIZE_AT) {
    StacksInt stacks({1, 2, 3, 4}, 2);
    stacks.popAt(0);

    EXPECT_EQ(stacks.sizeAt(0), 1);
}

TEST(III, SET_OF_STACKS_PEEK) {
    StacksInt stacks{1, 2, 3, 4};
    EXPECT_EQ(stacks.peek(), 4);

    stacks.push({5, 6});
    EXPECT_EQ(stacks.peek(), 6);
}

TEST(III, SET_OF_STACKS_PEEK_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peekAt(0), 2);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(III, SET_OF_STACKS_POP_AT) {
    StacksInt stacks{{1, 2, 3, 4, 5, 6}, 3};
    stacks.popAt(0);

    EXPECT_EQ(stacks.peek(), 6);
    EXPECT_EQ(stacks.size(), 5);
}

TEST(III, SET_OF_STACKS_EMPTY_STACKS_ON_MIDDLE_AMORTIZED) {
    StacksInt stacks{{1, 2, 3}, 1};
    EXPECT_EQ(stacks.numberOfStacks(), 3);

    stacks.popAt(1);
    EXPECT_EQ(stacks.numberOfStacks(), 2);

    stacks.pop();
    EXPECT_EQ(stacks.peek(), 1);
    EXPECT_EQ(stacks.numberOfStacks(), 1);
}

TEST(III, SET_OF_STACKS_EMPTY_STACK_ON_MIDDLE) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.popAt(1);
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(III, SET_OF_STACKS_EMPTY_STACK_ON_END) {
    StacksInt stacks{{1, 2, 3}, 1};

    stacks.pop();
    EXPECT_EQ(stacks.numberOfStacks(), 2);
}

TEST(III, SET_OF_STACKS_IS_EMPTY_TRUE) {
    StacksInt stacks;
    EXPECT_TRUE(stacks.empty());
}

TEST(III, SET_OF_STACKS_IS_EMPTY_FALSE) {
    StacksInt stacks{1, 2};
    EXPECT_FALSE(stacks.empty());
}

TEST(III, SET_OF_STACKS_IS_EMPTY_TWO_STACKS) {
    StacksInt stacks{{1, 2}, 1};

    stacks.popAt(0);
    EXPECT_FALSE(stacks.empty());

    stacks.pop();
    EXPECT_TRUE(stacks.empty());
}

using III = CTCI::III;

TEST(III, SORT_STACK) {
    CTCI::Stack<int> a{3, 4, 1, 5, 2};
    CTCI::Stack<int> b{5, 4, 3, 2, 1};

    III::sortStack(a);
    internal::testStacksIsEqual(a, b);
}

TEST(III, SORT_STACK_EMPTY) {
    CTCI::Stack<int> a;
    EXPECT_NO_THROW(III::sortStack(a));
}

TEST(III, SORT_STACK_EVEN) {
    CTCI::Stack<int> a{1, 2};
    CTCI::Stack<int> b{2, 1};

    III::sortStack(a);
    internal::testStacksIsEqual(a, b);
}

namespace {
using AnimalShelter = III::AnimalShelter;
using Dog = AnimalShelter::Dog;
using Cat = AnimalShelter::Cat;

auto createDog() -> std::unique_ptr<Dog> { return std::make_unique<Dog>(); }
auto createCat() -> std::unique_ptr<Cat> { return std::make_unique<Cat>(); }
} // namespace

using QueueInt = CTCI::III::Queue<int>;

TEST(III, QUEUE_INITIALIZATION) {
    QueueInt queue{5, 4, 3, 2, 1};

    EXPECT_EQ(queue.front(), 5);
}

TEST(III, QUEUE_PUSH) {
    QueueInt queue{4, 2, 1};

    queue.push(3);
    for (size_t i = 0; i < 3; ++i)
        queue.pop();

    EXPECT_EQ(queue.front(), 3);
}

TEST(III, QUEUE_POP) {
    QueueInt queue{5, 3, 1};

    queue.pop();
    EXPECT_EQ(queue.front(), 3);
}

TEST(III, QUEUE_EMPTY) {
    QueueInt queue{5, 2};

    EXPECT_FALSE(queue.empty());

    for (size_t i = 0; i < 2; ++i)
        queue.pop();

    EXPECT_TRUE(queue.empty());
}

TEST(III, ANIMAL_SHELTER_ENQUEUE_ANIMALS) {
    AnimalShelter shelter;

    auto dog1 = createDog();
    auto cat1 = createCat();

    shelter.enqueue(createDog());
    shelter.enqueue(createCat());

    internal::testUniquePtrIs<Dog>(shelter.dequeueAny().get());
    internal::testUniquePtrIs<Cat>(shelter.dequeueAny().get());
}

TEST(III, ANIMAL_SHELTER_DEQUEUE_DOGS_I) {
    AnimalShelter shelter;

    shelter.enqueue(createCat());
    shelter.enqueue(createDog());

    internal::testUniquePtrIs<Dog>(shelter.dequeueDog().get());
    EXPECT_FALSE(shelter.empty());
}

TEST(III, ANIMAL_SHELTER_DEQUEUE_DOGS_II) {
    AnimalShelter shelter;

    shelter.enqueue(createCat());
    shelter.enqueue(createCat());

    for (size_t i = 0; i < 2; ++i)
        internal::testUniquePtrIsnt<Dog>(shelter.dequeueDog().get());
    EXPECT_FALSE(shelter.empty());

    for (size_t i = 0; i < 2; ++i)
        shelter.dequeueAny();

    EXPECT_TRUE(shelter.empty());
}

TEST(III, ANIMAL_SHELTER_DEQUEUE_CATS) {
    AnimalShelter shelter;

    shelter.enqueue(createCat());
    shelter.enqueue(createDog());

    internal::testUniquePtrIs<Cat>(shelter.dequeueCat().get());
    EXPECT_FALSE(shelter.empty());
}

TEST(III, ANIMAL_SHELTER_DEQUEUE_EMPTY) {
    AnimalShelter shelter;

    EXPECT_EQ(shelter.dequeueAny(), nullptr);
    EXPECT_TRUE(shelter.empty());
}

TEST(III, ANIMAL_SHELTER_DEQUEUE_TYPE_EMPTY) {
    AnimalShelter shelter;
    EXPECT_EQ(shelter.dequeueCat(), nullptr);
    EXPECT_EQ(shelter.dequeueDog(), nullptr);
}
