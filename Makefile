all:
	gcc -Wall -O2 schedule.c -o schedule

clean:
	rm -f schedule

install: all
	cp schedule /usr/local/bin
