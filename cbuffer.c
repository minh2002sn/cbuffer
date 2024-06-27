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

/* Function definitions ----------------------------------------------- */
uint32_t cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
}

uint32_t cb_clear(cbuffer_t *cb)
{
}

uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
  int space_count     = 0;
  int num_avail_bytes = 0;
  if (cb == NULL)
    return CB_ERROR;

  if (buf == NULL)
    return CB_ERROR;

  if (!cb->active)
    return CB_ERROR;
  cb->active = 0;

  space_count = cb_space_count(cb);
  if (space_count >= nbytes)
  {
    num_avail_bytes = nbytes;
    cb->overflow    = 0;
  }
  else
  {
    num_avail_bytes = space_count;
    cb->overflow    = nbytes - space_count;
  }

  for (int i = 0; i < num_avail_bytes; i++)
  {
    cb_write_byte(cb, *((uint8_t *)buf + i));
  }

  cb->active = 1;
  return num_avail_bytes;
}

uint32_t cb_data_count(cbuffer_t *cb)
{
}

uint32_t cb_space_count(cbuffer_t *cb)
{
}

/* Private definitions ----------------------------------------------- */
static uint32_t cb_write_byte(cbuffer_t *cb, uint8_t byte)
{
  uint32_t next = cb->writer + 1;

  if (next == cb->size)
    next = 0;

  if (next == cb->reader)
    return CB_ERROR;

  *(cb->data + cb->writer) = byte;
  cb->writer               = next;
  return CB_SUCCESS;
}

/* End of file -------------------------------------------------------- */
