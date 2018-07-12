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
	${OBJECTDIR}/server/KC_GenID/KC_GenID.o \
	${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o \
	${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o \
	${OBJECTDIR}/server/KC_GenID/kc_genid_types.o \
	${OBJECTDIR}/server/KC_Storage/KC_Storage.o \
	${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o \
	${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o \
	${OBJECTDIR}/server/KC_Storage/kc_storage_types.o \
	${OBJECTDIR}/server/LRUCache/LRUCache.o \
	${OBJECTDIR}/server/UserStorage.o \
	${OBJECTDIR}/server/UserStorageHandler.o \
	${OBJECTDIR}/server/server.o \
	${OBJECTDIR}/server/user_profile_constants.o \
	${OBJECTDIR}/server/user_profile_types.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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

${OBJECTDIR}/server/KC_GenID/KC_GenID.o: server/KC_GenID/KC_GenID.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/KC_GenID.o server/KC_GenID/KC_GenID.cpp

${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o: server/KC_GenID/WZ_GenIdService.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o server/KC_GenID/WZ_GenIdService.cpp

${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o: server/KC_GenID/kc_genid_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o server/KC_GenID/kc_genid_constants.cpp

${OBJECTDIR}/server/KC_GenID/kc_genid_types.o: server/KC_GenID/kc_genid_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/kc_genid_types.o server/KC_GenID/kc_genid_types.cpp

${OBJECTDIR}/server/KC_Storage/KC_Storage.o: server/KC_Storage/KC_Storage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/KC_Storage.o server/KC_Storage/KC_Storage.cpp

${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o: server/KC_Storage/WZ_StorageService.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o server/KC_Storage/WZ_StorageService.cpp

${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o: server/KC_Storage/kc_storage_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o server/KC_Storage/kc_storage_constants.cpp

${OBJECTDIR}/server/KC_Storage/kc_storage_types.o: server/KC_Storage/kc_storage_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_types.o server/KC_Storage/kc_storage_types.cpp

${OBJECTDIR}/server/LRUCache/LRUCache.o: server/LRUCache/LRUCache.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/LRUCache
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/LRUCache/LRUCache.o server/LRUCache/LRUCache.cpp

${OBJECTDIR}/server/UserStorage.o: server/UserStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/UserStorage.o server/UserStorage.cpp

${OBJECTDIR}/server/UserStorageHandler.o: server/UserStorageHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/UserStorageHandler.o server/UserStorageHandler.cpp

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

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${OBJECTDIR}/server/KC_GenID/KC_GenID_nomain.o: ${OBJECTDIR}/server/KC_GenID/KC_GenID.o server/KC_GenID/KC_GenID.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_GenID/KC_GenID.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/KC_GenID_nomain.o server/KC_GenID/KC_GenID.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_GenID/KC_GenID.o ${OBJECTDIR}/server/KC_GenID/KC_GenID_nomain.o;\
	fi

${OBJECTDIR}/server/KC_GenID/WZ_GenIdService_nomain.o: ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o server/KC_GenID/WZ_GenIdService.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService_nomain.o server/KC_GenID/WZ_GenIdService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService.o ${OBJECTDIR}/server/KC_GenID/WZ_GenIdService_nomain.o;\
	fi

${OBJECTDIR}/server/KC_GenID/kc_genid_constants_nomain.o: ${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o server/KC_GenID/kc_genid_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/kc_genid_constants_nomain.o server/KC_GenID/kc_genid_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_GenID/kc_genid_constants.o ${OBJECTDIR}/server/KC_GenID/kc_genid_constants_nomain.o;\
	fi

${OBJECTDIR}/server/KC_GenID/kc_genid_types_nomain.o: ${OBJECTDIR}/server/KC_GenID/kc_genid_types.o server/KC_GenID/kc_genid_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_GenID
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_GenID/kc_genid_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_GenID/kc_genid_types_nomain.o server/KC_GenID/kc_genid_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_GenID/kc_genid_types.o ${OBJECTDIR}/server/KC_GenID/kc_genid_types_nomain.o;\
	fi

${OBJECTDIR}/server/KC_Storage/KC_Storage_nomain.o: ${OBJECTDIR}/server/KC_Storage/KC_Storage.o server/KC_Storage/KC_Storage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_Storage/KC_Storage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/KC_Storage_nomain.o server/KC_Storage/KC_Storage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_Storage/KC_Storage.o ${OBJECTDIR}/server/KC_Storage/KC_Storage_nomain.o;\
	fi

${OBJECTDIR}/server/KC_Storage/WZ_StorageService_nomain.o: ${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o server/KC_Storage/WZ_StorageService.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/WZ_StorageService_nomain.o server/KC_Storage/WZ_StorageService.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_Storage/WZ_StorageService.o ${OBJECTDIR}/server/KC_Storage/WZ_StorageService_nomain.o;\
	fi

${OBJECTDIR}/server/KC_Storage/kc_storage_constants_nomain.o: ${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o server/KC_Storage/kc_storage_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_constants_nomain.o server/KC_Storage/kc_storage_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_Storage/kc_storage_constants.o ${OBJECTDIR}/server/KC_Storage/kc_storage_constants_nomain.o;\
	fi

${OBJECTDIR}/server/KC_Storage/kc_storage_types_nomain.o: ${OBJECTDIR}/server/KC_Storage/kc_storage_types.o server/KC_Storage/kc_storage_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/KC_Storage
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/KC_Storage/kc_storage_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/KC_Storage/kc_storage_types_nomain.o server/KC_Storage/kc_storage_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/KC_Storage/kc_storage_types.o ${OBJECTDIR}/server/KC_Storage/kc_storage_types_nomain.o;\
	fi

${OBJECTDIR}/server/LRUCache/LRUCache_nomain.o: ${OBJECTDIR}/server/LRUCache/LRUCache.o server/LRUCache/LRUCache.cpp 
	${MKDIR} -p ${OBJECTDIR}/server/LRUCache
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/LRUCache/LRUCache.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/LRUCache/LRUCache_nomain.o server/LRUCache/LRUCache.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/LRUCache/LRUCache.o ${OBJECTDIR}/server/LRUCache/LRUCache_nomain.o;\
	fi

${OBJECTDIR}/server/UserStorage_nomain.o: ${OBJECTDIR}/server/UserStorage.o server/UserStorage.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/UserStorage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/UserStorage_nomain.o server/UserStorage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/UserStorage.o ${OBJECTDIR}/server/UserStorage_nomain.o;\
	fi

${OBJECTDIR}/server/UserStorageHandler_nomain.o: ${OBJECTDIR}/server/UserStorageHandler.o server/UserStorageHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/UserStorageHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/UserStorageHandler_nomain.o server/UserStorageHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/UserStorageHandler.o ${OBJECTDIR}/server/UserStorageHandler_nomain.o;\
	fi

${OBJECTDIR}/server/server_nomain.o: ${OBJECTDIR}/server/server.o server/server.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/server.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/server_nomain.o server/server.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/server.o ${OBJECTDIR}/server/server_nomain.o;\
	fi

${OBJECTDIR}/server/user_profile_constants_nomain.o: ${OBJECTDIR}/server/user_profile_constants.o server/user_profile_constants.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/user_profile_constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/user_profile_constants_nomain.o server/user_profile_constants.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/user_profile_constants.o ${OBJECTDIR}/server/user_profile_constants_nomain.o;\
	fi

${OBJECTDIR}/server/user_profile_types_nomain.o: ${OBJECTDIR}/server/user_profile_types.o server/user_profile_types.cpp 
	${MKDIR} -p ${OBJECTDIR}/server
	@NMOUTPUT=`${NM} ${OBJECTDIR}/server/user_profile_types.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/server/user_profile_types_nomain.o server/user_profile_types.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/server/user_profile_types.o ${OBJECTDIR}/server/user_profile_types_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/task1

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
