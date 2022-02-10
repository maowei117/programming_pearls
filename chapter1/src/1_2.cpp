#include <stdio.h>

#include <algorithm>
#include <random>
#include <vector>

class BitSet {
 public:
    BitSet(size_t size);
    ~BitSet();

    void set(unsigned int pos);
    void clear(unsigned int pos);
    bool test(unsigned int pos);

 private:
    size_t m_size{0};
    int* m_array{nullptr};

 private:
    static const size_t k_bitsPerSeg = 8 * sizeof(int);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    BitSet bs(10000000UL);

    // Random set bitset.
    std::mt19937 generator;
    std::uniform_int_distribution<std::mt19937::result_type> dist(0UL, 100UL);
    std::vector<int> random_nums;
    for (int i = 0; i < 20; i++) {
        int random = dist(generator);
        bs.set(random);
        random_nums.push_back(random);
    }

    std::stable_sort(random_nums.begin(), random_nums.end());
    printf("Generate random numbers:\n");
    for (auto r : random_nums) {
        printf("%d\t", r);
    }
    printf("\n\n");

    // Test bitset.
    printf("Test bitset.\n");
    for (int i = 0; i < 101; ++i) {
        printf("%d:%d\t", i, bs.test(i));
        if ((i + 1) % 10 == 0) { printf("\n"); }
    }

    // Clear bitset.
    printf("Clear bitset.\n");
    for (int i = 0; i < 101; ++i) {
        bs.clear(i);
    }

    // Test bitset.
    printf("Test bitset.\n");
    for (int i = 0; i < 101; ++i) {
        printf("%d:%d\t", i, bs.test(i));
        if ((i + 1) % 10 == 0) { printf("\n"); }
    }

    return 0;
}