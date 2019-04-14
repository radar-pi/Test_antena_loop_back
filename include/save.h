#ifndef SAVE_H
#define SAVE_H
#include <stdio.h>
#include <libbladeRF.h>

/* The RX and TX channels are configured independently for these parameters */
struct channel_config {
	bladerf_channel channel;
	unsigned int frequency;
	unsigned int bandwidth;
	unsigned int samplerate;
	int gain;
};

typedef struct {

	unsigned int num_buffer;		//The number of buffers to use in the underlying data stream.
	unsigned int buffer_size;		//The size of the underlying stream buffers, in samples. Multiples of 1024.
	unsigned int num_transfers;	//The number of active USB transfers that may be in-flight.
	unsigned int timeout_ms;		//Timeout (milliseconds) for transfers in the underlying data stream.
}meta_data_params;

int configure_channel(struct bladerf *dev, struct channel_config *c);
int sync_rx_meta_sched_example(struct bladerf *dev, meta_data_params params);
#endif
