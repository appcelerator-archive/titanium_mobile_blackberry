ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

USEFILE=

# Extra include path for libfreetype and for target overrides and patches
EXTRA_INCVPATH+=$(QNX_TARGET)/usr/include/freetype2 \
	$(QNX_TARGET)/usr/include \
	$(QNX_TARGET)/usr/include/qt4/QtCore \
	$(QNX_TARGET)/usr/include/qt4 \
	$(PROJECT_ROOT)/include \
	$(PROJECT_ROOT)/../libv8/include

PRE_BUILD=moc.exe -DQT_NO_DEBUG -DQT_DECLARATIVE_LIB -DQT_SCRIPT_LIB -DQT_SVG_LIB -DQT_SQL_LIB -DQT_GUI_LIB \
	-DQT_NETWORK_LIB -DQT_CORE_LIB $(addprefix -I, $(INCVPATH)) 


# Extra library search path for target overrides and patches
EXTRA_LIBVPATH+=$(QNX_TARGET)/$(CPUVARDIR)/usr/lib \
	$(QNX_TARGET)/$(CPUVARDIR)/usr/lib/qt4/lib \
	$(PROJECT_ROOT)/../libv8/lib/$(CPU)

# Compiler options for enhanced security and recording the compiler options in release builds
CCFLAGS+=-fstack-protector-all -D_FORTIFY_SOURCE=2 \
	$(if $(filter g so shared,$(VARIANTS)),,-fPIE) \
	$(if $(filter g,$(VARIANTS)),,-frecord-gcc-switches)

# Linker options for enhanced security
LDFLAGS+=-Wl,-z,relro -Wl,-z,now $(if $(filter g so shared,$(VARIANTS)),,-pie)

# Add your required library names, here
LIBS+=

include $(MKFILES_ROOT)/qmacros.mk

# Suppress the _g suffix from the debug variant
BUILDNAME=$(IMAGE_PREF_$(BUILD_TYPE))$(NAME)$(IMAGE_SUFF_$(BUILD_TYPE))

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))
