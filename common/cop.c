/**
 * @file    cop.c
 * @brief   Communications Operation Procedures (COP) support library.
 *
 * @addtogroup CCSDS
 * @{
 */
#include "cop.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

uint8_t cop_fop1(const uslp_vc_t *vc, fb_t *fb, bool expedite)
{
    uint8_t flags = 0;
    size_t vcf_cnt_len;
    uint64_t *vcf_cnt_var;
    uint8_t *vcf_cnt;

    if (expedite) {
        vcf_cnt_var = vc->expedited_cnt;
        vcf_cnt_len = vc->expedited_len;
    } else {
        vcf_cnt_var = vc->seq_ctrl_cnt;
        vcf_cnt_len = vc->seq_ctrl_len;
    }
    if (vcf_cnt_len) {
        vcf_cnt = fb_push(fb, vcf_cnt_len);
        if (vc->lock && vc->unlock)
            vc->lock(vc->lock_arg);
        *vcf_cnt_var += 1;
        *vcf_cnt_var %= USLP_TFPH_VCF_CNT(vcf_cnt_len) + 1;
        if (vc->lock && vc->unlock)
            vc->unlock(vc->lock_arg);
        for (uint8_t i = 0; i < vcf_cnt_len; i++) {
            vcf_cnt[i] = ((uint8_t*)vcf_cnt_var)[vcf_cnt_len - i - 1];
        }
    }
    flags |= vcf_cnt_len & USLP_TFPH_FLAGS_VCF_CNT_LEN;

#if (0)
    uslp_ocf_t *ocf;
    ocf = fb_put(fb, sizeof(uslp_ocf_t));
    flags |= USLP_TFPH_FLAGS_OCF;
#endif
    return flags;
}

/** @} */
