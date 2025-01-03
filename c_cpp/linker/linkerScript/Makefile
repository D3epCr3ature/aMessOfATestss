
FILENAME=main
SRC=$(FILENAME).c
OBJ=$(FILENAME).o
EXE=$(FILENAME)
DUMP_FILE=dump.txt
FULL_DUMP_FILE=full_$(DUMP_FILE)
DATA_CONTENT_NEW_POS=28

.PHONY: clean mrproper $(FULL_DUMP_FILE)

all: $(DUMP_FILE)

$(OBJ): $(SRC)
	gcc -O0 -c -Wall $<

$(EXE):	linkScript.lds.S $(OBJ)
	ld -T $^ -o $@

$(DUMP_FILE): $(EXE)
	@echo -e "\033[1;34mDumping executable...\033[0m"
	@objdump -D -S -j .text -j .data_section -j .code_section $< > $@.tmp
	@objdump -s -j .data_section $< >> $@.tmp
	@ed -s $@.tmp <<< $$'/Contents/-1,/Contents/+1m$(DATA_CONTENT_NEW_POS)\nw\nq'
	@head -n -2 $@.tmp > $@
	@rm $@.tmp

$(FULL_DUMP_FILE): $(EXE)
	@echo -e "\033[1;32mFull Dumping executable...\033[0m"
	@objdump -D -S $< > $@.tmp
	@objdump -s -j .data_section $< >> $@.tmp
	@ed -s $@.tmp <<< $$'/Contents/-1,/Contents/+1m$(DATA_CONTENT_NEW_POS)\nw\nq'
	@head -n -2 $@.tmp > $@
	@rm $@.tmp

clean:
	rm -rf $(OBJ) $(EXE)

mrproper:
	rm -rf $(OBJ) $(EXE) $(DUMP_FILE) $(FULL_DUMP_FILE)
