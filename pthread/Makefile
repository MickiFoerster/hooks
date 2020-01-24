run : libpthreadhook.so main
	LD_PRELOAD=$$PWD/$< ./main

main : main.c
	gcc -pthread -o $@ $< 

libpthreadhook.so : hook.c
	gcc -shared  -fPIC $< -ldl -o $@
