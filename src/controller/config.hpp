#ifndef VESUVIUS_CONFIG_HPP
#define VESUVIUS_CONFIG_HPP

//
// communication
//

// (incomplete, on the wire) message buffer size
#ifndef RECEIVE_BUFFER_SIZE
#define RECEIVE_BUFFER_SIZE 256         // frames should never exceed this
#endif // recv buffer

// (complete) message buffer size
#ifndef FRAME_BUFFER_SIZE
#define FRAME_BUFFER_SIZE   128         // keep 128 messages (max) on hand by default
#endif // frame buffer


// host->controller baud rate
#ifndef HOST_BAUD_RATE
#define HOST_BAUD_RATE      57600
#endif // host baud


// controller->servo baud rate
#ifndef SERVO_BAUD_RATE
#define SERVO_BAUD_RATE     1000000     // default to 1MB/s
#endif // servo baus

#endif // header guard
