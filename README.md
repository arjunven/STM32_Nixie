# STM32 and USB-C Based Nixie Clock
A [Nixie](http://en.wikipedia.org/wiki/Nixie_tube) clock that's powered by USB-C and based on a STM32 microcontroller. Designed schematic, layout, and firmware from scratch! Fun mix of retro tech with modern electronics. Main Features:
  - Custom 5V to 180V boost converter that operates in discontinous conduction mode to power the Nixie tubes
  - USB-C Power input + bootloader
  - Push button dial that's used to set time and interface with the menu
  - Used high voltage shift registers to run the tube display
  - STM32F100 micro controller with abysmal flash storage ... because that's all that was in stock during the great covid parts shortage of 2021 when I started this project 

## Mostly Finished Product
<img width="945" height="455" alt="image" src="https://github.com/user-attachments/assets/0f391c93-6ed3-4038-959f-34b74184fadf" />
 
  - Still would like to add a walnut enclosure and a nice wodden knob for the push button dial
  - 80/20 rule in full force

## Layout
<img width="1037" height="388" alt="image" src="https://github.com/user-attachments/assets/11c0f7fd-a7f3-46a4-984b-559e51a83343" />
<img width="1352" height="694" alt="image" src="https://github.com/user-attachments/assets/25c9e54e-c055-4959-9797-cf10624781be" />
<img width="1334" height="650" alt="image" src="https://github.com/user-attachments/assets/2eb64b77-7491-4165-9526-051c6a704a1e" />


- 4 Layer board

## Schematics
### 5V to 180V Boost Converter
<img width="1467" height="555" alt="image" src="https://github.com/user-attachments/assets/874b31fc-9460-4884-9e37-c6cf0e07cb47" />

### Full Schematics
[Full Schematics here
](https://github.com/arjunven/STM32_Nixie/blob/main/pcb/outputs/STM32_Nixie_Schematics.pdf
)

## Bringup/Development

![IMG_3918](https://github.com/user-attachments/assets/79d7169a-acb0-4275-b93e-1e199e8c3650)

- Bring up of HV shift register driver with assistance from Merlin
