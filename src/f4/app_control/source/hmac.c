#include <stdlib.h>
#include "hmac.h"
#include "CANopen.h"
#include "OD.h"

int hmac_send(void *data, size_t len, void *iv, void *seq_num, void *mac, void *arg)
{
    (void)iv;
    cryerror_t err;
    HMACSHA256Context ctx = {0};

    *((uint32_t*)seq_num) = __builtin_bswap32(OD_PERSIST_STATE.x6004_persistentState.EDL_SequenceCount);

    err = cryLoadHMACTransientKey(&CRYD1, 32, arg);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Init(&CRYD1, &ctx);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Update(&CRYD1, &ctx, len, data);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Final(&CRYD1, &ctx, mac);
    if (err != CRY_NOERROR) {
        return err;
    }

    return 0;
}
int hmac_recv(void *data, size_t len, void *iv, void *seq_num, void *mac, void *arg)
{
    (void)iv;
    cryerror_t err;
    HMACSHA256Context ctx = {0};
    uint8_t hmac[32] = {0};
    uint32_t recv_seq = __builtin_bswap32(*((uint32_t*)seq_num));

    err = cryLoadHMACTransientKey(&CRYD1, 32, arg);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Init(&CRYD1, &ctx);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Update(&CRYD1, &ctx, len, data);
    if (err != CRY_NOERROR) {
        return err;
    }

    err = cryHMACSHA256Final(&CRYD1, &ctx, hmac);
    if (err != CRY_NOERROR) {
        return err;
    }

    if (memcmp(hmac, mac, 32) != 0 && recv_seq >= OD_PERSIST_STATE.x6004_persistentState.EDL_SequenceCount) {
        return -1;
    }

    OD_PERSIST_STATE.x6004_persistentState.EDL_SequenceCount = recv_seq + 1;

    return 0;
}
