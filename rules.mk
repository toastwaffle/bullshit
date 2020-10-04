CXXFLAGS += -Wall -Wextra -Isrc -Igen

.PHONY: default
default: all

# Build with optimized configuration.
.PHONY: opt
opt: all

# Build with debug configuration.
.PHONY: debug
debug: all

# Delete all generated files.
.PHONY: clean
clean:
	@echo Removing generated files
	@rm -rf bin build

# Pattern rule for generating a static library.
bin/%.a:
	@echo Archiving $*
	@mkdir -p $(dir $@)
	@${AR} cr $@ $^

# Pattern rule for generating a binary.
bin/%:
	@echo Linking $*
	@mkdir -p $(dir $@)
	@${CXX} ${LDFLAGS} $^ -o $@ ${LDLIBS}

# Pattern rule for generated files.
.PRECIOUS: build/gen/%.cc build/gen/%.h
build/gen/%.cc build/gen/%.h &: src/gen_%.sh src/%.txt
	@echo Generating $*
	@mkdir -p build/gen/$(dir $*)
	@$^

GENERATORS = $(shell find src -name 'gen_*.sh')
GENERATED = $(patsubst src/gen_%.sh, gen/%.h, ${GENERATORS})

# Pattern rule for compiling a cc file into an o file.
build/%.o: src/%.cc $(wildcard src/%.h) | ${GENERATED}
	@echo Compiling $*
	@mkdir -p {build,build/dep}/$(dir $*)
	@${CXX} ${CXXFLAGS} ${CPPFLAGS} -MMD -MF build/dep/$*.d $< -c -o build/$*.o

# Pattern rule for compiling a generated cc file into an o file.
build/%.o: gen/%.cc $(wildcard gen/%.h)
	@echo Compiling $*
	@mkdir -p {build,build/dep}/$(dir $*)
	@${CXX} ${CXXFLAGS} ${CPPFLAGS} -MMD -MF build/dep/$*.d $< -c -o build/$*.o

DEPENDS = $(shell [[ -d build/dep ]] && find build/dep -name '*.d')
