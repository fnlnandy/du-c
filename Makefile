EXE :=
RM  := rm -rf

ifeq ($(OS),Windows_NT)
    EXE := .exe
    RM  := del
endif

DU := du-c$(EXE)

GCC := gcc
CCFLAGS := -std=c17 -Wall -Werror -O2
LDFLAGS :=

CFILES := du.c file.c dir.c
OFILES := $(CFILES:%.c=%.o)

all: $(DU)

$(DU): $(OFILES)
	$(GCC) $(OFILES) -o $(DU) $(LDFLAGS)

%.o: %.c
	$(GCC) -c $< -o $@ $(CCFLAGS)

clean:
	$(RM) $(OFILES)
	$(RM) $(DU)