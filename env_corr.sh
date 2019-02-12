echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '$HOME=test ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'ldldld=$HOME ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '~=kkjjj ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'hdhdhd=~ ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '$HOME= ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '=$HOME ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'ls $HOME=dhdhdh'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'ls djdjjd=$HOME'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'env ; unsetenv TERM_SESSION_ID; env'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unsetenv'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'setenv'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'unset'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'export'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'set $HOME=$PWD'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'env; unsetenv HOME USER PWD; env'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c ''
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c ''
echo "\n"
