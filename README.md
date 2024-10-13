# ESP-IDF DHT22 Library

ESP Library for reading DHT22 temperature and humidity sensor

## Usage

Copy the `dht.h` and `dht.c` files to your project.

Example usage:

```c
#include "dht.h"

void measure()
{
    dht_set_gpio(GPIO_NUM_4);

    dht_measurement_t measurement;
    dht_response_t ret = dht_read(&measurement);
    switch (ret) {
        case DHT_OK:
            printf("Hum: %.1f Tmp: %.1f\n", measurement.humidity, measurement.temperature);
            break;
        case DHT_TIMEOUT_ERROR:
            printf("DHT_TIMEOUT_ERROR");
            break;
        case DHT_CHECKSUM_ERROR:
            printf("DHT_CHECKSUM_ERROR");
            break;
    }
}
```

For complete example, see `main.c` file.

## Acknowledgements

This library is based on: https://github.com/gosouth/DHT22
