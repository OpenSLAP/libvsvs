#ifndef VESUVIUS_UTILITY_HPP
#define VESUVIUS_UTILITY_HPP

#include <cstdint>
#include <utility>

namespace vesuvius {

/** Simple ring buffer to stream data.
 */
template <typename T, std::uint16_t N>
class RingBuffer {
protected:
    // storage
    T buffer[N];

    // current resident count
    std::uint16_t count;
    // points to where we will be reading from
    std::uint16_t head;
    // points to where the next value will be inserted
    std::uint16_t tail;

    // (head == tail) means either empty or full

public:
    RingBuffer() : count(0), head(0), tail(0) {}

    /** Returns true if the buffer has no readable values in it.
     */
    inline bool empty() {
        return head == tail // where we want to inert is where we want to read
           and count == 0;  // with no items
    }

    /** Returns true if the buffer has no empty slots in it.
     */
    inline bool full() {
        return head == tail // where we want to inert is where we want to read
           and count == N;  // with all the lemons
    }

    /** Returns the number of items in the buffer.
     */
    inline std::uint16_t size() { return count; }

    /** Returns the max number of items that can be in the buffer.
     */
    inline std::uint16_t capacity() { return N; }

    /** Returns the number of slots left in the buffer.
     */
    inline std::uint16_t remaining() { return N - count; }


    /** Places a value in the buffer.
     *
     * Overwrites the "oldest" read value currently in the buffer.
     * Returns false if the buffer is full, otherwise true.
     */
    bool insert(const T& val) {
        if (full()) { return false; }

        // we aren't full so let's write it
        if (count < N) { count++; }
        buffer[tail] = val;

        // move the scribe
        tail = (tail + 1) % count;

        return true;
    }


    /** Get a value from the buffer.
     *
     * Returns the "oldest" unread value currently in the buffer.
     * Returns a pair containing the value (or it's default constructed value) and a boolean
     * where the boolean specifies whether the associated value is valid.
     *
     * Reads will be invalid if the buffer is empty.
     */
    std::pair<T, bool> pop() {
        if (empty()) {
            return std::make_pair(T(), false);
        }

        T val = buffer[head];

        // move the reader
        head = (head + 1) % count;
        --count;

        return std::make_pair(val, true);
    }
};

} // namespace

#endif // header guard
