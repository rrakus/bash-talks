--title Bash basics
--author Roman Rakus <rrakus@redhat.com>
--date today
--fgcolor black
--bgcolor white

--newpage agenda
--heading Agenda
 * How linux works
 * What is bash
 * Bash basics

--newpage linux_intro
--heading How Linux works
in perception of bash
 * files (and their permissions)
 * stdin, stdout, stderr, file descriptors
 * signals
 * command parameters
 * return code (exit status, 0-255)
 * one simple command for simple task
 * set of commands (GNU)

--newpage linux_coreutils
--heading Some commands
--color red
coreutils
--color black
  cat - concatenate files
  cp - copy files
  cut - remove section from each line
  date - print or set date and time
  echo - display text (printf)
  false - exit status 1 (unsuccess)
  ls - list directory contents
  mv - move files
  rm - remove files
--newpage linux_coreutils
  sleep - delay
  sort - sort lines of text
  true - return status 0 (success)
  uniq - report or omit repeated lines
  wc - print byte/character/line/word counts

--newpage linux_noncoreutils
--heading Some commands
--color red
non coreutils
--color black
  grep - print lines matching pattern
  sed - stream editor for filtering and transforming text
  awk - pattern and processing language
  man - an interface to the on-line reference manuals
  info - read info documents (some are not in man)

--newpage linux_bash_builtins
--heading Some commands
--color red
bash builtins
--color black
  cd - change directory
  echo - display text (also in coreutils)
  type - how bash interprets command

--newpage bash_intro
--heading What is bash
 * shell
 * Command language interpreter
 * programming language
 * Bourne-Again SHell
 * POSIX
--newpage bash_intro
 * can read from file, terminal or string
 * can work interactively (terminal) or not (script, string)
 * can run commands synchronous or asynchronous (wait for end)
 * can redirect input, output

--newpage bash_command_executing
--heading Executing command
 * first word is executed
 * PATH parameter (variable) to search commands
 * can use full path name
--beginoutput
ls
ls -la
/bin/echo Hello World
--endoutput


--newpage bash_scripting
--heading bash scripts
 * shebang (#!/bin/bash)
 * POSIX mode (#!/bin/sh)
 * # denotes comments
--beginoutput
#!/bin/bash
# Comment here
echo Hello World # Display Hello World
ls # list files in current directory
cd /
ls
cd
ls -la / /home/rrakus
--endoutput

--newpage bash_script_exercise
--heading bash script exercise
Write your own script which will just print on the screen Hello World.
Make the script executable

hint: use chmod, echo (or printf)

--newpage Variables
--heading Variables
 * bash uses parameteres, variable is special parameter
 * variable is denoted by name
 * everything is string
 * name=[value]
 * $name - parameter and variable expansion
 * name - letters, numbers, underscores beginning with a letter or underscore
 * good to use small letters

--newpage Variables_example
--heading Variables example
--beginoutput
var=Hello
var2=World
echo $var $var2
cat $var $var2
$var $var2
--endoutput

--newpage Variables_example_output
--heading Variables example output
--beginshelloutput
$ ./01-variables-example.sh
Hello World
cat: Hello: No such file or directory
cat: World: No such file or directory
./01-variables-example.sh: line 6: Hello: command not found
--endshelloutput
Return code 127

--newpage for_cycle
--heading Cycle for
--color red
for var in words...; do commands; done
--color black
 * perform commands for every word
 * Save word by word to var variable
 * can use break and continue builtins
 * can use newlines instead of ;

--newpage for_cycle_example
--heading Example of for cycle
--beginoutput
for name in I like how words are splitted
do
  echo $name
done
--endoutput

--newpage for_cycle_example_output
--heading Example of for cycle output
--beginshelloutput
$ ./02-for-cycle-example.sh
I
like
how
words
are
splitted
--endshelloutput
Return code 0

--newpage quoting
--heading Quoting
 * Used to remove special meaning
 * single quotes - '#$^$%&'
   Preserves literal value
 * double quotes - "will be one word"
   Preserves literal value, but $ ` \
 * escape character - \" \' \\
   Preserves literal value of next char
 * special characters - | & ; ( < > , " ' \ #

--newpage quoting_example
--heading Quoting example
--beginoutput
foo=bar
baz="Will be splitted?"
echo $foo $bar $baz
echo '$foo $bar $baz'
echo "$foo $bar $baz"
--endoutput

--newpage quoting_example_output
--heading Quoting example output
--beginshelloutput
$ ./03-quoting-example.sh
bar Will be splitted?
$foo $bar $baz
bar  Will be splitted?
--endshelloutput
Return code 0

--newpage quoting_for_cycle
--heading Quoting and for cycle
--beginoutput
foo=bar
baz="Will be splitted?"
for name in $foo $bar $baz; do echo $name; done
for name in "$foo $bar $baz"; do echo $name; done
for name in '$foo $bar $baz'; do echo $name; done
for name in "$foo" "$bar" "$baz"; do echo $name; done
for name in $foo "$bar $baz"; do echo "$name"; done
--endoutput

--newpage quoting_for_cycle_output
--heading Quoting and for cycle output
--beginshelloutput
$ ./04-quoting-and-for-example.sh
bar
Will
be
splitted?
bar Will be splitted?
$foo $bar $baz
bar

Will be splitted?
bar
 Will be splitted?
--endshelloutput
Return code 0

--newpage for_cycle_exercise
--heading For cycle exercise
Write a script which will use 2 varibles, first will be "Hello World"
and second will be "$foo $bar $baz" (both strings literally, without quotes).
Use for cycle to print above strings, one per line

--newpage conditionals
--heading Conditional expressions
 * test and [ builtin
 * [[ compound command
 * test file attributes
 * string and arithmetic comparisons
 * result is return code
 * ! for negation

--newpage arithmetics
--heading Bash arithmetics
 * You can use bash variables as numbers
 * Special attribute -i (declare -i variable)
 * non-numbers treated as 0
 * (( expr ))
 * $(( expr ))
 * let expr

--newpage arithmetic_evaluation
--heading Arithmetic evaluation
Most of operators:
id++ id-- ++id --id - pre/post increment/decrement
** - exponentiation
* / % - multiplication, division, remainder
+ - - addition, substraction
<= >= < > - comparison
== != - equality, inequality
&& - logical AND
|| - logical OR
expr ? expr : expr - conditional operator (if, then, else)
= *= /= %= += -= - assignment

--newpage arithmetic_expression
--heading Arithmetic expression
--color red
((expr))
--color black
 * expr is evaluated acording to arithmetic evaluation
 * Don't need to reference variables
 * return status is 0 if value of expr is non-zero
 * Equivalent to let "expr"

--newpage arithmetic_expression_example
--heading Arithmetic expression example
--beginoutput
#!/bin/bash
a=10
b=1
((c=a+b*a-b))
echo $a $b $c
--endoutput

--newpage arithmetic_expression_example_2
--heading Arithmetic expression example II
--beginoutput
#!/bin/bash
a=10
b=1
op1="+"
op2="-"
((c=a $op1 b $op2 a $op1 b))
echo $a $b $c
--endoutput

--newpage if_then_else
--heading Conditional constructs
--color red
if test-commands; then
  consequent-commands;
[elif more-tests; then
  more-consequents]
[else alternate-consequents;]
fi
--color black

--newpage if_example_1
--heading Conditional example I
--beginoutput
if [[ a < b ]]; then
  echo "Yes, a is before b"
fi
--endoutput

--newpage if_example_2
--heading Conditional example II
--beginoutput
a="z"; b="f";
if [[ $a < $b ]]; then
  echo "a<b"
else
  echo "b<a"
fi
--endoutput

--newpage if_example_3
--heading Conditional example III
--beginoutput
a=2; b=15
if [[ $a < $b ]]; then
  echo "a<b"
else
  echo "b<a"
fi
--endoutput

--newpage if_example_4
--heading Conditional example IV
--beginoutput
a=2; b=15
if [[ $a -lt $b ]]; then
  echo "a<b"
else
  echo "b<a"
fi
--endoutput

--newpage if_example_5
--heading Conditional example V
--beginoutput
a=2; b=15
if (( a < b )); then
  echo "a<b"
else
  echo "b<a"
fi
--endoutput

--newpage if_example_6
--heading Conditional example VI
--beginoutput
if [[ -e file ]]; then
  echo "This file exists"
else
  echo "not"
fi
--endoutput

--newpage if_exercise
--heading Conditional exercise
Write a script, which will use 2 variables with any strings and print
which one sort before other. If the strings are the same print both

--newpage while_loop
--heading While loop
--color red
while test-commands; do
  consequent-commands
done
--color black

--newpage while_loop_example
--heading While loop example
--beginoutput
a="c"
b="cccc"
while [[ $a != $b ]];do echo "$a $b"; a="$a"c;done
while ./test_script.sh; do echo "test script returns 0"; done
a=2;b=10;while (( a < b )); do echo "$a < $b"; (( a+= 2 )); done
--endoutput


--##TODO--newpage while_loop_exercise
--##TODO--heading While loop exercise
--##TODOWrite a script which will use 3 variables.

--newpage command_lists
--heading List of commands
 * AND lists - command1 && command2
 * OR lists - command1 || command2
 * return status of the last command executed is used
 * ; - also denotes lists
 * & - run asynchronous in a subshell (background)

--newpage command_lists_example
--heading List of commands example
--beginoutput
some_command && echo "Success" || echo "Failure"
some_command || echo "Failure" && echo "Success" # !!!
[[ $a == $b ]] && echo "Equal" || echo "Not equal"
while ... done && echo "While success" || echo "while failure"
--endoutput

--newpage grouping_commands
--heading Grouping commands
--color red
( list )
{ list; }
--color black
 * () will execute list of commands in subshell
 * {} will execute list in current shell
 * variables created in subshell are not visible in parent shell

--newpage functions
--heading Functions
--color red
name () compound-command
--color black
or
--color red
function name [()] compound-command
--color black
 * body is compound command
 * usually list enclosed in { }
 * exit status of last executed command
 * may use return builtin

--newpage functions_example
--heading Functions example
--beginoutput
my_echo ()
{
  echo Hello
  sleep 1
  echo World
}
my_echo
my_echo
--endoutput

--newpage positional_parameters
--heading Positional parameters
 * referenced by $N , N is digit (${N} for more digits)
 * assigned from shell arguments
 * functions have own positional parameters

--newpage positional_parameters_example
--heading Positional parameters example
--beginoutput
echo $1 $2 $3 $4
--endoutput
run the script
 * ./test a b c d
 * ./test "a b c d"
 * ./test
 * ./test 1 2 3 4 5 6 7 8 9 0
 * ./test "$not_set"

--newpage positional_and_functions
--heading Positional parameters in function
 * function's positional parameters set when fce is invoked
 * good to test the number of parameters
 * # - number of pos. parameters ($#)
 * shift builtin to pop parameters

--newpage positional_functions_example
--heading Positional parameters in function example I
--beginoutput
fce()
{
  if [[ $# -lt 2 ]]; then
    return 1
  fi
  echo $2
  echo $1
}

fce 1 2
fce 2 1
fce "1 2"
fce 1
--endoutput

--newpage positional_functions_example_2
--heading Positional parameters in function example II
--beginoutput
fce()
{
  while [[ $# -gt 0 ]]; do
    echo $1
    shift
  done
}
fce 1 2 3 4 5 6 7 8 9
fce "1 2 3 4 5 6 7 8 9"
fce "bread and butter" "fish and chips" "beers and girls"
fce ""
--endoutput

--newpage functions_exercise
--heading Functions exercise
Write a script with a function. Function will take exactly 3 arguments.
1st argument will be count
2nd will be the string
3rd is ending string
Function will print count times string and ends with ending string.
When not proper arguments return 1, else 0.

fce 1 ahoj cau
ahoj
cau

--newpage functions_exercise_2
--heading Functions exercise 2
Write a function which will compute factorial. Take 1 argument.

--newpage function_exercise_3
--heading Function exercise 3
Write a function which will write Fibonacci's n-th number.
n is given as 1st argument. Can use more than one function.

--newpage redirections
--heading Redirections
 * mostly redirect stdout, stderr, stdin
 * can redirect any file descriptor
 * < word - redirect input
 * > word - redirect output

--newpage redirections_example
--heading Redirections example
--beginoutput
echo Hello World > output.txt
cat output.txt
echo Hello > output.txt World
cat output.txt
--endoutput

--newpage redirections_2
--heading Redirections II
 * > word - redirect standard output
 * 2> word - redirect stderr
 * 6> word - redirect fd 6
 * >> - append to file
 * &> word or >& word or >word 2>&1 - redirect stderr and stdout
 * &>> word or >>word 2>&1 - append stderr and stdout
 * 2>&1 >word is not same as >word 2>&1

--newpage redirections_example_2
--heading Redirections example II
--beginoutput
echo Hello World > output.txt
cat output.txt
echo Hello World 2> output.txt
cat output.txt
echo Hello World >> output.txt
cat output.txt
this_command_doesn_exist &>> output.txt
cat output.txt
--endoutput

--newpage redirection_3
--heading Redirections III
 * < word - redirect standard input
 * 6< word - redirect file decriptor 6

--newpage redirections_example_3
--heading Redirections example III
--beginoutput
tail -n10 < output.txt # tail -n10 output.txt
grep 'World' < output.txt # grep World output.txt
tail -n10 < output.txt > output2.txt # tail -n10 output.txt > output2.txt
--endoutput

--newpage rediretions_4
--heading Redirections IV
 * can redirect whole grouping commands, loops and conditionals
 * every reading and writing is redirected for all commands in groups, loops...

--newpage redirections_example_4
--heading Redirections example IV
--beginoutput
i=5
if [[ $i -gt 4 ]]; then
  head -n5
  echo ---
  cat
else
  head -n5
fi < output.txt
--endoutput

--newpage here_doc
--heading Here documents
--color red
<<word
  here-document
delimiter
--color black
 * read input (stdin) from current source till delimiter
 * perform parameter expansion, command substitution and arithmetic expansion on here-document
 * can quote word to not perform

--newpage here_doc_example
--heading Here documents example
--beginoutput
cat <<EOL > script.sh
#!/bin/bash
echo Hello World
for i in H e l l o W o r l d; do
  echo $i
done
EOL
--endoutput

--newpage here_doc_example_2
--heading Here documents example II
--beginoutput
cat <<\EOL > script.sh
#!/bin/bash
echo Hello World
for i in H e l l o W o r l d; do
  echo $i
done
EOL
--endoutput

--newpage here_string
--heading Here strings
--color red
<<< word
--color black
 * expand word and supplied to command on stdin
--beginoutput
say="Hello World"
cat <<< $say
--endoutput

--newpage DU1
--heading Homework 1
--##if tests test jestli soubor zadany parametrem existuje, test poctu parametru
--##quoting pouzije nazev souboru jako parametr
--##while
--##for
--##functions
--##positional params pouzije nazev souboru jako parametr
--##redirection pouzije nazev souboru jako parametr
Write a script which will take 2 arguments. 1st will be the number and 2nd name.The number will be count of files created. Name will be filename prefix. Suffix for filenames will be number. Script will check if file with that filename exists. If exists, prints error message on stderr and continue to next filename. Every file will contain time of creation and one random number (use RANDOM variable). Script will return 0 on success, 1 when some file wasn't generated, 2 on any other error (wrong number of parameters, wrong parameter type...)
example: create.sh 3 "file prefix"
will create files file prefix1, file prefix2, file prefix3 (take care on spaces, tabs and so on)

--newpage Expansions
--heading Shell Expansions
 * brace expansion - we will know
 * tilde expansion - we can know
 * parameter and variable expansion - we know
 * command substitution - we will know
 * arithmetic expansion - we will know
 * word splitting - we know
 * filename expansion - we will know

--newpage brace_expansion
--heading Brace expansion
 * generates strings
 * optional preamble and/or postscript
 * comma seperated list {a,b,c}: a{d,c,b}e -> ade ace abe
or
 * sequence expression {a..c}: a{d..b}e -> ade ace abe
 * sequence can have increment: {a..e..2} -> a c e
 * sequence numbers can be prefixed by 0: {01..20..5} -> 01 06 11 16
 * can be nested: a{b,c{d,e},f}g -> abg acdg aceg afg

--newpage brace_expansion_example
--heading Brace expansion example
--beginoutput
for i in r{u,oma,u}n; do
  echo $i
done
mkdir dir{1..5}
touch dir{1..5}/file{001..125..33}
for i in {10..0}; do
  echo $i
done
echo BOOM
--endoutput

--newpage brace_expansion_exercise
--heading Brace Expansion Exercise
Create a simple script which will print numbers from 100 to 0 descending.

--newpage arithmetic_expansion
--heading Arithmetic Expansion
$((expression))
 * evaluation of arithmetic expression and substitution of result
 * can be nested

--newpage arithmetic_expansion_example
--heading Arithmetic Expansion Example
--beginoutput
a=5; b=66; echo "a*b=$((a*b))"
--endoutput

--newpage command_substitution
--heading Command Substitution
 * output of command replace command itself
 * $(command)
 * unquoted - word splitting - newlines deleted
 * quoted - word splitting and filename expansion not performed
 * can be nested

--newpage command_substitution_example
--heading Command Substitution Exmaple
--beginoutput
starttime=$(date +%s) #seconds since 1970-01-01 00:00:00 UTC
echo We started at $starttime on machine $(hostname)
sleep 5
endtime=$(date +%s)
((time = endtime - starttime))
echo It takes $time seconds
echo It takes $((endtime - starttime)) seconds
echo $(echo $(echo $(echo $(echo Too much nested))))
--endoutput

--newpage filename_expansion
--heading Filename Expansion
 * after word splitting
 * pattern matching when bash saw * ? [
 * alphabetically (current locale) sorted list of files
 * in basic don't match hidden (dotted) files
 * shopt - nocaseglob, nullglob, failglob, dotglob

--newpage pattern_matching
--heading Pattern mathing
 * any character match itself except * ? [
 * may escape (quote) special characters
 * * matches any string including null string
 * ? matches any single character
 * [...] matches any one enclosed character, may use range with -
   [afpz] - match any of a f p z characters
   [a-d] - match any of a through d characters according to locale
   [!a-c] - match any instead of a trhough c
 * ending / matches only directories
 * sorts acording to current locale setup

--newpage filename_expansion_example
--heading Filename Expansion Example
--beginoutput
for file in *; do
  echo file: "$file"
done
rm *
for dir in */; do
  echo directory: "$dir"
done
for hidden in .*; do
  echo hidden: "$hidden"
done
for f in *dir*/*file.???; do ... done
--endoutput

--newpage case
--heading case statements
--color red
case word in [ [(] pattern [| pattern]...) command-list ;;]... esac
--color black
 * selectively execute commands corresponding to first matched pattern
 * can have more patterns to one match - pat1|pat2|pat3
 * ) terminates pattern list
 * Can use ;; or ;& or ;;& to terminate command-list
 * return status 0 if no pattern matched, else return status of last command

--newpage case_example
--heading case example
--beginoutput
var=dog
case $var in
  dog|horse|cat) echo "It has 4 legs";;
  man|kangaroo) echo "It has 2 legs";;
  *) echo "I don't know what is $var";;
esac
--endoutput

--newpage case_example_2
--heading case example 2
--beginoutput
case $1 in
  "") echo "argument 1 not set or empty";;
  a*) echo "It beggins with a";;
  ???) echo "It has 3 characters";;
  *b*) echo "It has b character";;
  *) echo "It's everything else";;
esac
--endoutput

--newpage pipelines
--heading Pipelines
 * sequence of simple commands separated by | or |&
command1 | command2 | command3
 * stdout of command1 is connected to stdin of command2 and command2 to command3
 * |& redirects also stderr to stdin
 * run every command in subshell

--newpage environment
--heading Environment
 * every variable and function is stored in environment
 * can export variables to subshells and commands
 * can define variables for subshell and command
 * env (system) variable names are (mostly) upper case

--newpage environment_variables
--heading Environment Variables
 * env command - print or set environment
 * Some important environment variables
 * Used by shell scripts or any program
PATH - search  path for commands
HOME - home directory of current user
LANG, LC_ALL, LC_COLLATE, ... - locale specifications
HOSTNAME - name of current host (machine)
PWD - current working directory

--newpage environment_variables_setup
--heading Setting Environment variables
 * exporting variables with export builtin
or
 * specify env variables for command

--newpage environment_example
--heading Environment variables example
test.sh
--beginoutput
#!/bin/bash
echo "$PATH"
echo "$foobarbaz"
--endoutput
--beginoutput
#!/bin/bash
./test.sh
foobarbaz="Set for this command only" ./test.sh
echo "$foobarbaz"
export foobarbaz="exported variable"
./test.sh
echo "$foobarbaz"
--endoutput

--newpage builtins
--heading bash builtins
 * Commands built into bash itself
--color red
: . [ alias bg bind break builtin caller cd command
compgen complete compopt continue declare dirs disown echo
enable eval exec exit export false fc fg getopts hash help
history jobs kill let local logout mapfile popd printf pushd
pwd read readonly return set shift shopt source suspend test
times trap true type typeset ulimit umask unalias unset wait
--color black

--newpage source_builtin
--heading Source builtin
--color red
. file [arguments]
source file [arguments]
--color black
 * Read and execute commands from file in the current shell environment
 * good for setting some "global" variables
 * loading functions that are used across many scripts

--newpage source_example
--heading Source Example
test_source.sh
--beginoutput
lib_version="0.0.1"
is_running() {
  if [[ $# -eq 0 ]]; then return 127
  else pidof "$1" &>/dev/null
  fi
}
--endoutput
--beginoutput
#!/bin/bash
echo "$lib_version"
. test_source.sh
echo "$lib_version"
is_running "bash" && echo "bash is running"
is_running "firefox" && echo "firefox is running"
--endoutput

--newpage source_exercise
--heading Source exercise
Write a script which will be sourced and provides functions to compute factorial and to write Fibonacci's n-th number. Source that script in other script and use it's functions.

--newpage arrays
--heading Arrays
 * indexed or associative arrays
 * declaration and assignment
   name[subscript]=value
   declare -a name
   declare -A name
   name=(value1 value2 ... valuen)
 * referenced using ${name[subscript]}
 * if subscript is @ or * word expands to all members of array name

--newpage arrays_example
--heading Arrays Example
--beginoutput
arr=(jedna dve tri)
echo ${arr[0]}
echo ${arr[1]}
echo ${arr[2]}
for i in "${arr[@]}"; do
  echo "$i"
done
--endoutput

--newpage arrays_example_2
--heading Arrays Example 2
--beginoutput
arr=(*)
for i in "${arr[@]}"; do
  echo "$i"
done
--endoutput

--newpage arrays_example_3
--heading Arrays Example 3
--beginoutput
declare -A arr=( [vyska]=175 [vaha]=75 [vek]=28 )
echo "Vyska: ${arr[vyska]}"
echo "Vaha: ${arr[vaha]}"
echo "Vek: ${arr[vek]}"
for i in "${arr[@]}"; do
  echo "$i"
done
--endoutput

--newpage bash_parameters
--heading Bash special parameters
* expands to the positional parameters
@ expands to the positional parameters
# expands to the number of positional parameters
? expands to the exit status the most recently executed command
- expands to the current option flags
$ expands to the process ID of the shell, but in subshell it's parent shell
! expands to pid of the most recently executed background process
0 expands to the name of shell or shell script
_

--newpage bash_parameters_example
--heading Bash special parameters example
--beginoutput
#!/bin/bash
echo 'Difference between $* and $@'
for parameter in "$*"; do
  echo $parameter
  echo "$parameter"
  echo ---
done
echo 'end of $*'
for parameter in "$@"; do
  echo $parameter
  echo "$parameter"
  echo ---
done
echo 'end of $@'
--endoutput

--newpage bash_parameters_exercise
--heading Bash special parameters exercise
Write a script which will print out number of parameters and will print them out one per line.

for example: ./number.sh "a s d" a s d
will print out
4
a s d
a
s
d

--newpage DU2
--heading Home Work 2
Script which can list and count files in some directory. Script will be able to recognize file extension and directory.
List will print on stdout one file per line.
Count will print number on stdout (with end of line).
Script will be able to print usage.
Files means also directories - any type of file

Example:
script.sh list /home/rrakus .jpg
script.sh count /home/rrakus

--newpage references
--heading References
Bash Reference Manual
 bashref.pdf in bash-doc rpm
 http://www.gnu.org/software/bash/manual/bashref.html

Advanced Bash-Scripting Guide
 http://tldp.org/LDP/abs/html/

BASH Frequently Asked Questions (on Greg's Wiki)
 http://mywiki.wooledge.org/BashFAQ
 http://mywiki.wooledge.org/EnglishFrontPage

many others
