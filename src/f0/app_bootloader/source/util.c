#include "util.h"

const char* msg_t_to_str(const msg_t v) {
    switch (v) {
    case MSG_OK:
        return ("MSG_OK");
    case MSG_TIMEOUT:
        return ("MSG_TIMEOUT");
    case MSG_RESET:
        return ("MSG_RESET");
    default:
        return ("MSG_???");
    }
}
