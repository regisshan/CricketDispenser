# About the TG Lab CricketDispenser

If you're here, you're probably interested in the cricket hunting behavior task used by the Turrigiano lab to better understand mechanisms underlying plasticity in the developing visual system. Or maybe you just like throwing crickets at things and want a way to do it remotely.


Designing a containment and distribution system for crickets is surprisingly challenging. This is because crickets are sneaky and squeeze into cracks and crevaces to avoid their inevitable fate. Previous versions of this dispenser had a fatal flaw: crickets could escape the mechanism and fall into the arena at the wrong time, or finding their way into Gina's office where they would give their rather repetitive and chirp-y opinions on grant applications and paper revisions. While cricket chirps are a peaceful background for a fireside chat in the summer, it hits a little close to home when you're staring at a blank word document. Additionally, crickets are shockingly acrobatic and can cling to even the tiniest edge of plastic (think layer lines of a vertical 3d printed wall). 

The new dispenser needed to solve these problems:
* All-or-nothing release (no potential for a half-open chamber where crickets could hide on a tiny ledge)
* Contain the cricket in a glass tube until distribution

Some additional features carried over from the previous version:
*  Motors are distant from the behavior arena to reduce vibration and noise that could alert the mouse/rat where the next cricket will drop
*  Dispensers on opposite corners turn together (so crickets are loaded into every second chamber as a blank)
*  Dispesners are driven by an arduino that is connected to a computer

Anyway, behold: my overly complex cricket dispenser system!
![rendering of assembled dispenser](https://github.com/regisshan/CricketDispenser/blob/main/images/Final%20-%20all%20together%20now.png)



# Obtaining the Materials

3d Print out the following quantites of each print in the 'design files' folder and purchase or obtain materials from dispenser part spreadsheet.

note: one corner setup, which includes a cricket cartridge and dispenser base should be able to print in ~24h on a single print bed on a Prusa i3 MK3S printer. All 4 motor case setups should also print overnight on one print print bed. 



**4x Cricket cartridge**
   - bucket holder
   - 6x glass tube holder
   - hex cap 

**4x Dispenser base**
  - hex holder
  - tall base
  - outer ring

 **4x Motor case**
   - stepper pulley
   - stepper holder
   - tube stick

# Assembling the dispenser

## Assemble the cricket cartridge
The cricket cartridge is the removable part that actually holds the crickets with the glass swinging buckets.

The hexagonal piece has small 3mm round slots where the miniature steel bearings fit. Press fit a small bearing into each of these holes. Insert an undersized dowel pin into the center of each bearing, then squeeze a glass tube holder into each of the 6 spots (you can also leave one spot blank to mark the "0" spot on the cartridge). It might be a good idea to hot glue or super glue the glass tubes into the holders, I have heard some reports of the glass tubes being launched across the arena.

## Assemble the hex holder and dispenser base
The hex holder is the part that sits on the base and spins, where the cricket cartridge sits. 

Press fit a 608-2RS into the bottom of the hex holder. If it doesn't fit, use a heat gun to /gently/ heat the part to soften the plastic, so the bearing can fit inside. 

Put a rubber O-Ring in the slot around the top of the hex holder to dampen the sound of the glass buckets swinging against the part.

Insert a 1" dowel into the hole in the dispenser base. The hex holder should now be able to sit on the base and spin freely. 

Insert two 1/4"-20 nuts into the slot at the bottom of the dispenser holder, then screw in two 1/4"-20 screws through the holes on the side. This will hold the dispenser on the corners of the arena.

Attach the outer ring to the dispenser base by sliding it onto the top of the tower-like piece.

Screw in a push-connector into the hole in the side of the tower-like piece. It is a good idea to glue this in place (superglue works nicely).

Cut some 4mm OD teflon tubing  to the length needed to get from your stepper motors to your dispenser. Thread some braided fishing line through the tubing, with enough extra on either end to wrap around the hex holder and the stepper pulley. Thread the fishing line through the push connector and tie it to the attachment point on the hex holder. Connect the tubing to the push connector. 


## Assemble the motor case

Slide the stepper pulley onto the stepper motor shaft. This will be a tight fit but you want to get the pully down onto the shaft as far as it will go. 

Super glue the tube stick to the stepper holder. Glue the push connector into one of the holes on the tube stick, making sure it is level with the pully when the stepper motor is in the holder. 

Thread the fishing line through the push connector, then tie it to the pulley. attach the tubing to the push connector.

## Assemble the arduino and electronics

Mount the RAMPS shield onto the arduino mega. 

Mount 4 stepper motor drivers onto their spots on the RAMPs board (X, Y, Z, and E), paying attention to the orientation of the drivers vs the RAMPS board. 

Plug in the stepper motors on the RAMPS board.

Plug in the arduino USB and power supply (via the RAMPS board)

Upload the arduino code using the arduino IDE. The code requires the "AccelStepper" package to work
   
# Using the dispenser

With the arduino IDE open, open the serial monitor. A message should appear telling you what buttons to press to advance the motors, and how many steps per turn. If the motors are over or under turning, adjust the number of steps to get it right (I usually see about 40 steps)

# Ideas for future updates
- Integrate with Bonsai
- Use arduino timepoints to cut videos
