/*
------------------------------------------------------------------------------
~ File   : aura.h
~ Author : Majid Derhambakhsh
~ Version: V1.0.0
~ Created: 12/20/2022 09:49:00 PM
~ Brief  :
~ Support:
           E-Mail : Majid.Derhambakhsh@gmail.com (subject : Embedded Library Support)
           
           Github : https://github.com/Majid-Derhambakhsh
------------------------------------------------------------------------------
~ Description:    

~ Attention  :    

~ Changes    :    
                  
------------------------------------------------------------------------------
*/

#ifndef __AURA_H_
#define __AURA_H_

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Include ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include <stdint.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Defines ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ---------------------------- Public ---------------------------- */
/* ---------------------- Define by compiler ---------------------- */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Types ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef enum /* Aura Mode */
{
	
	AURA_OFF,
	AURA_STATIC,
	AURA_BLINK,
	AURA_BREATH,
	AURA_SMOOTH
	
}Aura_ModeTypeDef;

typedef enum /* Aura Color */
{
	
	AURA_COLOR_RED,
	AURA_COLOR_GREEN,
	AURA_COLOR_BLUE,
	AURA_COLOR_MAGENTA,
	AURA_COLOR_YELLOW,
	AURA_COLOR_CYAN,
	AURA_COLOR_WHITE
	
}Aura_ColorTypeDef;

typedef struct /* Aura Type */
{
	
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
	
}Aura_TypeDef;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Enum ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Struct ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Prototype ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*
 * Function: Aura_Init
 * -------------------
 * Initialize the Aura RGB Spectrum
 *
 * Param  : 
 *         AURAx      : Pointer to Aura type
 *         Mode       : Aura Mode
 *         Color      : Aura Default Color
 *         Brightness : Aura Maximum Brightness (Timer Overflow Value)
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         Aura_TypeDef RGB1;
 *
 *         Aura_Init(&RGB1, AURA_SMOOTH, AURA_COLOR_RED, 999U);
 *         ...
 *         
 */
void Aura_Init(Aura_TypeDef *AURAx, Aura_ModeTypeDef Mode, Aura_ColorTypeDef Color, uint16_t Brightness);

/*
 * Function: Aura_Handle
 * ---------------------
 * Handling the Aura RGB Spectrum
 *
 * Param  : 
 *         AURAx : Pointer to Aura type
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         Aura_TypeDef RGB1;
 *
 *         while (1)
 *         {
 *
 *             Aura_Handle(&RGB1);
 *             
 *             PWM_SetPulseWidth(PWM_CHANNEL_1, RGB1.R); // MCU Timer Function to Set PWM
 *             PWM_SetPulseWidth(PWM_CHANNEL_2, RGB1.G); // MCU Timer Function to Set PWM
 *             PWM_SetPulseWidth(PWM_CHANNEL_3, RGB1.B); // MCU Timer Function to Set PWM
 *
 *             Delay(5)
 *             ...
 *         }
 *         
 */
void Aura_Handle(Aura_TypeDef *AURAx);

/*
 * Function: Aura_SetRGB
 * ---------------------
 * Set the RGB value of the Aura RGB Spectrum
 *
 * Param  : 
 *         AURAx : Pointer to Aura type
 *         R     : Red color value (Range: 0 ~ 255)
 *         G     : Green color value (Range: 0 ~ 255)
 *         B     : Blue color value (Range: 0 ~ 255)
 *         
 * Returns: 
 *         -
 *         
 * Example: 
 *         Aura_TypeDef RGB1;
 *
 *         Aura_SetRGB(&RGB1, 100, 255, 255);
 *         ...
 *         
 */
void Aura_SetRGB(Aura_TypeDef *AURAx, uint16_t R, uint16_t G, uint16_t B);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ End of the program ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#endif /* __AURA_H_ */
