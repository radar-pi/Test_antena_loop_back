#include "save.h"

/**/

int sync_rx_meta_sched_example(struct bladerf *dev,rx_meta_data *data)
{
    int status;
    struct bladerf_metadata meta;
    unsigned int i;
    /* 150 ms timestamp increment */
    const uint64_t ts_inc_150ms = ((uint64_t)data->samplerate) * 150 / 1000;
    /* 1 ms timestamp increment */
    const uint64_t ts_inc_1ms = data->samplerate / 1000;
    memset(&meta, 0, sizeof(meta));
    /* Perform scheduled RXs by having meta.timestamp set appropriately
     * and ensuring the BLADERF_META_FLAG_RX_NOW flag is cleared. */
    meta.flags = 0;
    /* Retrieve the current timestamp */
    status = bladerf_get_timestamp(dev, BLADERF_RX, &meta.timestamp);
    if (status != 0) {
        fprintf(stderr, "Failed to get current RX timestamp: %s\n",
                bladerf_strerror(status));
    } else {
        printf("Current RX timestamp: 0x%016" PRIx64 "\n", meta.timestamp);
    }
  
    /* Schedule first RX to be 150 ms in the future */
    meta.timestamp += ts_inc_150ms;
    /* Receive samples and do work on them */
   
    for (i = 0; i < data->rx_count && status == 0; i++) {
       
        status = bladerf_sync_rx(dev, data->samples,
                 data -> samples_len, &meta, 2 * data->timeout_ms);
        
        if (status != 0) {
            fprintf(stderr, "Scheduled RX failed: %s\n\n",
                    bladerf_strerror(status));
        } else if (meta.status & BLADERF_META_STATUS_OVERRUN) {
            fprintf(stderr, "Overrun detected in scheduled RX. "
                            "%u valid samples were read.\n\n",
                    meta.actual_count);
        } else {
            printf("RX'd %u samples at t=0x%016" PRIx64 "\n", meta.actual_count,
                   meta.timestamp);
            fflush(stdout);
            /* ... Process samples here ... */
            /* Schedule the next RX to be 1 ms after the end of the samples we
             * just processed */
            meta.timestamp += data->samples_len + ts_inc_1ms;
        }
    }
    return status;
}

int configure_channel(struct bladerf *dev,channel_config *c)
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

int file_csv(){

	FILE*archive;
	archive = fopen("./Data/data_base_so.dat","r+b");

	if(archive==NULL) {
		perror("Erro ao abrir arquivo!");
		return -1;
	}
	else{


		fclose(archive);
		archive=NULL;
		return 1;
		
	}
}



