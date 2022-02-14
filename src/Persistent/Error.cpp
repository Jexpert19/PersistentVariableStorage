#include "Error.hpp"

namespace Persistent{
  const char eeprom_error_ok_pstr[] PROGMEM = "";
  const char eeprom_error_not_found_pstr[] PROGMEM = "Not found";
  const char eeprom_error_corrupted_pstr[] PROGMEM = "Corrupted";

  PGM_P eeprom_error_pstrs[]{
    eeprom_error_ok_pstr,
    eeprom_error_not_found_pstr,
    eeprom_error_corrupted_pstr
  };


  PGM_P eepromErrorToPstr(Error error){
    return eeprom_error_pstrs[static_cast<int>(error)];
  }
}