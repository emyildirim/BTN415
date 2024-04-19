#pragma once
#include <iostream>

unsigned char lfsr(unsigned char var) {
    unsigned char var2;
    var2 = (var << 1) + (((var & 0x80) >> 7) ^
        ((var & 0x20) >> 5) ^
        ((var & 0x04) >> 2));
    return var2;
}

unsigned char crc(unsigned char* buffer, size_t length) {
    unsigned char crc = 0;
    for (size_t i = 0; i < length; i++) {
        crc = lfsr(crc ^ buffer[i]);
    }
    return crc;
}

void sendChecksummedData(unsigned char* data, size_t len) {
    // Calculate CRC on the data
    unsigned char checksum = crc(data, len);
    // Send data followed by checksum...
}

bool verifyChecksummedData(unsigned char* receivedData, size_t len, unsigned char receivedChecksum) {
    // Recalculate CRC on the received data
    unsigned char calculatedChecksum = crc(receivedData, len);
    // Compare and return the result of verification
    return (calculatedChecksum == receivedChecksum);
}