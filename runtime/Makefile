all: libv8

# Build libv8 for a specific cpu arch. (arm / ia32).
define build_libv8
	@echo "Compiling V8 for $1"
	@cd v8; \
	./qnxbuild.sh $1; \
	mv libv8.a libv8-$1.a
endef

LIBV8_SRC := $(wildcard v8/include/* v8/src/*)
v8/libv8-arm.a: $(LIBV8_SRC)
	$(call build_libv8,arm)
v8/libv8-ia32.a: $(LIBV8_SRC)
	$(call build_libv8,ia32)

.PHONY: libv8 libv8-arm libv8-ia32
libv8-arm: v8/libv8-arm.a
libv8-ia32: v8/libv8-ia32.a
libv8: libv8-arm libv8-ia32

.PHONY: clean
clean:
	@cd v8; scons -c; rm *.a

