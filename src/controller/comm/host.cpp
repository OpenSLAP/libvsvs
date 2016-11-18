#include "host.hpp"

/** scratch buffer for storing incoming frames before processing */
static std::uint8_t recv_buffer[RECEIVE_BUFFER_SIZE];



// TODO: need some sort of return code?
// TODO: don't strong-arm it and bail on back to back [-inf, 0] return codes from write()?
template <typename T>
void send_frame(const T& frame) {
    std::size_t remaining = sizeof(T);
    const std::uint8_t* ptr = reinterpret_cast<const std::uint8_t*>(&frame);
    while (remaining > 0) {
        remaining -= Serial.write(ptr + (sizeof(T)-remaining), remaining);
    }
    Serial.flush(); // flush the tx
}

void request_frames(std::uint16_t count) {
    send_frame(RequestFrame(count));
}

void request_max_frames() {
    request_frames(action_buffer.remaining());
}



// TODO: don't strong-arm it and bail on back to back [-inf, 0] return codes from readBytes()?
template <typename T>
int read_frame(const std::uint8_t* buffer, std::size_t max_len) {
    // TODO: C++ is great, but a syntax to express "this argument is guaranteed to be a compile-time constant" would be great
    //       currently, the check must be done at call site.
    // static_assert(sizeof(T) < max_len, "buffer not large enough to hold frame type");
    if (sizeof(T) > max_len) { return -1; }

    // TODO: can simplify into one variable?
    auto remaining = sizeof(T);
    std::size_t total_bytes = 0;
    while (remaining > 0) {
        auto bytes_read = Serial.readBytes((char*)buffer + (sizeof(T) - remaining), remaining);
        remaining -= bytes_read;
        total_bytes += bytes_read;
    }

    if (total_bytes != sizeof(T)) {
        return -1;
    }


    return total_bytes;
}



// TODO: completion condition checking
int consume_frame_stream() {
    // make sure that
    //  a) we can fit an ActionFrame
    //  b) a SyncFrame is smaller than an ActionFrame so reading the terminating SyncFrame will simply read
    //     to completion and time out
    static_assert(sizeof(ActionFrame) < RECEIVE_BUFFER_SIZE, "receive buffer would never fit an ActionFrame");
    static_assert(sizeof(SyncFrame) < sizeof(ActionFrame),   "SyncFrame is larger than ActionFrame");

    int num_frames = 0;
    while (not action_buffer.full()) {
        auto bytes_read = read_frame<ActionFrame>(&recv_buffer[0], RECEIVE_BUFFER_SIZE);
        if (bytes_read == -1) {
            // TODO: panic here?
            return -1;
        }

        const ActionFrame* frame = (const ActionFrame*)(&recv_buffer[0]);

        // is this a valid message?
        if (frame->hdr.magic != FRAME_MAGIC) {
            return -1;
        }

        // what kind of message is it?
        switch (frame->hdr.type) {
        case ActionFrame::TYPE: {
            action_buffer.insert(*frame);
            ++num_frames;
            break;
        }

        case SyncFrame::TYPE: {
            // TODO: assert and save sync state
            return num_frames;
        }

        default:
            return -1; // TODO
        }
    }

    return -1;
}
