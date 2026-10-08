#include "concepts.hpp"
#include "list.hpp"
#include <initializer_list>
#include <type_traits>

namespace CTCI {

template <bool IsSet, Hashable Key, typename ValueType> class Map {
  private:
    using Entry = std::conditional_t<IsSet, Key, std::pair<Key, ValueType>>;
    using Bucket = List<Entry>;
    using Buckets = std::vector<Bucket>;

    Buckets buckets{101};

    size_t _size = 0;
    size_t _totalSize = 101;
    double _loadFactor = 0;

    std::hash<Key> hashFn = std::hash<Key>{};

    size_t hash(Key key) const { return hashFn(key) % _totalSize; }

    double calculateLoadFactor(double nSize) { return nSize / _totalSize; }

    void resize() {
        Buckets newBuckets{_totalSize *= 2};

        for (auto &entry : *this) {
            if constexpr (IsSet) {
                auto &bucket = newBuckets[hash(entry)];
                insert(bucket, std::move(entry));
            } else {
                auto &bucket = newBuckets[hash(entry.first)];
                insert(bucket, std::move(entry));
            }
            _loadFactor /= 2;
        }

        buckets = std::move(newBuckets);
    }

    ValueType &get(Bucket &bucket, Key key) {
        for (auto &entry : bucket) {
            if (entry.first == key)
                return entry.second;
        }

        bucket.push({key, ValueType{}});
        return get(bucket, key);
    }

    void insert(Bucket &bucket, Entry entry) {
        if constexpr (IsSet) {
            for (auto &key : bucket) {
                if (key == entry)
                    return;
            }
            bucket.push(entry);
        } else {
            auto &[key, val] = entry;
            for (auto &[bKey, bVal] : bucket) {
                if (bKey == key) {
                    bVal = val;
                    return;
                }
            }
            bucket.push(entry);
        }
    }

  public:
    Map() = default;
    Map(size_t size) : _totalSize(size), buckets(size) {}
    Map(std::initializer_list<Entry> list) { insert(list); }
    Map(size_t size, std::initializer_list<Entry> list) : _totalSize(size), buckets(size) { insert(list); }

    template <bool S = IsSet>
        requires(!S)
    ValueType &get(Key key) {
        auto hkey = hash(key);
        auto &bucket = buckets[hkey];

        return get(bucket, key);
    }

    template <std::ranges::range R> void insert(R &&rng) {
        for (auto &el : rng)
            insert(el);
    }

    void insert(Entry entry) {
        _loadFactor = calculateLoadFactor(++_size);
        if (_loadFactor > 0.80)
            resize();

        if constexpr (IsSet) {
            auto &bucket = buckets[hash(entry)];
            insert(bucket, std::move(entry));
        } else {
            auto &bucket = buckets[hash(entry.first)];
            insert(bucket, std::move(entry));
        }
    }

    [[nodiscard]] bool contains(Key key) const {
        auto bucket = buckets[hash(key)];
        for (auto &entry : bucket) {
            if constexpr (IsSet) {
                if (entry == key)
                    return true;
            } else {
                if (entry.first == key)
                    return true;
            }
        }
        return false;
    }

    template <bool A = IsSet>
        requires(!A)
    ValueType operator[](Key key) {
        return get(key);
    };

    [[nodiscard]] size_t size() const noexcept { return _size; }

    template <bool IsConst> class Iterator {
        List<Entry>::Pointer actual = nullptr;
        std::vector<List<Entry>> *buckets;
        size_t nBucket = 0;

        void next() {
            while (actual == nullptr && nBucket < buckets->size()) {
                actual = (*buckets)[nBucket].head;
                ++nBucket;
            }
        }

      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Entry;
        using pointer = std::conditional_t<IsConst, const Entry *, Entry *>;
        using reference = std::conditional_t<IsConst, const Entry &, Entry &>;

        Iterator(List<Entry>::Pointer ptr = nullptr) : actual(ptr) {};
        Iterator(std::vector<List<Entry>> *buckets) : buckets(buckets) { next(); }

        Iterator &operator++() {
            actual = actual->next;
            next();
            return *this;
        }

        Iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return *this;
        }

        reference operator*() const { return actual->val; }
        reference operator*() { return actual->val; }

        pointer operator->() const { return &actual->val; }
        pointer operator->() { return &actual->val; }

        friend bool operator==(const Iterator &a, const Iterator &b) { return a.actual == b.actual; };
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.actual != b.actual; };
    };

    using ForwardIterator = Iterator</*IsConst=*/false>;
    using ConstForwardIterator = Iterator</*IsConst=*/true>;

    ForwardIterator begin() { return {&buckets}; }
    ForwardIterator end() { return {}; }

    ConstForwardIterator begin() const { return {&buckets}; }
    ConstForwardIterator end() const { return {}; }
};

template <Hashable Key, typename Value> using HashMap = Map</**IsSet=*/false, Key, Value>;
template <Hashable Key> using Set = Map</**IsSet=*/true, Key, Key>;

} // namespace CTCI
