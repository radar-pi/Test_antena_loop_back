#include "save.h"
#include <pthread.h> 
int configure_channel(struct bladerf *dev, struct channel_config *c)
{
    int status;
    status = bladerf_set_frequency(dev, c->channel, c->frequency);
    if (status != 0) {
        fprintf(stderr, "Failed to set frequency = %u: %s\n", c->frequency,
                bladerf_strerror(status));
        return status;
    }
    status = bladerf_set_sample_rate(dev, c->channel, c->samplerate, NULL);
    if (status != 0) {
        fprintf(stderr, "Failed to set samplerate = %u: %s\n", c->samplerate,
                bladerf_strerror(status));
        return status;
    }
    status = bladerf_set_bandwidth(dev, c->channel, c->bandwidth, NULL);
    if (status != 0) {
        fprintf(stderr, "Failed to set bandwidth = %u: %s\n", c->bandwidth,
                bladerf_strerror(status));
        return status;
    }
    status = bladerf_set_gain(dev, c->channel, c->gain);
    if (status != 0) {
        fprintf(stderr, "Failed to set gain: %s\n", bladerf_strerror(status));
        return status;
    }
    return status;
}

int sync_rx_meta_sched_example(struct bladerf *dev, meta_data_params params)
{
    int status;	
    bladerf_enable_module(dev,BLADERF_CHANNEL_RX(0),true);
    /* Configure the device's RX for use with the sync interface.
    * SC16 Q11 samples *with* metadata are used. */
    status = bladerf_sync_config(dev, BLADERF_RX_X1,BLADERF_FORMAT_SC16_Q11_META,
         params.num_buffer, params.buffer_size, params.num_transfers, params.timeout_ms);
    if (status != 0) {
        fprintf(stderr, "Failed to configure RX sync interface: %s\n",
        bladerf_strerror(status));
        return status;
    }
    return status;
}



