#include <EEPROM.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Booting device ...");
    Serial.println("Hello in eeprom example 2");

    uint32_t reboot_counter = 0;

    /// make pointer to address of reboot counter
    uint8_t *ptr = (uint8_t *)&reboot_counter;

    /// read from eeprom byte by byte
    for (uint8_t i = 0; i < sizeof(reboot_counter); i++) {
        *(ptr + i) = EEPROM.read(i);
    }

    /// increment reboot counter
    reboot_counter++;

    /// write new value byte by byte
    for (uint8_t i = 0; i < sizeof(reboot_counter); i++) {
        EEPROM.write(i, *(ptr+ i));
    }

    Serial.print("Its ");
    Serial.print(reboot_counter);
    Serial.println(" device reboot");
}

void loop() {
    // put your main code here, to run repeatedly:
}
