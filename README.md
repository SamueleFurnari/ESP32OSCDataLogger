# Overview

The code in this repository can be used to log Serial OSC messages sent by an OSC sender.

The code relies on the [WiFiManager](https://github.com/tzapu/WiFiManager) library to manage WiFi connections and the [OSC](https://github.com/CNMAT/OSC) library to interpret OSC messages.

The code has been tested with PlatformIO on an ESP32 Wroom.

# First Boot

After the first boot, the ESP activates an AP with SSID `OSCDataLogger`. Connect to it using `password` as the password, and then connect the ESP to your network.

After the device reboots, open a serial terminal at `115200 baud` and connect with the ESP. If the connection is successful, you will see the message `Connected to WiFi!` on the serial monitor, indicating that the board is connected to your WiFi network. A second message will show the IP address assigned by your router to the device, followed by the string `Listening on port 8000`, indicating that the UDP server was started successfully.

# Usage

For testing purposes, you can download the [sendosc](https://github.com/yoggy/sendosc) utility to send OSC messages to the data logger.

Below are some example usages of the sendosc tool:

```shell
.\sendosc.exe 192.168.178.112 8000 /test1 s "hello"
.\sendosc.exe 192.168.178.112 8000 /test1 i 10
.\sendosc.exe 192.168.178.112 8000 /test1 f 1.2
```

In this example `192.168.178.112` is the IP address assigned by the router to your device. Use `s` to send a string, `i` to send an integer and `f` to send a float.