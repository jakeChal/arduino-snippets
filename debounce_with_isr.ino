int buttonPin = 2;

int stateToggle;
int previousState = HIGH;
unsigned int previousPress;
volatile int buttonFlag;
int buttonDebounce = 20;  // millis

void button_ISR() {
    buttonFlag = 1;
}

void setup() {
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(buttonPin), button_ISR, CHANGE);
}

void loop() {
    if ((millis() - previousPress) > buttonDebounce && buttonFlag) {
        previousPress = millis();
        if (digitalRead(buttonPin) == LOW && previousState == HIGH) {
            stateToggle = !stateToggle;
            Serial.println(stateToggle);
            previousState = LOW;
        }

        else if (digitalRead(buttonPin) == HIGH && previousState == LOW) {
            previousState = HIGH;
        }
        buttonFlag = 0;
    }
}

