#include "qstring.h"

int std::patterns_in_str(string str, char pattern){
        int count = 0;
        for (int i = 0; i < str.size(); i++) if (str[i] == pattern) count++;
        return count;
    }