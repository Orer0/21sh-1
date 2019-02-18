echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'setenv test=coucou; echo $test'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'set test=coucouset; echo $test'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'setenv $HOME=test; echo $HOME'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unsetenv PWD; setenv PWD=tetete; echo $PWD'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'setenv a=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb; setenv b=$a$a$a$a$a$a$a; setenv c=$b$b$b$b$b$b$b$b; echo $c'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '$HOME=ttttt'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unsetenv HOME; echo $HOME'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unset HOME; echo $HOME'
echo "\n"
