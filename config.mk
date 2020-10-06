CXXFLAGS += -std=c++17 -Wall -Wextra -pedantic
opt: CXXFLAGS += -ffunction-sections -fdata-sections -flto -O3 -march=native
debug: CXXFLAGS += -O0 -g3

LDFLAGS += -fuse-ld=gold
opt: LDFLAGS += -s -Wl,--gc-sections -flto -Ofast

LDLIBS = -lpthread -lprotobuf -lssl -lcrypto
