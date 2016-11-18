//
// cpp includes
//

#include <cstdint>
#include <tuple>


//
// arduino includes
//
#include <Arduino.h>


//
// project includes
//

#include "comm/comm.hpp"



//
// init code
//

void setup() {
    // configure and wait for USB<-->host connection
    Serial.begin(HOST_BAUD_RATE);
    while (!Serial) {}

    // configure the servo control serial
    servo_serial.begin(SERVO_BAUD_RATE);

    // send a RequestFrame to the host and gather the frames
    request_max_frames();       // TODO: error checking
    consume_frame_stream();     // TODO: need to hold num_messages? ring buffer _should_ have this info already

    // we now have work to do!
}



//
// loop
//

void loop() {
    bool valid;
    ActionFrame action;
    std::tie(action, valid) = action_buffer.pop();
    if (not valid) {
        return; // holding pattern
    }

    // doesn't hurt to double check
    if (action.hdr.magic != FRAME_MAGIC) {
        return; // TODO: halt? respond to host?
    } else if (action.hdr.type != ActionFrame::TYPE) {
        return; // TODO: halt? respond to host?
    }

    // TODO: take action!
}
