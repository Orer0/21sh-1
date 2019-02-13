echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '$HOME=test cd ; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd ; cd ~; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'ln -s /Users link ; env | grep "PWD"; cd link ; env | grep "PWD"'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd; cd ../../../../../; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd; cd ..../../.././; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd; cd ~///////Desktop/////; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd; cd /; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd ; cd ../../ ; pwd ; cd - ; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd ; cd link; env | grep "PWD"; cd ~; env |grep "PWD"; cd -; env |grep "PWD"'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd ; cd ./include/; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd ; cd //////////////../////////; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'pwd; cd -; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unset HOME PWD OLDPWD USER; cd ~; pwd'
echo "\n"
