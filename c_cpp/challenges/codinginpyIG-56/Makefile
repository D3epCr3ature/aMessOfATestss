
PROJ=repPattern

.PHONY: demo run_with_param run_with_expectation help clean

all: $(PROJ).elf $(PROJ)_expect.elf

$(PROJ).elf: $(PROJ).c
	gcc -Wall $< -o $@

$(PROJ)_expect.elf: $(PROJ).c
	gcc -Wall -DWITH_EXPECTATION=1 -o $@ $^

demo: $(PROJ)_expect.elf
	./$<

run_with_param: $(PROJ).elf
	./$< 3[2[a]1[b]c]4[kekw]

run_with_expectation: $(PROJ)_expect.elf
	./$< 2[4[a]2[bc4[i]]]5[kev] aaaabciiiibciiiiaaaabciiiibciiiikevkevkevkevkev

help: $(PROJ).elf
	./$< -h
	@#./$< --help

clean:
	rm -rf *.elf
