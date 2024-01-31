#include "machine.h"

using namespace Volga;

VolgaVM::VolgaVM(){
    rom = vector<ushort>(0x080000);
    ram = vector<ushort>(0x100000);
    ready = false;
    address = 0;
    value = 0;
}
int VolgaVM::get_value(){
    return get_value(address);
}
int VolgaVM::get_value(uint read_address){
    if(read_address < 0x080000){
        value = rom[read_address];
        return 0;
    }
    else if(read_address < 0x100000){
        value = ram[read_address];
        return 0;
    }
    else{
        return -1;
    }
}
int VolgaVM::run(){
    address = 0;
    while (true){
        {
            int res = get_value();
            if(res != 0){
                return 0;
            }
            switch (value)
            {
                case 0xFADE:
                case 0x0000:
                    return 0;
                    break;
                case 0x4100:
                    address++;
                    get_value();
                    accumulator = value;
                    break;
                case 0x4101:{
                    address++;
                    get_value();
                    ushort value_old = value;
                    address++;
                    get_value();
                    get_value(value_old*0x00010000+value);
                    accumulator = value;
                    break; 
                }
                case 0x4200:
                    break;
                case 0x1600:{
                    address++;
                    get_value();
                    if (!setlocale(LC_CTYPE, ""))
                    {   
                        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
                        return 1;
                    }
                    printf("%lc",value);
                    break;
                }
                case 0x16FF:
                    printf("\n");
                    break;
                case 0x1024:
                    break;
                default:
                    return -1;
                    break;
            }
            address++;
        }
    }
    return 0;
}
int VolgaVM::bios(){
    cout << "Welcome to Volga 16bit Virtual Machine v0.1\n" << "Type 'exit' to exit\n";
    bool state = true;
    while(true){
        string input;
        {
            string stateS = "READY";
            if(!state) stateS = "FAILURE";
            cout << stateS << ">";
        }
        getline(cin, input);
        input.erase(input.find_last_not_of(' ')+1);
        input.erase(0, input.find_first_not_of(' '));
        string command = input;
        string cmd = command.substr(0, command.find(' '));
        command.erase(0, command.find(' '));
        string arg = command.substr(0, command.find(' '));
        if(cmd.compare("exit") == 0){
            return 0;
        }
        else if(cmd.compare("load") == 0){
            ifstream rom_in( "rom.bin", ios::binary );
            if(rom_in.good()){
                vector<ubyte> buffer(istreambuf_iterator<char>(rom_in), {});
                for(int i = 0; i < buffer.size(); i+=2){
                    rom[i/2] = 256*buffer[i]+buffer[i+1];
                }
                cout << "File 'rom.bin' loaded, " << buffer.size() << " bytes loaded" << endl;
                state = true;
                ready = true;
            }
            else{
                cout << "File 'rom.bin' does not exists" << endl;
                state = false;
            }
        }
        else if(cmd.compare("run") == 0){
            if(ready){
                int res = run();
                if(res == 0){
                    cout << "Program closed with code 0, success." << endl;
                    state = true;
                }
                else{
                    cout << "Program closed with code " << res <<", failure" << endl;
                    state = false;
                }
            }
            else{
                cout << "No ROM loaded" << endl;
                state = false;
            }
        }
        else if(input.compare("") != 0){
            cout << "Cannot resolve '" << input << "' as command\n";
            state = false;
        }
    }
}