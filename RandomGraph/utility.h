/*************************************************************************************************************
*  File    : utility.h                                                                        
*                                                                                                    
*  Abstract: This file contains interfaces for various utility functions that are used througout the
*            application.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#ifndef _utility_h_
#define _utility_h_

#ifdef _WIN32

#include <windows.h>
#include <io.h>
#endif                      // end windows block...

void showConsole();
void hideConsole();


int displayMsg(const char*, ...);

#endif
