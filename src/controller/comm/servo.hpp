#ifndef VESUVIUS_COMM_SERVO_HPP
#define VESUVIUS_COMM_SERVO_HPP

#include "monoplex/monoplex.hpp"

/** Singleton to be used for all communication to the servos. */
static monoplex::Serial servo_serial = monoplex::Serial::at_usart0();

#endif
