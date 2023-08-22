/*
 * EEPROM_data.h
 *
 * Created: 17/5/2018 3:32:48 p. m.
 *  Author: IoT SolucioneX
 */ 


#ifndef EEPROM_DATA_H_
#define EEPROM_DATA_H_

// -------- Includes --------- //


// -------- Defines --------- //


//--- Function Prototypes ---//

#ifdef DEBUG_TASK
void EEPROMSaveDefaultData(void);
void EEPROMPrint(void);
#endif


#endif /* EEPROM_DATA_H_ */