/* =====================================================
   Smart Gate Controller - Arduino
   Real-Time Motor & Safety Control
   ===================================================== */

#define MOTOR_PWM   5
#define MOTOR_DIR   4

#define IR_SENSOR       7
#define LIMIT_OPEN      8
#define LIMIT_CLOSE     9
#define EMERGENCY_BTN   10
#define CURRENT_SENSOR  A0

#define BUZZER      6
#define LED_ALARM   11

#define CURRENT_THRESHOLD 600
#define MOTOR_SPEED 180

enum State {
  IDLE,
  OPENING,
  OPEN,
  CLOSING,
  ERROR_STATE
};

State gateState = IDLE;

/* ---------- Motor Control ---------- */
void motorOpen() {
  digitalWrite(MOTOR_DIR, HIGH);
  analogWrite(MOTOR_PWM, MOTOR_SPEED);
}

void motorClose() {
  digitalWrite(MOTOR_DIR, LOW);
  analogWrite(MOTOR_PWM, MOTOR_SPEED);
}

void motorStop() {
  analogWrite(MOTOR_PWM, 0);
}

/* ---------- Alarm ---------- */
void alarmOn() {
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED_ALARM, HIGH);
}

void alarmOff() {
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_ALARM, LOW);
}

/* ---------- Safety Check ---------- */
bool safetyTriggered() {
  int current = analogRead(CURRENT_SENSOR);

  if (digitalRead(IR_SENSOR) == LOW) return true;
  if (current > CURRENT_THRESHOLD) return true;
  if (digitalRead(EMERGENCY_BTN) == LOW) return true;

  return false;
}

/* ---------- Setup ---------- */
void setup() {
  pinMode(MOTOR_PWM, OUTPUT);
  pinMode(MOTOR_DIR, OUTPUT);

  pinMode(IR_SENSOR, INPUT);
  pinMode(LIMIT_OPEN, INPUT_PULLUP);
  pinMode(LIMIT_CLOSE, INPUT_PULLUP);
  pinMode(EMERGENCY_BTN, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_ALARM, OUTPUT);

  Serial.begin(9600);
  Serial.println("ARDUINO_READY");
}

/* ---------- Main Loop ---------- */
void loop() {

  /* ---- UART Commands ---- */
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "OPEN" && gateState == IDLE) {
      gateState = OPENING;
    }
    else if (cmd == "CLOSE" && gateState == OPEN) {
      gateState = CLOSING;
    }
    else if (cmd == "STOP") {
      motorStop();
      gateState = IDLE;
    }
  }

  /* ---- State Machine ---- */
  switch (gateState) {

    case IDLE:
      motorStop();
      alarmOff();
      break;

    case OPENING:
      motorOpen();

      if (safetyTriggered()) {
        motorStop();
        alarmOn();
        gateState = ERROR_STATE;
        Serial.println("ERROR");
      }

      if (digitalRead(LIMIT_OPEN) == LOW) {
        motorStop();
        gateState = OPEN;
        Serial.println("OPENED");
      }
      break;

    case OPEN:
      // Wait reccive CLOSE from Raspberry Pi
      break;

    case CLOSING:
      motorClose();

      if (safetyTriggered()) {
        motorStop();
        motorOpen();     
        alarmOn();
        delay(800);
        gateState = OPEN;
        Serial.println("OBSTRUCTION");
      }

      if (digitalRead(LIMIT_CLOSE) == LOW) {
        motorStop();
        gateState = IDLE;
        Serial.println("CLOSED");
      }
      break;

    case ERROR_STATE:
      motorStop();
      alarmOn();
      delay(2000);
      gateState = IDLE;
      break;
  }
}
