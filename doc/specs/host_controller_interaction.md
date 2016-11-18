Host-Controller Interaction
===========================

A guide to message passing between the host and the printer controller.


Initialization
==============

1. Controller sends a `RequestFrame`
    * This validates the `frame_version` to make sure we are speaking the same "language".
    * Gives the Host the number of frames the controller can (or wants to in some cases) receive.
        * May not make sense to always fill the buffer
            * For instance, you would not want to full-stop and fill the entire buffer during a long and/or detailed trace-path.
            * This method lets the controller and host both make decisions independently about frame synchronization.

2. Host responds with a stream of `Frame` messages terminated by a `SyncFrame`
    * The host must respond with [1, N] frames where N is given in the `RequestFrame`.
        * The host can certainly send less than N, but sending a `SyncFrame` immediately is considered an error.
    * The stream of N frames is terminated by a `SyncFrame`
        * Verifies the host and the controller are on the same step (0 during initialization).
        * Simple sanity check.



Printing
========

When the action buffer has been exhausted (or in high performance, DMA-heavy systems, during long servo times)
the controller can issue `RequestFrame` messages until the print is done.


Completion
==========

Completion conditions for the print is a `SyncFrame` where the current step is equal to the total step count.

This same paradigm (current == total) can be used as a soft-abort. The controller should realize it's count
is off and halt awaiting new instructions.
