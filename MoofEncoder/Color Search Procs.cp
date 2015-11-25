/*	File:		Color Search Procs.cp	Contains:	This file defines a number of commonly used color search procs.  For the encoder,	   			we only use one of the procs, which returns white if the color of a pixel is within				a certain delta of a key color, and returns black for all other cases.  We can use				this to quickly create masks of an image.	Written by: Timothy Carroll		Copyright:	Copyright � 1996-1999 by Apple Computer, Inc., All Rights Reserved.				You may incorporate this Apple sample source code into your program(s) without				restriction. This Apple sample source code has been provided "AS IS" and the				responsibility for its operation is yours. You are not permitted to redistribute				this Apple sample source code as "Apple sample source code" after having made				changes. If you're going to re-distribute the source, we require that you make				it clear in the source that the code was descended from Apple sample source				code, but that you've made changes.	Change History (most recent first):				7/1/1999	Karl Groethe	Updated for Metrowerks Codewarror Pro 2.1				8/15/96		Timothy Carroll	Initial Release				*/#include "Color Search Procs.h"SInt32		gSearchDelta = 0x2000;RGBColor	gMaskColor = {0,0,0};// We're going to define a custom color search proc.  This will be used by the class routines// to create the mask.static pascal Boolean	MaskSearchProc (RGBColor *theColor, long *result);static pascal Boolean	LightenSearchProc (RGBColor *theColor, long *result);static pascal Boolean   DarkenSearchProc (RGBColor *theColor, long *result);// We want to be able to compile for powermacs, so we'll provide UPPs for all// of the custom search procs. Note that we don't actually allow passing// the search proc's directly, only the UPPs.ColorSearchUPP MaskSearchProcUPP = NewColorSearchProc(MaskSearchProc);ColorSearchUPP LightenSearchProcUPP = NewColorSearchProc(LightenSearchProc);ColorSearchUPP DarkenSearchProcUPP = NewColorSearchProc(DarkenSearchProc);// The Mask search proc needs to be able to pass in a specific color to be used as// the mask.  We can't change the calling parameters or provide it via a handle// (unlike some System 7 routines, this one doesn't pass any "user data".). // So any additional parameters, like our key color and the delta, need to be// defined and passed in as global variables.pascal Boolean MaskSearchProc (RGBColor *theColor, long *result){	long temp;	if (theColor->red > gMaskColor.red)	{		temp = theColor->red - gMaskColor.red;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;		}	}	else	{		temp = gMaskColor.red - theColor->red;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;				}	}		if (theColor->green > gMaskColor.green)	{		temp = theColor->green - gMaskColor.green;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;		}	}	else	{		temp = gMaskColor.green - theColor->green;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;				}	}		if (theColor->blue > gMaskColor.blue)	{		temp = theColor->blue - gMaskColor.blue;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;		}	}	else	{		temp = gMaskColor.blue - theColor->blue;		if (temp > gSearchDelta)		{			*theColor = kBlack;			return false;				}	}		*theColor = kWhite;	return false;#pragma unused (result)}pascal Boolean DarkenSearchProc (RGBColor *theColor, long *result){	(theColor->red) >>= 1;	(theColor->green) >>= 1;	(theColor->blue) >>= 1;		return false;#pragma unused (result)}pascal Boolean LightenSearchProc (RGBColor *theColor, long *result){	(theColor->red) <<= 1;	(theColor->green) <<= 1;	(theColor->blue) <<= 1;	return false;#pragma unused (result)}