
#include <stdio.h>
#include "save.h"




/* Usage:
 *   libbladeRF_example_boilerplate [serial #]
 *
 * If a serial number is supplied, the program will attempt to open the
 * device with the provided serial number.
 *
 * Otherwise, the first available device will be used.
 */
int main(int argc, char *argv[]){

    int status; 
    struct bladerf *dev = NULL; /*Reference for pointing to the device*/
    struct bladerf_devinfo dev_info; /* Information about a bladeRF attached to the system*/
    rx_meta_data *data;
		channel_config config;

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
        return 1;
    }

     /* Set up RX channel parameters */
    config.channel    = BLADERF_CHANNEL_RX(0);
    config.frequency  = 910000000;
    config.bandwidth  = 2000000;
    config.samplerate = 300000;
    config.gain       = 39;
    status = configure_channel(dev, &config);
    if (status != 0) {
        fprintf(stderr, "Failed to configure RX channel. Exiting.\n");
        goto out;
    }

    /* Set up TX channel parameters */
    config.channel    = BLADERF_CHANNEL_TX(0);
    config.frequency  = 918000000;
    config.bandwidth  = 1500000;
    config.samplerate = 250000;
    config.gain       = -14;
    status = configure_channel(dev, &config);
    if (status != 0) {
        fprintf(stderr, "Failed to configure TX channel. Exiting.\n");
        goto out;
    }

    /* Application code goes here.
     *
     * Don't forget to call bladerf_enable_module() before attempting to
     * transmit or receive samples!
     */
    printf("Hello world naaaaa\n");
    
    status = sync_rx_meta_sched_example(dev,data);
    if (status!=0){
        fprintf(stderr, "Failed to read RX channel. Exiting.\n");
        goto out;
    }

    out:
    bladerf_close(dev);
    return status;
}

