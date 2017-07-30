#ifndef eGUIStyles_H
#define eGUIStyles_H

/*
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Properties						Default Value				Potential Values								Notes
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Border
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
border-colour					CColour(0, 0, 0)
border-thickness				0
border-style					consistent					consistent, dashed, dotted
border-intersection-radius		0
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Fill
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
fill-colour						CColour(0xFF, 0xFF, 0xFF)
fill-colour-start				CColour(0xFF, 0xFF, 0xFF)
fill-colour-stop				CColour(0x80, 0x80, 0x80)
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Text
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
text-colour						CColour(0, 0, 0)
text-size						11
text-font						Verdana
text-style						default						bold, italic, underline, strikethrough			Multiple values supported. Separated by either spaces and/or commas.
text-thickness					1
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Position/Size
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
text-align						"left top"					Sets both independently: text-align-x, text-align-y
text-align-x					"left"						left, right, center
text-align-y					"center"					left, right, center
inner-spacing					0							Sets all together: inner-spacing-left, inner-spacing-top, inner-spacing-right, inner-spacing-bottom
inner-spacing-x					0							Sets both together: inner-spacing-left, inner-spacing-right
inner-spacing-y					0							Sets both together: inner-spacing-top, inner-spacing-bottom
inner-spacing-left				0							In pixels.
inner-spacing-top				0							In pixels.
inner-spacing-right				0							In pixels.
inner-spacing-bottom			0							In pixels.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Control Specific
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
caret-colour					CColour(0, 0, 0)
row-fill-colour-1				CColour(255, 255, 255)														For list controls.
row-fill-colour-2				CColour(200, 200, 200)														For list controls.
progress-bar-fill-colour		CColour(0, 50, 150)															For progress controls.
fill-colour-marked				CColour(0, 255, 0)															For radio and check controls.
fill-colour-unmarked			CColour(255, 255, 255)														For radio and check controls.
markable-text-spacing			5							In pixels.										For radio and check controls.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Notes
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Fill is drawn if at least one fill property is used, per control component.
Border is drawn if at least one border property is used, per control component.

Control component is for example seek bar for scroll control, or background bar for scroll control.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#endif