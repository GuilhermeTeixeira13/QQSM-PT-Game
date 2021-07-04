SOURCEFILES = $(wildcard *.c) 

OBJECTS = $(SOURCEFILES:%.c=%.o) 
.PHONY: clean all execute 
CC=cc
EXE = main.exe 
all: execute 

execute : $(EXE)
	make clean 
	./$<
                        
$(EXE) : $(OBJECTS)        
	$(CC) -o $@ $^ -lm      

%.o : %.c   
	$(CC) -c $< -lm

clean :
	rm *.o

