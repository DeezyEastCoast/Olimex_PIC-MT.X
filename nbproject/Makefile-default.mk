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
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2058854102/buttons.o ${OBJECTDIR}/_ext/2058854102/analog_2520.o ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o ${OBJECTDIR}/_ext/2058854102/lcd.o ${OBJECTDIR}/_ext/2058854102/main.o ${OBJECTDIR}/_ext/2058854102/timers.o ${OBJECTDIR}/_ext/2058854102/uart_2520.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2058854102/buttons.o.d ${OBJECTDIR}/_ext/2058854102/analog_2520.o.d ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o.d ${OBJECTDIR}/_ext/2058854102/lcd.o.d ${OBJECTDIR}/_ext/2058854102/main.o.d ${OBJECTDIR}/_ext/2058854102/timers.o.d ${OBJECTDIR}/_ext/2058854102/uart_2520.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2058854102/buttons.o ${OBJECTDIR}/_ext/2058854102/analog_2520.o ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o ${OBJECTDIR}/_ext/2058854102/lcd.o ${OBJECTDIR}/_ext/2058854102/main.o ${OBJECTDIR}/_ext/2058854102/timers.o ${OBJECTDIR}/_ext/2058854102/uart_2520.o

# Source Files
SOURCEFILES=C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c


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

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2520
MP_PROCESSOR_OPTION_LD=18f2520
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x5f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2058854102/buttons.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/buttons.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/buttons.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/buttons.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/buttons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/analog_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/analog_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/analog_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/analog_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/analog_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/analog_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/interrupts_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/interrupts_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/lcd.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/lcd.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/main.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/main.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/timers.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/timers.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/uart_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/uart_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/uart_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/uart_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/uart_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/uart_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/2058854102/buttons.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/buttons.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/buttons.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/buttons.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/buttons.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/buttons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/analog_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/analog_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/analog_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/analog_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/analog_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/analog_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/analog_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/interrupts_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/interrupts_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/interrupts_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/interrupts_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/lcd.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/lcd.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/lcd.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/main.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/main.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/timers.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/timers.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/timers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2058854102/uart_2520.o: C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2058854102 
	@${RM} ${OBJECTDIR}/_ext/2058854102/uart_2520.o.d 
	@${RM} ${OBJECTDIR}/_ext/2058854102/uart_2520.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"../../../../../Program Files (x86)/Microchip/mplabc18/v3.45/h" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/2058854102/uart_2520.o   C:/Users/Deezy/Documents/PIC_Programs/Olimex_PIC-MT.X/uart_2520.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2058854102/uart_2520.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2058854102/uart_2520.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/Olimex_PIC-MT.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
