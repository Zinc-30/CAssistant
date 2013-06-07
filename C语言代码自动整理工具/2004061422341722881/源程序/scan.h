/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 85 of your 30 day trial period.
* 
* This file was produced by an UNREGISTERED COPY of Parser Generator. It is
* for evaluation purposes only. If you continue to use Parser Generator 30
* days after installation then you are required to purchase a license. For
* more information see the online help or go to the Bumble-Bee Software
* homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* scan.h
* C header file generated from scan.l.
* 
* Date: 06/24/03
* Time: 17:07:53
* 
* ALex Version: 2.05
****************************************************************************/

#ifndef _SCAN_H
#define _SCAN_H

#include <yylex.h>

#line 15 ".\\scan.l"

    #define MAXTOKENLEN 40

	extern char tokenString[MAXTOKENLEN+1];

	TokenType getToken(void);

#line 41 "scan.h"
#ifndef INITIAL
#define INITIAL 0
#endif

#endif
