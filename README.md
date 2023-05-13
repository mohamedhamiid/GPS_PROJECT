# GPS_PROJECT

## Objective:
- On reaching the final destination, the GREEN led is turned on.

## Bonus:
- when the target destination is far away by distance > 5 meters , the RED led will turn on.
- When the target destination is about to be reached < 5 meters , the BLUE led will turn on.

## What we used ?
- Tiva TM4C123GH6PM Microcontroller based on ARM Cortex-M4.
- GPS Module.

## Algorithm :
- Getting the current location from GPS Module using UART, then calculating the distance between it and final location which is hard coded inside the code.
- Based on the distance we choose which led to turn on.

## Repo Files:
- INCLUDE: Contain Prototypes and hash defines of each file
- SRC : Contain source code.
- SERVICES : Contain Bit_utilies which contain some Sets and clears + header file of tiva which contains registers adrresses 
## Architecture Layers and Contributions :

### App (Application Layer)
#### Main : 
- Kirollos George Louis           2000356
- Omar Magdy Mostafa Mahmoud      2001135

### HAL (Hardware Architecture Layer)
#### GPS :
- Mohamed Abdel Hamid Abdel Hares 2001087
- Anas Hamed Ahmed                2001584
#### LED :
- Mostafa Mohamed Osman Shaheen   2000912

### MCAL (Microcontroller Architecture Layer)
#### DIO:
- Yousif Hazim Nazar              2001741
#### UART:
- Zeyad Abdullah Sayed            2000417
- Ahmed gamal helmy               2000082
## Video Link:

## Functions description is included with each function in code
