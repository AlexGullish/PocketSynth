#include <Arduino.h>
#include <avr/interrupt.h>




const byte KEY_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};

const byte PIEZO_PIN = 10;

const uint16_t NOTES[] = {262, 294, 330, 349, 392, 440, 494, 523};

const byte OCTAVE_PIN = 11;
const byte NUM_OCTAVES = 3;
const byte NUM_KEYS = 8;
const byte MAX_VOICES = 4;
const uint16_t DEBOUNCE_MS = 15;
const uint32_t SAMPLE_RATE = 8000;

byte octaveIndex = 1;  // 0 = low, 1 = normal, 2 = high

bool octaveLastReading = HIGH;
bool octaveStableState = HIGH;
unsigned long octaveLastChange = 0;

bool lastReading[NUM_KEYS];
bool stableState[NUM_KEYS];
unsigned long lastChange[NUM_KEYS];

volatile uint32_t phase[ MAX_VOICES ] = {};
volatile uint32_t increment[ MAX_VOICES ] = {};
volatile byte activeMask = 0;

ISR(TIMER2_COMPA_vect) {
  int16_t mix = 0;

  for (byte v = 0; v < MAX_VOICES; v++) {
    if (activeMask & (1 << v)) {
      phase[v] += increment[v];


      if (phase[v] & 0x80000000UL) {
        mix += 24;
      } else {
        mix -= 24;
      }
    }
  }

  OCR1B = (byte)(128 + mix);
}

void setup() {
  for (byte i = 0; i < NUM_KEYS; i++) {
    pinMode(KEY_PINS[i], INPUT_PULLUP);
    lastReading[i] = HIGH;
    stableState[i] = HIGH;
    lastChange[i] = 0;
  }
  pinMode(OCTAVE_PIN, INPUT_PULLUP);
  pinMode(PIEZO_PIN, OUTPUT);

  noInterrupts();

  TCCR1A = _BV(COM1B1) | _BV(WGM10);
  TCCR1B = _BV(WGM12) | _BV(CS10);
  OCR1B = 128;

  TCCR2A = _BV(WGM21);
  TCCR2B = _BV(CS21);
  OCR2A = 249;

  TCNT2 = 0;
  TIFR2 = _BV(OCF2A);
  TIMSK2 = _BV(OCIE2A);

  interrupts();

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();

  bool octaveReading = digitalRead(OCTAVE_PIN);

  if (octaveReading != octaveLastReading) {
    octaveLastReading = octaveReading;
    octaveLastChange = now;
  }

  if (now - octaveLastChange >= DEBOUNCE_MS) {
    if (octaveReading != octaveStableState) {
      octaveStableState = octaveReading;

      // Cycle octave only when the button is pressed
      if (octaveStableState == LOW) {
        octaveIndex = (octaveIndex + 1) % NUM_OCTAVES;
      }
    }
  }

  for (byte i = 0; i < NUM_KEYS; i++) {
    bool reading = digitalRead(KEY_PINS[i]);

    if (reading != lastReading[i]) {
      lastReading[i] = reading;
      lastChange[i] = now;

    }

    if (now - lastChange[i] >= DEBOUNCE_MS) {
      stableState[i] = reading;
    }
  }

  uint32_t newIncrement[MAX_VOICES] = {0, 0, 0, 0};
  byte newMask = 0;
  byte voice = 0;

  for (byte key = 0; key < NUM_KEYS; key++) {
    if (stableState[key] == LOW && voice < MAX_VOICES) {
      uint16_t frequency = NOTES[key];

      if (octaveIndex == 0) {
        frequency /= 2;
      } else if (octaveIndex == 2) {
        frequency *= 2;
      }

    newIncrement[voice] = ((uint64_t)frequency * 4294967296ULL) / SAMPLE_RATE;
      newMask |= (1 << voice);
      voice++;
    }
  }

  noInterrupts();

  for (byte v = 0; v < MAX_VOICES; v++) {
    if (!(newMask & (1 << v))) {
      phase[v] = 0;
    }

    increment[v] = newIncrement[v];
  }

  activeMask = newMask;

  interrupts();

}
