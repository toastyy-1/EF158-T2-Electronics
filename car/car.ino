#define SONAR_TRIG_PIN 9
#define SONAR_ECHO_PIN 10
#define BUILTIN_LED_PIN 13
#define TOGGLE_PROGRAM_PIN 2 // when activated, the program will run


void setup() {
  Serial.begin(9600);
  pinMode(SONAR_TRIG_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
  pinMode(BUILTIN_LED_PIN, OUTPUT);
  pinMode(TOGGLE_PROGRAM_PIN, INPUT);
}

// @return returns distance in centimeters
float get_distance() {
  digitalWrite(SONAR_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIG_PIN, LOW);

  long duration = pulseIn(SONAR_ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

// start of control loop
bool program_running = false;
bool motor_on = false;

void loop() {
  if (program_running) {
    if (!digitalRead(TOGGLE_PROGRAM_PIN)) program_running = false;

    float distance = get_distance();

    if (distance < 10.0) {
      digitalWrite(BUILTIN_LED_PIN, HIGH);
    }
    else {
      digitalWrite(BUILTIN_LED_PIN, LOW);
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(10);

  }
  else {
    if (digitalRead(TOGGLE_PROGRAM_PIN)) {
      program_running = true;
    }
    delay(50);
  }
}
