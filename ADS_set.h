#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

template<typename Key, size_t N = 7>
class ADS_set {
public:
    class Iterator;

    using value_type = Key;
    using key_type = Key;
    using reference = key_type &;
    using const_reference = const key_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = Iterator;
    using const_iterator = Iterator;
    using key_compare = std::less<key_type>;   // B+-Tree
    using key_equal = std::equal_to<key_type>; // Hashing
    using hasher = std::hash<key_type>;        // Hashing
private:
    struct Node {
        key_type value;
        Node *next = nullptr;
        Node *head = nullptr;

        ~Node() {
            delete next;
            delete head;
        }
    };

    Node *table = nullptr;


    size_type sz = 0, table_size = N;
    float max_lf = 0.7;

    size_type hash_idx(const key_type &key) const { return hasher{}(key) % table_size; }

    bool find_pos(const key_type &key) const {
        size_type a = hash_idx(key);
        if (table[a].head == nullptr) return false;
        for (Node *i = table[a].head; i != nullptr; i = i->next) {
            if (key_equal{}(key, i->value)) {
                return true;
            }
        }
        return false;
    }

    void insert_unchecked(const key_type &key) {
        Node *tmp = new Node();
        size_type position = hash_idx(key);


        tmp->next = table[position].head;
        tmp->value = key;
        table[position].head = tmp;


        ++sz;
        if (sz > max_lf * table_size) rehash();
    }


    void rehash() {
        std::vector<Key> v;
        for (size_t i = 0; i < table_size; ++i) {
            if (table[i].head != nullptr) {
                for (Node *j = table[i].head; j != nullptr; j = j->next) {
                    v.push_back(j->value);
                }
            }
        }

        delete[] table;
        sz = 0;
        table_size = table_size * 2;
        table = new Node[table_size];

        for (const auto &it2: v) {
            insert_unchecked(it2);
        }
    }


public:

    ADS_set() {
        table = new Node[table_size];
    }

    ADS_set(std::initializer_list<key_type> ilist) {
        table = new Node[table_size];
        insert(ilist);
    }

    template<typename InputIt>
    ADS_set(InputIt first, InputIt last) {
        table = new Node[table_size];
        insert(first, last);
    }

    ADS_set(const ADS_set &other) { throw std::runtime_error{"Not implemented!1"}; }
//    {
//        table = new Node[table_size];
//        for (const auto &elem:other) insert_unchecked(elem);
//    }

    ~ADS_set() { delete[] table; }

    ADS_set &operator=(const ADS_set &other) { throw std::runtime_error{"Not implemented!2"}; }

    ADS_set &operator=(std::initializer_list<key_type> ilist) { throw std::runtime_error{"Not implemented!3"}; }

    iterator find(const key_type &key) const { throw std::runtime_error{"Not implemented!4"}; }

    void clear() { throw std::runtime_error{"Not implemented!5"}; }

    void swap(ADS_set &other) { throw std::runtime_error{"Not implemented!6"}; }

    std::pair<iterator, bool> insert(const key_type &key) { throw std::runtime_error{"Not implemented!7"}; }

    size_type erase(const key_type &key) { throw std::runtime_error{"Not implemented!8"}; }

    const_iterator begin() const { throw std::runtime_error{"Not implemented!9"}; }

    const_iterator end() const { throw std::runtime_error{"Not implemented!10"}; }

    friend bool operator==(const ADS_set &lhs, const ADS_set &rhs) { throw std::runtime_error{"Not implemented!10"}; }

    friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs) { throw std::runtime_error{"Not implemented!11"}; }


    size_type count(const key_type &key) const { return find_pos(key); }

    size_type size() const { return sz; }

    bool empty() const { return !sz; }

    void insert(std::initializer_list<key_type> ilist) {

    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (auto it = first; it != last; ++it) {
            if (!find_pos(*it)) {
                insert_unchecked(*it);
            }
        }
    }


    void dump(std::ostream &o = std::cerr) const {
        for (size_type i = 0; i < table_size; i++) {
            o << "Element[" << i << "]: ";
            for (Node *j = table[i].head; j != nullptr; j = j->next) {
                o << j->value;
                if (j->next != nullptr) o << " --> ";
            }
            o << std::endl;
        }
    }
};

template<typename Key, size_t N>
class ADS_set<Key, N>::Iterator {
public:
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using iterator_category = std::forward_iterator_tag;

    explicit Iterator(/* implementation-dependent */);

    reference operator*() const;

    pointer operator->() const;

    Iterator &operator++();

    Iterator operator++(int);

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) { throw std::runtime_error{"Not implemented!12"}; }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) { throw std::runtime_error{"Not implemented!12"}; }
};

template<typename Key, size_t N>
void swap(ADS_set<Key, N> &lhs, ADS_set<Key, N> &rhs) { lhs.swap(rhs); }

#endif // ADS_SET_H