#include <EEPROM.h>

/*
 * Led channel configuration
 */
typedef struct {
    uint32_t sunrise;     ///< Sunrise time
    uint32_t sunset;      ///< Sunset time
    uint8_t day_power;    ///< Power in day
    uint8_t night_power;  ///< Power in night
} led_channel_cfg;

static const uint32_t seconds_in_hour = 3600;

led_channel_cfg led_1 = {.sunrise = 7 * seconds_in_hour + 30 * 60, 
                         .sunset = (uint32_t)20 * seconds_in_hour, 
                         .day_power = 100, 
                         .night_power = 1};


/*
 * Print led channel configuration.
 * 
 * @param led Pointer to led channel configuration to print
 */
void led_channel_print(led_channel_cfg *led)
{
    Serial.println("---------------------------------");
    Serial.println("LED channel configuration");
    uint8_t h = (led->sunset / seconds_in_hour);
    
    uint8_t m = (led->sunset - ((uint32_t)h * seconds_in_hour)) / 60;
    Serial.print("Sunset "); Serial.print(h); Serial.print(":"); Serial.println(m);
    
    h = (led->sunrise / seconds_in_hour);
    m = (led->sunrise - ((uint32_t)h * seconds_in_hour)) / 60;
    Serial.print("Sunrise "); Serial.print(h); Serial.print(":"); Serial.println(m);
    
    Serial.print("Day power "); Serial.println(led->day_power);
    Serial.print("Night power "); Serial.println(led->night_power);
    Serial.println("---------------------------------");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Booting device ...");
    Serial.println("Hello in eeprom example 3");
    
    uint32_t reboot_counter = 0;
    uint8_t *ptr = (uint8_t *)&reboot_counter;

    /// Read reboot counter from eeprom
    for (uint8_t i = 0; i < sizeof(reboot_counter); i++) {
        *ptr = EEPROM.read(i);
        ptr++;
    }

    /// Increment reboot counter
    reboot_counter++;
    ptr = (uint8_t *)&reboot_counter;

    /// Save new value of reboot counter
    for (uint8_t i = 0; i < sizeof(reboot_counter); i++) {
        EEPROM.write(i, *ptr);
        ptr++;
    }

    Serial.print("Its ");
    Serial.print(reboot_counter);
    Serial.println(" device reboot");

    /// Print led_1 channel configuration
    led_channel_print(&led_1);
    ptr = (uint8_t *)&led_1;

    /// Save led_1 in eeprom byte by byte
    for (uint8_t i = sizeof(reboot_counter); i < sizeof(reboot_counter) + sizeof(led_1); i++) {
        EEPROM.write(i, *ptr);
        ptr++;
    }

    led_channel_cfg led_read =  {.sunrise = 0, .sunset = 0, .day_power = 0, .night_power = 0};
    ptr = (uint8_t *)&led_read;

    /// Read led channel configuration from eeprom
    for (uint8_t i = sizeof(reboot_counter); i < sizeof(reboot_counter) + sizeof(led_read); i++) {
        *ptr = EEPROM.read(i);
        ptr++;
    }
    
    led_channel_print(&led_read);
}

void loop() {

}
