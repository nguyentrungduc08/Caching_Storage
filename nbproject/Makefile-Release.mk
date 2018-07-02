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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/server/KC_Storage/KC_Storage.o \
	${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o \
	${OBJECTDIR}/server/KC_Storage/kc_storage_types.o \
	${OBJECTDIR}/server/UserStorage.o \
	${OBJECTDIR}/server/server.o \
	${OBJECTDIR}/server/user_profile_constants.o \
	${OBJECTDIR}/server/user_profile_types.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/server/KC_Storage/KC_Storage.o: server/KC_Storage/KC_Storage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/KC_Storage.o server/KC_Storage/KC_Storage.cpp

${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o: server/KC_Storage/kc_storage_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o server/KC_Storage/kc_storage_constants.cpp

${OBJECTDIR}/server/KC_Storage/kc_storage_types.o: server/KC_Storage/kc_storage_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_types.o server/KC_Storage/kc_storage_types.cpp

${OBJECTDIR}/server/UserStorage.o: server/UserStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/UserStorage.o server/UserStorage.cpp

${OBJECTDIR}/server/server.o: server/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/server.o server/server.cpp

${OBJECTDIR}/server/user_profile_constants.o: server/user_profile_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/user_profile_constants.o server/user_profile_constants.cpp

${OBJECTDIR}/server/user_profile_types.o: server/user_profile_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/user_profile_types.o server/user_profile_types.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
