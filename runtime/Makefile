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

V8_VERSION_FILE := "v8/src/version.cc"
V8_MAJOR_VERSION := $(shell grep "\#define MAJOR_VERSION" $(V8_VERSION_FILE) | awk '{print $$NF}')
V8_MINOR_VERSION := $(shell grep "\#define MINOR_VERSION" $(V8_VERSION_FILE) | awk '{print $$NF}')
V8_BUILD_NUMBER := $(shell grep "\#define BUILD_NUMBER" $(V8_VERSION_FILE) | awk '{print $$NF}')
V8_GIT_HASH := $(shell git rev-parse --short HEAD)

# The V8 prebuild package that is download or uploaded.
V8_PREBUILD_PACKAGE := libv8-$(V8_MAJOR_VERSION).$(V8_MINOR_VERSION).$(V8_BUILD_NUMBER)-$(V8_GIT_HASH).zip

$(V8_PREBUILD_PACKAGE): v8/libv8-arm.a v8/libv8-ia32.a
	@echo "Packing V8 prebuild..."
	@zip -r $@ $(wildcard v8/libv8-*.a) v8/include
	@echo "$@ ready for uploading."

.PHONY: package-v8
package-v8: $(V8_PREBUILD_PACKAGE)

# V8 prebuild S3 upload and download info.
V8_PREBUILD_S3_BUCKET ?= "timobile.appcelerator.com"
V8_PREBUILD_S3_SUFFIX ?= "blackberry/v8"

.PHONY: upload-v8
upload-v8: $(V8_PREBUILD_PACKAGE)
	@echo "Uploading to S3 bucket..."
	@s3cmd put --acl-public --guess-mime-type $(V8_PREBUILD_PACKAGE) "s3://$(V8_PREBUILD_S3_BUCKET)/$(V8_PREBUILD_S3_SUFFIX)"
	@echo "Done!"

download-v8:
	@echo "Downloading V8 prebuild..."
	@curl -f "http://$(V8_PREBUILD_S3_BUCKET).s3.amazonaws.com/$(V8_PREBUILD_S3_SUFFIX)/$(V8_PREBUILD_PACKAGE)" \
		-o $(V8_PREBUILD_PACKAGE)
	@echo "Extracting..."
	@unzip $(V8_PREBUILD_PACKAGE) -d v8/

.PHONY: clean
clean:
	@cd v8; scons -c; rm *.a

