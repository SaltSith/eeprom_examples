#include <EEPROM.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Booting device ...");
    Serial.println("Hello in eeprom example 1");

    uint8_t reboot_counter = EEPROM.read(0);

    reboot_counter++;
    EEPROM.write(0, reboot_counter);

    Serial.print("Its ");
    Serial.print(reboot_counter);
    Serial.println(" device reboot");
}

void loop() {
  // put your main code here, to run repeatedly:

}
