/*!
 * DHT22 temperature sensor driver
 */

#ifndef _DHT_H_
#define _DHT_H_

typedef enum dht_response_t {
    DHT_OK = 0,
    DHT_CHECKSUM_ERROR = -1,
    DHT_TIMEOUT_ERROR = -2
} dht_response_t;

typedef struct dht_measurement_t {
    float humidity;
    float temperature;
} dht_measurement_t;

/**
 * @brief Set the DHT used GPIO pin
 *
 * @param gpio The DHT used GPIO pin
 */
void dht_set_gpio(int gpio);

/**
 * @brief Read DHT22 sensor
 *
 * @param measurement Pointer to a dht_measurement_t struct to store the measurement in
 * @return DHT_OK if reading was successful, DHT_TIMEOUT_ERROR if reading timed out, DHT_CHECKSUM_ERROR if checksum was incorrect
 */
dht_response_t dht_read(dht_measurement_t *measurement);

#endif
