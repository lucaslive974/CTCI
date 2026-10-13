#pragma once

#include <atomic>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace CTCI {

template <typename T> struct Allocator {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using void_pointer = void *;
    using size_type = std::size_t;

    Allocator() = default;
    ~Allocator() = default;

    [[nodiscard]] pointer allocate(size_type n) {
        auto *ptr = ::operator new(sizeof(T) * n);

        return static_cast<T *>(ptr);
    };
    void deallocate(pointer p, size_type n = 1) { ::operator delete(p); };

    template <typename... Args> void construct(pointer xp, Args &&...args) { ::new (xp) T(std::forward<Args>(args)...); };
    void destroy(pointer xp) {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            xp->~T();
        }
    };

    template <typename U> Allocator<U> rebind() { return Allocator<U>{}; }

    friend bool operator==(const Allocator &a, const Allocator &b) { return true; }
    friend bool operator!=(const Allocator &a, const Allocator &b) { return !(a == b); }
};

template <typename T, typename Allocator = Allocator<T>> class SharedPtr {
    using Pointer = T *;
    using Reference = T &;
    using Counter = std::atomic_uint;
    Allocator _alloc;

    Counter *_counter = nullptr;
    Pointer _data = nullptr;

  public:
    SharedPtr() = default;

    explicit SharedPtr(Pointer data, Counter *counter) {
        if (data == nullptr)
            return;

        counter->fetch_add(1);
        _data = data;
        _counter = counter;
    };

    SharedPtr(Pointer data) {
        _data = data;
        _counter = _alloc.template rebind<std::atomic_uint>().allocate(1);
        _alloc.template rebind<std::atomic_uint>().construct(_counter, 1);
    };

    SharedPtr(const SharedPtr &other) {
        other._counter->fetch_add(1);
        _data = other._data;
        _counter = other._counter;
    };

    SharedPtr(SharedPtr &&other) noexcept {
        using std::swap;
        swap(_data, other._data);
        swap(_counter, other._counter);
    };

    SharedPtr &operator=(SharedPtr other) {
        using std::swap;
        swap(_data, other._data);
        swap(_counter, other._counter);
        return *this;
    }

    ~SharedPtr() {
        if (_data == nullptr)
            return;

        auto val = _counter->fetch_sub(1);
        if (val > 1)
            return;

        _alloc.destroy(_data);
        _alloc.deallocate(_data);

        _alloc.template rebind<std::atomic_uint>().destroy(_counter);
        _alloc.template rebind<std::atomic_uint>().deallocate(_counter);
    };

    Reference operator*() const { return *_data; }
    Pointer operator->() const { return _data; }
    Pointer get() const { return _data; }

    [[nodiscard]] size_t useCount() const { return _counter->load(); }

    friend bool operator==(const SharedPtr &a, const SharedPtr &b) { return a._data == b._data; }
    friend bool operator==(const SharedPtr &a, const std::nullptr_t b) { return a._data == b; }
    friend bool operator==(const std::nullptr_t a, const SharedPtr &b) { return a == b._data; }

    template <typename U> static SharedPtr<U> dynamicCast(SharedPtr<T> ptr) {
        auto newPtr = dynamic_cast<U *>(ptr.get());
        auto shared = SharedPtr<U>{newPtr, ptr._counter};
        return std::move(shared);
    }

    template <typename U> static SharedPtr<U> staticCast(SharedPtr<T> ptr) {
        auto shared = SharedPtr<U>{static_cast<U *>(ptr.get()), ptr._counter};
        return std::move(shared);
    }
};

template <typename Ty, typename Allocator = Allocator<Ty>> class UniquePtr {
    using Pointer = Ty *;
    using ConstPointer = const Ty *;
    using Reference = Ty &;
    using ConstReference = const Ty &;
    Pointer _data = nullptr;
    Allocator _alloc;

  public:
    UniquePtr() = default;
    UniquePtr(Pointer ptr) { _data = ptr; };

    UniquePtr(UniquePtr &other) = delete;

    UniquePtr(UniquePtr &&other) noexcept { std::swap(_data, other._data); }

    UniquePtr &operator=(UniquePtr &&other) noexcept {
        std::swap(_data, other._data);
        return *this;
    }

    ~UniquePtr() {
        if (_data == nullptr)
            return;

        _alloc.destroy(_data);
        _alloc.deallocate(_data);
    }

    Reference operator*() { return *_data; }
    Pointer operator->() { return _data; }
    Pointer get() const { return _data; }
    Pointer release() {
        auto tmp = _data;
        _data = nullptr;
        return tmp;
    }

    friend bool operator==(const UniquePtr &a, const std::nullptr_t b) { return a._data == b; }
    friend bool operator==(const std::nullptr_t a, const UniquePtr &b) { return a == b._data; }
};

template <typename T, typename... Args> static SharedPtr<T> makeShared(Args &&...args) {
    static Allocator<T> alloc;

    auto ptr = alloc.allocate(1);
    alloc.construct(ptr, std::forward<Args>(args)...);

    return std::move(SharedPtr<T>{ptr});
}

template <typename T, typename... Args> static UniquePtr<T> makeUnique(Args &&...args) {
    static Allocator<T> alloc;

    auto ptr = alloc.allocate(1);
    alloc.construct(ptr, std::forward<Args>(args)...);

    return std::move(UniquePtr<T>{ptr});
}

template <typename U, typename T> SharedPtr<U> dynamicPointerCast(SharedPtr<T> &ptr) {
    return ptr.template dynamicCast<U>(ptr);
}
template <typename U, typename T> SharedPtr<U> staticPointerCast(SharedPtr<T> &ptr) {
    return ptr.template staticCast<U>(ptr);
}

/* STL Compatibility */
template <typename T, typename... Args> SharedPtr<T> make_shared(Args &&...args) {
    return makeShared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args> UniquePtr<T> make_unique(Args &&...args) {
    return makeUnique<T>(std::forward<Args>(args)...);
}

} // namespace CTCI
