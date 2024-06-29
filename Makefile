DU := du-c

GCC := gcc
CCFLAGS := -std=c17 -Wall -Werror -O2
LDFLAGS :=

CFILES := du.c file.c
OFILES := $(CFILES:%.c=%.o)

all: $(DU)

$(DU): $(OFILES)
	$(GCC) $(OFILES) -o $(DU) $(LDFLAGS)

%.o: %.c
	$(GCC) -c $< -o $@ $(CCFLAGS)

clean:
	rm -rf $(OFILES)
	rm -rf $(DU)