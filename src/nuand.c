#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <libbladeRF.h>
#include "save.h"

int main(int argc, char *argv[]){
	int status;
	struct channel_config config;
	struct bladerf *dev = NULL;
	struct bladerf_devinfo dev_info;
	meta_data_params params;
	//params = (meta_data_params*)malloc(sizeof(meta_data_params));
	/* Initialize the information used to identify the desired device
	* to all wildcard (i.e., "any device") values */
	bladerf_init_devinfo(&dev_info);
	/* Request a device with the provided serial number.
	* Invalid strings should simply fail to match a device. */
	if (argc >= 2) {
		strncpy(dev_info.serial, argv[1], sizeof(dev_info.serial) - 1);
	}
	status = bladerf_open_with_devinfo(&dev, &dev_info);
	if (status != 0) {
		fprintf(stderr, "Unable to open device: %s\n",
		bladerf_strerror(status));
		return status;
	}
	/* Set up TX channel parameters */
	config.channel    = BLADERF_CHANNEL_TX(0);
	config.frequency  = 918000000;
	config.bandwidth  = 1500000;
	config.samplerate = 250000;
	config.gain       = -14;

	if ((status = configure_channel(dev, &config)) != 0) {
		fprintf(stderr, "Failed to configure TX channel. Exiting.\n");
		bladerf_close(dev);
		return status;
	}

	/* Set up RX channel parameters */
	config.channel    = BLADERF_CHANNEL_RX(0);
	config.frequency  = 910000000;
	config.bandwidth  = 2000000;
	config.samplerate = 300000;
	config.gain       = 39;

	if ((status = configure_channel(dev, &config)) != 0) {
		fprintf(stderr, "Failed to configure RX channel. Exiting.\n");
		bladerf_close(dev);
		return status;
	}

	params.num_buffer = 32 ;
	params.buffer_size = 2048;
	params.num_transfers = 32;
	params.timeout_ms = 10000; 

	if ((status = sync_rx_meta_sched_example(dev,params))!= 0){
		fprintf(stderr, "Failed read rx meta data = %s\n",
      	bladerf_strerror(status));	
   	return status;
	}

	bladerf_close(dev);
	return 0;
}


