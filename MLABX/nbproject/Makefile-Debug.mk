#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-Debug.mk)" "nbproject/Makefile-local-Debug.mk"
include nbproject/Makefile-local-Debug.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=Debug
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=actuators/airDistMotor.c actuators/elecSpeedReg.c actuators/lamps.c actuators/threeLevelSwitch.c comms/usart.c display/lcd.c display/led.c display/MM5481N.asm.S display/PCF2112CT.asm.S EEPROM/EEPROM_data.c EEPROM/EEPROM_fncs.c HAL/adc.c HAL/board.c keypad/keypad.c rtos/tasks.c rtos/timers.c sensors/tempSensor.c ui/unit.c ui/unitUI.c common.c ElectronicACUnitAVR8.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/actuators/airDistMotor.o ${OBJECTDIR}/actuators/elecSpeedReg.o ${OBJECTDIR}/actuators/lamps.o ${OBJECTDIR}/actuators/threeLevelSwitch.o ${OBJECTDIR}/comms/usart.o ${OBJECTDIR}/display/lcd.o ${OBJECTDIR}/display/led.o ${OBJECTDIR}/display/MM5481N.asm.o ${OBJECTDIR}/display/PCF2112CT.asm.o ${OBJECTDIR}/EEPROM/EEPROM_data.o ${OBJECTDIR}/EEPROM/EEPROM_fncs.o ${OBJECTDIR}/HAL/adc.o ${OBJECTDIR}/HAL/board.o ${OBJECTDIR}/keypad/keypad.o ${OBJECTDIR}/rtos/tasks.o ${OBJECTDIR}/rtos/timers.o ${OBJECTDIR}/sensors/tempSensor.o ${OBJECTDIR}/ui/unit.o ${OBJECTDIR}/ui/unitUI.o ${OBJECTDIR}/common.o ${OBJECTDIR}/ElectronicACUnitAVR8.o
POSSIBLE_DEPFILES=${OBJECTDIR}/actuators/airDistMotor.o.d ${OBJECTDIR}/actuators/elecSpeedReg.o.d ${OBJECTDIR}/actuators/lamps.o.d ${OBJECTDIR}/actuators/threeLevelSwitch.o.d ${OBJECTDIR}/comms/usart.o.d ${OBJECTDIR}/display/lcd.o.d ${OBJECTDIR}/display/led.o.d ${OBJECTDIR}/display/MM5481N.asm.o.d ${OBJECTDIR}/display/PCF2112CT.asm.o.d ${OBJECTDIR}/EEPROM/EEPROM_data.o.d ${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d ${OBJECTDIR}/HAL/adc.o.d ${OBJECTDIR}/HAL/board.o.d ${OBJECTDIR}/keypad/keypad.o.d ${OBJECTDIR}/rtos/tasks.o.d ${OBJECTDIR}/rtos/timers.o.d ${OBJECTDIR}/sensors/tempSensor.o.d ${OBJECTDIR}/ui/unit.o.d ${OBJECTDIR}/ui/unitUI.o.d ${OBJECTDIR}/common.o.d ${OBJECTDIR}/ElectronicACUnitAVR8.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/actuators/airDistMotor.o ${OBJECTDIR}/actuators/elecSpeedReg.o ${OBJECTDIR}/actuators/lamps.o ${OBJECTDIR}/actuators/threeLevelSwitch.o ${OBJECTDIR}/comms/usart.o ${OBJECTDIR}/display/lcd.o ${OBJECTDIR}/display/led.o ${OBJECTDIR}/display/MM5481N.asm.o ${OBJECTDIR}/display/PCF2112CT.asm.o ${OBJECTDIR}/EEPROM/EEPROM_data.o ${OBJECTDIR}/EEPROM/EEPROM_fncs.o ${OBJECTDIR}/HAL/adc.o ${OBJECTDIR}/HAL/board.o ${OBJECTDIR}/keypad/keypad.o ${OBJECTDIR}/rtos/tasks.o ${OBJECTDIR}/rtos/timers.o ${OBJECTDIR}/sensors/tempSensor.o ${OBJECTDIR}/ui/unit.o ${OBJECTDIR}/ui/unitUI.o ${OBJECTDIR}/common.o ${OBJECTDIR}/ElectronicACUnitAVR8.o

# Source Files
SOURCEFILES=actuators/airDistMotor.c actuators/elecSpeedReg.c actuators/lamps.c actuators/threeLevelSwitch.c comms/usart.c display/lcd.c display/led.c display/MM5481N.asm.S display/PCF2112CT.asm.S EEPROM/EEPROM_data.c EEPROM/EEPROM_fncs.c HAL/adc.c HAL/board.c keypad/keypad.c rtos/tasks.c rtos/timers.c sensors/tempSensor.c ui/unit.c ui/unitUI.c common.c ElectronicACUnitAVR8.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega324pa"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=ATmega324PA
ProjectDir="X:\Development\IoT SolucioneX\ElectronicACUnitAVR8\UnitMLABX\Unit"
ProjectName=ElectronicACUnitAVR8
ConfName=Debug
ImagePath="dist\Debug\${IMAGE_TYPE}\Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\Debug\${IMAGE_TYPE}"
ImageName="Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [if ${IsDebug} == "false" ${ProjectDir}\flash_hex.cmd ${Device} ${ProjectDir} ${ImagePath}]"
	@if ${IsDebug} == "false" ${ProjectDir}\flash_hex.cmd ${Device} ${ProjectDir} ${ImagePath}
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=ATmega324PA
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/display/MM5481N.asm.o: display/MM5481N.asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o.d 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o.ok ${OBJECTDIR}/display/MM5481N.asm.o.err 
	 ${MP_CC} $(MP_EXTRA_AS_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -DDEBUG  -x assembler-with-cpp -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -MD -MP -MF "${OBJECTDIR}/display/MM5481N.asm.o.d" -MT "${OBJECTDIR}/display/MM5481N.asm.o.d" -MT ${OBJECTDIR}/display/MM5481N.asm.o -o ${OBJECTDIR}/display/MM5481N.asm.o display/MM5481N.asm.S  -DXPRJ_Debug=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/display/MM5481N.asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -Wa,-gdwarf2 -Wa,-g
	
${OBJECTDIR}/display/PCF2112CT.asm.o: display/PCF2112CT.asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o.d 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o.ok ${OBJECTDIR}/display/PCF2112CT.asm.o.err 
	 ${MP_CC} $(MP_EXTRA_AS_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -DDEBUG  -x assembler-with-cpp -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -MD -MP -MF "${OBJECTDIR}/display/PCF2112CT.asm.o.d" -MT "${OBJECTDIR}/display/PCF2112CT.asm.o.d" -MT ${OBJECTDIR}/display/PCF2112CT.asm.o -o ${OBJECTDIR}/display/PCF2112CT.asm.o display/PCF2112CT.asm.S  -DXPRJ_Debug=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/display/PCF2112CT.asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1 -Wa,-gdwarf2 -Wa,-g
	
else
${OBJECTDIR}/display/MM5481N.asm.o: display/MM5481N.asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o.d 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o 
	@${RM} ${OBJECTDIR}/display/MM5481N.asm.o.ok ${OBJECTDIR}/display/MM5481N.asm.o.err 
	 ${MP_CC} $(MP_EXTRA_AS_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x assembler-with-cpp -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -MD -MP -MF "${OBJECTDIR}/display/MM5481N.asm.o.d" -MT "${OBJECTDIR}/display/MM5481N.asm.o.d" -MT ${OBJECTDIR}/display/MM5481N.asm.o -o ${OBJECTDIR}/display/MM5481N.asm.o display/MM5481N.asm.S  -DXPRJ_Debug=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/display/MM5481N.asm.o.asm.d" -Wa,-gdwarf2 -Wa,-g
	
${OBJECTDIR}/display/PCF2112CT.asm.o: display/PCF2112CT.asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o.d 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o 
	@${RM} ${OBJECTDIR}/display/PCF2112CT.asm.o.ok ${OBJECTDIR}/display/PCF2112CT.asm.o.err 
	 ${MP_CC} $(MP_EXTRA_AS_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x assembler-with-cpp -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -MD -MP -MF "${OBJECTDIR}/display/PCF2112CT.asm.o.d" -MT "${OBJECTDIR}/display/PCF2112CT.asm.o.d" -MT ${OBJECTDIR}/display/PCF2112CT.asm.o -o ${OBJECTDIR}/display/PCF2112CT.asm.o display/PCF2112CT.asm.S  -DXPRJ_Debug=$(CND_CONF)  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/display/PCF2112CT.asm.o.asm.d" -Wa,-gdwarf2 -Wa,-g
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/actuators/airDistMotor.o: actuators/airDistMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/airDistMotor.o.d 
	@${RM} ${OBJECTDIR}/actuators/airDistMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/airDistMotor.o.d" -MT "${OBJECTDIR}/actuators/airDistMotor.o.d" -MT ${OBJECTDIR}/actuators/airDistMotor.o  -o ${OBJECTDIR}/actuators/airDistMotor.o actuators/airDistMotor.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/elecSpeedReg.o: actuators/elecSpeedReg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/elecSpeedReg.o.d 
	@${RM} ${OBJECTDIR}/actuators/elecSpeedReg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/elecSpeedReg.o.d" -MT "${OBJECTDIR}/actuators/elecSpeedReg.o.d" -MT ${OBJECTDIR}/actuators/elecSpeedReg.o  -o ${OBJECTDIR}/actuators/elecSpeedReg.o actuators/elecSpeedReg.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/lamps.o: actuators/lamps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/lamps.o.d 
	@${RM} ${OBJECTDIR}/actuators/lamps.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/lamps.o.d" -MT "${OBJECTDIR}/actuators/lamps.o.d" -MT ${OBJECTDIR}/actuators/lamps.o  -o ${OBJECTDIR}/actuators/lamps.o actuators/lamps.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/threeLevelSwitch.o: actuators/threeLevelSwitch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/threeLevelSwitch.o.d 
	@${RM} ${OBJECTDIR}/actuators/threeLevelSwitch.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/threeLevelSwitch.o.d" -MT "${OBJECTDIR}/actuators/threeLevelSwitch.o.d" -MT ${OBJECTDIR}/actuators/threeLevelSwitch.o  -o ${OBJECTDIR}/actuators/threeLevelSwitch.o actuators/threeLevelSwitch.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/comms/usart.o: comms/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/comms" 
	@${RM} ${OBJECTDIR}/comms/usart.o.d 
	@${RM} ${OBJECTDIR}/comms/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/comms/usart.o.d" -MT "${OBJECTDIR}/comms/usart.o.d" -MT ${OBJECTDIR}/comms/usart.o  -o ${OBJECTDIR}/comms/usart.o comms/usart.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/display/lcd.o: display/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/lcd.o.d 
	@${RM} ${OBJECTDIR}/display/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/display/lcd.o.d" -MT "${OBJECTDIR}/display/lcd.o.d" -MT ${OBJECTDIR}/display/lcd.o  -o ${OBJECTDIR}/display/lcd.o display/lcd.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/display/led.o: display/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/led.o.d 
	@${RM} ${OBJECTDIR}/display/led.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/display/led.o.d" -MT "${OBJECTDIR}/display/led.o.d" -MT ${OBJECTDIR}/display/led.o  -o ${OBJECTDIR}/display/led.o display/led.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/EEPROM/EEPROM_data.o: EEPROM/EEPROM_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_data.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_data.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM_data.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM_data.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM_data.o  -o ${OBJECTDIR}/EEPROM/EEPROM_data.o EEPROM/EEPROM_data.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/EEPROM/EEPROM_fncs.o: EEPROM/EEPROM_fncs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_fncs.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM_fncs.o  -o ${OBJECTDIR}/EEPROM/EEPROM_fncs.o EEPROM/EEPROM_fncs.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/HAL/adc.o: HAL/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/HAL" 
	@${RM} ${OBJECTDIR}/HAL/adc.o.d 
	@${RM} ${OBJECTDIR}/HAL/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/HAL/adc.o.d" -MT "${OBJECTDIR}/HAL/adc.o.d" -MT ${OBJECTDIR}/HAL/adc.o  -o ${OBJECTDIR}/HAL/adc.o HAL/adc.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/HAL/board.o: HAL/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/HAL" 
	@${RM} ${OBJECTDIR}/HAL/board.o.d 
	@${RM} ${OBJECTDIR}/HAL/board.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/HAL/board.o.d" -MT "${OBJECTDIR}/HAL/board.o.d" -MT ${OBJECTDIR}/HAL/board.o  -o ${OBJECTDIR}/HAL/board.o HAL/board.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/keypad/keypad.o: keypad/keypad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/keypad" 
	@${RM} ${OBJECTDIR}/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/keypad/keypad.o.d" -MT "${OBJECTDIR}/keypad/keypad.o.d" -MT ${OBJECTDIR}/keypad/keypad.o  -o ${OBJECTDIR}/keypad/keypad.o keypad/keypad.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/rtos/tasks.o: rtos/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/rtos" 
	@${RM} ${OBJECTDIR}/rtos/tasks.o.d 
	@${RM} ${OBJECTDIR}/rtos/tasks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/rtos/tasks.o.d" -MT "${OBJECTDIR}/rtos/tasks.o.d" -MT ${OBJECTDIR}/rtos/tasks.o  -o ${OBJECTDIR}/rtos/tasks.o rtos/tasks.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/rtos/timers.o: rtos/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/rtos" 
	@${RM} ${OBJECTDIR}/rtos/timers.o.d 
	@${RM} ${OBJECTDIR}/rtos/timers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/rtos/timers.o.d" -MT "${OBJECTDIR}/rtos/timers.o.d" -MT ${OBJECTDIR}/rtos/timers.o  -o ${OBJECTDIR}/rtos/timers.o rtos/timers.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/sensors/tempSensor.o: sensors/tempSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sensors" 
	@${RM} ${OBJECTDIR}/sensors/tempSensor.o.d 
	@${RM} ${OBJECTDIR}/sensors/tempSensor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/sensors/tempSensor.o.d" -MT "${OBJECTDIR}/sensors/tempSensor.o.d" -MT ${OBJECTDIR}/sensors/tempSensor.o  -o ${OBJECTDIR}/sensors/tempSensor.o sensors/tempSensor.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ui/unit.o: ui/unit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ui" 
	@${RM} ${OBJECTDIR}/ui/unit.o.d 
	@${RM} ${OBJECTDIR}/ui/unit.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ui/unit.o.d" -MT "${OBJECTDIR}/ui/unit.o.d" -MT ${OBJECTDIR}/ui/unit.o  -o ${OBJECTDIR}/ui/unit.o ui/unit.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ui/unitUI.o: ui/unitUI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ui" 
	@${RM} ${OBJECTDIR}/ui/unitUI.o.d 
	@${RM} ${OBJECTDIR}/ui/unitUI.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ui/unitUI.o.d" -MT "${OBJECTDIR}/ui/unitUI.o.d" -MT ${OBJECTDIR}/ui/unitUI.o  -o ${OBJECTDIR}/ui/unitUI.o ui/unitUI.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/common.o: common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/common.o.d" -MT "${OBJECTDIR}/common.o.d" -MT ${OBJECTDIR}/common.o  -o ${OBJECTDIR}/common.o common.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ElectronicACUnitAVR8.o: ElectronicACUnitAVR8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ElectronicACUnitAVR8.o.d 
	@${RM} ${OBJECTDIR}/ElectronicACUnitAVR8.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ElectronicACUnitAVR8.o.d" -MT "${OBJECTDIR}/ElectronicACUnitAVR8.o.d" -MT ${OBJECTDIR}/ElectronicACUnitAVR8.o  -o ${OBJECTDIR}/ElectronicACUnitAVR8.o ElectronicACUnitAVR8.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
else
${OBJECTDIR}/actuators/airDistMotor.o: actuators/airDistMotor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/airDistMotor.o.d 
	@${RM} ${OBJECTDIR}/actuators/airDistMotor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/airDistMotor.o.d" -MT "${OBJECTDIR}/actuators/airDistMotor.o.d" -MT ${OBJECTDIR}/actuators/airDistMotor.o  -o ${OBJECTDIR}/actuators/airDistMotor.o actuators/airDistMotor.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/elecSpeedReg.o: actuators/elecSpeedReg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/elecSpeedReg.o.d 
	@${RM} ${OBJECTDIR}/actuators/elecSpeedReg.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/elecSpeedReg.o.d" -MT "${OBJECTDIR}/actuators/elecSpeedReg.o.d" -MT ${OBJECTDIR}/actuators/elecSpeedReg.o  -o ${OBJECTDIR}/actuators/elecSpeedReg.o actuators/elecSpeedReg.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/lamps.o: actuators/lamps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/lamps.o.d 
	@${RM} ${OBJECTDIR}/actuators/lamps.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/lamps.o.d" -MT "${OBJECTDIR}/actuators/lamps.o.d" -MT ${OBJECTDIR}/actuators/lamps.o  -o ${OBJECTDIR}/actuators/lamps.o actuators/lamps.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/actuators/threeLevelSwitch.o: actuators/threeLevelSwitch.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/actuators" 
	@${RM} ${OBJECTDIR}/actuators/threeLevelSwitch.o.d 
	@${RM} ${OBJECTDIR}/actuators/threeLevelSwitch.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/actuators/threeLevelSwitch.o.d" -MT "${OBJECTDIR}/actuators/threeLevelSwitch.o.d" -MT ${OBJECTDIR}/actuators/threeLevelSwitch.o  -o ${OBJECTDIR}/actuators/threeLevelSwitch.o actuators/threeLevelSwitch.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/comms/usart.o: comms/usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/comms" 
	@${RM} ${OBJECTDIR}/comms/usart.o.d 
	@${RM} ${OBJECTDIR}/comms/usart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/comms/usart.o.d" -MT "${OBJECTDIR}/comms/usart.o.d" -MT ${OBJECTDIR}/comms/usart.o  -o ${OBJECTDIR}/comms/usart.o comms/usart.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/display/lcd.o: display/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/lcd.o.d 
	@${RM} ${OBJECTDIR}/display/lcd.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/display/lcd.o.d" -MT "${OBJECTDIR}/display/lcd.o.d" -MT ${OBJECTDIR}/display/lcd.o  -o ${OBJECTDIR}/display/lcd.o display/lcd.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/display/led.o: display/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/display" 
	@${RM} ${OBJECTDIR}/display/led.o.d 
	@${RM} ${OBJECTDIR}/display/led.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/display/led.o.d" -MT "${OBJECTDIR}/display/led.o.d" -MT ${OBJECTDIR}/display/led.o  -o ${OBJECTDIR}/display/led.o display/led.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/EEPROM/EEPROM_data.o: EEPROM/EEPROM_data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_data.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_data.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM_data.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM_data.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM_data.o  -o ${OBJECTDIR}/EEPROM/EEPROM_data.o EEPROM/EEPROM_data.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/EEPROM/EEPROM_fncs.o: EEPROM/EEPROM_fncs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/EEPROM" 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d 
	@${RM} ${OBJECTDIR}/EEPROM/EEPROM_fncs.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d" -MT "${OBJECTDIR}/EEPROM/EEPROM_fncs.o.d" -MT ${OBJECTDIR}/EEPROM/EEPROM_fncs.o  -o ${OBJECTDIR}/EEPROM/EEPROM_fncs.o EEPROM/EEPROM_fncs.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/HAL/adc.o: HAL/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/HAL" 
	@${RM} ${OBJECTDIR}/HAL/adc.o.d 
	@${RM} ${OBJECTDIR}/HAL/adc.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/HAL/adc.o.d" -MT "${OBJECTDIR}/HAL/adc.o.d" -MT ${OBJECTDIR}/HAL/adc.o  -o ${OBJECTDIR}/HAL/adc.o HAL/adc.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/HAL/board.o: HAL/board.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/HAL" 
	@${RM} ${OBJECTDIR}/HAL/board.o.d 
	@${RM} ${OBJECTDIR}/HAL/board.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/HAL/board.o.d" -MT "${OBJECTDIR}/HAL/board.o.d" -MT ${OBJECTDIR}/HAL/board.o  -o ${OBJECTDIR}/HAL/board.o HAL/board.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/keypad/keypad.o: keypad/keypad.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/keypad" 
	@${RM} ${OBJECTDIR}/keypad/keypad.o.d 
	@${RM} ${OBJECTDIR}/keypad/keypad.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/keypad/keypad.o.d" -MT "${OBJECTDIR}/keypad/keypad.o.d" -MT ${OBJECTDIR}/keypad/keypad.o  -o ${OBJECTDIR}/keypad/keypad.o keypad/keypad.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/rtos/tasks.o: rtos/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/rtos" 
	@${RM} ${OBJECTDIR}/rtos/tasks.o.d 
	@${RM} ${OBJECTDIR}/rtos/tasks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/rtos/tasks.o.d" -MT "${OBJECTDIR}/rtos/tasks.o.d" -MT ${OBJECTDIR}/rtos/tasks.o  -o ${OBJECTDIR}/rtos/tasks.o rtos/tasks.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/rtos/timers.o: rtos/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/rtos" 
	@${RM} ${OBJECTDIR}/rtos/timers.o.d 
	@${RM} ${OBJECTDIR}/rtos/timers.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/rtos/timers.o.d" -MT "${OBJECTDIR}/rtos/timers.o.d" -MT ${OBJECTDIR}/rtos/timers.o  -o ${OBJECTDIR}/rtos/timers.o rtos/timers.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/sensors/tempSensor.o: sensors/tempSensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/sensors" 
	@${RM} ${OBJECTDIR}/sensors/tempSensor.o.d 
	@${RM} ${OBJECTDIR}/sensors/tempSensor.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/sensors/tempSensor.o.d" -MT "${OBJECTDIR}/sensors/tempSensor.o.d" -MT ${OBJECTDIR}/sensors/tempSensor.o  -o ${OBJECTDIR}/sensors/tempSensor.o sensors/tempSensor.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ui/unit.o: ui/unit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ui" 
	@${RM} ${OBJECTDIR}/ui/unit.o.d 
	@${RM} ${OBJECTDIR}/ui/unit.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ui/unit.o.d" -MT "${OBJECTDIR}/ui/unit.o.d" -MT ${OBJECTDIR}/ui/unit.o  -o ${OBJECTDIR}/ui/unit.o ui/unit.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ui/unitUI.o: ui/unitUI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ui" 
	@${RM} ${OBJECTDIR}/ui/unitUI.o.d 
	@${RM} ${OBJECTDIR}/ui/unitUI.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ui/unitUI.o.d" -MT "${OBJECTDIR}/ui/unitUI.o.d" -MT ${OBJECTDIR}/ui/unitUI.o  -o ${OBJECTDIR}/ui/unitUI.o ui/unitUI.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/common.o: common.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/common.o.d 
	@${RM} ${OBJECTDIR}/common.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/common.o.d" -MT "${OBJECTDIR}/common.o.d" -MT ${OBJECTDIR}/common.o  -o ${OBJECTDIR}/common.o common.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
${OBJECTDIR}/ElectronicACUnitAVR8.o: ElectronicACUnitAVR8.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ElectronicACUnitAVR8.o.d 
	@${RM} ${OBJECTDIR}/ElectronicACUnitAVR8.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega324pa ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -I"." -funsigned-char -funsigned-bitfields -O3 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -DDEBUG -Wall -v -MD -MP -MF "${OBJECTDIR}/ElectronicACUnitAVR8.o.d" -MT "${OBJECTDIR}/ElectronicACUnitAVR8.o.d" -MT ${OBJECTDIR}/ElectronicACUnitAVR8.o  -o ${OBJECTDIR}/ElectronicACUnitAVR8.o ElectronicACUnitAVR8.c  -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -std=gnu99 -g2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega324pa ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-u,vprintf -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\Unit.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,--end-group  -Wl,--start-group -Wl,--end-group
	
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.srec"
	${MP_CC_DIR}\\avr-objcopy -j .user_signatures --set-section-flags=.user_signatures=alloc,load --change-section-lma .user_signatures=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.usersignatures" || exit 0
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega324pa ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-u,vprintf -Wl,-Map="dist\${CND_CONF}\${IMAGE_TYPE}\Unit.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_Debug=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,--end-group  -Wl,--start-group -Wl,--end-group
	${MP_CC_DIR}\\avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.hex"
	${MP_CC_DIR}\\avr-objcopy -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.eep" || exit 0
	${MP_CC_DIR}\\avr-objdump -h -S "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" > "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.lss"
	${MP_CC_DIR}\\avr-objcopy -O srec -R .eeprom -R .fuse -R .lock -R .signature "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.srec"
	${MP_CC_DIR}\\avr-objcopy -j .user_signatures --set-section-flags=.user_signatures=alloc,load --change-section-lma .user_signatures=0 --no-change-warnings -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/Unit.${IMAGE_TYPE}.usersignatures" || exit 0
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} -r dist/Debug

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
