BLE Keybaord: Original BLE Keyboard keeps connecting and disconnecting in some of the computers and fails to connect to android phones. To fix this nimble mode should be enabled as mentioned in the reference https://github.com/h2zero/NimBLE-Arduino. 
To enable nimble mode, go to %userprofile%\Documents\Arduino\libraries\ESP32_BLE_Keyboard\BleKeyboard.h  un comment the line //#define USE_NIMBLE. Once enabled, nimble lib should be added in arduino IDE  (https://github.com/h2zero/NimBLE-Arduino)

![image](https://github.com/shyamasndr/BLE-Remote-by-techiesms-/assets/22287304/a790e666-dff6-43e5-8cad-d2d73c2fece7) 

Another problem with Seeed Studio XIAO ESP32C3 is that, every time uploading the program to chip, bootloader should be enabled. To enable boot loader hold the reset button and press boot button and release by holding the reset button. 

![image](https://github.com/shyamasndr/BLE-Remote-by-techiesms-/assets/22287304/0d651dfd-ad1a-4663-aeff-f2b64aac5b66)

Or try this method https://github.com/StevenSlaa/SeeedStudio-XIAO-Boards/blob/main/XIAO%20ESP32C3%20Flashing.md

