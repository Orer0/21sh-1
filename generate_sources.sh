#! /bin/zsh

rm sources.mk

for file in `ls -1 src/**/*.c`
do
	printf "SRCS+=%s\n" $file >> sources.mk
done

chmod 755 sources.mk
