# build an executable named hello from hello.c
hello: countwords.c
	clang countwords.c `pkg-config --cflags --libs glib-2.0` -o countwords

clean: 
	$(RM) countwords