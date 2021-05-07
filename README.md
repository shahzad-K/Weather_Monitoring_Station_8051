# Weather_Monitoring_8051

This project is developed for collecting and monitoring weather/climatic conditions. Here atmospheric temperature, light intensity, potentiometer reading is monitored continuously and accordingly this data is logged into external memory with respect to RTC(Real-time clock).

These parameters are measured using different sensors connected to the 8051 Microcontroller.
An LCD module displays data in real-time and a serial terminal is used to display the Weather Log on the press of a switch.

Here are the devices and sensors used viz., 
1. 8051 Microcontroller (AT89c52)
2. RTC (DS1307)
3. EEPROM (AT24C512)
4. Temperature sensor (DS1621)
5. LDR
6. Potentiometer
7. ADC (MCP3204)
8. Virtual Terminal (Serial Window)
9. LCD (20*4)

Interfacing of external devices is done using UART, I2C & SPI protocols.
