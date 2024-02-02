#ifndef SerialHandshake_h
#define SerialHandshake_h

#include <Arduino.h>

class Handshake {
public:
    /**
     * Constructor
     *
     * @param serial_number  The unique identifier for the device.
     * @param ping_delay_millis  The time interval (in milliseconds) between ping messages.
     */
    Handshake(const char* serial_number, int16_t ping_delay_millis);

    /**
     * Check if the received data matches the expected acknowledgment string.
     *
     * @param data  The data received for checking synchronization.
     */
    void check(const String& data);

    /**
     * Get the current synchronization state.
     *
     * @return  True if the device is synchronized, false otherwise.
     */
    bool is_synced() const;

    /**
     * Send a ping message over Serial if the specified time interval has passed.
     * Update the synchronization state accordingly.
     */
    void ping();

private:
    String serial_number;               // Holds the unique serial number
    bool synced;                        // Represents the synchronization state
    int16_t ping_delay;                 // Specifies the delay between ping messages
    uint32_t lastSuccessfulCheckMillis; // Tracks the timestamp of the last successful check
};

#endif
