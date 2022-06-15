#pragma once

#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include <iostream>
#include <QString>
#include <forward_list>
#include <vector>

using std::pair;
using std::forward_list;
using std::vector;

template<typename Key, typename Value,
    typename Hash = std::hash<Key>, typename EqualTo = std::equal_to<Key>>
class unordered_map {

    typedef pair<Key, Value> value_type;

    struct node {

        value_type data;

        size_t cached;

        node(value_type _data, size_t _cached) :
            data(_data), cached(_cached) {}

        QString key_val() {

            return QString::number(data.first) + " " + data.second;

        }

    };

    const size_t default_sz = 60;

    size_t bucket_count = 0, sz = default_sz;

    double load_factor = 0;

    double max_load_factor = 0.5;


    forward_list<node> elements;

    typedef typename forward_list<node>::iterator bucket_iter;

    vector<bucket_iter> buckets;

public:

    class iterator {

        bucket_iter cur;

    public:

        iterator(const iterator& other) : cur(other.cur) {}

        iterator(const bucket_iter& other) : cur(other) {}

        iterator& operator++() {

            ++cur;

            return *this;

        }

        iterator& operator--() {

            --cur;

            return *this;
        }

        node& operator*() {

            return *cur;

        }

        bool operator== (const iterator& other) const noexcept {
            return cur == other.cur;
        }

        bool operator!= (const iterator& other) const noexcept {
            return cur != other.cur;
        }

        bool operator== (const bucket_iter& other) const noexcept {
            return cur == other;
        }

        bool operator!= (const bucket_iter& other) const noexcept {
            return cur != other;
        }
    };

    bucket_iter begin() {

        return elements.begin();
    }

    bucket_iter end() {

        return elements.end();

    }

    unordered_map() {

        buckets.resize(default_sz, elements.end());

    }

    size_t bucket_counter() const noexcept {
        return bucket_count;
    }

    const size_t size() const noexcept {
        return sz;
    }

    const double get_max_load_factor() const noexcept {
        return max_load_factor;
    }

    void set_max_load_factor(double new_value) noexcept {
        max_load_factor = new_value;
    }

    const double get_load_factor() noexcept {

        load_factor = bucket_count / sz;

        return load_factor;
    }

    bool empty() const noexcept {
        return !sz;
    }

    void rehash(size_t new_size) {

        if (new_size <= sz)
            return;

        vector<bucket_iter> new_buckets(new_size, elements.end());

        for (bucket_iter it = elements.begin(); it != elements.end(); ++it) {

            it->cached = Hash{}(it->data.first) % new_size;

        }

        size_t prev_cached = elements.begin()->cached;

        bucket_iter it = elements.begin();

        new_buckets[it->cached] = it;

        for (++it; it != elements.end(); it) {

            if (!EqualTo{}(prev_cached, it->cached)) {

                new_buckets[it->cached] = it;

            }

            if (++it != elements.end()) {

                prev_cached = it->cached;

            }

        }

        sz = new_size;

        buckets = new_buckets;

    }

    void insert(Key&& _key, Value&& _val = Value()) {

        if (get_load_factor() >= max_load_factor)
            rehash(sz * 4);

        size_t cache = Hash{}(_key) % buckets.size();

        if (buckets[cache] != elements.end()) {

            elements.insert_after(buckets[cache], node(std::make_pair(_key, _val), cache));
        }

        else {

            buckets[cache] = elements.insert_after(elements.before_begin(),
                node(std::make_pair(_key, _val), cache));
        }

        ++bucket_count;
    }

    QString deploy_by(Key&& _key) {

        QString info = "\n";

        size_t cached = Hash{}(_key) % buckets.size();

        bucket_iter it = buckets[cached];

        for (it; it != elements.end() && it->cached == cached; ++it) {

            info += QString::number(it->data.first);
            info += "\n";
        }

        return info;

    }

    QString show() {

        QString info = "\n";

        for (auto& it : elements) {
            info += QString::number((it).data.first);
            info += "\n";
        }

        return info;
    }

    void erase(Key&& _key) {

        if (empty())
            return;

        size_t cached = Hash{}(_key) % buckets.size();

        if (buckets[cached] == elements.end())
            return;

        bucket_iter it = buckets[cached];

        for (it; it->cached == cached; ++it) {

            bucket_iter next_next = it;

            ++next_next;

            if (next_next == elements.end() || ++next_next == elements.end())
                break;

            if (it->cached != next_next->cached)
                break;

        }

        if (it == buckets[cached]) {

            bucket_iter temp = it;

            if (++temp == elements.end())
                buckets[cached] = elements.end();
            else
                elements.erase_after(it);

        }

        else
            elements.erase_after(it);

        --bucket_count;

    }

    bool contains(Key&& _key) {

        size_t cached = Hash{}(_key) % buckets.size();

        return buckets[cached] != elements.end();

    }

    void clear() {

        elements.clear();

        buckets.clear();

        bucket_count = 0;

        buckets.resize(default_sz, elements.end());

    }

    Value& operator[] (Key&& _key) {

        Key unhashed_key = _key;

        size_t cached = Hash{}(_key) % buckets.size();

        if (buckets[cached] == elements.end())
            insert(std::move(unhashed_key));

        bucket_iter it = buckets[cached];

        for (it; it->cached == cached; ++it) {

            bucket_iter temp = it;

            if (++temp == elements.end() || temp->cached != cached)
                break;

        }

        return it->data.second;
    }

    size_t count(Key&& _key) {

        size_t cached = Hash{}(_key) % buckets.size();

        bucket_iter it = buckets[cached];

        size_t counter = 0;

        for (it; it != elements.end() && it->cached == cached; ++it) {

            ++counter;

        }

        return counter;

    }

};

#endif // UNORDERED_SET_H
