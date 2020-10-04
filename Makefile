include config.mk
include rules.mk

.PHONY: all

BINARIES =  \
	bs
all: $(patsubst %, bin/%, ${BINARIES})

BS_DEPS =  \
	bs.pb  \
	bs
bin/bs: $(patsubst %, build/%.o, ${BS_DEPS})

-include ${DEPENDS}
