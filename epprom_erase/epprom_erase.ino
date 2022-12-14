#include <EEPROM.h>

void epprom_erase(void) {
    Serial.println("Erasing eeprom");
    
    for (uint32_t i = 0; i < EEPROM.length(); i++) {
        EEPROM.write(i, 0);
        Serial.print("\r");
        Serial.print(((uint32_t) 100 * i) / EEPROM.length());
        Serial.print("%");
    }
    
    Serial.println("\r100%\r\nDone.");
}
    
void setup() {
    Serial.begin(115200);
    Serial.println("Booting device ...");
    Serial.println("Hello in eeprom erase example");
    
    epprom_erase();
}

void loop() {
    // put your main code here, to run repeatedly:
}
