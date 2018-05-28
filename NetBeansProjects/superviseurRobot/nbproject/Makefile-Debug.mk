#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/4d6c2c92/main.o \
	${OBJECTDIR}/_ext/2b96aee7/functions.o \
	${OBJECTDIR}/_ext/b41571d8/image.o \
	${OBJECTDIR}/_ext/b41571d8/message.o \
	${OBJECTDIR}/_ext/b41571d8/monitor.o \
	${OBJECTDIR}/_ext/b41571d8/robot.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__MERCURY__ -I/usr/xenomai/include/alchemy -g -D_WITH_TRACE_ -I/usr/xenomai/include/ -I/usr/xenomai/include/mercury -MMD -MP
CXXFLAGS=-D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__MERCURY__ -I/usr/xenomai/include/alchemy -g -D_WITH_TRACE_ -I/usr/xenomai/include/ -I/usr/xenomai/include/mercury -MMD -MP

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/superviseurrobot

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/superviseurrobot: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/superviseurrobot ${OBJECTFILES} ${LDLIBSOPTIONS} -D_GNU_SOURCE -D_REENTRANT -fasynchronous-unwind-tables -D__MERCURY__ -I/usr/xenomai/include/alchemy -L/usr/xenomai/lib -lalchemy -lcopperplate -lmercury -L/opt/vc/lib -I/usr/local/include -lopencv_highgui -lopencv_core -lopencv_imgproc -Wl,--no-as-needed -lalchemy -lcopperplate /usr/xenomai/lib/xenomai/bootstrap.o -Wl,--wrap=main -Wl,--dynamic-list=/usr/xenomai/lib/dynlist.ld -L/usr/xenomai/lib -lmercury -lpthread -lrt -Wl,-rpath /usr/xenomai/lib -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lraspicam_cv -lopencv_imgproc -lpthread

${OBJECTDIR}/_ext/4d6c2c92/main.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/destijl_init/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4d6c2c92
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4d6c2c92/main.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/destijl_init/main.cpp

${OBJECTDIR}/_ext/2b96aee7/functions.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/destijl_init/src/functions.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2b96aee7
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2b96aee7/functions.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/destijl_init/src/functions.cpp

${OBJECTDIR}/_ext/b41571d8/image.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/image.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b41571d8
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b41571d8/image.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/image.cpp

${OBJECTDIR}/_ext/b41571d8/message.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/message.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b41571d8
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b41571d8/message.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/message.cpp

${OBJECTDIR}/_ext/b41571d8/monitor.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/monitor.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b41571d8
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b41571d8/monitor.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/monitor.cpp

${OBJECTDIR}/_ext/b41571d8/robot.o: ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/robot.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b41571d8
	${RM} "$@.d"
	$(COMPILE.cc) -g -include include_xenomai/include/alarm.h -include include_xenomai/include/buffer.h -include include_xenomai/include/compat.h -include include_xenomai/include/cond.h -include include_xenomai/include/event.h -include include_xenomai/include/heap.h -include include_xenomai/include/mutex.h -include include_xenomai/include/queue.h -include include_xenomai/include/sem.h -include include_xenomai/include/task.h -include include_xenomai/include/timer.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b41571d8/robot.o ../../Documents/4IR-RT/TempsReel/superviseur_robot-master/src/robot.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
