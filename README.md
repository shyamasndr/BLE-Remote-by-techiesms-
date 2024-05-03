BLE Keybaord: Original BLE Keyboard keeps connecting and disconnecting in some of the computers and fails to connect to android phones. To fix this nimble mode should be enabled as mentioned in the reference https://github.com/h2zero/NimBLE-Arduino. 
To enable nimble mode, go to %userprofile%\Documents\Arduino\libraries\ESP32_BLE_Keyboard\BleKeyboard.h  un comment the line //#define USE_NIMBLE. Once enabled, nimble lib should be added in arduino IDE  (https://github.com/h2zero/NimBLE-Arduino)

![image](https://github.com/shyamasndr/BLE-Remote-by-techiesms-/assets/22287304/a790e666-dff6-43e5-8cad-d2d73c2fece7) 
