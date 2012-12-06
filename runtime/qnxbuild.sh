#!/bin/bash

# Copied from blackberry/v8.
# TODO(josh): We can probably move this setup into the Makefile
# and then just call V8's scons directly.

if [ ! -d "${QNX_HOST}" ]; then
  echo "QNX_HOST must be set to the path of the QNX host toolchain."
  exit 1
fi

if [ ! -d "${QNX_TARGET}" ]; then
  echo "QNX_TARGET must be set to the path of the QNX target toolchain."
  exit 1
fi

TARGET="${1}"
shift 1

if [ "${TARGET}" == "ia32" ]; then
	CPU="x86"
	CPUDIR="${CPU}"
	CPUTYPE="${CPU}"
	BUSUFFIX="${CPU}"
	CPU_CFLAGS=""
else
	TARGET="arm"
	CPU="arm"
	CPUDIR="${CPU}le-v7"
	CPUTYPE="${CPU}v7le"
	BUSUFFIX="${CPU}v7"
	CPU_CFLAGS="-mtune=cortex-a9 -mfpu=vfpv3"
fi

QNX_TOOL_DIR="${QNX_HOST}/usr/bin"
QNX_COMPILER="${QNX_TOOL_DIR}/qcc"
QNX_INC="${QNX_TARGET}/usr/include"
QNX_TOOL_PREFIX="${QNX_TOOL_DIR}/nto${BUSUFFIX}"
QNX_LIB="${QNX_TARGET}/${CPUDIR}/lib"
QNX_USR_LIB="${QNX_TARGET}/${CPUDIR}/usr/lib"

COMP_PATHS=" \
	-Wl,-rpath-link,${QNX_LIB} \
    -Wl,-rpath-link,${QNX_USR_LIB} \
	-L${QNX_LIB} \
	-L${QNX_USR_LIB} \
	-I${QNX_INC}"

# Set up the cross compile environment for the build

CXX="${QNX_COMPILER}"
CXXFLAGS="-Vgcc_nto${CPUTYPE}_cpp-ne -lang-c++ -fPIE ${COMP_PATHS} ${CPU_CFLAGS}"
AR="${QNX_TOOL_PREFIX}-ar"
RANLIB="${QNX_TOOL_PREFIX}-ranlib"

# Do the build

cd v8

CXX=${CXX} CCFLAGS=${CXXFLAGS} AR=${AR} RANLIB=${RANLIB} \
scons arch=${TARGET} os=qnx importenv=QNX_HOST,QNX_TARGET snapshot=off $@
