const int trig1 = 10;
const int trig2 = 11;
const int echo1 = 12;
const int echo2 = 13;
#define NOTE_ON 0x90
#define NOTE_OFF 0x80

void setup() {
    pinMode(trig1, OUTPUT);
    pinMode(trig2, OUTPUT);
    pinMode(echo1, INPUT);
    pinMode(echo2, INPUT);
    Serial.begin(31250);
}

void sendMIDI(int cmd, int pitch, int velocity) {
    Serial.write(cmd);
    Serial.write(pitch);
    Serial.write(velocity);
}

float getDistance(int trigger, int echo) {
    // Transmit signal
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH)
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    // Receive signal
    float duration = pulseIn(echo, HIGH);
    float distance = duration * 0.01715;
    return distance;
}

int getPitch(int distance) {
    // Convert distance to pitch
    // TODO
    return 0x3A;
}

int getVeloc(int distance) {
    // Convert distance to velocity
    // TODO
    return 0x45;
}

void loop() {
    while(1) {
        float d1 = getDistance(trig1, echo1);
        float d2 = getDistance(trig2, echo2);
        int pitch = getPitch(d1);
        int veloc = getVeloc(d2);
        if (pitch != old_pitch) {
            sendMIDI(NOTE_OFF, old_pitch, 0x0);
            sendMIDI(NOTE_ON,  pitch,   veloc);
        }
        int old_pitch = pitch;
        int olc_veloc = veloc;
    }
}
