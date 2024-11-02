
EXE=qt7SegDriver
EXE_DBG=$(EXE).dbg
IP=127.0.0.1
PORT=5000

.PHONY: clean run run_dbg

all: $(EXE)

$(EXE): 7segSocketDriver.c
	gcc -Wall -o $@ $<

run: $(EXE)
	./$< $(IP) $(PORT)

$(EXE_DBG): 7segSocketDriver.c
	gcc -Wall -DENA_DBG=1 -o $@ $<

run_dbg: $(EXE_DBG)
	./$< $(IP) $(PORT)

clean:
	rm -rf $(EXE) $(EXE_DBG)

