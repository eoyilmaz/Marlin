#include "mmu2_fsensor.h"
// #include "Filament_sensor.h"


namespace MMU2 {

FilamentState WhereIsFilament(){
    // return fsensor.getFilamentPresent() ? FilamentState::AT_FSENSOR : FilamentState::NOT_PRESENT;
    return FILAMENT_PRESENT() ? FilamentState::AT_FSENSOR : FilamentState::NOT_PRESENT;
}

} // namespace MMU2
