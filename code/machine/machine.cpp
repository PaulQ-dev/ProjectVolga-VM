#include "machine.h"

using namespace Volga;

VolgaVM::VolgaVM(){
    rom = vector<ushort>(0x080000);
    ram = vector<ushort>(0x100000);
    console_buffer = vector<ushort>();
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
    else if(read_address < 0x180000){
        value = ram[read_address-0x080000];
        return 0;
    }
    else{
        return -1;
    }
}
int VolgaVM::set_value(uint write_address){
    if(write_address < 0x080000){
        return -1;
    }
    else if(write_address < 0x180000){
        ram[write_address-0x080000] = value;
        return 0;
    }
    else{
        return -1;
    }
}
int VolgaVM::run(){
    address = 0;
    value = 0;
    console_buffer = vector<ushort>();
    while (true){
        {
            int res = get_value();
            if(res != 0) return res;
            switch (value)
            {
                //NOP
                case 0x1024:{
                    break;
                }
                //COUT #UTF-16
                case 0x1600:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    if (!setlocale(LC_CTYPE, "")){                                      //)
                        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                        return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                    }                                                                   //)
                    printf("%lc",value);                                                //)
                    break;
                }
                //COUT ADR
                case 0x1601:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    res = get_value(value_old*0x00010000+value);
                    if(res != 0) return res;
                    if (!setlocale(LC_CTYPE, "")){                                      //)
                        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                        return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                    }                                                                   //)
                    printf("%lc",value);                                                //)
                    break;
                }
                //COUT #N #UTF-16[N]
                case 0x1602:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    for(ushort i = 0; i < len; i++){
                        address++;
                        get_value();
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",value);     
                    }
                    break;
                }
                //COUT #N ADR
                case 0x1603:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    uint value_address = value_old*0x00010000+value;
                    for(ushort i = 0; i < len; i++){
                        get_value(value_address);
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",value);
                        value_address++;     
                    }
                    break;
                }
                //CLINE #UTF-16
                case 0x1610:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    if (!setlocale(LC_CTYPE, "")){                                      //)
                        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                        return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                    }                                                                   //)
                    printf("%lc\n",value);                                                //)
                    break;
                }
                //CLINE ADR
                case 0x1611:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    res = get_value(value_old*0x00010000+value);
                    if(res != 0) return res;
                    if (!setlocale(LC_CTYPE, "")){                                      //)
                        fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                        return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                    }                                                                   //)
                    printf("%lc\n",value);                                                //)
                    break;
                }
                //CLINE #N #UTF-16[N]
                case 0x1612:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    for(ushort i = 0; i < len; i++){
                        address++;
                        get_value();
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",value);     
                    }
                    printf("\n");
                    break;
                }
                //CLINE #N ADR
                case 0x1613:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    uint value_address = value_old*0x00010000+value;
                    for(ushort i = 0; i < len; i++){
                        get_value(value_address);
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",value);
                        value_address++;     
                    }
                    printf("\n");
                    break;
                }
                //CLINE
                case 0x161F:{
                    printf("\n");
                    break;
                }
                //CINS
                case 0x1700:{
                    string buffer;
                    getline(cin,buffer);
                    for(ushort i = 0; i < buffer.length(); i++){
                        console_buffer.push_back(buffer[i]);
                    }
                    break;
                }
                //COUTS
                case 0x1701:{
                    for(int i = 0; i < console_buffer.size(); i++){
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",console_buffer[i]);  
                    }
                    break;
                }
                //CLINES
                case 0x1702:{
                    for(int i = 0; i < console_buffer.size(); i++){
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        printf("%lc",console_buffer[i]);  
                    }
                    printf("\n");  
                    break;
                }
                //CBCLR
                case 0x170F:{
                    console_buffer.clear();
                    break;
                }
                //CPUSH #UTF-16
                case 0x1710:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    console_buffer.push_back(value);
                    break;
                }
                //CPUSH ADR
                case 0x1711:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    res = get_value(value_old*0x00010000+value);
                    if(res != 0) return res;
                    console_buffer.push_back(value);
                    break;
                }
                //CPUSH #N #UTF-16[]
                case 0x1712:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    for(ushort i = 0; i < len; i++){
                        address++;
                        res = get_value();
                        if(res != 0) return res;
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        console_buffer.push_back(value);     
                    }
                    break;
                }
                //CPUSH #N ADR
                case 0x1713:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort len = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    uint value_address = value_old*0x00010000+value;
                    for(ushort i = 0; i < len; i++){
                        get_value(value_address);
                        if (!setlocale(LC_CTYPE, "")){                                      //)
                            fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");//)
                            return 1;                                                       //}https://stackoverflow.com/questions/26325227/c-print-value-of-unsigned-short-variable-as-unicode-character
                        }                                                                   //)
                        console_buffer.push_back(value);
                        value_address++;     
                    }
                    break;
                }
                //CPUSHA
                case 0x171A:{
                    console_buffer.push_back(accumulator);
                    break;
                }
                //LDA #N
                case 0x4100:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    accumulator = value;
                    break;
                }
                //LDA ADR
                case 0x4101:{
                    address++;
                    int res = get_value();
                    if(res != 0) return res;
                    ushort value_old = value;
                    address++;
                    res = get_value();
                    if(res != 0) return res;
                    res = get_value(value_old*0x00010000+value);
                    if(res != 0) return res;
                    accumulator = value;
                    break;
                }
                //STA ADR
                case 0x4200:{
					address++;
                    int res = get_value();
                    if(res != 0) return res;
					ushort value_old = value;
					address++;
                    res = get_value();
                    if(res != 0) return res;
                    uint address_new = value_old*0x00010000+value;
                    value = accumulator;
                    res = set_value(address_new);
                    break;
				}
                //HLT
                case 0xFADE:{
                    return 0;
                    break;
                }
                //Other
                default:{
                    cout << address << " : " << value << endl;
                    return -2;
                    break;
                }
            }
            address++;
        }
    }
    return 0;
}
int VolgaVM::bios(){
    cout << "Welcome to Volga 16bit Virtual Machine v0.2\nVolga BIOS v1.0" << "Type 'exit' to exit\n";
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
        if(cmd.compare("exit") == 0) return 0;
        else if(cmd.compare("load") == 0){
            ifstream rom_in( "rom.bin", ios::binary );                      //)
            if(rom_in.good()){                                              //}https://stackoverflow.com/questions/5420317/reading-and-writing-binary-file
                vector<ubyte> buffer(istreambuf_iterator<char>(rom_in), {});//)
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
