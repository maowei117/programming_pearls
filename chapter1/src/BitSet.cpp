#include "BitSet.h"

BitSet::BitSet(size_t size) : m_size(size) {
    m_array = new int[1 + m_size / sizeof(int)];
}

BitSet::~BitSet() {
    if (m_array != nullptr) {
        delete m_array;
        m_array = nullptr;
    }
}

void BitSet::set(unsigned int pos) {
    unsigned int seg_pos = pos / k_bitsPerSeg;
    unsigned int bit_pos = pos % k_bitsPerSeg;
    m_array[seg_pos] |= (0x1 << bit_pos);
}

void BitSet::clear(unsigned int pos) {
    unsigned int seg_pos = pos / k_bitsPerSeg;
    unsigned int bit_pos = pos % k_bitsPerSeg;
    m_array[seg_pos] &= ~(0x1 << bit_pos);
}

bool BitSet::test(unsigned int pos) {
    unsigned int seg_pos = pos / k_bitsPerSeg;
    unsigned int bit_pos = pos % k_bitsPerSeg;
    return m_array[seg_pos] & (0x1 << bit_pos);
}