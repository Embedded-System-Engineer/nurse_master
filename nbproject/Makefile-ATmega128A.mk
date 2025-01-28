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
ifeq "$(wildcard nbproject/Makefile-local-ATmega128A.mk)" "nbproject/Makefile-local-ATmega128A.mk"
include nbproject/Makefile-local-ATmega128A.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=ATmega128A
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/app.c src/SystemTime.c src/EventsHandles.c src/message.c src/WorkingTime.c src/Main.c src/Requests.c src/selectIP.c src/SystemGenralOption.c src/switchCallbacks.c src/TypeNumberSystem.c src/loadConfig.c src/configuration.c src/ResetSystem.c src/loadIp.c src/network.c src/displayCallbacks.c src/password.c src/Memory.c src/userSytstem.c src/display_queue.c src/dataTiming.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/SystemTime.o ${OBJECTDIR}/src/EventsHandles.o ${OBJECTDIR}/src/message.o ${OBJECTDIR}/src/WorkingTime.o ${OBJECTDIR}/src/Main.o ${OBJECTDIR}/src/Requests.o ${OBJECTDIR}/src/selectIP.o ${OBJECTDIR}/src/SystemGenralOption.o ${OBJECTDIR}/src/switchCallbacks.o ${OBJECTDIR}/src/TypeNumberSystem.o ${OBJECTDIR}/src/loadConfig.o ${OBJECTDIR}/src/configuration.o ${OBJECTDIR}/src/ResetSystem.o ${OBJECTDIR}/src/loadIp.o ${OBJECTDIR}/src/network.o ${OBJECTDIR}/src/displayCallbacks.o ${OBJECTDIR}/src/password.o ${OBJECTDIR}/src/Memory.o ${OBJECTDIR}/src/userSytstem.o ${OBJECTDIR}/src/display_queue.o ${OBJECTDIR}/src/dataTiming.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/app.o.d ${OBJECTDIR}/src/SystemTime.o.d ${OBJECTDIR}/src/EventsHandles.o.d ${OBJECTDIR}/src/message.o.d ${OBJECTDIR}/src/WorkingTime.o.d ${OBJECTDIR}/src/Main.o.d ${OBJECTDIR}/src/Requests.o.d ${OBJECTDIR}/src/selectIP.o.d ${OBJECTDIR}/src/SystemGenralOption.o.d ${OBJECTDIR}/src/switchCallbacks.o.d ${OBJECTDIR}/src/TypeNumberSystem.o.d ${OBJECTDIR}/src/loadConfig.o.d ${OBJECTDIR}/src/configuration.o.d ${OBJECTDIR}/src/ResetSystem.o.d ${OBJECTDIR}/src/loadIp.o.d ${OBJECTDIR}/src/network.o.d ${OBJECTDIR}/src/displayCallbacks.o.d ${OBJECTDIR}/src/password.o.d ${OBJECTDIR}/src/Memory.o.d ${OBJECTDIR}/src/userSytstem.o.d ${OBJECTDIR}/src/display_queue.o.d ${OBJECTDIR}/src/dataTiming.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/app.o ${OBJECTDIR}/src/SystemTime.o ${OBJECTDIR}/src/EventsHandles.o ${OBJECTDIR}/src/message.o ${OBJECTDIR}/src/WorkingTime.o ${OBJECTDIR}/src/Main.o ${OBJECTDIR}/src/Requests.o ${OBJECTDIR}/src/selectIP.o ${OBJECTDIR}/src/SystemGenralOption.o ${OBJECTDIR}/src/switchCallbacks.o ${OBJECTDIR}/src/TypeNumberSystem.o ${OBJECTDIR}/src/loadConfig.o ${OBJECTDIR}/src/configuration.o ${OBJECTDIR}/src/ResetSystem.o ${OBJECTDIR}/src/loadIp.o ${OBJECTDIR}/src/network.o ${OBJECTDIR}/src/displayCallbacks.o ${OBJECTDIR}/src/password.o ${OBJECTDIR}/src/Memory.o ${OBJECTDIR}/src/userSytstem.o ${OBJECTDIR}/src/display_queue.o ${OBJECTDIR}/src/dataTiming.o

# Source Files
SOURCEFILES=src/app.c src/SystemTime.c src/EventsHandles.c src/message.c src/WorkingTime.c src/Main.c src/Requests.c src/selectIP.c src/SystemGenralOption.c src/switchCallbacks.c src/TypeNumberSystem.c src/loadConfig.c src/configuration.c src/ResetSystem.c src/loadIp.c src/network.c src/displayCallbacks.c src/password.c src/Memory.c src/userSytstem.c src/display_queue.c src/dataTiming.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/atmega128a"



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
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-ATmega128A.mk ${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega128A
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega128A/c7c7d5a0a6397c02b9aef405805b83c2d0b6c859 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemTime.o: src/SystemTime.c  .generated_files/flags/ATmega128A/9d579c38631ad2341eda19edec122c7cfff4b211 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemTime.o.d 
	@${RM} ${OBJECTDIR}/src/SystemTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/SystemTime.o.d" -MT "${OBJECTDIR}/src/SystemTime.o.d" -MT ${OBJECTDIR}/src/SystemTime.o  -o ${OBJECTDIR}/src/SystemTime.o src/SystemTime.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/EventsHandles.o: src/EventsHandles.c  .generated_files/flags/ATmega128A/1f7fbdc67c2afd88b2b6cc6c216b81d91ce1fd99 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o.d 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/EventsHandles.o.d" -MT "${OBJECTDIR}/src/EventsHandles.o.d" -MT ${OBJECTDIR}/src/EventsHandles.o  -o ${OBJECTDIR}/src/EventsHandles.o src/EventsHandles.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/message.o: src/message.c  .generated_files/flags/ATmega128A/424e525b044c5a117afd9768bb2a77f117db15c6 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/message.o.d 
	@${RM} ${OBJECTDIR}/src/message.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/message.o.d" -MT "${OBJECTDIR}/src/message.o.d" -MT ${OBJECTDIR}/src/message.o  -o ${OBJECTDIR}/src/message.o src/message.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/WorkingTime.o: src/WorkingTime.c  .generated_files/flags/ATmega128A/50232f0b445c449645e4820b781d910e9e6b3327 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o.d 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/WorkingTime.o.d" -MT "${OBJECTDIR}/src/WorkingTime.o.d" -MT ${OBJECTDIR}/src/WorkingTime.o  -o ${OBJECTDIR}/src/WorkingTime.o src/WorkingTime.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Main.o: src/Main.c  .generated_files/flags/ATmega128A/3f5c89a666561994a54a3b9531fc9839d99d5f9 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Main.o.d 
	@${RM} ${OBJECTDIR}/src/Main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Main.o.d" -MT "${OBJECTDIR}/src/Main.o.d" -MT ${OBJECTDIR}/src/Main.o  -o ${OBJECTDIR}/src/Main.o src/Main.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Requests.o: src/Requests.c  .generated_files/flags/ATmega128A/6539bf4bee03c808024439041f2f1373dec790b .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Requests.o.d 
	@${RM} ${OBJECTDIR}/src/Requests.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Requests.o.d" -MT "${OBJECTDIR}/src/Requests.o.d" -MT ${OBJECTDIR}/src/Requests.o  -o ${OBJECTDIR}/src/Requests.o src/Requests.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/selectIP.o: src/selectIP.c  .generated_files/flags/ATmega128A/322aa05e07903b5b1e82879a056ed2a6d7f7b285 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/selectIP.o.d 
	@${RM} ${OBJECTDIR}/src/selectIP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/selectIP.o.d" -MT "${OBJECTDIR}/src/selectIP.o.d" -MT ${OBJECTDIR}/src/selectIP.o  -o ${OBJECTDIR}/src/selectIP.o src/selectIP.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemGenralOption.o: src/SystemGenralOption.c  .generated_files/flags/ATmega128A/50b1572baeee1746688657b75f10c60a23c2d8c7 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemGenralOption.o.d 
	@${RM} ${OBJECTDIR}/src/SystemGenralOption.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/SystemGenralOption.o.d" -MT "${OBJECTDIR}/src/SystemGenralOption.o.d" -MT ${OBJECTDIR}/src/SystemGenralOption.o  -o ${OBJECTDIR}/src/SystemGenralOption.o src/SystemGenralOption.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/switchCallbacks.o: src/switchCallbacks.c  .generated_files/flags/ATmega128A/5a8d201107f66f7ea255c47f6417bf05ba315d3e .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/switchCallbacks.o.d 
	@${RM} ${OBJECTDIR}/src/switchCallbacks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/switchCallbacks.o.d" -MT "${OBJECTDIR}/src/switchCallbacks.o.d" -MT ${OBJECTDIR}/src/switchCallbacks.o  -o ${OBJECTDIR}/src/switchCallbacks.o src/switchCallbacks.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/TypeNumberSystem.o: src/TypeNumberSystem.c  .generated_files/flags/ATmega128A/dd9f23b0cdec618ee9c4811f7a1f32445187bec5 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TypeNumberSystem.o.d 
	@${RM} ${OBJECTDIR}/src/TypeNumberSystem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/TypeNumberSystem.o.d" -MT "${OBJECTDIR}/src/TypeNumberSystem.o.d" -MT ${OBJECTDIR}/src/TypeNumberSystem.o  -o ${OBJECTDIR}/src/TypeNumberSystem.o src/TypeNumberSystem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/loadConfig.o: src/loadConfig.c  .generated_files/flags/ATmega128A/ceec35cd1bffb258cd55e566af4ab3fe18cded91 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/loadConfig.o.d 
	@${RM} ${OBJECTDIR}/src/loadConfig.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/loadConfig.o.d" -MT "${OBJECTDIR}/src/loadConfig.o.d" -MT ${OBJECTDIR}/src/loadConfig.o  -o ${OBJECTDIR}/src/loadConfig.o src/loadConfig.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/configuration.o: src/configuration.c  .generated_files/flags/ATmega128A/51be8c816655815f83368930b36e7acd8324d2a .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration.o.d 
	@${RM} ${OBJECTDIR}/src/configuration.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/configuration.o.d" -MT "${OBJECTDIR}/src/configuration.o.d" -MT ${OBJECTDIR}/src/configuration.o  -o ${OBJECTDIR}/src/configuration.o src/configuration.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/ResetSystem.o: src/ResetSystem.c  .generated_files/flags/ATmega128A/37fca710d91872c99137e8c01638abf5341c0b1b .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ResetSystem.o.d 
	@${RM} ${OBJECTDIR}/src/ResetSystem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/ResetSystem.o.d" -MT "${OBJECTDIR}/src/ResetSystem.o.d" -MT ${OBJECTDIR}/src/ResetSystem.o  -o ${OBJECTDIR}/src/ResetSystem.o src/ResetSystem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/loadIp.o: src/loadIp.c  .generated_files/flags/ATmega128A/a9aa0fa7dfbfc27b0b62b4c716261393f9fe76da .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/loadIp.o.d 
	@${RM} ${OBJECTDIR}/src/loadIp.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/loadIp.o.d" -MT "${OBJECTDIR}/src/loadIp.o.d" -MT ${OBJECTDIR}/src/loadIp.o  -o ${OBJECTDIR}/src/loadIp.o src/loadIp.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/network.o: src/network.c  .generated_files/flags/ATmega128A/b7c69efe54c7a84a6805f6787d1a20665543d880 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/network.o.d 
	@${RM} ${OBJECTDIR}/src/network.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/network.o.d" -MT "${OBJECTDIR}/src/network.o.d" -MT ${OBJECTDIR}/src/network.o  -o ${OBJECTDIR}/src/network.o src/network.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/displayCallbacks.o: src/displayCallbacks.c  .generated_files/flags/ATmega128A/cc96bea71c686f52f75757af95c343119ce3e9f7 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/displayCallbacks.o.d 
	@${RM} ${OBJECTDIR}/src/displayCallbacks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/displayCallbacks.o.d" -MT "${OBJECTDIR}/src/displayCallbacks.o.d" -MT ${OBJECTDIR}/src/displayCallbacks.o  -o ${OBJECTDIR}/src/displayCallbacks.o src/displayCallbacks.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/password.o: src/password.c  .generated_files/flags/ATmega128A/32cb724155e41c4b2820314dfc4b12fe62d6ea87 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/password.o.d 
	@${RM} ${OBJECTDIR}/src/password.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/password.o.d" -MT "${OBJECTDIR}/src/password.o.d" -MT ${OBJECTDIR}/src/password.o  -o ${OBJECTDIR}/src/password.o src/password.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Memory.o: src/Memory.c  .generated_files/flags/ATmega128A/970219a2a31b79f9e611871d3320d5fc217fb44b .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Memory.o.d 
	@${RM} ${OBJECTDIR}/src/Memory.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Memory.o.d" -MT "${OBJECTDIR}/src/Memory.o.d" -MT ${OBJECTDIR}/src/Memory.o  -o ${OBJECTDIR}/src/Memory.o src/Memory.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/userSytstem.o: src/userSytstem.c  .generated_files/flags/ATmega128A/f5363bc3a342736dfba6650d77ac3f5fe9fe894 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/userSytstem.o.d 
	@${RM} ${OBJECTDIR}/src/userSytstem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/userSytstem.o.d" -MT "${OBJECTDIR}/src/userSytstem.o.d" -MT ${OBJECTDIR}/src/userSytstem.o  -o ${OBJECTDIR}/src/userSytstem.o src/userSytstem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/display_queue.o: src/display_queue.c  .generated_files/flags/ATmega128A/93f1a89d549d5ee043e939fbfe0c09720b653025 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/display_queue.o.d 
	@${RM} ${OBJECTDIR}/src/display_queue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/display_queue.o.d" -MT "${OBJECTDIR}/src/display_queue.o.d" -MT ${OBJECTDIR}/src/display_queue.o  -o ${OBJECTDIR}/src/display_queue.o src/display_queue.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/dataTiming.o: src/dataTiming.c  .generated_files/flags/ATmega128A/ba51199b7cf3017b7f865791ef909d9b49bc98ae .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/dataTiming.o.d 
	@${RM} ${OBJECTDIR}/src/dataTiming.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/dataTiming.o.d" -MT "${OBJECTDIR}/src/dataTiming.o.d" -MT ${OBJECTDIR}/src/dataTiming.o  -o ${OBJECTDIR}/src/dataTiming.o src/dataTiming.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/app.o: src/app.c  .generated_files/flags/ATmega128A/99323f99137748b62afed0bd0dc9c00ebacbfb48 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app.o.d 
	@${RM} ${OBJECTDIR}/src/app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/app.o.d" -MT "${OBJECTDIR}/src/app.o.d" -MT ${OBJECTDIR}/src/app.o  -o ${OBJECTDIR}/src/app.o src/app.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemTime.o: src/SystemTime.c  .generated_files/flags/ATmega128A/281c5cedf7edbf125e4f6969e1824c55232abe09 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemTime.o.d 
	@${RM} ${OBJECTDIR}/src/SystemTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/SystemTime.o.d" -MT "${OBJECTDIR}/src/SystemTime.o.d" -MT ${OBJECTDIR}/src/SystemTime.o  -o ${OBJECTDIR}/src/SystemTime.o src/SystemTime.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/EventsHandles.o: src/EventsHandles.c  .generated_files/flags/ATmega128A/fc390eb99504ce3fcf409881e6418c513c6e3f27 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o.d 
	@${RM} ${OBJECTDIR}/src/EventsHandles.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/EventsHandles.o.d" -MT "${OBJECTDIR}/src/EventsHandles.o.d" -MT ${OBJECTDIR}/src/EventsHandles.o  -o ${OBJECTDIR}/src/EventsHandles.o src/EventsHandles.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/message.o: src/message.c  .generated_files/flags/ATmega128A/6057f969e4ffadcd30592d4a27537c86303ee343 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/message.o.d 
	@${RM} ${OBJECTDIR}/src/message.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/message.o.d" -MT "${OBJECTDIR}/src/message.o.d" -MT ${OBJECTDIR}/src/message.o  -o ${OBJECTDIR}/src/message.o src/message.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/WorkingTime.o: src/WorkingTime.c  .generated_files/flags/ATmega128A/5f10575e39178819541abef7547323e637ca417 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o.d 
	@${RM} ${OBJECTDIR}/src/WorkingTime.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/WorkingTime.o.d" -MT "${OBJECTDIR}/src/WorkingTime.o.d" -MT ${OBJECTDIR}/src/WorkingTime.o  -o ${OBJECTDIR}/src/WorkingTime.o src/WorkingTime.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Main.o: src/Main.c  .generated_files/flags/ATmega128A/97d884efdbc49cb28a76c5c88ae767be762ad3dc .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Main.o.d 
	@${RM} ${OBJECTDIR}/src/Main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Main.o.d" -MT "${OBJECTDIR}/src/Main.o.d" -MT ${OBJECTDIR}/src/Main.o  -o ${OBJECTDIR}/src/Main.o src/Main.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Requests.o: src/Requests.c  .generated_files/flags/ATmega128A/875dcf5b0dc9b51ed993d2243c8cd05f8e72ce8c .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Requests.o.d 
	@${RM} ${OBJECTDIR}/src/Requests.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Requests.o.d" -MT "${OBJECTDIR}/src/Requests.o.d" -MT ${OBJECTDIR}/src/Requests.o  -o ${OBJECTDIR}/src/Requests.o src/Requests.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/selectIP.o: src/selectIP.c  .generated_files/flags/ATmega128A/84b28e2ca957b3348f18c8e17616a52442f79231 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/selectIP.o.d 
	@${RM} ${OBJECTDIR}/src/selectIP.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/selectIP.o.d" -MT "${OBJECTDIR}/src/selectIP.o.d" -MT ${OBJECTDIR}/src/selectIP.o  -o ${OBJECTDIR}/src/selectIP.o src/selectIP.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/SystemGenralOption.o: src/SystemGenralOption.c  .generated_files/flags/ATmega128A/f82c5cfed96d219e417536fdf2043b08ca301204 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/SystemGenralOption.o.d 
	@${RM} ${OBJECTDIR}/src/SystemGenralOption.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/SystemGenralOption.o.d" -MT "${OBJECTDIR}/src/SystemGenralOption.o.d" -MT ${OBJECTDIR}/src/SystemGenralOption.o  -o ${OBJECTDIR}/src/SystemGenralOption.o src/SystemGenralOption.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/switchCallbacks.o: src/switchCallbacks.c  .generated_files/flags/ATmega128A/5e4f8ff351764379fedc4d4550a739a59e19990b .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/switchCallbacks.o.d 
	@${RM} ${OBJECTDIR}/src/switchCallbacks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/switchCallbacks.o.d" -MT "${OBJECTDIR}/src/switchCallbacks.o.d" -MT ${OBJECTDIR}/src/switchCallbacks.o  -o ${OBJECTDIR}/src/switchCallbacks.o src/switchCallbacks.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/TypeNumberSystem.o: src/TypeNumberSystem.c  .generated_files/flags/ATmega128A/10e5d575b70752cd6b10fb5372550be2d508c19c .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TypeNumberSystem.o.d 
	@${RM} ${OBJECTDIR}/src/TypeNumberSystem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/TypeNumberSystem.o.d" -MT "${OBJECTDIR}/src/TypeNumberSystem.o.d" -MT ${OBJECTDIR}/src/TypeNumberSystem.o  -o ${OBJECTDIR}/src/TypeNumberSystem.o src/TypeNumberSystem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/loadConfig.o: src/loadConfig.c  .generated_files/flags/ATmega128A/2a0307e5c8cca9e3eeef66262e5d34193e1a36f7 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/loadConfig.o.d 
	@${RM} ${OBJECTDIR}/src/loadConfig.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/loadConfig.o.d" -MT "${OBJECTDIR}/src/loadConfig.o.d" -MT ${OBJECTDIR}/src/loadConfig.o  -o ${OBJECTDIR}/src/loadConfig.o src/loadConfig.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/configuration.o: src/configuration.c  .generated_files/flags/ATmega128A/88f48c4f86e72c5e58834301c50f45ba33147fbe .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration.o.d 
	@${RM} ${OBJECTDIR}/src/configuration.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/configuration.o.d" -MT "${OBJECTDIR}/src/configuration.o.d" -MT ${OBJECTDIR}/src/configuration.o  -o ${OBJECTDIR}/src/configuration.o src/configuration.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/ResetSystem.o: src/ResetSystem.c  .generated_files/flags/ATmega128A/92dbfa104cdf572644fcc3db7c99f6ece2170b64 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ResetSystem.o.d 
	@${RM} ${OBJECTDIR}/src/ResetSystem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/ResetSystem.o.d" -MT "${OBJECTDIR}/src/ResetSystem.o.d" -MT ${OBJECTDIR}/src/ResetSystem.o  -o ${OBJECTDIR}/src/ResetSystem.o src/ResetSystem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/loadIp.o: src/loadIp.c  .generated_files/flags/ATmega128A/15794de22daa476f84acf4a655ffd3002d6d12ef .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/loadIp.o.d 
	@${RM} ${OBJECTDIR}/src/loadIp.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/loadIp.o.d" -MT "${OBJECTDIR}/src/loadIp.o.d" -MT ${OBJECTDIR}/src/loadIp.o  -o ${OBJECTDIR}/src/loadIp.o src/loadIp.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/network.o: src/network.c  .generated_files/flags/ATmega128A/41acc47211bfb5ad34ca6701448dd008d02bebec .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/network.o.d 
	@${RM} ${OBJECTDIR}/src/network.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/network.o.d" -MT "${OBJECTDIR}/src/network.o.d" -MT ${OBJECTDIR}/src/network.o  -o ${OBJECTDIR}/src/network.o src/network.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/displayCallbacks.o: src/displayCallbacks.c  .generated_files/flags/ATmega128A/95fc47eb08015f77ad590ddf89e9fb51a8090e69 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/displayCallbacks.o.d 
	@${RM} ${OBJECTDIR}/src/displayCallbacks.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/displayCallbacks.o.d" -MT "${OBJECTDIR}/src/displayCallbacks.o.d" -MT ${OBJECTDIR}/src/displayCallbacks.o  -o ${OBJECTDIR}/src/displayCallbacks.o src/displayCallbacks.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/password.o: src/password.c  .generated_files/flags/ATmega128A/14c57d12485688aa71abb7273a7fa158590717d6 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/password.o.d 
	@${RM} ${OBJECTDIR}/src/password.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/password.o.d" -MT "${OBJECTDIR}/src/password.o.d" -MT ${OBJECTDIR}/src/password.o  -o ${OBJECTDIR}/src/password.o src/password.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Memory.o: src/Memory.c  .generated_files/flags/ATmega128A/11bb8575f47460f405d90349341a0865e365d85f .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Memory.o.d 
	@${RM} ${OBJECTDIR}/src/Memory.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/Memory.o.d" -MT "${OBJECTDIR}/src/Memory.o.d" -MT ${OBJECTDIR}/src/Memory.o  -o ${OBJECTDIR}/src/Memory.o src/Memory.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/userSytstem.o: src/userSytstem.c  .generated_files/flags/ATmega128A/addf0ef1d59add30c446ff6c4cd4c50adf79fd4f .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/userSytstem.o.d 
	@${RM} ${OBJECTDIR}/src/userSytstem.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/userSytstem.o.d" -MT "${OBJECTDIR}/src/userSytstem.o.d" -MT ${OBJECTDIR}/src/userSytstem.o  -o ${OBJECTDIR}/src/userSytstem.o src/userSytstem.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/display_queue.o: src/display_queue.c  .generated_files/flags/ATmega128A/d77ee9796bc8b242f473e5e7eb01bf30b7df0ef8 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/display_queue.o.d 
	@${RM} ${OBJECTDIR}/src/display_queue.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/display_queue.o.d" -MT "${OBJECTDIR}/src/display_queue.o.d" -MT ${OBJECTDIR}/src/display_queue.o  -o ${OBJECTDIR}/src/display_queue.o src/display_queue.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/dataTiming.o: src/dataTiming.c  .generated_files/flags/ATmega128A/9d0220a7cc6805f725d8786457f98f38479a518 .generated_files/flags/ATmega128A/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/dataTiming.o.d 
	@${RM} ${OBJECTDIR}/src/dataTiming.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega128a ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums  -I "inc" -I "lib/inc" -Wall -Wextra -MD -MP -MF "${OBJECTDIR}/src/dataTiming.o.d" -MT "${OBJECTDIR}/src/dataTiming.o.d" -MT ${OBJECTDIR}/src/dataTiming.o  -o ${OBJECTDIR}/src/dataTiming.o src/dataTiming.c  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib/mega2.X.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a ${PACK_COMMON_OPTIONS}  -D__MPLAB_DEBUGGER_SIMULATOR=1 -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\NurseMaster.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib\mega2.X.a  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  lib/mega2.X.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega128a ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\NurseMaster.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    lib\mega2.X.a  -DXPRJ_ATmega128A=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/NurseMaster.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
