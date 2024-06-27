/**
 * @file       cbuffer.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date       26/06/2024
 * @author     Minh Phung Nhat
 *             Hung Pham Duc
 *             Khoi Nguyen Thanh
 * @brief      Circular Buffer
 *             This Circular Buffer is safe to use in IRQ with single reader,
 *             single writer. No need to disable any IRQ.
 *
 *             Capacity = <size> - 1
 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------ */
#include "cbuffer.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/**
 * @brief           Read 1 byte from circular buffer
 *
 * @param[in]       cb      Pointer to a cbuffer_t structure
 * @param[in]       byte    Pointer to data buffer
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
static uint32_t cb_read_byte(cbuffer_t *cb, uint8_t *byte);

/* Function definitions ----------------------------------------------- */
uint32_t cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
  if (cb == NULL)
    return CB_ERROR;
  if (buf == NULL)
    return CB_ERROR;
  if (size >= CB_MAX_SIZE)
    return CB_ERROR;

  cb->data     = buf;
  cb->size     = size;
  cb->writer   = 0;
  cb->reader   = 0;
  cb->overflow = 0;
  cb->active   = 1;

  return CB_SUCCESS;
}

uint32_t cb_clear(cbuffer_t *cb)
{
  if (cb == NULL)
    return CB_ERROR;

  cb->data     = 0;
  cb->size     = 0;
  cb->writer   = 0;
  cb->reader   = 0;
  cb->overflow = 0;
  cb->active   = 0;

  return CB_SUCCESS;
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  int data_count      = 0;
  int num_avail_bytes = 0;
  if (cb == NULL)
    return CB_ERROR;

  if (buf == NULL)
    return CB_ERROR;

  if (!cb->active)
    return CB_ERROR;
  cb->active = 0;

  data_count = cb_data_count(cb);
  if (data_count >= nbytes)
    num_avail_bytes = nbytes;
  else
    num_avail_bytes = data_count;

  for (int i = 0; i < num_avail_bytes; i++)
  {
    cb_read_byte(cb, (uint8_t *)buf + i);
  }

  cb->active = 1;
  return num_avail_bytes;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
}

uint32_t cb_data_count(cbuffer_t *cb)
{
}

uint32_t cb_space_count(cbuffer_t *cb)
{
  int res = 0;

  if (cb == NULL)
    return CB_ERROR;

  if (cb->reader > cb->writer)
    res = cb->reader - cb->writer - 1;
  else if (cb->reader < cb->writer)
    res = cb->size - cb->writer + cb->reader - 1;
  else
    res = cb->size - 1;

  return res;
}

/* Private definitions ----------------------------------------------- */

static uint32_t cb_read_byte(cbuffer_t *cb, uint8_t *byte)
{
  uint32_t next = cb->reader + 1;

  if (cb->reader == cb->writer)
    return CB_ERROR;

  if (next == cb->size)
    next = 0;

  *byte      = *(cb->data + cb->reader);
  cb->reader = next;
  return CB_SUCCESS;
}

/* End of file -------------------------------------------------------- */
