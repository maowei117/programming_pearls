#ifndef CHAPTER1_SRC_BITSET_H_
#define CHAPTER1_SRC_BITSET_H_

#include <stdlib.h>

class BitSet {
 public:
    BitSet(size_t size);
    ~BitSet();

    void set(unsigned int pos);
    void clear(unsigned int pos);
    bool test(unsigned int pos);

    inline size_t size() const { return m_size; }

 private:
    size_t m_size{0};
    int* m_array{nullptr};

 private:
    static const size_t k_bitsPerSeg = 8 * sizeof(int);
};

#endif  // CHAPTER1_SRC_BITSET_H_