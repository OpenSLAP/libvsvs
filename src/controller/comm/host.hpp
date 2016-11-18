#ifndef VESUVIUS_COMM_HOST_HPP
#define VESUVIUS_COMM_HOST_HPP

#include <cstdint>

#include <Arduino.h>

#include "../config.hpp"
#include "../utility.hpp"

#include "gosuvius/structures.hpp"



/** holds a (linearized) buffer of Frames that need to be executed */
static vesuvius::RingBuffer<ActionFrame, FRAME_BUFFER_SIZE> action_buffer;


/** Send a frame from the controller to the host.
 *
 * Blocks until completion.
 * In the case of cascading errors, may never return.
 */
template <typename T>
void send_frame(const T& frame);


/** Request as many frames as will fit in the global frame buffer.
 *
 * NOTE: The host can choose to send less frames than we request.
 */
void request_max_frames();

/** Request N frames from the host.
 *
 * NOTE: The host can choose to send less frames than we request.
 */
void request_frames(std::uint16_t count);


/** Reads an entire frame (designated by T), blocking until complete.
 *
 * Returns a negative integral in the case of an error.
 * Some error cases include:
 *   - buffer length is smaller than size of the message
 *   - total bytes read != size of the message (unlikely, but possible)
 *
 * Otherwise, returns the number of bytes read.
 */
template <typename T>
int read_frame(const std::uint8_t* buffer, std::size_t max_len);


/** Consumes the [Frame, Frame, ..., SyncFrame] stream from the host.
 *
 * Returns a negative integral if an error was encountered in read_frame() or in post-process.
 * Otherwise, returns the number of frames we received (excluding the terminating SyncFrame).
 */
int consume_frame_stream();

#endif
