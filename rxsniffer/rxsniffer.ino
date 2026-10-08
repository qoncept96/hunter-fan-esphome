const int RX_PIN = 5;

// Buffer to hold raw timings (high/low durations)
#define MAX_PULSES 200
unsigned long pulseDurations[MAX_PULSES];
bool pulseStates[MAX_PULSES];

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(50); }
  
  pinMode(RX_PIN, INPUT);
  
  Serial.println("\n==============================================");
  Serial.println("📡 Raw RF Timing Sniffer Active");
  Serial.println("Press a button on the Hunter remote close to the RX...");
  Serial.println("==============================================");
}

void loop() {
  // Wait for the line to go HIGH (start of a transmission packet)
  if (digitalRead(RX_PIN) == HIGH) {
    int pulseCount = 0;
    unsigned long lastChangeTime = micros();
    bool lastState = HIGH;
    
    // Set a timeout window (if nothing changes for 15ms, the packet is done)
    unsigned long timeoutWindow = 15000; 
    unsigned long lastActivity = micros();
    
    while (pulseCount < MAX_PULSES && (micros() - lastActivity < timeoutWindow)) {
      bool currentState = digitalRead(RX_PIN);
      
      if (currentState != lastState) {
        unsigned long now = micros();
        unsigned long duration = now - lastChangeTime;
        
        pulseDurations[pulseCount] = duration;
        pulseStates[pulseCount] = lastState; // Save if this duration was HIGH or LOW
        pulseCount++;
        
        lastState = currentState;
        lastChangeTime = now;
        lastActivity = now;
      }
    }
    
    // Only print if we captured a meaningful burst of data (not random static)
    if (pulseCount > 15) {
      Serial.print("\n📦 Captured Packet (");
      Serial.print(pulseCount);
      Serial.println(" transitions):");
      Serial.println("----------------------------------------");
      
      for (int i = 0; i < pulseCount; i++) {
        Serial.print(pulseStates[i] ? "HIGH: " : "LOW:  ");
        Serial.print(pulseDurations[i]);
        Serial.println(" us");
      }
      Serial.println("----------------------------------------");
      
      // Post-capture cooldown so we don't flood the serial screen
      delay(500); 
    }
  }
}