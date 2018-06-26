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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/gen-cpp/UserStorage.o \
	${OBJECTDIR}/gen-cpp/UserStorage_server.o \
	${OBJECTDIR}/gen-cpp/user_profile_constants.o \
	${OBJECTDIR}/gen-cpp/user_profile_types.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lthrift -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/gen-cpp/UserStorage.o: gen-cpp/UserStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/thrift -I/usr/local/include/boost -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gen-cpp/UserStorage.o gen-cpp/UserStorage.cpp

${OBJECTDIR}/gen-cpp/UserStorage_server.o: gen-cpp/UserStorage_server.cpp 
	${MKDIR} -p ${OBJECTDIR}/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/thrift -I/usr/local/include/boost -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gen-cpp/UserStorage_server.o gen-cpp/UserStorage_server.cpp

${OBJECTDIR}/gen-cpp/user_profile_constants.o: gen-cpp/user_profile_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/thrift -I/usr/local/include/boost -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gen-cpp/user_profile_constants.o gen-cpp/user_profile_constants.cpp

${OBJECTDIR}/gen-cpp/user_profile_types.o: gen-cpp/user_profile_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/gen-cpp
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/include/thrift -I/usr/local/include/boost -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gen-cpp/user_profile_types.o gen-cpp/user_profile_types.cpp

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
