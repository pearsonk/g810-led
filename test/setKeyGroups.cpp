#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <hidapi/hidapi.h>
#include <DeviceFactory.h>
#include <Device.h>
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

    unordered_map<string, vector<LedDevice::LED>> groups = keyboard->getLEDGroups();
    cout << "Setting keyboard to black to get started" << endl;
    if (! keyboard->setAllLEDs(black)) return 1;
    if (! keyboard->commit()) return -1;

    if (groups.empty())
    {
      cout << "No groups found" << endl;
      continue;
    }

    for (auto group : groups) {
      cout << "Setting LED group: " << group.first << endl;
      if (! keyboard->setLEDGroup(group.first, red)) return 2;
      if (! keyboard->commit()) return -1;
      sleep(4);
      if (! keyboard->setLEDGroup(group.first, black)) return 3;
      if (! keyboard->commit()) return -1;
      sleep(1);
    }

    delete keyboard;
  }
}
