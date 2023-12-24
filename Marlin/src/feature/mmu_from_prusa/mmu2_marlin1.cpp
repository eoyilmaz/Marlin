/// @file
/// MK3 / Marlin1 implementation of support routines for the MMU2
#include "mmu2_marlin.h"
#include "../../MarlinCore.h"
#include "../../module/stepper.h"
#include "../../module/planner.h"
#include "../../module/temperature.h"
#include "mmu2_config.h"

namespace MMU2 {

static void planner_line_to_current_position(float feedRate_mm_s){
    // plan_buffer_line_curposXYZE(feedRate_mm_s);
    line_to_current_position(feedRate_mm_s);
}

static void planner_line_to_current_position_sync(float feedRate_mm_s){
    planner_line_to_current_position(feedRate_mm_s);
    planner_synchronize();
}

void extruder_move(float delta, float feedRate) {
    current_position[E_AXIS] += delta;
    planner_line_to_current_position(feedRate);
}

float move_raise_z(float delta) {
    // return raise_z(delta);
    xyze_pos_t current_position_before = current_position;
    do_z_clearance_by(delta);
    return (current_position - current_position_before).z;
}

void planner_abort_queued_moves() {
    // planner_abort_hard();

    // // Unblock the planner. This should be safe in the
    // // toolchange context. Currently we are mainly aborting
    // // excess E-moves after detecting filament during toolchange.
    // // If a MMU error is reported, the planner must be unblocked
    // // as well so the extruder can be parked safely.
    // planner_aborted = false;
    quickstop_stepper();
}

void planner_synchronize() {
    // st_synchronize();
    planner.synchronize();
}

bool planner_any_moves() {
    // return blocks_queued();
    return planner.has_blocks_queued();
}

float planner_get_machine_position_E_mm(){
    return current_position[E_AXIS];
}

float stepper_get_machine_position_E_mm(){
    // return st_get_position_mm(E_AXIS);
    return planner.get_axis_position_mm(E_AXIS);
}

float planner_get_current_position_E(){
    return current_position[E_AXIS];
}

void planner_set_current_position_E(float e){
        current_position[E_AXIS] = e;
}

xyz_pos_t planner_current_position(){
    // return pos3d(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS]);
    return xyz_pos_t(current_position);
}

void motion_do_blocking_move_to_xy(float rx, float ry, float feedRate_mm_s){
    current_position[X_AXIS] = rx;
    current_position[Y_AXIS] = ry;
    planner_line_to_current_position_sync(feedRate_mm_s);
}

void motion_do_blocking_move_to_z(float z, float feedRate_mm_s){
    current_position[Z_AXIS] = z;
    planner_line_to_current_position_sync(feedRate_mm_s);
}

void nozzle_park() {
    xyz_pos_t park_point = NOZZLE_PARK_POINT;
    // current_position[X_AXIS] = park_point.x;
    // current_position[Y_AXIS] = park_point.y;
    // planner_line_to_current_position_sync(NOZZLE_PARK_XY_FEEDRATE);
    nozzle.park(2, park_point);
}

bool marlin_printingIsActive() {
    // return IS_SD_PRINTING || usb_timer_running();
    // return printer_active();
    return printingIsActive();
}

void marlin_manage_heater(){
    // manage_heater();
    thermalManager.task();
}

void marlin_manage_inactivity(bool b){
    // manage_inactivity(b);
    idle(b);
}

void marlin_idle(bool b){
    // manage_heater();
    // manage_inactivity(b);
    thermalManager.task();
    idle(b);
}

void marlin_refresh_print_state_in_ram(){
    // refresh_print_state_in_ram();
    // TODO: I don't see a comparable implementation in Marlin.
}

void marlin_clear_print_state_in_ram(){
    // clear_print_state_in_ram();
    // TODO: I don't see a comparable implementation in Marlin.
}

void marlin_stop_and_save_print_to_ram(){
    // stop_and_save_print_to_ram(0,0);
    // TODO: I don't see a comparable implementation in Marlin.
}

int16_t thermal_degTargetHotend() {
    return thermalManager.degTargetHotend(0);
}

int16_t thermal_degHotend() {
    return thermalManager.degHotend(0);
}

void thermal_setExtrudeMintemp(int16_t t) {
    thermalManager.extrude_min_temp = t;
    // set_extrude_min_temp(t);
}

void thermal_setTargetHotend(int16_t t) {
    // setTargetHotend(t);
    thermalManager.setTargetHotend(t, 0);
}

void safe_delay_keep_alive(uint16_t t) {
    // delay_keep_alive(t);
    safe_delay(t);
}

void Enable_E0(){
    // enable_e0();
    active_extruder = 0;
    stepper.enable_extruder();
}
void Disable_E0(){
    // disable_e0();
    active_extruder = 0;
    stepper.disable_extruder();
}

bool all_axes_homed(){
    // return axis_known_position[X_AXIS] && axis_known_position[Y_AXIS];
    return axis_is_trusted(X_AXIS) && axis_is_trusted(Y_AXIS);
}

} // namespace MMU2
