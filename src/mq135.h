#ifndef MQ135_H
#define MQ135_H

#include <stdint.h>

typedef struct
{
    uint32_t (*read)(void);
} mq135_hw_ops_t;

/* HW OPS*/
void mq135_set_hw_ops(mq135_hw_ops_t *ops);
uint32_t mq135_read_adc(void);

/* API */
uint32_t mq135_get_adc(void);

#endif // MQ135_H