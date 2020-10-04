CXXFLAGS += -Wall -Wextra -Isrc -Ibuild/proto

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

# Pattern rule for proto files.
.PRECIOUS: build/proto/%.cc build/proto/%.h
build/proto/%.pb.cc build/proto/%.pb.h &: src/%.proto
	@echo Generating $*
	@mkdir -p build/proto/$(dir $*)
	@protoc --proto_path=src --cpp_out=build/proto/$(dir $*) $^

# Pattern rule for compiling a cc file into an o file.
build/%.o: src/%.cc $(wildcard src/%.h) | ${GENERATED}
	@echo Compiling $*
	@mkdir -p {build,build/dep}/$(dir $*)
	@${CXX} ${CXXFLAGS} ${CPPFLAGS} -MMD -MF build/dep/$*.d $< -c -o build/$*.o

# Pattern rule for compiling a generated cc file into an o file.
build/%.o: build/proto/%.cc | build/proto/%.h
	@echo Compiling $*
	@mkdir -p {build,build/dep}/$(dir $*)
	@${CXX} ${CXXFLAGS} ${CPPFLAGS} -MMD -MF build/dep/$*.d $< -c -o build/$*.o

DEPENDS = $(shell [[ -d build/dep ]] && find build/dep -name '*.d')
