
echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'foo'
echo " "

echo "\033[104m sh :\033[0m"
sh -c '/bin/ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '/bin/ls'
echo "\n"

echo "\033[104m sh :\033[0m"
sh -c '/bin/ls -laf'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '/bin/ls -laf'
echo "\n"

echo "\033[104m sh :\033[0m"
sh -c '/bin/ls -l -a -f' 
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c '/bin/ls -l -a -f'
echo "\n"

echo "\033[104m sh :\033[0m"
sh -c 'echo it works'
echo "\n"

echo "\033[102m 21sh :\033[0m"
valgrind ./21sh -c 'echo it works'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = cd /Users/aroblin/Documents/Ft_ls/ ; pwd"
sh -c 'cd /Users/aroblin/Documents/Ft_ls/ ; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = cd /Users/aroblin/Documents/Ft_ls/ ; pwd"
valgrind ./21sh -c 'cd /Users/aroblin/Documents/Ft_ls/ ; pwd'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = cd ~/Documents/Ft_ls/ ; pwd"
sh -c 'cd ~/Documents/Ft_ls/ ; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = cd ~/Documents/Ft_ls/ ; pwd"
valgrind ./21sh -c 'cd ~/Documents/Ft_ls/ ; pwd'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = cd ; pwd"
sh -c 'cd ; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = cd ; pwd"
valgrind ./21sh -c 'cd ; pwd'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = cd / ; cd -"
sh -c 'cd / ; cd -; pwd'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = cd / ; cd -"
valgrind ./21sh -c 'cd / ; cd -; pwd'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = cd ~root"
sh -c 'cd ~root'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = cd ~root"
valgrind ./21sh -c 'cd ~root'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = env"
sh -c 'env'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = env"
valgrind ./21sh -c 'env'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = var=test ; set"
sh -c 'var=test ; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = var=test; set"
valgrind ./21sh -c 'var=test ; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = set var=test; set"
sh -c 'set var=test; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = set var=test; set"
valgrind ./21sh -c 'set var=test; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = set test=var; export test; env"
valgrind ./21sh -c 'set test=var; export test; env'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = set test=var; set; unset test; set"
valgrind ./21sh -c 'set test=var; set; unset test; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = set test=var; set; export test; env; unset test; env"
valgrind ./21sh -c 'set test=var; set; export test; env; unset test; env'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = env"
valgrind ./21sh -c 'env'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = echo HOME"
sh -c 'echo $HOME'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = echo HOME"
valgrind ./21sh -c 'echo $HOME'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande = echo jjjj#HOME#PWD"
sh -c 'echo jjj$HOME$PWD'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande echo jjjj#HOME#PWD"
valgrind ./21sh -c 'echo jjjj$HOME$PWD'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande test=#HOME; set"
sh -c 'test=$HOME; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande = test=#HOME; set"
valgrind ./21sh -c 'test=$HOME; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande kkk#HOME#PWD=jjj#HOMElll#HOME; set"
sh -c 'kkk$HOME$PWD=jjj$HOMElll$HOME; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande kkk#HOME#PWD=jjj#HOMElll#HOME; set"
valgrind ./21sh -c 'kkk$HOME$PWD=jjj$HOMElll$HOME; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande test=; set"
sh -c 'test=; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande test=; set"
valgrind ./21sh -c 'test= ; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande #HOME=; set"
sh -c '$HOME=; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande #HOME=; set"
valgrind ./21sh -c '$HOME=; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ~=test; set"
sh -c '~=test; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ~=test; set"
valgrind ./21sh -c '~=test; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande test=~; set"
sh -c 'test=~; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande test=~; set"
valgrind ./21sh -c 'test=~; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande test=~root; set"
sh -c 'test=~root; set'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande test=~root; set"
valgrind ./21sh -c 'test=~root; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande #HOME#PWD~test~=~hhh#HOMEjjj#PWD#USER~"
sh -c '$HOME$PWD~test~=~hhh$HOMEjjj$PWD$USER~'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande #HOME#PWD~test~=~hhh#HOMEjjj#PWD#USER~; set"
valgrind ./21sh -c '$HOME$PWD~test~=~hhh$HOMEjjj$PWD$USER~; set'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls #HOME "
sh -c 'ls $HOME'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls #HOME"
valgrind ./21sh -c 'ls $HOME'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande unset PATH; set PATH=/bin/:/usr/bin; export PATH; ls"
sh -c 'unset PATH; set PATH=/bin/:/usr/bin; export PATH; ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande unset PATH; set PATH=/bin/:/usr/bin; export PATH; ls"
valgrind ./21sh -c 'unset PATH; set PATH=/bin/:/usr/bin; export PATH; ls'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande unset PATH; ls; /bin/ls"
sh -c 'unset PATH; ls; /bin/ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande unset PATH; ls; /bin/ls"
valgrind ./21sh -c 'unset PATH; ls ; /bin/ls'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls | cat -e"
sh -c 'ls | cat -e'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls |cat -e"
valgrind ./21sh -c 'ls | cat -e'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls | sort | cat -e"
sh -c 'ls | sort | cat -e'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls | sort | cat -e"
valgrind ./21sh -c 'ls | sort | cat -e'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g"
#sh -c 'base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g''
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e s/1/Yes/g -e s/0/No/g"
#valgrind ./21sh -c 'base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | sed -e 's/1/Yes/g' -e 's/0/No/g''
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande  echo 'Testing redirections' > /tmp/test.txt; cat /tmp/test.txt"
sh -c ' echo "Testing redirections," > /tmp/test.txt; cat /tmp/test.txt'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande echo Testing redirections, > /tmp/test.txt; cat /tmp/test.txt"
valgrind ./21sh -c ' echo "Testing redirections," > /tmp/test.txt; cat /tmp/test.txt'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande  echo 'Testing redirections' >> /tmp/test.txt; cat /tmp/test.txt *2"
sh -c ' echo "Testing redirections," >> /tmp/test.txt; echo "FOISDEUX" >> /tmp/test.txt; cat /tmp/test.txt'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande echo Testing redirections, >> /tmp/test.txt; cat /tmp/test.txt * 2"
valgrind ./21sh -c ' echo "Testing redirections," >> /tmp/test.txt; echo "fois deux" >> /tmp/test.txt; cat /tmp/test.txt'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande echo '12346' > fil; wc -c < fil"
sh -c 'echo "123456" > fil; wc -c < fil'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande echo 123456 > fil; wc -c < fil"
valgrind ./21sh -c 'echo "123456" > fil; wc -c fil'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls -l && ls"
sh -c 'ls -l && ls '
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls -l && ls"
valgrind ./21sh -c 'ls -l && ls'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls something || ls"
sh -c 'ls something || ls'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls something || ls"
valgrind ./21sh -c 'ls something || ls'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls || ls something"
sh -c 'ls || ls something'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls || ls something"
valgrind ./21sh -c 'ls || ls something'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande ls -1; touch test_file; ls -1"
sh -c 'ls -1; touch test_file; ls -1; rm test_file'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande ls -1; touch test_file; ls -1; rm test_file"
valgrind ./21sh -c 'ls -1; touch test_file; ls -1; rm test_file'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi; rm -rf ../test"
sh -c 'mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi; rm -rf test'
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi; rm -rf test"
valgrind ./21sh -c 'mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi; rm -rf ../test'
echo "\n"

echo "\033[104m sh :\033[0m"
echo "comande "
sh -c ''
echo "\n"

echo "\033[102m 21sh :\033[0m"
echo "comande "
valgrind ./21sh -c ''
echo "\n"
