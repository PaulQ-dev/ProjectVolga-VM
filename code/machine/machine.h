#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <iomanip>
#include "../misc/qstring.h"
#include "../misc/qtypes.h"

using namespace std;

namespace Volga{
    class VolgaVM{
        private:
            bool ready;
            uint address;
            ushort value;
            ushort accumulator;
            vector<ushort> rom;
            vector<ushort> ram;
            vector<ushort> console_buffer;
            int get_value();
            int get_value(uint read_address);
            int set_value(uint write_address);
        public:
            int run();
            int bios();
            VolgaVM();
    };
}