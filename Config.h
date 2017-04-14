// -----------------------------------------------------------------------------------------------------------------
// Configure options

// ========= Also remember to see Weather.ino and Thermostat.ino to setup any sensors ==========
// ======== See Weather.ino.txt for an example of how to setup a couple of I2C sensors  ========

// Relay's are mapped to digital output pins: 23,25,27,29,31,33,35,37,39,41,43,45,47,49
//                                    Relay#:  1  2  3  4  5  6  7  8  9 10 11 12 13 14
//
// note: PWM can be activated (if you choose) on relay's 7 to 14 (I use SSR's for most of those)

// Sense's are mapped to digital input pins: 22,24,26,28,30,32
//                                   Sense#:  1  2  3  4  5  6
// (I use an optocoupler on these)

// Analog inputs are not mapped (at the analog pin#)

#define NTP_DEBUG_OFF
#define WEBSERVER_DEBUG_OFF
#define CMDSERVER_DEBUG_OFF
#define AJAX_RELAY_DEBUG_OFF

// Network settings ----------------------------------------------------------

// Enter an MAC address for your controller
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// The IP address will be dependent on your local network
IPAddress ip(192, 168, 1, 50);

// NTP Servers:
IPAddress timeServer(132, 163, 4, 101);   // time-a.timefreq.bldrdoc.gov
//IPAddress timeServer(132, 163, 4, 102);   // time-b.timefreq.bldrdoc.gov
//IPAddress timeServer(132, 163, 4, 103);   // time-c.timefreq.bldrdoc.gov

// Your time zone, default = -5 (US Eastern Standard Time)
#define TimeZone -5

// Status Panel Features -----------------------------------------------------

// Watchdog enable, causes the Mega2560 to reset after 8 seconds if it hangs for any reason
#define WATCHDOG_OFF

// The OCS uses METRIC units by default
#define IMPERIAL_UNITS_ON

// Status panel is always ON, use _OFF to disable individual items
#define STAT_MAINS_SENSE_OFF        // Sense# for mains power good, mains power failure is considered UNSAFE
#define STAT_TIME_NTP_ON            // I use NTP for time, adding an RTC or GPS for time instead should be easy too, see: https://github.com/PaulStoffregen/Time
#define STAT_12V_BAT_ANALOG 0       // Analog# for 12V roof battery voltage (these have a voltage divider /100 so 12V = 1.2V)
#define STAT_12V_PS_ANALOG 1        // Analog# for 12V power supply voltage (these have a voltage divider /100 so 12V = 1.2V)

// Weather panel (see Weather.ino for more info.)
#define WEATHER_ON
#define SD_CARD_ON                  // for logging weather an SD card must be present
#define WEATHER_ALTITUDE 120        // site altitude in meters
#define WEATHER_INS_TEMP_ON
#define WEATHER_OUT_TEMP_ON
#define WEATHER_PRESSURE_ON
#define WEATHER_HUMIDITY_ON
#define WEATHER_WIND_SPD_ON
#define WEATHER_WIND_SPD_THRESHOLD 10 // above this wind speed (kph) is considered to be UNSAFE
#define WEATHER_SKY_QUAL_ON
#define WEATHER_CLOUD_CVR_ON
#define WEATHER_RAIN_ON             // a "wet" condition is considered to be UNSAFE, default location is on Analog 2
#define WEATHER_CLER_THRESHOLD -19
#define WEATHER_HAZE_THRESHOLD -17
#define WEATHER_SAFE_THRESHOLD -14  // above this temperature (deg C) is considered to be UNSAFE
#define WEATHER_OVRC_THRESHOLD -11
#define WEATHER_CLDY_THRESHOLD -8
#define WEATHER_VCLD_THRESHOLD -5

// Power panel (relay number in dbl quotes "",) use _OFF to disable individual items
#define POWER_ON
#define POWER_DEVICE1_RELAY "3"
#define POWER_DEVICE1_NAME "Main Computer Outlets"
#define POWER_DEVICE1_MEMORY_ON
#define POWER_DEVICE2_RELAY "5"
#define POWER_DEVICE2_NAME "Telescope Outlets"
#define POWER_DEVICE2_MEMORY_OFF
#define POWER_DEVICE3_RELAY "2"
#define POWER_DEVICE3_NAME "Telescope 12V power"
#define POWER_DEVICE3_MEMORY_OFF
#define POWER_DEVICE4_RELAY_OFF
#define POWER_DEVICE4_NAME_OFF
#define POWER_DEVICE4_MEMORY_OFF
#define POWER_DEVICE5_RELAY_OFF
#define POWER_DEVICE5_NAME_OFF
#define POWER_DEVICE5_MEMORY_OFF
#define POWER_DEVICE6_RELAY_OFF
#define POWER_DEVICE6_NAME_OFF
#define POWER_DEVICE6_MEMORY_OFF

// Thermostat panel, use _OFF to disable individual items
#define THERMOSTAT_ON
#define HEAT_RELAY 4                // Relay# for heating
#define COOL_RELAY_OFF              // Relay# for cooling/venting, default=OFF

// Lighting panel (relay number in dbl quotes "",) use _OFF to disable individual items
#define LIGHT_ON
#define LIGHT_WRW_RELAY "11"        // Warm room white lights, default="11"
#define LIGHT_WRR_RELAY "9"         // Warm room red lights, default="9"
#define LIGHT_ORW_RELAY "12"        // Observing room white lights, default="12"
#define LIGHT_ORR_RELAY "10"        // Observing room red lights, default="10"
#define LIGHT_OUTSIDE_RELAY "1"     // Outside flood, default="1"
#define LIGHT_SW_SENSE 3            // A switch to turn WRW lights on/off (ON when input is HIGH), default=3

// Roll-off roof panel
#define ROR_ON
// allow the option of closing the roof automatically at dawn and set it's default state
#define ROR_AUTOCLOSE_DAWN_OFF
#define ROR_AUTOCLOSE_DAWN_DEFAULT_OFF
// allow the option of closing the roof automatically if UNSAFE condition is detected
#define ROR_AUTOCLOSE_SAFETY_OFF
// set relays to cause roof to open or close, A=HIGH and B=LOW to OPEN, A=LOW and B=HIGH to CLOSE
// both A and B are normally LOW to stop the roof motor and this is it's default state
#define ROR_DIR_RELAY_A 7
#define ROR_DIR_RELAY_B 8
// this "relay", a MOSFET power transistor on my ROR, is setup to do slow PWM on the 12VDC roof motor
// to control the motor speed.  It can also be used with a relay to just enable/disable the roof motor
// as a backup to the relay's above
#define ROR_PWR_RELAY   14
// these sense the roof limits, inputs are normally LOW but go HIGH when the roof is fully opened or closed
#define ROR_CLOSED_LIMIT_SENSE 1    // Sense# for closed switch (CLOSED when input is HIGH)
#define ROR_OPENED_LIMIT_SENSE 2    // Sense# for open switch (OPEN when input is HIGH)
// PWM frequency for roof control, set to _OFF to disable, default=5, range 1 to 100
#define ROR_PWM_SPEED_HZ 5
// PWM power levels for DC control, default=20, this gets rounded at tens for 10%, 20%, 30%, etc.
#define ROR_PWM_POWER_PERCENT 30
// PWM soft start, begins at 0% and adds 10% per second until ROR_PWM_POWER_PERCENT is reached
#define ROR_SOFTSTART_OFF
// Average amount of time to open/close the roof (in seconds), default=60*5 (five minutes)
#define ROR_TIME_AVG (60*5)
// Additional time +/- (in seconds,) > this range and the roof is stopped/error thrown, default=30 (+/- one minute)
#define ROR_TIME_TOL 30


