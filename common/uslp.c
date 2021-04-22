/**
 * @file    uslp.c
 * @brief   Unified Space Data Link Protocol (USLP) support library.
 *
 * @addtogroup CCSDS
 * @{
 */
#include "uslp.h"

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

static inline uint32_t uslp_gen_id(uint16_t scid, uint8_t vcid, uint8_t mapid)
{
    return __builtin_bswap32(
                USLP_TFVN   << USLP_TFPH_ID_TFVN_Pos |
                scid        << USLP_TFPH_ID_SCID_Pos |
                vcid        << USLP_TFPH_ID_VCID_Pos |
                mapid       << USLP_TFPH_ID_MAPID_Pos);
}

static inline bool uslp_parse_id(uint32_t id, uint16_t *scid, uint8_t *vcid, uint8_t *mapid)
{
    id = __builtin_bswap32(id);
    if ((id & USLP_TFPH_ID_TFVN) >> USLP_TFPH_ID_TFVN_Pos != USLP_TFVN)
        return false;
    *scid = (id & USLP_TFPH_ID_SCID) >> USLP_TFPH_ID_SCID_Pos;
    *vcid = (id & USLP_TFPH_ID_VCID) >> USLP_TFPH_ID_VCID_Pos;
    *mapid = (id & USLP_TFPH_ID_MAPID) >> USLP_TFPH_ID_MAPID_Pos;
    return true;
}

static inline void uslp_parse_tfdf_hdr(uslp_tfdf_hdr_t *hdr, uint8_t *rules, uslp_pid_t *upid, uint16_t *offset)
{
    *rules = (hdr->flags & USLP_TFDF_HDR_TFDZ_RULES) >> USLP_TFDF_HDR_TFDZ_RULES_Pos;
    *upid = (hdr->flags & USLP_TFDF_HDR_UPID) >> USLP_TFDF_HDR_UPID_Pos;
    *offset = __builtin_bswap16(hdr->offset);
}

static void *uslp_map_gen(const uslp_map_t *map, fb_t *fb)
{
    uslp_tfdf_hdr_t *tfdf_hdr;

    /* TODO: Currently only handles unsegmented data, implement remaining rules */
    if (fb->len > map->max_pkt_len)
        return NULL;

    tfdf_hdr = fb_push(fb, 1);
    tfdf_hdr->flags = map->upid << USLP_TFDF_HDR_UPID_Pos;
    if (map->sdu == SDU_MAP_OCTET_STREAM) {
        tfdf_hdr->flags |= USLP_TFDZ_RULES_OCTET_STREAM << USLP_TFDF_HDR_TFDZ_RULES_Pos;
    } else {
        tfdf_hdr->flags |= USLP_TFDZ_RULES_NO_SEG << USLP_TFDF_HDR_TFDZ_RULES_Pos;
    }

    return tfdf_hdr;
}

static void *uslp_vc_gen(const uslp_vc_t *vc, fb_t *fb, uint16_t scid, uint8_t vcid, uint8_t mapid, bool expedite)
{
    uslp_tfph_t *tfph;
    size_t vcf_cnt_len;
    uint64_t *vcf_cnt_var;

    if (expedite) {
        vcf_cnt_len = vc->expedited_len;
        vcf_cnt_var = vc->expedited_cnt;
    } else {
        vcf_cnt_len = vc->seq_ctrl_len;
        vcf_cnt_var = vc->seq_ctrl_cnt;
    }

#if USLP_USE_SDLS == 1
    sdls_hdr_t *sdls_hdr = NULL;
    sdls_tlr_t *sdls_tlr = NULL;
    /* TODO: Call SDLS functions */
    if (vc->has_sdls_hdr) {
        sdls_hdr = fb_push(fb, vc->sdls_hdr_len);
    }
    if (vc->has_sdls_tlr) {
        sdls_tlr = fb_put(fb, vc->sdls_tlr_len);
    }
#endif

    tfph = fb_push(fb, sizeof(uslp_tfph_t) + vcf_cnt_len);

    tfph->id = uslp_gen_id(scid, vcid, mapid);

#if (0)
    /* TODO: Implement FOP */
    uslp_ocf_t *ocf;
    ocf = fb_put(fb, sizeof(uslp_ocf_t));

    if (vcf_cnt_len) {
        (++(*vcf_cnt_var)) %= USLP_TFPH_VCF_CNT(vcf_cnt_len) + 1;
        for (uint8_t i = 0; i < vcf_cnt_len; i++) {
            tfph->vcf_cnt[i] = ((uint8_t*)vcf_cnt_var)[vcf_cnt_len - i];
        }
    }
#endif
    return tfph;
}

static void uslp_vc_recv(const uslp_vc_t *vc, fb_t *fb)
{
    (void)vc;
    uslp_tfph_t *tfph = (uslp_tfph_t*)fb->data;
    size_t vcf_cnt_len;

    if (tfph->id & USLP_TFPH_ID_EOFPH) {
        fb_pull(fb, sizeof(uint32_t));
        return;
    }

    vcf_cnt_len = (tfph->flags & USLP_TFPH_FLAGS_VCF_CNT_LEN) >> USLP_TFPH_FLAGS_VCF_CNT_LEN_Pos;

#if (0)
    /* TODO: Implement FARM */

#endif

    fb_pull(fb, sizeof(uslp_tfph_t) + vcf_cnt_len);
}

static void uslp_map_recv(const uslp_map_t *map, fb_t *fb)
{
    uslp_tfdf_hdr_t *tfdf_hdr = (uslp_tfdf_hdr_t*)fb->data;
    uint8_t rules, upid;
    uint16_t offset;

    /* Extract TFDF Header */
    uslp_parse_tfdf_hdr(tfdf_hdr, &rules, &upid, &offset);
    if (upid != map->upid)
        return;

    switch (rules) {
    case USLP_TFDZ_RULES_OCTET_STREAM:
    case USLP_TFDZ_RULES_NO_SEG:
        fb_pull(fb, 1);
        break;
    default:
        /* TODO: Currently only handles unsegmented data, implement remaining rules */
        return;
    }

    if (map->map_recv)
        map->map_recv(fb);
}

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

int uslp_map_send(const uslp_link_t *link, fb_t *fb, uint8_t vcid, uint8_t mapid, bool expedite)
{
    const uslp_pc_t *pc = link->pc_tx;
    const uslp_mc_t *mc = link->mc;
    const uslp_vc_t *vc = mc->vcid[vcid];
    const uslp_map_t *map = vc->mapid[mapid];

    uslp_map_gen(map, fb);
    fb->mac_hdr = uslp_vc_gen(vc, fb, mc->scid, vcid, mapid, expedite);
    ((uslp_tfph_t*)fb->mac_hdr)->len = __builtin_bswap16(fb->len) + pc->fecf_len;
    pc->phy_send(fb);

    return 0;
}

int uslp_mc_ocf_send(const uslp_link_t *link, fb_t *fb, uint8_t vcid)
{
    const uslp_pc_t *pc = link->pc_tx;
    const uslp_mc_t *mc = link->mc;
    const uslp_vc_t *vc = mc->vcid[vcid];
    (void)pc;
    (void)mc;
    (void)vc;
    (void)fb;

    return 0;
}

int uslp_cop_send(const uslp_link_t *link, fb_t *fb, uint8_t vcid)
{
    const uslp_pc_t *pc = link->pc_tx;
    const uslp_mc_t *mc = link->mc;
    const uslp_vc_t *vc = mc->vcid[vcid];
    (void)pc;
    (void)mc;
    (void)vc;
    (void)fb;

    return 0;
}

int uslp_vcf_send(const uslp_link_t *link, fb_t *fb, uint8_t vcid)
{
    const uslp_pc_t *pc = link->pc_tx;
    const uslp_mc_t *mc = link->mc;
    const uslp_vc_t *vc = mc->vcid[vcid];
    (void)pc;
    (void)mc;
    (void)vc;
    (void)fb;

    return 0;
}

int uslp_mcf_send(const uslp_link_t *link, fb_t *fb)
{
    const uslp_pc_t *pc = link->pc_tx;
    const uslp_mc_t *mc = link->mc;
    (void)pc;
    (void)mc;
    (void)fb;

    return 0;
}

void uslp_recv(const uslp_link_t *link, fb_t *fb)
{
    uslp_tfph_t *tfph = (uslp_tfph_t*)fb->data;
    const uslp_pc_t *pc = link->pc_rx;
    const uslp_mc_t *mc = link->mc;
    const uslp_vc_t *vc;
    const uslp_map_t *map;
    uint16_t scid;
    uint8_t vcid, mapid;

    /* Parse out IDs */
    if (!uslp_parse_id(tfph->id, &scid, &vcid, &mapid))
        return;

    /* Insert Service */
    if (pc->insert_zone) {
        /* TODO: Extract IN_SDU */
        if (mc->insert_recv)
            mc->insert_recv(fb);
    }

    /* Demux MC */
    /* TODO: Handle multiple master channels */

    /* MCF Service */
    if (mc->mcf_recv)
        mc->mcf_recv(fb);

    /* USLP_MC_OCF Service */
    /* TODO: Handle MC_OCF */

    /* Demux VC */
    vc = mc->vcid[vcid];
    if (vc == NULL)
        return;

    /* VCF Service */
    if (vc->vcf_recv)
        vc->vcf_recv(fb);

    /* VC Reception */
    uslp_vc_recv(vc, fb);

    /* Demux MAP */
    map = vc->mapid[mapid];
    if (map == NULL)
        return;

    /* MAP Reception/Extraction */
    uslp_map_recv(map, fb);
}
/** @} */
