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
}

uint32_t cb_data_count(cbuffer_t *cb)
{
}

uint32_t cb_space_count(cbuffer_t *cb)
{
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
