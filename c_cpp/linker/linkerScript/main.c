/**
 * Note: Might get following warning:
 *       "ld: warning: main has a LOAD segment with RWX permissions"
 *       Don't worry about it, as it is: a) a warning
 *                                       b) this is not the
 *                                          interesting part here...
 *       TODO: Want to investigate though...
 */

__attribute__ ((__section__(".data_section"))) char str[] = "Hello World!";

__attribute__ ((__section__(".code_section"))) int compute(int arg) {
	static int value = 0;

	value += arg;

	return value;
}

int main(int argc, char **argv) {
	compute(3);
}
