MMU3 Messages
=============

Starting with the version 2 of the MMU firmware, the requests and responds have
a trailing section that contains the CRC8 of the original message. The general
structure is as follows:

```shell
Requests (what Marlin requests):
Marlin: {RequestMsgCode}{Value}*{CRC8}

Responses (what MMU responds with):
MMU   : {RequestMsgCode}{Value} {ResponseMsgParamCode}{paramValue}*{CRC8}
```

An example to that would be:

```shell
Marlin: S0*c6
MMU   : S0 A3*22

Marlin: S1*ad
MMU   : S1 A0*34

Marlin: S2*10
MMU   : S2 A2*65

# All combined we have a response of v3.0.2 as the firmware version.
```

Startup sequence
================

When initialized, MMU waits for requests. Marlin repeatedly sends `S0` commands
until it gets an answer:

```shell
Marlin: S0*c6\n
Marlin: S0*c6\n
Marlin: S0*c6\n
Marlin: S0*c6\n
Marlin: S0*c6\n
Marlin: S0*c6\n
Marlin: S0*c6\n
...
```

When the communication is in place MMU follows with:

```shell
MMU   : S0 A3*22
```

Then Marlin continues to get the rest of the MMU firmware version.

```shell
Marlin: S1*ad
MMU   : S1 A0*34
Marlin: S2*10
MMU   : S2 A2*65
```

#if (12V_mode)

- MMU <= 'M1\n'
- MMU => 'ok\n'

#endif

- MMU <= 'P0\n'
- MMU => '*FINDA status*\n'

Now we are sure MMU is available and ready. If there was a timeout or other communication problem somewhere, printer will be killed.

- *Firmware version* is an integer value, but we don't care about it
- *Build number* is an integer value and has to be >=126, or =>132 if 12V mode is enabled
- *FINDA status* is 1 if the filament is loaded to the extruder, 0 otherwise


*Build number* is checked against the required value, if it does not match, printer is halted.



Toolchange
==========

- MMU <= 'T*Filament index*\n'

MMU sends

- MMU => 'ok\n'

as soon as the filament is fed down to the extruder. We follow with

- MMU <= 'C0\n'

MMU will feed a few more millimeters of filament for the extruder gears to grab.
When done, the MMU sends

- MMU => 'ok\n'

We don't wait for a response here but immediately continue with the next G-code which should
be one or more extruder moves to feed the filament into the hotend.


FINDA status
============

- MMU <= 'P0\n'
- MMU => '*FINDA status*\n'

*FINDA status* is 1 if the is filament loaded to the extruder, 0 otherwise. This could be used as filament runout sensor if probed regularly.



Load filament
=============

- MMU <= 'L*Filament index*\n'

MMU will feed filament down to the extruder, when done

- MMU => 'ok\n'


Unload filament
=============

- MMU <= 'U0\n'

MMU will retract current filament from the extruder, when done

- MMU => 'ok\n'



Eject filament
==============

- MMU <= 'E*Filament index*\n'
- MMU => 'ok\n'
