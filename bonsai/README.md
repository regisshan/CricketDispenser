# Bonsai Files:
## 1. Arduino stepper motor
Controls a stepper motor using a RAMPS V1.4 and XXXX motor drivers. Requires basic firmata protocol to be uploaded to arduino. Ensure baud rate is the same as in the uploaded firmata file.

### pins
X_STEP_PIN         54

X_DIR_PIN          55

X_ENABLE_PIN       38

X_MIN_PIN           3

X_MAX_PIN           2



Y_STEP_PIN         60 

Y_DIR_PIN          61 

Y_ENABLE_PIN       56 

Z_STEP_PIN         46

Z_DIR_PIN          48

Z_ENABLE_PIN       62

Z_MIN_PIN          18

Z_MAX_PIN          19

E_STEP_PIN         26

E_DIR_PIN          28

E_ENABLE_PIN       24

## 2. Arduino servo
Controls servo motors as an alternative to stepper motors - don't need ramps board but servos aren't as strong


## 3. DLC label file
Labels videos with exported DLC model 

## 4. basic dispenser
basic control of the dispenser

## 5. Camera control
basic control of FLIR camera
