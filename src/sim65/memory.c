/*****************************************************************************/
/*                                                                           */
/*				   memory.h				     */
/*                                                                           */
/*		    Memory subsystem for the 6502 simulator		     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 2002      Ullrich von Bassewitz                                       */
/*               Wacholderweg 14                                             */
/*               D-70597 Stuttgart                                           */
/* EMail:        uz@cc65.org                                                 */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



/* sim65 */
#include "memory.h"



/*****************************************************************************/
/*  				     Data				     */
/*****************************************************************************/



static unsigned char RAM[0x10000];



/*****************************************************************************/
/*  				     Code				     */
/*****************************************************************************/



void WriteMem (unsigned Addr, unsigned char Val)
/* Write a byte to a memory location */
{
    RAM[Addr] = Val;
}



unsigned char ReadMem (unsigned Addr)
/* Read a byte from a memory location */
{
    return RAM[Addr];
}



unsigned ReadMemW (unsigned Addr)
/* Read a word from a memory location */
{
    unsigned W = ReadMem (Addr++);
    return (W | (ReadMem (Addr) << 8));
}



unsigned ReadZeroPageW (unsigned char Addr)
/* Read a word from the zero page. This function differs from ReadMemW in that
* the read will always be in the zero page, even in case of an address
* overflow.
*/
{
    unsigned W = ReadMem (Addr++);
    return (W | (ReadMem (Addr) << 8));
}



