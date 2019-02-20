#include "Arduino.h"

#include "BleMidi.h"

BLEMIDI_CREATE_INSTANCE(bm);

// ====================================================================================
// Event handlers for incoming MIDI messages
// ====================================================================================

// -----------------------------------------------------------------------------
// rtpMIDI session. Device connected
// -----------------------------------------------------------------------------
void OnBleMidiConnected() {
  Serial.println("Connected");
}

// -----------------------------------------------------------------------------
// rtpMIDI session. Device disconnected
// -----------------------------------------------------------------------------
void OnBleMidiDisconnected() {
  Serial.println("Disconnected");
}

// -----------------------------------------------------------------------------
// received note on
// -----------------------------------------------------------------------------
void OnBleMidiNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("Incoming NoteOn from channel:");
  Serial.print(channel);
  Serial.print(" note:");
  Serial.print(note);
  Serial.print(" velocity:");
  Serial.print(velocity);
  Serial.println();
}


// -----------------------------------------------------------------------------
// received note off
// -----------------------------------------------------------------------------
void OnBleMidiNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("Incoming NoteOff from channel:");
  Serial.print(channel);
  Serial.print(" note:");
  Serial.print(note);
  Serial.print(" velocity:");
  Serial.print(velocity);
  Serial.println();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void setup()
{
  // Serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  bm.begin("ESP_MIDI");

  bm.onConnected(OnBleMidiConnected);
  bm.onDisconnected(OnBleMidiDisconnected);

  bm.setHandleNoteOn(OnBleMidiNoteOn);
  bm.setHandleNoteOff(OnBleMidiNoteOff);

  Serial.println("looping");
}

// -----------------------------------------------------------------------------
void loop()
{
  bm.sendNoteOn(60, 127, MIDI_CHANNEL_2);

  delay(2000);

  bm.sendNoteOff(60, 0, MIDI_CHANNEL_2);

  delay(2000);
}

// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEServer.h>
// #include <BLE2902.h>
//
// #define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
// #define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"
//
// BLECharacteristic *pCharacteristic;
// bool deviceConnected = false;
//
// uint8_t midiPacket[] = {
//    0x80,  // header
//    0x80,  // timestamp, not implemented
//    0x00,  // status
//    0x3c,  // 0x3c == 60 == middle c
//    0x00   // velocity
// };
//
// class MyServerCallbacks: public BLEServerCallbacks {
//     void onConnect(BLEServer* pServer) {
//       Serial.println("deviceConnected");
//       deviceConnected = true;
//     };
//
//     void onDisconnect(BLEServer* pServer) {
//       Serial.println("deviceDisconnected");
//       deviceConnected = false;
//     }
//
//     // void onWrite(BLECharacteristic * characteristic) {
//         // std::string rxValue = pCharacteristic->getValue();
//         // if (rxValue.length() > 0) {
//             // _bleMidiInterface->receive((uint8_t *)(rxValue.c_str()), rxValue.length());
//         // }
//     // }
// };
//
// void setup() {
//   Serial.begin(115200);
//
//   BLEDevice::init("ESP32 MIDI Example");
//
//   BLEServer *pServer = BLEDevice::createServer();
//   pServer->setCallbacks(new MyServerCallbacks());
//
//   // Create the BLE Service
//   auto service = pServer->createService(BLEUUID(SERVICE_UUID));
//
//   // Create a BLE Characteristic
//   pCharacteristic = service->createCharacteristic(
//                                                    BLEUUID(CHARACTERISTIC_UUID),
//                                                    BLECharacteristic::PROPERTY_READ   |
//                                                    BLECharacteristic::PROPERTY_WRITE  |
//                                                    BLECharacteristic::PROPERTY_NOTIFY |
//                                                    BLECharacteristic::PROPERTY_WRITE_NR
//                                                    );
//   // Add CCCD 0x2902 to allow notify
//   pCharacteristic->addDescriptor(new BLE2902());
//
//   // Start the service
//   service->start();
//
//   auto advertisementData = BLEAdvertisementData();
//   advertisementData.setFlags(0x04);
//   advertisementData.setCompleteServices(BLEUUID(SERVICE_UUID));
//   advertisementData.setName("ESP32 MIDI Example");
//
//   // Start advertising
//   auto advertising = pServer->getAdvertising();
//   advertising->setAdvertisementData(advertisementData);
//   advertising->start();
//
//   //
//   // Serial.println("Setup");
//   //
//   // BLEDevice::init("ESP32 MIDI Example");
//   //
//   // // Create the BLE Server
//   // BLEServer *pServer = BLEDevice::createServer();
//   // pServer->setCallbacks(new MyServerCallbacks());
//   //
//   // // Create the BLE Service
//   // BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));
//   //
//   // // Create a BLE Characteristic
//   // pCharacteristic = pService->createCharacteristic(
//   //   BLEUUID(CHARACTERISTIC_UUID),
//   //   BLECharacteristic::PROPERTY_READ   |
//   //   BLECharacteristic::PROPERTY_WRITE  |
//   //   BLECharacteristic::PROPERTY_NOTIFY |
//   //   BLECharacteristic::PROPERTY_WRITE_NR
//   // );
//   //
//   // // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
//   // // Create a BLE Descriptor
//   // pCharacteristic->addDescriptor(new BLE2902());
//   //
//   // // Start the service
//   // pService->start();
//   //
//   // // Start advertising
//   // pServer->getAdvertising()->start();
//   //
//   // Serial.println("Started");
// }
//
// void loop() {
//   if (deviceConnected) {
//    // note down
//    midiPacket[2] = 0x90; // note down, channel 0
//    midiPacket[4] = 127;  // velocity
//    pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes
//    pCharacteristic->notify();
//
//    // play note for 500ms
//    delay(500);
//
//    // note up
//    midiPacket[2] = 0x80; // note up, channel 0
//    midiPacket[4] = 0;    // velocity
//    pCharacteristic->setValue(midiPacket, 5); // packet, length in bytes)
//    pCharacteristic->notify();
//
//    delay(500);
//  } else {
//    delay(1000);
//    Serial.println("Loop");
//  }
// }


// __________

// // Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
//
// void setup()
// {
//   // initialize LED digital pin as an output.
//   pinMode(LED_BUILTIN, OUTPUT);
// }
//
// void loop()
// {
//   // turn the LED on (HIGH is the voltage level)
//   digitalWrite(LED_BUILTIN, HIGH);
//
//   // wait for a second
//   delay(1000);
//
//   // turn the LED off by making the voltage LOW
//   digitalWrite(LED_BUILTIN, LOW);
//
//    // wait for a second
//   delay(1000);
// }
