#ifndef BEACON_H
#define BEACON_H
typedef struct iBeacon {
    uint8_t prefix[9];
    uint8_t uuid[16];
    uint8_t majorNumber[2];
    uint8_t minorNumber[2];
    int8_t txPower;
} iBeacon;

typedef struct record {
    uint16_t major;
    uint16_t minor;
    int8_t occurance;
    int8_t txPower;
    float rssi;
    float sigStr;
} record;


typedef union unionType {
    struct iBeacon iBeacon_m;
    uint8_t rawData[30];
}unionType;


#endif