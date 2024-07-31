
<video src='Arduino Example On X-Noabara R1.mp4' width=180> </video>

# Aura
"Aura" is A dynamic library for creating and controlling vibrant color effects on all platforms such as Arduino, microcontrollers, etc...

## Release
### Version: 1.0.0

- #### Author: [Majid Derhambakhsh](https://github.com/majid-derhambakhsh)

- #### Type: Software/Embedded Software.

- #### Support :  
               - All Platforms

- #### Program Language: C/C++

- #### Requirement Libraries: 
               
- #### Properties:
               - Support 5 Color Modes
               - Support 7 Color

- #### Changelog:
               -   

## Overview 
### Types:
- `enum Aura_ModeTypeDef`: Color Spectrum Mode, Params:
  ```c++  
	- AURA_OFF
	- AURA_STATIC
	- AURA_BLINK
	- AURA_BREATH
	- AURA_SMOOTH
  ```

- `enum Aura_ColorTypeDef`: Color, Params:
  ```c++  
	- AURA_COLOR_RED
	- AURA_COLOR_GREEN
	- AURA_COLOR_BLUE
	- AURA_COLOR_MAGENTA
	- AURA_COLOR_YELLOW
	- AURA_COLOR_CYAN
	- AURA_COLOR_WHITE
  ```

- `struct Aura_TypeDef`: Aura Handle Type, Params:
  ```c++  
	/* RGB Value */
	volatile uint16_t R;
	volatile uint16_t G;
	volatile uint16_t B;
	
	/* Aura Color Mode */
	Aura_ModeTypeDef Mode;
	
	/* Aura Color */
	Aura_ColorTypeDef Color;
	
	/* RGB Max Brightness */
	uint16_t Brightness;
	
	/* Transition State */
	volatile uint8_t TransitionState;
  ```

### Macros:
```c++  
- None 
``` 

### Initialization and de-initialization functions:
```c++
void Aura_Init(Aura_TypeDef *AURAx, Aura_ModeTypeDef Mode, Aura_ColorTypeDef Color, uint16_t Brightness);
```  

### Operation functions:
```c++  
void Aura_Handle(Aura_TypeDef *AURAx);
void Aura_SetRGB(Aura_TypeDef *AURAx, uint16_t R, uint16_t G, uint16_t B);
``` 

## Guide

#### This library can be used as follows:
#### 1.  Add `aura.h` header
#### 2.  Define the `Aura_TypeDef` object in the global section of your C/C++ Code, for example:
  ```c++
Aura_TypeDef RGB1;
  ```
#### 3.  Initialize Aura with the `Aura_Init`, for example:
  ```c++
Aura_TypeDef RGB1;

void main()
{
	  Aura_Init(&RGB1, AURA_SMOOTH, AURA_COLOR_RED, 999U);
}
  ```
#### 4.  Add the `Aura_Handle` function in Loop or ISR, Get R, G, and B values, and set in PWM, etc..., for example:
  ```c++
void main()
{
	  Aura_Init(&RGB1, AURA_SMOOTH, AURA_COLOR_RED, 999U);

	  while(1)
	  {
	  	  Aura_Handle(&RGB1);

	  	  PWM_SetPulseWidth(PWM_CHANNEL_1, RGB1.R); // MCU Timer Function to Set PWM
	  	  PWM_SetPulseWidth(PWM_CHANNEL_2, RGB1.G); // MCU Timer Function to Set PWM
	  	  PWM_SetPulseWidth(PWM_CHANNEL_3, RGB1.B); // MCU Timer Function to Set PWM
        
	  	  Delay(5)
	  }
}
  ```
      
## Examples  
#### Example 1: Two Color Spectrum via Arduino and WS2812 LEDs
```c++  
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "FastLED.h"
#include "aura.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#define NUM_LEDS 2
#define DATA_PIN 13

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Global object ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* RGB LED */
CRGB leds[NUM_LEDS];

Aura_TypeDef LED1;
Aura_TypeDef LED2;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void setup()
{
  /* ---------------- Aura RGB Initialize --------------- */
  Aura_Init(&LED1, AURA_SMOOTH, AURA_COLOR_RED, 255U);
  Aura_Init(&LED2, AURA_BREATH, AURA_COLOR_GREEN, 255U);
  
  delay(1000);
  
  /* ---------------- WS2812 Initialize ----------------- */
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop()
{
  Aura_Handle(&LED1);
  Aura_Handle(&LED2);

  leds[0] = CRGB(LED1.G, LED1.R, LED1.B);
  leds[1] = CRGB(LED2.G, LED2.R, LED2.B);
  FastLED.show();
  delay(20);
}
```

## Test Performed:
- [x] STM32   
- [x] Arduino  
- [x] AVR  

> [!NOTE]
> Be a part of making this library better by [sharing your thoughts and suggestions](mailto:majid.derhambakhsh@outlook.com).
