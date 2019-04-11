#ifndef SAVE_H
#define SAVE_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libbladeRF.h>



typedef struct {
    bladerf_channel channel;
    unsigned int frequency;
    unsigned int bandwidth;
    unsigned int samplerate;
    int gain;
}channel_config ;

typedef struct{
    int16_t *samples;
    unsigned int samples_len;
    unsigned int rx_count;
    unsigned int samplerate;
    unsigned int timeout_ms;

}rx_meta_data;


int sync_rx_meta_sched_example(struct bladerf *dev, rx_meta_data *data);
int configure_channel(struct bladerf *dev, channel_config *c);

#endif