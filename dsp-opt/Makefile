# Use one of these commands to build the manifest for curl:
#
# - make
# - make DEBUG=1
# - make SGX=1
# - make SGX=1 DEBUG=1
#
# Use `make clean` to remove Graphene-generated files.

APP_NAME ?= dsp
#WL: must be current abs path
APP_DIR = /u/weijliu/graphene-dida-bwa/dsp-opt

# Relative path to Graphene root and key for enclave signing
GRAPHENEDIR ?= /usr/local/src/graphene
SGX_SIGNER_KEY ?= $(GRAPHENEDIR)/Pal/src/host/Linux-SGX/signer/enclave-key.pem

ifeq ($(DEBUG),1)
GRAPHENE_LOG_LEVEL = debug
else
GRAPHENE_LOG_LEVEL = error
endif

.PHONY: all
all: $(APP_NAME) $(APP_NAME).manifest
ifeq ($(SGX),1)
all: $(APP_NAME) $(APP_NAME).manifest.sgx $(APP_NAME).sig $(APP_NAME).token
endif

include $(GRAPHENEDIR)/Scripts/Makefile.configs

$(APP_NAME).manifest: $(APP_NAME).manifest.template
	graphene-manifest \
		-Dlog_level=$(GRAPHENE_LOG_LEVEL) \
		-Dhome=$(HOME) \
		-Darch_libdir=$(ARCH_LIBDIR) \
		-Dapp_dir=$(APP_DIR) \
		-Dapp_name=$(APP_NAME) \
		$< >$@

# Generate SGX-specific manifest, enclave signature, and token for enclave initialization
$(APP_NAME).manifest.sgx: $(APP_NAME).manifest
	graphene-sgx-sign \
		--key $(SGX_SIGNER_KEY) \
		--manifest $(APP_NAME).manifest \
		--output $@

$(APP_NAME).sig: $(APP_NAME).manifest.sgx

$(APP_NAME).token: $(APP_NAME).sig
	graphene-sgx-get-token --output $@ --sig $^

ifeq ($(SGX),)
GRAPHENE = graphene-direct
else
GRAPHENE = graphene-sgx
endif

$(APP_NAME): $(APP_NAME).cpp
	g++ -g -fopenmp $< -o $@

PARTITIONS = 10

run-bf: $(APP_NAME)
	$(RM) -r /usr/local/src/work/up/
	mkdir /usr/local/src/work/up/
	./$(APP_NAME) -b25 -p $(PARTITIONS) -g /usr/local/src/work/ref_$(PARTITIONS) -u /usr/local/src/work/up -d /usr/local/src/work/pr -e 0 /usr/local/src/work/SRR062634.filt.fastq -r 0

.PHONY: run
run: all
	# must create the pr dir first, otherwise the callback would fail
	$(RM) -r /usr/local/src/work/pr/	
	mkdir /usr/local/src/work/pr/
	$(GRAPHENE) ./$(APP_NAME) -b25 -p$(PARTITIONS) -g /usr/local/src/work/ref_$(PARTITIONS) -u /usr/local/src/work/up -d /usr/local/src/work/pr -e 1 /usr/local/src/work/SRR062634.filt.fastq -r 0

.PHONY: clean
clean:
	$(RM) *.manifest *.manifest.sgx *.token *.sig $(APP_NAME) pal_loader OUTPUT
	$(RM) *-trusted-libs *-deps
.PHONY: distclean
distclean: clean
