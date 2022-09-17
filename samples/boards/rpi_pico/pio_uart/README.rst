.. _pio_uart:

PIO UART
###########

Overview
********

A sample shows how to use PIO based UART.
This sample disable uart0 periperal and
replace it with PIO based UART.

Building and Running
********************

This application can be built and executed as follows:

.. zephyr-app-commands::
   :zephyr-app: samples/boards/rpi_pico/pio_uart
   :board: rpi_pico
   :goals: run
   :compact:

