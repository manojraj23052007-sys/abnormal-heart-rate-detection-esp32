#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_PIN 25
#define BUZZER_PIN 26

#define NORMAL_MIN 60
#define NORMAL_MAX 100

#define ALERT_DELAY 400UL
#define SAMPLE_INTERVAL 300UL

// Test active-LOW buzzer
#define BUZZER_ACTIVE_LOW false

LiquidCrystal_I2C lcd(0x27, 16, 2);

int heartRate = 75;

unsigned long lastSampleTime = 0;
unsigned long abnormalStartTime = 0;

bool abnormalDetected = false;
bool alertActive = false;

// Buzzer ON/OFF control
void setBuzzer(bool turnOn) {
  if (BUZZER_ACTIVE_LOW) {
    digitalWrite(BUZZER_PIN, turnOn ? LOW : HIGH);
  } else {
    digitalWrite(BUZZER_PIN, turnOn ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  setBuzzer(false);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  randomSeed(micros());

  lcd.setCursor(0, 0);
  lcd.print("PULSE MONITOR");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(1500);
  lcd.clear();

  lastSampleTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Generate synthetic BPM every 2 seconds
  if (currentTime - lastSampleTime >= SAMPLE_INTERVAL) {
    lastSampleTime = currentTime;

    heartRate = random(45, 121);

    Serial.print("Heart Rate: ");
    Serial.print(heartRate);
    Serial.println(" BPM");
  }

  bool isAbnormal =
    (heartRate < NORMAL_MIN || heartRate > NORMAL_MAX);

  // Start or reset the abnormal timer
  if (isAbnormal) {
    if (!abnormalDetected) {
      abnormalDetected = true;
      abnormalStartTime = millis();
      alertActive = false;
    }

    if (millis() - abnormalStartTime >= ALERT_DELAY) {
      alertActive = true;
    }
  } else {
    abnormalDetected = false;
    abnormalStartTime = 0;
    alertActive = false;
  }

  // Control LED and buzzer
  if (isAbnormal && alertActive) {
    digitalWrite(LED_PIN, HIGH);
    setBuzzer(true);
    Serial.println("ABNORMAL - ALERT ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    setBuzzer(false);

    if (isAbnormal) {
      Serial.println("ABNORMAL - CHECKING");
    } else {
      Serial.println("NORMAL - ALERT OFF");
    }
  }

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("HR: ");
  lcd.print(heartRate);
  lcd.print(" BPM     ");

  lcd.setCursor(0, 1);
  if (isAbnormal) {
    lcd.print("Status: ABNORMAL");
  } else {
    lcd.print("Status: NORMAL  ");
  }
}  
