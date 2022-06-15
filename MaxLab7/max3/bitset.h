#pragma once

#ifndef BITSET_H
#define BITSET_H

#include <QString>

#define bit (8 * sizeof(int))

template<size_t Bits>
class bitset {

private:

    int bits[Bits / 32 + 1];

    bool get_bit(size_t bit_num) {

        return ((bits[bit_num / bit] & (1U << (bit_num % bit))));
    }

    void _reset(size_t bit_num) {

        bits[bit_num / bit] &= ~(1U << (bit_num % bit));
    }

    void _set(size_t bit_num) {

        bits[bit_num / bit] |= (1U << (bit_num % bit));
    }

public:

    bitset() {

        for (size_t i = 0; i < Bits; ++i)
            reset(i);

    }

    void set(size_t bit_num) {

        if (bit_num >= Bits)
            return;

        bit_num = Bits - bit_num;

        --bit_num;

        bits[bit_num / bit] |= (1U << (bit_num % bit));

    }

    void reset(size_t bit_num) {

        if (bit_num >= Bits)
            return;

        bit_num = Bits - bit_num;

        --bit_num;

        bits[bit_num / bit] &= ~(1U << (bit_num % bit));

    }

    void reset() {

        for (size_t i = 0; i < Bits; ++i)
            reset(i);

    }

    bool test(size_t bit_num) {

        if (bit_num >= Bits)
            return false;

        bit_num = Bits - bit_num;

        --bit_num;

        return (bits[bit_num / bit] & (1U << (bit_num % bit)));

    }

    void flip(size_t bit_num) {

        if (bit_num >= Bits)
            return;

        bit_num = Bits - bit_num;

        --bit_num;

        bits[bit_num / bit] ^= (1U << (bit_num % bit));

    }

    void flip() {

        for (size_t i = 0; i < Bits; ++i) {

            if (get_bit(i))
                _reset(i);
            else
                _set(i);
        }

    }

    bool operator[] (size_t bit_num) {

        if (bit_num >= Bits)
            return false;

        bit_num = Bits - bit_num;

        --bit_num;

        return ((bits[bit_num / bit] & (1U << (bit_num % bit))));
    }

    size_t size() noexcept {

        return Bits;

    }

    size_t count() {

        size_t counter = 0;

        for (size_t i = 0; i < Bits; ++i)
            if (get_bit(i))
                ++counter;

        return counter;

    }

    QString to_string() {

        QString s_bits;

        for (size_t i = 0; i < Bits; i++) {

            s_bits.push_back(get_bit(i) ? '1' : '0');

        }

        return s_bits;

    }

    unsigned to_ulong() {

        unsigned num = 0;

        for (size_t i = 0; i < Bits; ++i)
            num += get_bit(i) * pow(2, Bits - 1 - i);

        return num;

    }

    bool any() {

        for (size_t i = 0; i <= Bits; ++i)
            if (get_bit(i))
                return true;

        return false;

    }

    bool none() {

        return !any();

    }

    bool all() {

        return count() == size();
    }

};

#endif // BITSET_H
