#include <assert.h>
#include <string.h>
#include <limits.h>

#include "test_hmac.h"
#include "chprintf.h"

struct TestCase {
    const uint8_t *key;
    const size_t keylen;
    const uint8_t *data;
    const size_t datalen;
    const uint8_t *hmac;
    const size_t hmaclen;
};

void testHMACSHA256(BaseSequentialStream *chp, CRYDriver *cryp, const struct TestCase * tc) {
    HMACSHA256Context ctx = {0};

    chprintf(chp, "cryLoadHMACTransientKey() ... ");
    if (cryLoadHMACTransientKey(cryp, tc->keylen, tc->key) != CRY_NOERROR) {
        chprintf(chp, "failed\r\n");
        return;
    } else {
        chprintf(chp, "good\r\n");
    }

    chprintf(chp, "cryHMACSHA256Init() ... ");
    if (cryHMACSHA256Init(cryp, &ctx) != CRY_NOERROR) {
        chprintf(chp, "failed\r\n");
        return;
    } else {
        chprintf(chp, "good\r\n");
    }

    chprintf(chp, "cryHMACSHA256Update() ... ");
    if (cryHMACSHA256Update(cryp, &ctx, tc->datalen, tc->data) != CRY_NOERROR) {
        chprintf(chp, "failed\r\n");
        return;
    } else {
        chprintf(chp, "good\r\n");
    }

    chprintf(chp, "cryHMACSHA256Final() ... ");
    uint8_t out[32] = {0};
    if (cryHMACSHA256Final(cryp, &ctx, out) != CRY_NOERROR) {
        chprintf(chp, "HMACFinal failed\r\n");
        return;
    } else {
        chprintf(chp, "good\r\n");
    }

    chprintf(chp, "HMAC result comparison ... ");
    if (memcmp(out, tc->hmac, sizeof(out) < tc->hmaclen ? sizeof(out) : tc->hmaclen) != 0) {
        chprintf(chp, "failed\r\n");
        chprintf(chp, "- Expect:");
        for(size_t i = 0; i < tc->hmaclen; ++i) {
                chprintf(chp, " %02x", tc->hmac[i]);
        }
        chprintf(chp, "\r\n- Result:");
        for(size_t i = 0; i < sizeof(out); ++i) {
                chprintf(chp, " %02x", out[i]);
        }
        chprintf(chp, "\r\n");
    } else {
        chprintf(chp, "good\r\n");
    }
}


void cmd_hmac(BaseSequentialStream *chp, int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    /* Taken from RFC 4231: Test Vectors for HMAC-SHA-256 */
    // 4.2. Test Case 1
    static const uint8_t tc1_key[] = {  // 20 bytes
        0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
        0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, };
    static const uint8_t tc1_data[] = {  // "Hi There"
        0x48, 0x69, 0x20, 0x54, 0x68, 0x65, 0x72, 0x65 };
    static const uint8_t tc1_hmac[] = {
        0xb0, 0x34, 0x4c, 0x61, 0xd8, 0xdb, 0x38, 0x53, 0x5c, 0xa8, 0xaf, 0xce,
        0xaf, 0x0b, 0xf1, 0x2b, 0x88, 0x1d, 0xc2, 0x00, 0xc9, 0x83, 0x3d, 0xa7,
        0x26, 0xe9, 0x37, 0x6c, 0x2e, 0x32, 0xcf, 0xf7 };
    static_assert(sizeof(tc1_key) == 20);
    static_assert(sizeof(tc1_data) == sizeof("Hi There")-1);
    osalDbgAssert(memcmp(tc1_data, "Hi There",
        sizeof(tc1_data)) == 0, "TC1 data does not match expected string");
    static_assert(sizeof(tc1_hmac) == 32);

    const struct TestCase TC1 = {
        .key = tc1_key,
        .keylen = sizeof(tc1_key),
        .data = tc1_data,
        .datalen = sizeof(tc1_data),
        .hmac = tc1_hmac,
        .hmaclen = sizeof(tc1_hmac),
    };

    // 4.3. Test Case 2: Test with a key shorter than the length of the HMAC
    // output.
    static const uint8_t tc2_key[] = { 0x4a, 0x65, 0x66, 0x65 };  // "Jefe"
    static const uint8_t tc2_data[] = {  // "what do ya want for nothing?"
        0x77, 0x68, 0x61, 0x74, 0x20, 0x64, 0x6f, 0x20, 0x79, 0x61, 0x20, 0x77,
        0x61, 0x6e, 0x74, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x6e, 0x6f, 0x74, 0x68,
        0x69, 0x6e, 0x67, 0x3f };
    static const uint8_t tc2_hmac[] = {
        0x5b, 0xdc, 0xc1, 0x46, 0xbf, 0x60, 0x75, 0x4e, 0x6a, 0x04, 0x24, 0x26,
        0x08, 0x95, 0x75, 0xc7, 0x5a, 0x00, 0x3f, 0x08, 0x9d, 0x27, 0x39, 0x83,
        0x9d, 0xec, 0x58, 0xb9, 0x64, 0xec, 0x38, 0x43 };
    static_assert(sizeof(tc2_key) == sizeof("Jefe")-1);
    osalDbgAssert(memcmp(tc2_key, "Jefe",
        sizeof(tc2_key)) == 0, "TC2 key does not match expected string");
    static_assert(sizeof(tc2_data) == sizeof("what do ya want for nothing?")-1);
    osalDbgAssert(memcmp(tc2_data, "what do ya want for nothing?",
        sizeof(tc2_data)) == 0, "TC2 data does not match expected string");
    static_assert(sizeof(tc2_hmac) == 32);

    const struct TestCase TC2 = {
        .key = tc2_key,
        .keylen = sizeof(tc2_key),
        .data = tc2_data,
        .datalen = sizeof(tc2_data),
        .hmac = tc2_hmac,
        .hmaclen = sizeof(tc2_hmac),
    };

    // 4.4. Test Case 3: Test with a combined length of key and data that is
    // larger than 64 bytes (= block-size of SHA-224 and SHA-256).
    static const uint8_t tc3_key[] = {  // 20 bytes
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa };
    static const uint8_t tc3_data[] = {  // 50 bytes
        0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
        0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
        0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
        0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
        0xdd, 0xdd };
    static const uint8_t tc3_hmac[] = {
        0x77, 0x3e, 0xa9, 0x1e, 0x36, 0x80, 0x0e, 0x46, 0x85, 0x4d, 0xb8, 0xeb,
        0xd0, 0x91, 0x81, 0xa7, 0x29, 0x59, 0x09, 0x8b, 0x3e, 0xf8, 0xc1, 0x22,
        0xd9, 0x63, 0x55, 0x14, 0xce, 0xd5, 0x65, 0xfe };
    static_assert(sizeof(tc3_key) == 20);
    static_assert(sizeof(tc3_data) == 50);
    static_assert(sizeof(tc3_hmac) == 32);

    const struct TestCase TC3 = {
        .key = tc3_key,
        .keylen = sizeof(tc3_key),
        .data = tc3_data,
        .datalen = sizeof(tc3_data),
        .hmac = tc3_hmac,
        .hmaclen = sizeof(tc3_hmac),
    };

    // 4.5. Test Case 4: Test with a combined length of key and data that is
    // larger than 64 bytes (= block-size of SHA-224 and SHA-256).
    static const uint8_t tc4_key[] = {  // 25 bytes
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19 };
    static const uint8_t tc4_data[] = {  // 50 bytes
        0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
        0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
        0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
        0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd,
        0xcd, 0xcd };
    static const uint8_t tc4_hmac[] = {
        0x82, 0x55, 0x8a, 0x38, 0x9a, 0x44, 0x3c, 0x0e, 0xa4, 0xcc, 0x81, 0x98,
        0x99, 0xf2, 0x08, 0x3a, 0x85, 0xf0, 0xfa, 0xa3, 0xe5, 0x78, 0xf8, 0x07,
        0x7a, 0x2e, 0x3f, 0xf4, 0x67, 0x29, 0x66, 0x5b };
    static_assert(sizeof(tc4_key) == 25);
    static_assert(sizeof(tc4_data) == 50);
    static_assert(sizeof(tc4_hmac) == 32);

    const struct TestCase TC4 = {
        .key = tc4_key,
        .keylen = sizeof(tc4_key),
        .data = tc4_data,
        .datalen = sizeof(tc4_data),
        .hmac = tc4_hmac,
        .hmaclen = sizeof(tc4_hmac),
    };

    // 4.6. Test Case 5: Test with a truncation of output to 128 bits.
    static const uint8_t tc5_key[] = {  // 20 bytes
        0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c };
    static const uint8_t tc5_data[] = {  // "Test With Truncation"
        0x54, 0x65, 0x73, 0x74, 0x20, 0x57, 0x69, 0x74, 0x68, 0x20, 0x54, 0x72,
        0x75, 0x6e, 0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e };
    static const uint8_t tc5_hmac[] = {
        0xa3, 0xb6, 0x16, 0x74, 0x73, 0x10, 0x0e, 0xe0, 0x6e, 0x0c, 0x79, 0x6c,
        0x29, 0x55, 0x55, 0x2b };
    static_assert(sizeof(tc5_key) == 20);
    static_assert(sizeof(tc5_data) == sizeof("Test With Truncation") - 1);
    osalDbgAssert(memcmp(tc5_data, "Test With Truncation",
        sizeof(tc5_data)) == 0, "TC5 data does not match expected string");
    static_assert(sizeof(tc5_hmac)*CHAR_BIT == 128);

    const struct TestCase TC5 = {
        .key = tc5_key,
        .keylen = sizeof(tc5_key),
        .data = tc5_data,
        .datalen = sizeof(tc5_data),
        .hmac = tc5_hmac,
        .hmaclen = sizeof(tc5_hmac),
    };

    // 4.7. Test Case 6: Test with a key larger than 128 bytes (= block-size
    // of SHA-384 and SHA-512)
    static const uint8_t tc6_key[] = {  // 131 bytes
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa };
    static const uint8_t tc6_data[] = {  // "Test Using Larger Than Block-Size
        // Key - Hash Key First"
        0x54, 0x65, 0x73, 0x74, 0x20, 0x55, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x4c,
        0x61, 0x72, 0x67, 0x65, 0x72, 0x20, 0x54, 0x68, 0x61, 0x6e, 0x20, 0x42,
        0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x53, 0x69, 0x7a, 0x65, 0x20, 0x4b, 0x65,
        0x79, 0x20, 0x2d, 0x20, 0x48, 0x61, 0x73, 0x68, 0x20, 0x4b, 0x65, 0x79,
        0x20, 0x46, 0x69, 0x72, 0x73, 0x74 };
    static const uint8_t tc6_hmac[] = {
        0x60, 0xe4, 0x31, 0x59, 0x1e, 0xe0, 0xb6, 0x7f, 0x0d, 0x8a, 0x26, 0xaa,
        0xcb, 0xf5, 0xb7, 0x7f, 0x8e, 0x0b, 0xc6, 0x21, 0x37, 0x28, 0xc5, 0x14,
        0x05, 0x46, 0x04, 0x0f, 0x0e, 0xe3, 0x7f, 0x54 };
    static_assert(sizeof(tc6_key) == 131);
    static_assert(sizeof(tc6_data) == sizeof("Test Using Larger Than Block-"
        "Size Key - Hash Key First") - 1);
    osalDbgAssert(memcmp(tc6_data, "Test Using Larger Than Block-Size Key - "
        "Hash Key First",
        sizeof(tc6_data)) == 0, "TC6 Data does not match expected string");
    static_assert(sizeof(tc6_hmac) == 32);

    const struct TestCase TC6 = {
        .key = tc6_key,
        .keylen = sizeof(tc6_key),
        .data = tc6_data,
        .datalen = sizeof(tc6_data),
        .hmac = tc6_hmac,
        .hmaclen = sizeof(tc6_hmac),
    };

    // 4.8. Test Case 7: Test with a key and data that is larger than 128
    // bytes (= block-size of SHA-384 and SHA-512).
    static const uint8_t tc7_key[] = {  // 131 bytes
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa };
    static const uint8_t tc7_data[] = {  // "This is a test using a larger than
        // block-size key and a larger than block-size data. The key needs to
        // be hashed before being used by the HMAC algorithm."
        0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x74, 0x65,
        0x73, 0x74, 0x20, 0x75, 0x73, 0x69, 0x6e, 0x67, 0x20, 0x61, 0x20, 0x6c,
        0x61, 0x72, 0x67, 0x65, 0x72, 0x20, 0x74, 0x68, 0x61, 0x6e, 0x20, 0x62,
        0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x73, 0x69, 0x7a, 0x65, 0x20, 0x6b, 0x65,
        0x79, 0x20, 0x61, 0x6e, 0x64, 0x20, 0x61, 0x20, 0x6c, 0x61, 0x72, 0x67,
        0x65, 0x72, 0x20, 0x74, 0x68, 0x61, 0x6e, 0x20, 0x62, 0x6c, 0x6f, 0x63,
        0x6b, 0x2d, 0x73, 0x69, 0x7a, 0x65, 0x20, 0x64, 0x61, 0x74, 0x61, 0x2e,
        0x20, 0x54, 0x68, 0x65, 0x20, 0x6b, 0x65, 0x79, 0x20, 0x6e, 0x65, 0x65,
        0x64, 0x73, 0x20, 0x74, 0x6f, 0x20, 0x62, 0x65, 0x20, 0x68, 0x61, 0x73,
        0x68, 0x65, 0x64, 0x20, 0x62, 0x65, 0x66, 0x6f, 0x72, 0x65, 0x20, 0x62,
        0x65, 0x69, 0x6e, 0x67, 0x20, 0x75, 0x73, 0x65, 0x64, 0x20, 0x62, 0x79,
        0x20, 0x74, 0x68, 0x65, 0x20, 0x48, 0x4d, 0x41, 0x43, 0x20, 0x61, 0x6c,
        0x67, 0x6f, 0x72, 0x69, 0x74, 0x68, 0x6d, 0x2e};
    static const uint8_t tc7_hmac[] = {
        0x9b, 0x09, 0xff, 0xa7, 0x1b, 0x94, 0x2f, 0xcb, 0x27, 0x63, 0x5f, 0xbc,
        0xd5, 0xb0, 0xe9, 0x44, 0xbf, 0xdc, 0x63, 0x64, 0x4f, 0x07, 0x13, 0x93,
        0x8a, 0x7f, 0x51, 0x53, 0x5c, 0x3a, 0x35, 0xe2 };

    static_assert(sizeof(tc7_key) == 131);
    static_assert(sizeof(tc7_data) == sizeof("This is a test using a larger "
        "than block-size key and a larger than block-size data. The key needs "
        "to be hashed before being used by the HMAC algorithm.") - 1);
    osalDbgAssert(memcmp(tc7_data, "This is a test using a larger than block-"
        "size key and a larger than block-size data. The key needs to be "
        "hashed before being used by the HMAC algorithm.",
        sizeof(tc7_data)) == 0, "Test 7 data does not match expected string");
    static_assert(sizeof(tc7_hmac) == 32);

    const struct TestCase TC7 = {
        .key = tc7_key,
        .keylen = sizeof(tc7_key),
        .data = tc7_data,
        .datalen = sizeof(tc7_data),
        .hmac = tc7_hmac,
        .hmaclen = sizeof(tc7_hmac),
    };

    chprintf(chp, "TC1\r\n");
    testHMACSHA256(chp, &CRYD1, &TC1);
    chprintf(chp, "TC2\r\n");
    testHMACSHA256(chp, &CRYD1, &TC2);
    chprintf(chp, "TC3\r\n");
    testHMACSHA256(chp, &CRYD1, &TC3);
    chprintf(chp, "TC4\r\n");
    testHMACSHA256(chp, &CRYD1, &TC4);
    chprintf(chp, "TC5\r\n");
    testHMACSHA256(chp, &CRYD1, &TC5);
    chprintf(chp, "TC6\r\n");
    testHMACSHA256(chp, &CRYD1, &TC6);
    chprintf(chp, "TC7\r\n");
    testHMACSHA256(chp, &CRYD1, &TC7);
    chprintf(chp, "HMAC test complete\r\n");
}
