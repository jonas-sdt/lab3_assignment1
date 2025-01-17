#******************************************************************************
#
# Makefile - Rules for building the lab3_assignment1 example.
#
# Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.4.178 of the EK-TM4C129EXL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C129ENCPDT

#
# The base directory for TivaWare.
#
ROOT=../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=../../examples/boards/ek-tm4c129exl/drivers
VPATH+=../../grlib
VPATH+=../../utils
# VPATH+=../../driverlib
VPATH+=./include

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=../../examples/boards/ek-tm4c129exl/
IPATH+=../..
IPATH+=../../utils
# IPATH+=../../grlib
# IPATH+=../../driverlib
IPATH+=./include/

#
# The default rule, which causes the lab3_assignment1 example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/lab3_assignment1.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the lab3_assignment1 example.
#
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/lab3_assignment1.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/stopwatch.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/uart.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/uartstdio.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/buttons.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/pinout.o
${COMPILER}/lab3_assignment1.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/lab3_assignment1.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/lab3_assignment1.axf: lab3_assignment1.ld
SCATTERgcc_lab3_assignment1=lab3_assignment1.ld
ENTRY_lab3_assignment1=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C129_RA1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
