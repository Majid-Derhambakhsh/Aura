/*
------------------------------------------------------------------------------
~ File   : aura.cpp
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

#include "aura.h"

/* ~~~~~~~~~~~~~~~~~~~~~ Global variables ~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~ */
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
void Aura_Init(Aura_TypeDef *AURAx, Aura_ModeTypeDef Mode, Aura_ColorTypeDef Color, uint16_t Brightness)
{
	
	AURAx->Mode       = Mode;
	AURAx->Color      = Color;
	AURAx->Brightness = Brightness;
	AURAx->R          = 0;
	AURAx->G          = 0;
	AURAx->B          = 0;
	
	/* --------------------- Setup RGB Value --------------------- */
	if (Mode == AURA_BREATH)
	{
		
		/*
			Color Mix:
				Magenta: Red + Blue
				Yellow: Red + Green
				Cyan: Blue + Green
				White: Red + Green + Blue
			
		*/
		
		/* Red, Magenta, Yellow, White */
		if ((Color == AURA_COLOR_RED) || (Color == AURA_COLOR_MAGENTA) || (Color == AURA_COLOR_YELLOW) || (Color == AURA_COLOR_WHITE))
		{
			AURAx->R = AURAx->Brightness;
		}
		
		/* Green, Yellow, Cyan, White */
		if ((Color == AURA_COLOR_GREEN) || (Color == AURA_COLOR_YELLOW) || (Color == AURA_COLOR_CYAN) || (Color == AURA_COLOR_WHITE))
		{
			AURAx->G = AURAx->Brightness;
		}
		
		/* Blue, Magenta, Cyan, White */
		if ((Color == AURA_COLOR_BLUE) || (Color == AURA_COLOR_MAGENTA) || (Color == AURA_COLOR_CYAN) || (Color == AURA_COLOR_WHITE))
		{
			AURAx->B = AURAx->Brightness;
		}
		
	}
	else if (Mode == AURA_SMOOTH)
	{
		AURAx->R = AURAx->Brightness;
	}
	
}

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
void Aura_Handle(Aura_TypeDef *AURAx)
{
	
	/*
		Color Mix:
			Magenta: Red + Blue
			Yellow: Red + Green
			Cyan: Blue + Green
			White: Red + Green + Blue
			
	*/
	
	/* --------------------- Aura Mode - Off --------------------- */
	if (AURAx->Mode == AURA_OFF)
	{
		AURAx->R = 0;
		AURAx->G = 0;
		AURAx->B = 0;
	}
	
	/* -------------------- Aura Mode - Static ------------------- */
	else if (AURAx->Mode == AURA_STATIC)
	{
		
		/* ...................... Red ...................... */
		if (AURAx->Color == AURA_COLOR_RED)
		{
			AURAx->R = AURAx->Brightness;
		}
		
		/* ..................... Green ..................... */
		else if (AURAx->Color == AURA_COLOR_GREEN)
		{
			AURAx->G = AURAx->Brightness;
		}
		
		/* ..................... Blue ...................... */
		else if (AURAx->Color == AURA_COLOR_BLUE)
		{
			AURAx->B = AURAx->Brightness;
		}
		
		/* .................... Magenta .................... */
		else if (AURAx->Color == AURA_COLOR_MAGENTA)
		{
			AURAx->R = AURAx->Brightness;
			AURAx->B = AURAx->Brightness;
		}
		
		/* ..................... Yellow .................... */
		else if (AURAx->Color == AURA_COLOR_YELLOW)
		{
			AURAx->R = AURAx->Brightness;
			AURAx->G = AURAx->Brightness;
		}
		
		/* ...................... Cyan ..................... */
		else if (AURAx->Color == AURA_COLOR_CYAN)
		{
			AURAx->G = AURAx->Brightness;
			AURAx->B = AURAx->Brightness;
		}
		
		/* ..................... White ..................... */
		else
		{
			AURAx->R = AURAx->Brightness;
			AURAx->G = AURAx->Brightness;
			AURAx->B = AURAx->Brightness;
		}
		
	}
	
	/* -------------------- Aura Mode - Blink -------------------- */
	else if (AURAx->Mode == AURA_BLINK)
	{
		
		if (AURAx->TransitionState == 0)
		{
			
			AURAx->R = 0;
			AURAx->G = 0;
			AURAx->B = 0;
			
			AURAx->TransitionState = 1;
			
		}
		else
		{
			
			/* ...................... Red ...................... */
			if (AURAx->Color == AURA_COLOR_RED)
			{
				AURAx->R = AURAx->Brightness;
			}
			
			/* ..................... Green ..................... */
			else if (AURAx->Color == AURA_COLOR_GREEN)
			{
				AURAx->G = AURAx->Brightness;
			}
			
			/* ..................... Blue ...................... */
			else if (AURAx->Color == AURA_COLOR_BLUE)
			{
				AURAx->B = AURAx->Brightness;
			}
			
			/* .................... Magenta .................... */
			else if (AURAx->Color == AURA_COLOR_MAGENTA)
			{
				AURAx->R = AURAx->Brightness;
				AURAx->B = AURAx->Brightness;
			}
			
			/* ..................... Yellow .................... */
			else if (AURAx->Color == AURA_COLOR_YELLOW)
			{
				AURAx->R = AURAx->Brightness;
				AURAx->G = AURAx->Brightness;
			}
			
			/* ...................... Cyan ..................... */
			else if (AURAx->Color == AURA_COLOR_CYAN)
			{
				AURAx->G = AURAx->Brightness;
				AURAx->B = AURAx->Brightness;
			}
			
			/* ..................... White ..................... */
			else
			{
				AURAx->R = AURAx->Brightness;
				AURAx->G = AURAx->Brightness;
				AURAx->B = AURAx->Brightness;
			}
			
			AURAx->TransitionState = 0;
			
		}
		
	}
	
	/* -------------------- Aura Mode - Breath ------------------- */
	else if (AURAx->Mode == AURA_BREATH)
	{
		
		/* ...................... Red ...................... */
		if (AURAx->Color == AURA_COLOR_RED)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->R--;
				
				if (AURAx->R == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->R++;
				
				if (AURAx->R == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* ..................... Green ..................... */
		else if (AURAx->Color == AURA_COLOR_GREEN)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->G--;
				
				if (AURAx->G == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->G++;
				
				if (AURAx->G == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* ..................... Blue ...................... */
		else if (AURAx->Color == AURA_COLOR_BLUE)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->B--;
				
				if (AURAx->B == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->B++;
				
				if (AURAx->B == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* .................... Magenta .................... */
		else if (AURAx->Color == AURA_COLOR_MAGENTA)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->R--;
				
				AURAx->B = AURAx->R;
				
				if (AURAx->R == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->R++;
				
				AURAx->B = AURAx->R;
				
				if (AURAx->R == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* ..................... Yellow .................... */
		else if (AURAx->Color == AURA_COLOR_YELLOW)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->R--;
				
				AURAx->G = AURAx->R;
				
				if (AURAx->R == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->R++;
				
				AURAx->G = AURAx->R;
				
				if (AURAx->R == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* ...................... Cyan ..................... */
		else if (AURAx->Color == AURA_COLOR_CYAN)
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->G--;
				
				AURAx->B = AURAx->G;
				
				if (AURAx->G == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->G++;
				
				AURAx->B = AURAx->G;
				
				if (AURAx->G == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/* ..................... White ..................... */
		else
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->R--;
				
				AURAx->G = AURAx->R;
				AURAx->B = AURAx->R;
				
				if (AURAx->R == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->R++;
				
				AURAx->G = AURAx->R;
				AURAx->B = AURAx->R;
				
				if (AURAx->R == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		/*
		if ((AURAx->Color == AURA_COLOR_RED) || (AURAx->Color == AURA_COLOR_MAGENTA) || (AURAx->Color == AURA_COLOR_YELLOW) || (AURAx->Color == AURA_COLOR_WHITE))
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->R--;
				
				if (AURAx->R == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->R++;
				
				if (AURAx->R == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		// Green, Yellow, Cyan, White
		if ((AURAx->Color == AURA_COLOR_GREEN) || (AURAx->Color == AURA_COLOR_YELLOW) || (AURAx->Color == AURA_COLOR_CYAN) || (AURAx->Color == AURA_COLOR_WHITE))
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->G--;
				
				if (AURAx->G == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->G++;
				
				if (AURAx->G == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		
		// Blue, Magenta, Cyan, White
		if ((AURAx->Color == AURA_COLOR_BLUE) || (AURAx->Color == AURA_COLOR_MAGENTA) || (AURAx->Color == AURA_COLOR_CYAN) || (AURAx->Color == AURA_COLOR_WHITE))
		{
			
			if (AURAx->TransitionState == 0)
			{
				
				AURAx->B--;
				
				if (AURAx->B == 0)
				{
					AURAx->TransitionState = 1;
				}
				
			}
			else
			{
				
				AURAx->B++;
				
				if (AURAx->B == AURAx->Brightness)
				{
					AURAx->TransitionState = 0;
				}
				
			}
			
		}
		*/
		
	}
	
	/* -------------------- Aura Mode - Smooth ------------------- */
	else if (AURAx->Mode == AURA_SMOOTH)
	{
		
		if (AURAx->TransitionState == 0)
		{
			
			AURAx->R--;
			AURAx->B++;
			
			if ((AURAx->R == 0) && (AURAx->B == AURAx->Brightness))
			{
				AURAx->TransitionState = 1;
			}
			
		}
		else if (AURAx->TransitionState == 1)
		{
			
			AURAx->B--;
			AURAx->G++;
			
			if ((AURAx->B == 0) && (AURAx->G == AURAx->Brightness))
			{
				AURAx->TransitionState = 2;
			}
			
		}
		else
		{
			
			AURAx->G--;
			AURAx->R++;
			
			if ((AURAx->G == 0) && (AURAx->R == AURAx->Brightness))
			{
				AURAx->TransitionState = 0;
			}
			
		}
		
	}
	
}

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
void Aura_SetRGB(Aura_TypeDef *AURAx, uint16_t R, uint16_t G, uint16_t B)
{
	
	AURAx->R = R * AURAx->Brightness / UINT8_MAX;
	AURAx->G = G * AURAx->Brightness / UINT8_MAX;
	AURAx->B = B * AURAx->Brightness / UINT8_MAX;
	
}
