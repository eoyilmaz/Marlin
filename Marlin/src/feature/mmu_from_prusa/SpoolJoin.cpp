#include "SpoolJoin.h"
#include "src/MarlinCore.h"
#include "eeprom.h"
#include "messages.h"
#include "src/core/language.h"

namespace SpoolJoin {

SpoolJoin spooljoin;

SpoolJoin::SpoolJoin()
    : currentMMUSlot(0)
{
}

void SpoolJoin::initSpoolJoinStatus()
{
    // Useful information to see during bootup
    SERIAL_ECHOPGM("SpoolJoin is ");
    // uint8_t status = eeprom_init_default_byte((uint8_t*)EEPROM_SPOOL_JOIN, (uint8_t)EEPROM::Disabled);
    // TODO: I need help with this...
    // uint8_t status = persistentStore.read_data((uint8_t*)EEPROM_SPOOL_JOIN, (uint8_t)EEPROM::Disabled);
    uint8_t status = 1;
    if (status == (uint8_t)EEPROM::Enabled)
    {
        SERIAL_ECHOLN_P(MSG_ON + 2);
    } else {
        SERIAL_ECHOLN_P(MSG_OFF + 2);
    }
}

void SpoolJoin::toggleSpoolJoin()
{
    // TODO: This uses persistentStore, I need guidance on this
    // if (eeprom_read_byte((uint8_t*)EEPROM_SPOOL_JOIN) == (uint8_t)EEPROM::Disabled)
    // {
    //     eeprom_write_byte((uint8_t*)EEPROM_SPOOL_JOIN, (uint8_t)EEPROM::Enabled);
    // } else {
    //     eeprom_write_byte((uint8_t*)EEPROM_SPOOL_JOIN, (uint8_t)EEPROM::Disabled);
    // }
}

bool SpoolJoin::isSpoolJoinEnabled()
{
    // TODO: This uses persistentStore, I need guidance on this
    // if(eeprom_read_byte((uint8_t*)EEPROM_SPOOL_JOIN) == (uint8_t)EEPROM::Enabled) {
    //     return true;
    // } else {
    //     return false;
    // }
    return false;
}

void SpoolJoin::setSlot(uint8_t slot)
{
    currentMMUSlot = slot;
}

uint8_t SpoolJoin::nextSlot()
{
    SERIAL_ECHOPGM("SpoolJoin: ");
    SERIAL_ECHO((int)currentMMUSlot);

    if (currentMMUSlot >= 4) currentMMUSlot = 0;
    else currentMMUSlot++;

    SERIAL_ECHOPGM(" -> ");
    SERIAL_ECHOLN((int)currentMMUSlot);

    return currentMMUSlot;
}

}
