/* 
 * File:   password.h
 * Author: hassa
 *
 * Created on September 3, 2024, 7:55 AM
 */

#ifndef PASSWORD_H
#define	PASSWORD_H


/*
 --------------------------------------------------------------------------------------------------------
 |                            <  general password  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   general password                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : 0 is run , one is done                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t GeneralPasswordCallback();
/*
 --------------------------------------------------------------------------------------------------------
 |                            <  custome password  >                                                        |
 --------------------------------------------------------------------------------------------------------
 | < @Function          : void   custome password                                                         |
 | < @Description       : run this callback to active data                                              |                                                  |                                                           
 | < @return            : 0 is run , one is done                                                                          |                     
 --------------------------------------------------------------------------------------------------------
 */
uint8_t CustomPasswordCallback();

#endif	/* PASSWORD_H */

