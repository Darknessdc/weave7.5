G28
M104 S195
M140 S40
M190 S40
M109 S195
G0 F1000 X0 Y0 Z10
;End GCode
M104 S0; extruder heater off
M140 S0; heated bed heater off(if you have it)
G91; relative positioning
G1 E - 1 F300; retract the filament a bit before lifting the nozzle, to release some of the pressure
G1 Z + 0.5 E - 5 X - 20 Y - 20 F2700; move Z up a bit and retract filament even more
G28 X0 Y0; move X / Y to min endstops, so the head is out of the way
M84; steppers off
G90
G0 F9000 X0 Y0 Z0