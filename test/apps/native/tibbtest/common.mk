ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

USEFILE=



# Extra include path for libfreetype and for target overrides and patches
EXTRA_INCVPATH+=$(QNX_TARGET)/usr/include/freetype2 \
	$(QNX_TARGET)/../target-override/usr/include \
	${QNX_TARGET}/usr/include/qt4 \
	${QNX_TARGET}/usr/include/qt4/QtCore \
	$(PROJECT_ROOT)/../../../../runtime/v8/include \
	$(PROJECT_ROOT)/../../../../src/ticore/include \
	$(PROJECT_ROOT)/../../../../src/tibb/include \
	/Users/penrique/build/1.0/header	
# Extra library search path for target overrides and patches
EXTRA_LIBVPATH+=$(QNX_TARGET)/$(CPUVARDIR)/usr/lib \
	$(QNX_TARGET)/$(CPUVARDIR)/usr/lib/qt4/lib \
	$(PROJECT_ROOT)/../../../../runtime/v8/$(CPU) \
	$(PROJECT_ROOT)/../../../../src/ticore/$(CPU)/a$(if $(filter arm,$(CPULIST)),.le-v7,)$(if $(filter g,$(VARIANTS)),-g,) \
	$(PROJECT_ROOT)/../../../../src/tibb/$(CPU)/a$(if $(filter arm,$(CPULIST)),.le-v7,)$(if $(filter g,$(VARIANTS)),-g,) \
	/Users/penrique/build/1.0/$(CPU)/a$(if $(filter arm,$(CPULIST)),.le-v7,)$(if $(filter g,$(VARIANTS)),-g,)

# Extra library search path for native module extentions
#EXTRA_LIBVPATH+=/Users/rmcmahon/ndk-10.1.0-workspace/ReplaceWithModuleName/$(CPU)/a$(if $(filter arm,$(CPULIST)),.le-v7,)$(if $(filter g,$(VARIANTS)),-g,)
	

# Compiler options for enhanced security and recording the compiler options in release builds
CCFLAGS+=-fstack-protector-all -D_FORTIFY_SOURCE=2 \
	$(if $(filter g so shared,$(VARIANTS)),,-fPIE) \
	$(if $(filter g,$(VARIANTS)),,-frecord-gcc-switches)

# Linker options for enhanced security
LDFLAGS+=-Wl,-E,-z,relro -Wl,-z,now $(if $(filter g so shared,$(VARIANTS)),,-pie)

#LIBS+=ReplaceWithModuleName

# Add your required library names, here
LIBS+=tibb v8 ticore
LIBS+=socket bps 
# Add your native module library names, here

# Extra .so required
LDFLAGS+=-lbbcascades -lbbdevice -lbbsystem -lQtCore -lQtDeclarative -lQtGui -lQtMultimedia -lQtNetwork -lscreen -lm -lbb -lbbdata -lbbpim
LDFLAGS+=-lQtSensors -lQtSql -lQtTest -lQtXml -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut -lasound -lbbmultimedia

include $(MKFILES_ROOT)/qmacros.mk

PROJECT_NAME=tibbtest
# Suppress the _g suffix from the debug variant
BUILDNAME=$(PROJECT_NAME)

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
