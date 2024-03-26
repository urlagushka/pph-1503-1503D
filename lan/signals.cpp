#include "signals.h"

#include <map>
#include <string>

const char * get_signals(const std::string& key) {
    std::map<std::string, const char*> signals;
    signals["get_voltage"] = ":MEAS:VOLT";
    signals["get_amperage"] = ":MEAS:CURR";
    signals["set_voltage"] = ":SOUR:VOLT";
    signals["set_amperage"] = "SOUR:CURR";
    signals["on"] = ":SYST:POS1";
    signals["off"] = ":SYST:POS0";
    return signals.at(key);
}

