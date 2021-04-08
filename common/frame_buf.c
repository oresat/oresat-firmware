/**
 * @file    frame_buf.c
 * @brief   Frame buffer support library.
 *
 * @addtogroup RADIO
 * @{
 */
#include "frame_buf.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

static const fb_t empty_frame;

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

fb_t *fb_alloc(size_t len)
{
    if (len > FB_MAX_LEN) {
        return NULL;
    }

    fb_t *fb = __fb_alloc();
    if (fb != NULL) {
        *fb = empty_frame;
        fb->max_len = FB_MAX_LEN;
        fb->head = fb->buf;
        fb->data = fb->head;
        fb->tail = fb->head;
        fb->end = fb->head + len;
    }

    return fb;
}

void fb_free(fb_t *fb)
{
    if (fb == NULL) {
        return;
    }
    __fb_free(fb);
}


void fb_post(fb_t *fb)
{
    if (fb == NULL) {
        return;
    }
    __fb_post(fb);
}

void fb_post_first(fb_t *fb)
{
    if (fb == NULL) {
        return;
    }
    __fb_post_first(fb);
}

fb_t *fb_get(void)
{
    return __fb_get();
}

void fb_reserve(fb_t *fb, size_t len)
{
    if (fb == NULL || fb->data != fb->tail || fb->data + len > fb->end) {
        return;
    }
    fb->data += len;
    fb->tail = fb->data;
}

void *fb_put(fb_t *fb, size_t len)
{
    if (fb == NULL || fb->tail + len > fb->end) {
        return NULL;
    }
    void *ptr = fb->tail;
    fb->tail += len;
    fb->len += len;
    return ptr;
}

void *fb_push(fb_t *fb, size_t len)
{
    if (fb == NULL || fb->data - len < fb->head) {
        return NULL;
    }
    fb->data -= len;
    fb->len += len;
    return fb->data;
}

void *fb_pull(fb_t *fb, size_t len)
{
    if (fb == NULL || fb->data + len > fb->tail) {
        return NULL;
    }
    fb->data += len;
    fb->len -= len;
    return fb->data;

}

void fb_trim(fb_t *fb, size_t len)
{
    if (fb == NULL || fb->tail - len < fb->data) {
        return;
    }
    fb->tail -= len;
    fb->len -= len;
}

size_t fb_headroom(fb_t *fb)
{
    if (fb == NULL) {
        return 0;
    }
    return fb->data - fb->head;
}

size_t fb_tailroom(fb_t *fb)
{
    if (fb == NULL) {
        return 0;
    }
    return fb->end - fb->tail;
}

/** @} */
