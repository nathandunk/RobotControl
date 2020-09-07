// MIT License
//
// Copyright (c) 2020 Nathan Dunkelberger
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// Author: Nathan Dunkelberger
#include <Mahi/Daq.hpp>
#include <Mahi/Util.hpp>

using namespace mahi::daq;
using namespace mahi::util;

int main(int argc, char** argv) {

    MahiLogger->set_max_severity(Verbose);

    /// For this example, connect MSPC AO[0] to AI[0]
    /// DIO[1] to DIO[3]
    /// Encoder to MSPC DIO[0,2]
    MyRio myrio;
    if (!myrio.is_open())
        return 1;    

    /// On myRIO, DIO pins are shared with encoders. We must
    /// enable the encoder channels we wish to use. This will
    /// free DI[0,2,4,6].
    myrio.mspC.encoder.set_channels({0});
    // Set the units on one of our encoders
    myrio.mspC.encoder.units[0] = 360.0 / (46.8512*12);
    // Zero the encoder
    myrio.mspC.encoder.zero(0);

    myrio.mspC.AO.enable_values[0] = 0.0;
    
    myrio.mspC.DO.set_channels({3,4});
    myrio.mspC.DO.enable_values[3] = TTL_LOW;
    myrio.mspC.DO.enable_values[4] = TTL_LOW;

    /// Enable, this will set enable values on AO and DO, which we can read on AI[0] and DI[0]
    myrio.enable();
    sleep(1_ms);

    /// General I/O loop
    prompt("press enter to enable the motor");
    myrio.mspC.DO[3] = TTL_HIGH;

    while (!myrio.is_button_pressed()) {
        /// Synced read, reads all DAQ inputs
        // 0.2 A/V
        myrio.read_all();
        myrio.mspC.AO[0] = 0.5;
        print("encoder[0]: {} = {:+.2f} deg.", myrio.mspC.encoder[0], myrio.mspC.encoder.positions[0]);
        myrio.write_all();
        sleep(1_ms);
    }

    myrio.mspC.AO[0] = 0.00;
    myrio.mspC.DO[3] = TTL_LOW;

    myrio.mspC.DI.set_channels(myrio.mspC.DI.channels_allowed());

    /// myRIO will auto disable/close on destruction, but explicit calls are good practice
    myrio.disable();
    myrio.close();
}
