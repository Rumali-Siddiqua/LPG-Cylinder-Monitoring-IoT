# LPG cylinder monitoring device with custom designed mobile application followed by sensor node based safety system
# System Overview
## LPG Monitoring Device
The hardware device that includes a BMP 180 pressure sensor, Arduino Uno with ATmega328P microchip, Ethernet shield, and sensor node. The gas cylinder's pressure is measured using the BMP-180 barometric pressure sensor.

<p align="middle">
<img src="Overall system.jpg">
</p>

## Mobile Application
Android Studio has been used to create a custom-designed mobile application with versatile functionality. The amount of gas is displayed as a percentage, and the data that has been obtained from the gas pressure are converted into percentages by this app, which then displays the values. Then, if there is a gas leak of any kind, a warning signal will appear on the app and a message notification will be sent.

<p align="middle">
<img src="Mobile App.jpg">
</p>




