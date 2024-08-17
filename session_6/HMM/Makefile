BUILD_TYPE = DEBUG

ifeq ($(BUILD_TYPE),DEBUG)
bug = -g
endif

files = main.c linkedList.c HMM.c

all: HMM

HMM:
	gcc $(bug) -Wl,-Map=output.map $(files) --static -o HMM

clean:
	rm -f HMM output.map
.PHONY: all clean

