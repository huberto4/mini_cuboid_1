#include "mbed.h"
#include <stdint.h>
#include "math.h" 
#include "ControllerLoop.h"
#include "sensors_actuators.h"
#include "uart_comm_thread.h"
#include "state_machine.h"
 
static BufferedSerial serial_port(USBTX, USBRX);

float Ts = 0.002f;    // sampling time, typically approx 1/500

//******************************************************************************
//---------- main loop -------------
//******************************************************************************

int main()
{

    // --------- mini cuboid,
    sensors_actuators hardware(Ts);         // in this class all the physical ios are handled
    ControllerLoop loop(&hardware,Ts);       // this is for the main controller loop
    state_machine sm(&hardware,&loop,0.02);
    ThisThread::sleep_for(200);
// ----------------------------------
    serial_port.set_baud(115200);
    serial_port.set_format(8,BufferedSerial::None,1);
    serial_port.set_blocking(false); // force to send whenever possible and data is there
// ----------------------------------
    loop.start_loop();
    ThisThread::sleep_for(20);
    sm.start_loop();
    while(1)
        ThisThread::sleep_for(200);
        
}   // END OF main

