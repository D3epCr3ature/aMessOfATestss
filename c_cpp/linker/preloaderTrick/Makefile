EXE=main.elf
STATIC_MEMCPY=memcpy.so

.PHONY: clean run_replace run

all: $(EXE) $(STATIC_MEMCPY)

$(EXE): main.c
	gcc -Wall -O0 -o $@ $^

$(STATIC_MEMCPY): memcpy.c
	gcc -shared -o $@ -fPIC $^

run: $(EXE)
	./$(EXE) 8

run_replace: $(EXE) $(STATIC_MEMCPY)
	LD_PRELOAD=./$(STATIC_MEMCPY) ./$(EXE) 8

clean:
	rm -rf $(EXE) $(STATIC_MEMCPY)

