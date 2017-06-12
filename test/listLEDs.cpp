#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <hidapi/hidapi.h>
#include <DeviceFactory.h>
#include <Device.h>
#include <Logitech/LogitechDevice.h>
#include <Logitech/LogitechPerKeyLED.h>
#include <unistd.h>

using namespace std;

LedDevice::Color red = { 0xff, 0x0, 0x0 };
LedDevice::Color green = { 0x0, 0xff, 0x0 };
LedDevice::Color blue = { 0x0, 0x0, 0xff };
LedDevice::Color black = { 0x0, 0x0, 0x0 };
LedDevice::Color white = { 0xff, 0xff, 0xff };

int main(int argc, char** argv) {
  vector<LedDevice::DeviceInfo> keyboards;
  keyboards = LedDeviceFactory::listAttachedDevices();

  cout << "Number of devices: " << keyboards.size() << endl;

  for(unsigned int index=0;index<keyboards.size();index++) {
    LedDevice::DeviceInfo device = keyboards.at(index);
    cout << "Device: vendorID=" <<std::hex<<device.vendorID<<", productID="<<device.productID<<std::hex<<", serial="<<device.serialNumber<<std::endl;
    
    LedDevice* keyboard = LedDeviceFactory::getDevice(device.vendorID, device.productID, device.serialNumber);
    if (keyboard == NULL) {
      cout << "Device failure" <<endl;
      continue;
    }

    vector<LedDevice::LED> leds = keyboard->getLEDs();
    cout << "LEDs: {";
    for (auto led : leds) {
      cout << led.name << ", ";
    }
    cout << "\b\b}" << endl;

    unordered_map<string, vector<LedDevice::LED>> groups = keyboard->getLEDGroups();
    cout << "LED Groups:" << endl;
    for (auto group : groups) {
      cout << "\t" << group.first << ": {";
      for (auto led : group.second) {
        cout << led.name << ", ";
      }
      cout << "\b\b}" << endl;
    }

    delete keyboard;
  }
}
