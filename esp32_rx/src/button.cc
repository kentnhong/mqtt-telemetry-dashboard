#include "button.h"
#include <string.h>
#include <stdlib.h>

bool btn_parse(const char* msg, uint32_t* count, uint32_t* timestamp_ms) {
    if (strncmp(msg, "BTN,", 4) != 0) {
        return false;
    }
    
    char* ptr = (char*)msg + 4;
    char* comma = strchr(ptr, ',');
    if (!comma) {
        return false;
    }
    
    *count = strtoul(ptr, nullptr, 10);
    *timestamp_ms = strtoul(comma + 1, nullptr, 10);
    return true;
}
