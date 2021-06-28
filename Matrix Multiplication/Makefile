csrc =  $(wildcard *.c)

CC = gcc

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

ifeq ($(PROF),1)
CFLAGS += -DPROF
endif

obj = $(csrc:.c=.o)

all : clean exe

exe : $(obj)
	$(CC) -o $@ $^ $(CFLAGS) -o exe

CFLAGS += -mavx2 -mfma
CFLAGS += $(WERROR_FLAGS)

.PHONY : clean
clean :
	rm -rf $(obj) exe *.o *.txt
