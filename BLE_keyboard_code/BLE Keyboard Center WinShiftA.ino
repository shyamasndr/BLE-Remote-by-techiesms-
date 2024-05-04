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
BleKeyboard bleKeyboard("ESP32 BLE Keyboard", "SeedStudio", 100);

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
  digitalWrite(R, HIGH);
  delay(500);
  digitalWrite(R, LOW);
  delay(500);

  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
  status = true;
}
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wakeup caused by external signal using RTC_IO");
      blink_Blue();
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
  digitalWrite(B, HIGH);
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
    delay(750);
  }
  if (digitalRead(D_BUT) == 0) {
    bleKeyboard.write(KEY_DOWN_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("DOWN KEY PRESSED");
    delay(750);
  }
  if (digitalRead(L_BUT) == 0) {
    bleKeyboard.write(KEY_LEFT_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("LEFT KEY PRESSED");
    delay(750);
  }
  if (digitalRead(R_BUT) == 0) {
    bleKeyboard.write(KEY_RIGHT_ARROW);
    but_pressed();
    reset_timer();
    Serial.println("RIGHT KEY PRESSED");
    delay(750);
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
    delay(750);
  } else {
    digitalWrite(B, LOW);
    gotodeepsleep();
  }
}
void gotodeepsleep() {
  unsigned long latestMils = millis();  // get the current time

  // check if it's time to print
  if (latestMils - previousMillis >= interval) {
    Serial.println("More than two minute has passed!");
    Serial.println("Going to sleep now");
    // Your code to print to serial goes here
    Serial.println("No button is pressed for more than minute. Going to sleep");
    blink_Red();
    esp_deep_sleep_start();
  }
}

void blink_Red() {

  digitalWrite(R, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
  delay(1000);
  digitalWrite(R, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
  delay(1000);
  digitalWrite(R, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
  delay(1000);
  digitalWrite(R, HIGH);
  delay(1000);
  digitalWrite(R, LOW);
}
void blink_Blue() {

  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(B, LOW);
  delay(1000);
  digitalWrite(B, HIGH);
  delay(1000);
  digitalWrite(B, LOW);
}

void loop() {
  if (bleKeyboard.isConnected()) {
    if (status == true) {
      digitalWrite(G, HIGH);
      delay(3000);
      status = false;
    }
    digitalWrite(G, LOW);
    keyboardconnected();
  } else {
    not_connected();
  }
}
