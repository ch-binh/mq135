#include "mq135.h"

static mq135_hw_ops_t hw_ops;

void mq135_set_hw_ops(mq135_hw_ops_t *ops)
{
    hw_ops = *ops;
}

uint32_t mq135_read_adc(void)
{
    if (hw_ops.read)
    {
        return hw_ops.read();
    }
    return -1;
}

uint32_t mq135_get_adc(void)
{
    return mq135_read_adc();
}
