// Include BLE Keybaord library
#include <BleKeyboard.h>
// RBG led pin definition
#define G D0
#define R D2
#define B D4

// definition for button connected to XIAO C3
#define U_BUT D1
#define L_BUT D3
#define C_BUT D5
#define R_BUT D7
#define D_BUT D9

unsigned long previousMillis = 0;  // variable to store the previous time

const long interval = 120000;  // interval in milliseconds (2 minute)


RTC_DATA_ATTR int bootCount = 0;
// BLEMOUSE gloal declaration
BleKeyboard bleKeyboard("ShyamsKeyboard", "ShyamsLab", 100);
int ledVoltageHigh = 6;
int ledVoltageLow = 0;
bool status = true;
void setup() {
  Serial.begin(115200);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  pinMode(U_BUT, INPUT_PULLUP);
  pinMode(L_BUT, INPUT_PULLUP);
  pinMode(C_BUT, INPUT_PULLUP);
  pinMode(R_BUT, INPUT_PULLUP);
  pinMode(D_BUT, INPUT_PULLUP);

  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  //Print the wakeup reason for ESP32
  print_wakeup_reason();

  esp_deep_sleep_enable_gpio_wakeup(BIT(U_BUT), ESP_GPIO_WAKEUP_GPIO_LOW);
  bleKeyboard.begin();
}
// when bluetooth is not connected
void not_connected() {
  analogWrite(R, ledVoltageHigh);
  delay(500);
  analogWrite(R, ledVoltageLow);
  delay(500);

  analogWrite(G, ledVoltageLow);
  analogWrite(B, ledVoltageLow);
  status = true;
}
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wakeup caused by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP: Serial.println("Wakeup caused by ULP program"); break;
    default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

// when bluetooth is connected and but is presses led
void but_pressed() {
  analogWrite(B, ledVoltageHigh);
  delay(750);
  analogWrite(B, ledVoltageLow);
}

void reset_timer() {
  previousMillis = millis();
}


// to read button value and transmit data
void keyboardconnected() {
  if (digitalRead(U_BUT) == 0) {
    bleKeyboard.write(KEY_UP_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("UP KEY PRESSED");
  }
  if (digitalRead(D_BUT) == 0) {
    bleKeyboard.write(KEY_DOWN_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("DOWN KEY PRESSED");
  }
  if (digitalRead(L_BUT) == 0) {
    bleKeyboard.write(KEY_LEFT_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("LEFT KEY PRESSED");
  }
  if (digitalRead(R_BUT) == 0) {
    bleKeyboard.write(KEY_RIGHT_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("RIGHT KEY PRESSED");
  }
  if (digitalRead(C_BUT) == 0) {
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.print("a");
    delay(100);
    bleKeyboard.releaseAll();
    but_pressed();
    reset_timer();
    Serial.println("Sending Win+Shift+A");
  } else {
    gotodeepsleep();
  }
}
void gotodeepsleep() {
  unsigned long latestMils = millis();  // get the current time

  // check if it's time to print
  if (latestMils - previousMillis >= interval) {
    Serial.println("No button is pressed for more than minute. Going to sleep");
    blink_Red();
    esp_deep_sleep_start();
  }
}

void blink_Red() {

  analogWrite(R, ledVoltageHigh);
  delay(1000);
  analogWrite(R, ledVoltageLow);
  delay(1000);
  analogWrite(R, ledVoltageHigh);
  delay(1000);
  analogWrite(R, ledVoltageLow);
  delay(1000);
  analogWrite(R, ledVoltageHigh);
  delay(1000);
  analogWrite(R, ledVoltageLow);
  delay(1000);
  analogWrite(R, ledVoltageHigh);
  delay(1000);
  analogWrite(R, ledVoltageLow);
}
void blink_Blue() {

  analogWrite(B, ledVoltageHigh);
  delay(1000);
  analogWrite(B, ledVoltageLow);
  delay(1000);
  analogWrite(B, ledVoltageHigh);
  delay(1000);
  analogWrite(B, ledVoltageLow);
  delay(1000);
  analogWrite(B, ledVoltageHigh);
  delay(1000);
  analogWrite(B, ledVoltageLow);
  delay(1000);
  analogWrite(B, ledVoltageHigh);
  delay(1000);
  analogWrite(B, ledVoltageLow);
  delay(1000);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    if (status == true) {
      analogWrite(G, ledVoltageHigh);
      delay(3000);
      status = false;
    }
    analogWrite(G, ledVoltageLow);
    keyboardconnected();
  } else {
    not_connected();
  }
}
