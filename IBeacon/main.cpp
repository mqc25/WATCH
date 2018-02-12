/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "toolchain.h"
#include "ble/BLE.h"
#include "Beacon.h"
#define SIZE 11
Serial pc(USBTX, USBRX);

uint16_t MAJOR[] = {5472,21159,10418,976,62853,52866,1,540,540,540,540};
uint16_t MINOR[] = {7,7,111,2,1,7,5,5,7,6,3};
float RSSI[] = { -80,-80,-81,-82,-81,-80,-78,-76,-79,-78,-80};
//float RSSI[] = { -78,-78,-81.5,-82,-82,-78,-80,-80,-80,-80};

Ticker print;

union unionType u;
const uint8_t iBeaconPrefix[] = {0x02,0x01,0x06,0x1a,0xff,0x4c,0x00,0x02,0x15};

volatile int counter = 0;
record buffer[SIZE];


/*
 * This function is called every time we scan an advertisement.
 */

void addToBuffer(const Gap::AdvertisementCallbackParams_t *params)
{
    if (memcmp(params->advertisingData,iBeaconPrefix,sizeof(iBeaconPrefix)) != 0) {
        //pc.printf("Not IBeacon!\r\n\r\n");
        return;
    }
    memset(u.rawData, 0 , sizeof(u.rawData));
    memcpy(u.rawData, params->advertisingData,params->advertisingDataLen);

    uint16_t major = ((uint16_t)(u.iBeacon_m.majorNumber[0]) << 8) + (uint16_t)(u.iBeacon_m.majorNumber[1]);
    uint16_t minor = ((uint16_t)(u.iBeacon_m.minorNumber[0]) << 8) + (uint16_t)(u.iBeacon_m.minorNumber[1]);


    for(int i=0; i<sizeof(MAJOR)/sizeof(MAJOR[0]); i++) {
        if (major == MAJOR[i] && minor == MINOR[i]) {
            buffer[i].txPower = u.iBeacon_m.txPower;
            buffer[i].rssi = params->rssi;
            buffer[i].sigStr += buffer[i].rssi - RSSI[i];
            buffer[i].occurance++;
            return;
        }
    }
}
void printBuffer()
{

    int index = -1;
    float signal = -999;

    for (int i =0; i<SIZE; i++) {
        if(buffer[i].occurance == 0) continue;
        
        pc.printf("Major: %u, Minor: %u, SigStr: %.2f, Counter: %d\r\n"
        ,buffer[i].major,buffer[i].minor,(float)buffer[i].sigStr/(float)buffer[i].occurance,buffer[i].occurance);
        
        if(signal < (float)buffer[i].sigStr/(float)buffer[i].occurance) {
            index = i;
            signal = (float)buffer[i].sigStr/(float)buffer[i].occurance;
        }
        /*
        pc.printf("Minor: %02d\r\n",buffer[i].minor);
        pc.printf("TxPower: %02d\r\n",buffer[i].txPower);
        pc.printf("Rssi: %02d\r\n",buffer[i].rssi);
        pc.printf("Signal power: %02d\r\n",buffer[i].sigStr);
        pc.printf("\r\n\r\n");*/
    }
    pc.printf("Closest Major: %u  Closest Minor: %u  Tx: %d Rssi: %.2f  Sig Str: %.2f  Counter: %d\r\n\r\n",buffer[index].major, buffer[index].minor,buffer[index].txPower/*RSSI[index]*/,buffer[index].rssi,signal, buffer[index].occurance);
    for (int i = 0; i< SIZE ; i++) {
        buffer[i].major = MAJOR[i];
        buffer[i].minor = MINOR[i];
        buffer[i].txPower = 0;
        buffer[i].rssi = 0;
        buffer[i].sigStr = 0;
        buffer[i].occurance = 0;
    }
}

void advertisementCallback(const Gap::AdvertisementCallbackParams_t *params)
{
    if (memcmp(params->advertisingData,iBeaconPrefix,sizeof(iBeaconPrefix)) != 0) {
        return;
    }

    memset(u.rawData, 0 , sizeof(u.rawData));
    memcpy(u.rawData, params->advertisingData,params->advertisingDataLen);

    uint16_t major = ((uint16_t)(u.iBeacon_m.majorNumber[0]) << 8) + (uint16_t)(u.iBeacon_m.majorNumber[1]);
    uint16_t minor = ((uint16_t)(u.iBeacon_m.minorNumber[0]) << 8) + (uint16_t)(u.iBeacon_m.minorNumber[1]);
    bool inList = false;

    for (int i =0; i < sizeof(MAJOR)/sizeof(MAJOR[0]); i++) {
        if (major == MAJOR[i]) {
            inList = true;
            break;
        }
    }
    if(!inList) return;
    for (int i =0; i < sizeof(MINOR)/sizeof(MINOR[0]); i++) {
        if (minor == MINOR[i]) {
            inList = true;
            break;
        }
    }
    if(!inList) return;

    pc.printf("uuid:");
    for( int i = 0; i < 16; i++) {
        pc.printf("%02x",u.iBeacon_m.uuid[i]);
        if(i == 4 || i ==6 || i == 8 || i==10 || i ==12) pc.printf("-");
    }
    pc.printf("\r\n");


    pc.printf("majorNumber:%u\r\n",major);
    pc.printf("minorNumber:%u\r\n",minor);
    pc.printf("majorNumber:%02x %02x\r\n",u.iBeacon_m.majorNumber[0],u.iBeacon_m.majorNumber[1]);
    pc.printf("minorNumber:%02x %02x\r\n",u.iBeacon_m.minorNumber[0],u.iBeacon_m.minorNumber[1]);
    pc.printf("txPower:%02d\r\n",u.iBeacon_m.txPower);
    pc.printf("txPower:%02d\r\n",params->rssi);
    pc.printf("\r\n\r\n");
}

/**
 * This function is called when the ble initialization process has failed
 */
void onBleInitError(BLE &ble, ble_error_t error)
{
    /* Initialization error handling should go here */
}

/**
 * Callback triggered when the ble initialization process has finished
 */
void bleInitComplete(BLE::InitializationCompleteCallbackContext *params)
{
    BLE&        ble   = params->ble;
    ble_error_t error = params->error;

    if (error != BLE_ERROR_NONE) {
        /* In case of error, forward the error handling to onBleInitError */
        onBleInitError(ble, error);
        return;
    }

    /* Ensure that it is the default instance of BLE */
    if(ble.getInstanceID() != BLE::DEFAULT_INSTANCE) {
        return;
    }

    /* Setup and start scanning */
    ble.gap().setScanParams(500 /* scan interval */, 180 /* scan window */);
    ble.gap().startScan(addToBuffer);
    //ble.gap().startScan(advertisementCallback);
}

int main(void)
{   pc.baud(115200);
    for (int i = 0; i< SIZE ; i++) {
        buffer[i].major = MAJOR[i];
        buffer[i].minor = MINOR[i];
        buffer[i].txPower = 0;
        buffer[i].rssi = 0;
        buffer[i].sigStr = 0;
        buffer[i].occurance = 0;
    }
    BLE &ble = BLE::Instance();
    ble.init(bleInitComplete);

    print.attach(&printBuffer, 2);

    while (true) {
        ble.waitForEvent();
    }

}
