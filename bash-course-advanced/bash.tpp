--title Bash advanced
--author Roman Rakus <rrakus@redhat.com>
--date today
--fgcolor black
--bgcolor white

--## TODO:
--## advanced parameter expansion ${var:-par} etc.

--## IFS, PATH and maybe other shell variables

--## echo vs printf
--##  - long text with "" maybe others and var expansion
--##  - -e -n and other variable values

--## [[ ={=,~} ]] regexp pattern matching, BASH_REMATCH
--##  - match variable with some regexp
--##  - ???

--## read builtin - while read with < redirection, TMOUT
--## - use read, IFS=, == and =~ regexp matching
--## - ???

--## <() >() substitutions
--## - diff of two commands
--## - use read, IFS... and output of some command:
--##   while IFS= read... < <(command)

--## trap builtin
--##  - to catch some signal
--##  - to do something when exiting

--## debugging?
--##  - set -x
--##  - trap? LINENO
--##  - ???

--## Du - cetnost slov? cetnost znaku
--## du - neco jako basename, 

--newpage schedule
--heading Schedule
 * 3 lecters, each 3 hours long
 * 3rd lecture also for questions
 * Ask whenever you want
 * Course will consist of theory-example-exercise parts
 * 2 homeworks

--newpage agenda
--heading Agenda
 * Advanced parameter expansion
 * Shell variables - IFS, PATH, PIPESTATUS, FUNCNEST, GLOBIGNORE...
 * echo vs printf
 * Pattern matching in [[ expression ]]
 * read
 * Process substitution <() and >()
 * trap builtin
 * a bit of debugging

--newpage APE
--heading Advanced parameter expansion
Example: ${parameter:-word}
On word is performed
 * tilde expansion
 * parameter expansion
 * arithmetic expansion
 * command substituion

Nested quoting has unspecified effect
"${var:-"$var"}"

--newpage APE2
--heading Advanced parameter expansion II
--color red
${parameter:-word}
--color black
If parameter is unset or null, the expansion of word is substituted. Otherwise, the value of parameter is substituted.

Ommit colon and bash tests only for existence (unset).

--newpage APE2e
--heading Advanced parameter expansion II example
--beginoutput
a="set and have value"
b=

echo ${a:-"word used"}
echo ${b:-"word used"}
echo ${c:-"word used"}
echo ${a-"word used"}
echo ${b-"word used"}
echo ${c-"word used"}
--endoutput

--newpage APE2o
--heading Advanced parameter expansion II example output
--beginoutput
$ ./01-parameter-expansion1.sh
set and have value
word used
word used
set and have value

word used
--endoutput

--newpage APE3
--heading Advanced parameter expansion III
--color red
${parameter:=word}
--color black
If parameter unset or null, assign word to parameter. Substitute parameter.
In other words, assign if have not value and substitute.

Cannot use special parameters nor positional parameters to assign to.
Ommit colon and bash tests only for existence (unset).

--newpage APE3e
--heading Advanced parameter expansion III example
--beginoutput
unset a b c
a="set and have value"
b=

echo ${a:="word used"}
echo ${b:="word used"}
echo ${c:="word used"}

echo "$a" "$b" "$c"

unset a b c
a="set and have value"
b=

echo ${a-"word used"}
echo ${b-"word used"}
echo ${c-"word used"}

echo "$a" "$b" "$c"
--endoutput

--newpage APE3o
--heading Advanced parameter expansion III example output
--beginoutput
$ ./02-parameter-expansion2.sh
set and have value
word used
word used
set and have value word used word used
set and have value

word used
set and have value
--endoutput

--newpage APE4
--heading Advanced parameter expansion IV
--color red
${parameter:?word}
--color black
If parameter is unset (or null), on stderr print word message and shell exits. Otherwise parameter is substituted.

--newpage APE4e
--heading Advanced parameter expansion IV example
--beginoutput
echo "The 1st parameter is: ${1:?Parameter 1 is not set}"
echo "The 2nd parameter is: ${2:?}"
--endoutput

--newpage APE4o
--heading Advanced parameter expansion IV example output
--beginoutput
$ ./03-parameter-expansion3.sh
./03-parameter-expansion3.sh: line 2: 1: Parameter 1 is not set
$ ./03-parameter-expansion3.sh one
The 1st parameter is: one
./03-parameter-expansion3.sh: line 3: 2: parameter null or not set
$ ./03-parameter-expansion3.sh one two
The 1st parameter is: one
The 2nd parameter is: two
$ ./03-parameter-expansion3.sh one "" two
The 1st parameter is: one
./03-parameter-expansion3.sh: line 3: 2: parameter null or not set
--endoutput

--newpage APE5
--heading Advanced parameter expansion V
--color red
${parameter:offset}
${parameter:offset:length}
--color black
Substring expansion. Expands to string starting at offset with given length or till the end.
Length and offset are arithmetic expressions.
Negative offset - offset from the end of string
Negative length - second offset from the end, result is between 2 offsets
Can use indexed arrays and positional parameters

--newpage APE5e
--heading Advanced parameter expansion V example
--beginoutput
var="123456789" # string with length 9
arr=(1st 2nd 3rd 4th 5th 6th 7th 8th 9th) # indexed array with 9 elements
printf '[%s]\n' "${var:1:3}"
printf '[%s]\n' "${var: -4:3}"
printf '[%s]\n' "${var:1:-3}"
echo
printf '[%s]\n' "${arr[@]:1:3}"
printf '[%s]\n' "${arr[@]: -4:3}"
echo
printf '[%s]\n' "${@:1:3}"
printf '[%s]\n' "${@: -4:3}"
--endoutput

--newpage APE5o
--heading Advanced parameter expansion V example output
--beginoutput
$ ./04-parameter-expansion4.sh {a..z}
[234]
[678]
[23456]

[2nd]
[3rd]
[4th]
[6th]
[7th]
[8th]

[a]
[b]
[c]
[w]
[x]
[y]
--endoutput

--newpage APE6
--heading Advanced parameter expansion VI
--color red
${#parameter}
--color black
The length of parameter in characters.
Can use @ or * - number of positional parameters
Can use array with @ or * subscript - number of elements in array

--newpage APE6e
--heading Advanced parameter expansion VI example
--beginoutput
var="123456789" # string with length 9
arr=(1th 2th 3th 4th 5th 6th 7th 8th) # indexed array with 8 elements - how Red Hat number the floors
printf '[%s]\n' "${#var}"
printf '[%s]\n' "${#arr}" # length of the first element
printf '[%s]\n' "${#arr[@]}"
printf '[%s]\n' "${#@}"
--endoutput

--newpage APE6o
--heading Advanced parameter expansion VI example output
--beginoutput
$ ./05-parameter-expansion5.sh 'one parameter'
[9]
[3]
[8]
[1]
--endoutput

--newpage APE7
--heading Advanced parameter expansion VII
--color red
${!prefix*}
${!prefix@}
--color black
Expands to variable names beginning with prefix

--newpage APE8
--heading Advanced parameter expansion VIII
--color red
${!name[@]}
${!name[*]}
--color black
Expands to the list of array indices (keys)

--newpage APE9
--heading Advanced parameter expansion IX
--color red
${parameter#word}
${parameter##word}
--color black
* word expanded to produce pattern as in filename expansion
* result is deleted pattern from beginning of the parameter
* # is shortest match, ## is longest match
* Can use @ or * - positional parameters are used. Result is a list
* Can use array with @ or *

--newpage APE9e
--heading Advanced parameter expansion IX example
--beginoutput
var="foofoobarbaz"
printf '%s\n' "${var#foo}"
printf '%s\n' "${var##foo}"
printf '%s\n' "${var#*a}"
printf '%s\n' "${var##*a}"
printf '%s\n' "${@#?[a-c]*?}"
--endoutput

--newpage APE9o
--heading Advanced parameter expansion IX example output
--beginoutput
$ ./06-parameter-expansion6.sh a{b..f}ghi
foobarbaz
foobarbaz
rbaz
z
hi
hi
adghi
aeghi
afghi
--endoutput

--newpage APE10
--heading Advanced parameter expansion X
--color red
${parameter%word}
${parameter%word}
--color black
* similar to # and ##
* match the trailing portion

--newpage APE10e
--heading Advanced parameter expansion X example
--beginoutput
var="foofoobarbazbaz"
printf '%s\n' "${var%baz}"
printf '%s\n' "${var%%baz}"
printf '%s\n' "${var%o*}"
printf '%s\n' "${var%%o*}"
printf '%s\n' "${@%?*[a-c]*?}"
--endoutput

--newpage APE10o
--heading Advanced parameter expansion X example output
--beginoutput
$ ./07-parameter-expansion7.sh a{b..f}ghi
foofoobarbaz
foofoobarbaz
foofo
f


adghi
aeghi
afghi
--endoutput

--newpage APE11
--heading Advanced parameter expansion XI
--color red
${parameter/pattern/string}
--color black
* Replace pattern longest match with string on parameter
* Pattern is same like in filename expansion
* Pattern can specialy begin with:
  / - all matches are replaced
  # - must match beginning
  % - must match at the end
* Can use array substcipt * or @ to substitute all members of array

--newpage APE11e
--heading Advanced parameter expansion XI example
--beginoutput
var=foobarbazfoobarbaz
echo "${var/a/e}"
echo "${var/ar/eq}"
echo "${var/[obr]?[af]/X}"
echo "${var//a/e}"
echo "${var//ar/eq}"
echo "${var//o/e}"
echo "${var//[obr]?[af]/X}"
echo "${var/#foo/XXX}"
echo "${var/%foo/XXX}"
echo "${var/#baz/XXX}"
echo "${var/%baz/XXX}"
echo "${var/*o/X}"
--endoutput

--newpage APE11o
--heading Advanced parameter expansion XI example output
--beginoutput
$ ./08-parameter-expansion8.sh
fooberbazfoobarbaz
foobeqbazfoobarbaz
foXrbazfoobarbaz
fooberbezfooberbez
foobeqbazfoobeqbaz
feebarbazfeebarbaz
foXXzfoXXz
XXXbarbazfoobarbaz
foobarbazfoobarbaz
foobarbazfoobarbaz
foobarbazfoobarXXX
Xbarbaz
--endoutput

--newpage APE12
--heading Advanced parameter expansion XII
--color red
${parameter^pattern}
${parameter^^pattern}
${parameter,pattern}
${parameter,,pattern}
--color black
 * case modification on letters matching the pattern
 * pattern like in filename expansion
 * ^ to uppercase, only first letter. ^^ all letters
 * , to lowercase, only first letter. ,, all letters

--newpage APE12e
--heading Advanced parameter expansion XII example
--beginoutput
#!/bin/bash
var=foobarbazfoobarbaz
echo 'f:' "${var^f}"
echo 'b:' "${var^b}"
echo 'fb:' "${var^fb}"
echo '[fb]:' "${var^[fb]}"
echo 'fo:' "${var^fo}"
echo '*': "${var^*}"
echo 'f:' "${var^^f}"
echo 'b:' "${var^^b}"
echo 'fb:' "${var^^fb}"
echo '[fb]:' "${var^^[fb]}"
echo 'fo:' "${var^^fo}"
echo '*:' "${var^^*}"
--endoutput

--newpage APE12o
--heading Advanced parameter expansion XII example output
--beginoutput
$ ./09-parameter-expansion9.sh
f: Foobarbazfoobarbaz
b: foobarbazfoobarbaz
fb: foobarbazfoobarbaz
[fb]: Foobarbazfoobarbaz
fo: foobarbazfoobarbaz
*: Foobarbazfoobarbaz
f: FoobarbazFoobarbaz
b: fooBarBazfooBarBaz
fb: foobarbazfoobarbaz
[fb]: FooBarBazFooBarBaz
fo: foobarbazfoobarbaz
*: FOOBARBAZFOOBARBAZ
--endoutput

--newpage APE-ex
--heading Advanced parameter expansion exercise
--color green
TODO
--color black

--newpage SHV
--heading Shell variables
--color red
BASH_SOURCE BASH_LINENO BASHPID DIRSTACK FUNCNAME FUNCNEST GLOBIGNORE IFS LANG LC_ALL LC_COLLATE LC_CTYPE LC_MESSAGE LC_NUMERIC LINENO PATH PIPESTATUS PWD RANDOM SECONDS
--color black
 * if variable is unset it loses its special meaning, even if reset.
 * not all can be unset

--newpage SHV2
--heading Shell variables - BASHPID
--color red
BASHPID
--color black
Expands to process ID of the current bash process.
Different than $$, on subshell...

--newpage SHV2e
--heading Shell variables - BASHPID example
--beginoutput
#!/bin/bash
echo $BASHPID
echo $$
(
  echo $BASHPID
  echo $$
)
BASHPID=666
echo $BASHPID
--endoutput

--newpage SHV2o
--heading Shell variables - BASHPID example output
--beginoutput
$ ./10-bash-variables1.sh
27696
27696
27697
27696
27696
--endoutput

--newpage SHV3
--heading Shell variables - DIRSTACK
--color red
DIRSTACK
--color black
 * array containing directory stack
 * stack manipulated with pushd and popd builtins
 * can modify by assigning to array member
 * cannot add or remove without calling pushd, popd

--newpage SHV3e
--heading Shell variables - DIRSTACK example
--beginoutput
#!/bin/bash
printf '<%s>\n' "${DIRSTACK[@]}" "---"
pushd /tmp >/dev/null
pushd / > /dev/null
pushd /home > /dev/null
printf '<%s>\n' "${DIRSTACK[@]}" "---"
DIRSTACK[3]="/just/modified"
printf '<%s>\n' "${DIRSTACK[@]}" "---"
popd > /dev/null
popd > /dev/null
popd > /dev/null
printf '<%s>\n' "${DIRSTACK[@]}" "---"
--endoutput

--newpage SHV3o
--heading Shell variables - DIRSTACK example output
--beginoutput
$ ./11-bash-variables2.sh
<~/git/bash-talks/bash-course-advanced/scripts>
<--->
</home>
</>
</tmp>
</home/rrakus/git/bash-talks/bash-course-advanced/scripts>
<--->
</home>
</>
</tmp>
</just/modified>
<--->
./11-bash-variables2.sh: line 11: popd: /just/modified: No such file or directory
</tmp>
</just/modified>
<--->
--endoutput

--newpage SHV4
--heading Shell variables - FUNCNAME
--color red
FUNCNAME BASH_SOURCE BASH_LINENO
--color black
 * array variables
 * contains call stack of functions, source file names, line numbers
 * index 0 - current function executed
 * last index - main

--newpage SHV4e
--heading Shell variables - FUNCNAME example
--beginoutput
#!/bin/bash
f1() {
  for i in ${!FUNCNAME[@]}; do
    printf '%s at %s[%s]\n' "${FUNCNAME[$i]}" "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  echo '^^ f1 ^^'
  f2
}
f2() {
  for i in ${!FUNCNAME[@]}; do
    printf '%s at %s[%s]\n' "${FUNCNAME[$i]}" "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  echo '^^ f2 ^^'
}
f1 && echo ---
f2 && echo ---
--endoutput

--newpage SHV4o
--heading Shell variables - FUNCNAME example output
--beginoutput
$ ./12-bash-variables3.sh
f1 at ./12-bash-variables3.sh[15]
main at ./12-bash-variables3.sh[0]
^^ f1 ^^
f2 at ./12-bash-variables3.sh[7]
f1 at ./12-bash-variables3.sh[15]
main at ./12-bash-variables3.sh[0]
^^ f2 ^^
===
f2 at ./12-bash-variables3.sh[16]
main at ./12-bash-variables3.sh[0]
^^ f2 ^^
===
--endoutput

--newpage SHV5
--heading Shell variables - FUNCNEST
--color red
FUNCNEST
--color black
 * maximum function nesting
 * have to set it
 * value greater than 0

--newpage SHV5e
--heading Shell variables - FUNCNEST example
--beginoutput
#!/bin/bash
FUNCNEST=$1
printf 'FUNCNEST = %s\n' "$FUNCNEST"
f()
{
 ((i++))
 f
}
i=0
f
printf 'Nested %d times\n' "$i"
--endoutput

--newpage SHV5o
--heading Shell variables - FUNCNEST example output
--beginoutput
$ ./13-bash-variables4.sh
FUNCNEST = 
Segmentation fault

$ ./13-bash-variables4.sh 5
FUNCNEST = 5
./13-bash-variables4.sh: line 7: f: maximum function nesting level exceeded (5)
Nested 5 times
--endoutput

--newpage SHV6
--heading Shell variables - GLOBIGNORE
--color red
GLOBIGNORE
--color black
 * colon separated list of patterns
 * filename expansion ignores files matched by defined patterns

--newpage SHV6e
--heading Shell variables - GLOBIGNORE example
--beginoutput
#!/bin/bash
echo "GLOBIGNORE = $GLOBIGNORE"
printf '<%s>\n' 0*
GLOBIGNORE=*2.sh:*4*.sh
echo "GLOBIGNORE = $GLOBIGNORE"
printf '<%s>\n' 0*
--endoutput

--newpage SHV6o
--heading Shell variables - GLOBIGNORE example output
--beginoutput
$ ./14-bash-variables5.sh
GLOBIGNORE = 
<01-parameter-expansion1.sh>
<02-parameter-expansion2.sh>
<03-parameter-expansion3.sh>
<04-parameter-expansion4.sh>
<05-parameter-expansion5.sh>
<06-parameter-expansion6.sh>
<07-parameter-expansion7.sh>
<08-parameter-expansion8.sh>
<09-parameter-expansion9.sh>
GLOBIGNORE = *2.sh:*4*.sh
<01-parameter-expansion1.sh>
<03-parameter-expansion3.sh>
<05-parameter-expansion5.sh>
<06-parameter-expansion6.sh>
<07-parameter-expansion7.sh>
<08-parameter-expansion8.sh>
<09-parameter-expansion9.sh>
--endoutput

--newpage SHV7
--heading Shell variables - IFS
--color red
IFS
--color black
 * internat field separator
 * each character is used for splitting
 * used during word splitting
 * on parameter expansion, command substitution, arithmetic expansion
 * on unquoted with double quotes
 * Beware filename expansion!

--newpage SHV7e
--heading Shell variables - IFS example
--beginoutput
#!/bin/bash

p()
{
  printf 'IFS=%q\n' "$IFS"
  printf '<%s>' "$@"
  echo
}

v="a  b- c.* ..d"
p $(date)
p $v
p $((2**10 + 21))

IFS='.0:'
p $(date)
p $v
p $((2**10 + 21))

p "$(date)"
p "$v"
p "$((2**10 + 21))"
--endoutput

--newpage SHV7o
--heading Shell variables - IFS example output
--beginoutput
$ ./15-bash-variables6.sh
IFS=$' \t\n'
<Sun><Dec><2><16:14:36><CET><2012>
IFS=$' \t\n'
<a><b-><c.*><..d>
IFS=$' \t\n'
<1045>
IFS=.0:
<Sun Dec  2 16><14><36 CET 2><12>
IFS=.0:
<a  b- c><* ><><d>
IFS=.0:
<1><45>
IFS=.0:
<Sun Dec  2 16:14:36 CET 2012>
IFS=.0:
<a  b- c.* ..d>
IFS=.0:
<1045>
--endoutput

--newpage SHV8
--heading Shell variables - LANG LC_*
--color red
LANG LC_ALL LC_COLLATE LC_CTYPE LC_MESSAGE LC_NUMERIC
--color black
Bash locale settings.
LANG - Used when category in LC_ not specified
LC_ALL - overrides LANG and all LC_
LC_COLLATE - collation order - mainly sorting filename expansion
LC_CTYPE - character classes in filename expansion and pattern matching
LC_MESSAGES - settings for $"" strings translations
LC_NUMERIC - number formatting

external programs also have locale specifications

--newpage SHV8e
--heading Shell variables - LANG LC_* example
--beginoutput
p() {
  printf '%s\n' "$1"; shift
  printf ' %s' "$@" $'\n'
}
pf() {
  printf '%s\n' "$1"; shift
  printf "%s\n" "$@"
  printf "%'.2f\n" "$@"
}
rm -rf /tmp/collate/; mkdir -p /tmp/collate/
pushd /tmp/collate >/dev/null
  touch {A..Z} {a..z} {и,ф,р} {č,Č,ň,ů,ü,ch}
  LC_COLLATE=C; p "LC_COLLATE = $LC_COLLATE" *
  LC_COLLATE=cs_CZ.utf8; p "LC_COLLATE = $LC_COLLATE" *
  LC_CTYPE=C; p "LC_CTYPE = $LC_CTYPE" [[:lower:]]
  LC_CTYPE=cs_CZ.utf8; p "LC_CTYPE = $LC_CTYPE" [[:lower:]]
  LC_NUMERIC=C; pf "LC_NUMERIC = $LC_NUMERIC" 1234567.89
  LC_NUMERIC=cs_CZ.utf8; pf "LC_NUMERIC = $LC_NUMERIC" 1234567,89
popd >/dev/null
--endoutput

--newpage SHV8o
--heading Shell variables - LANG LC_* example output
--beginoutput
$ ./16-bash-variables7.sh
LC_COLLATE = C
 A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c ch d e f g h i j k l m n o p q r s t u v w x y z ü Č č ň ů и р ф 
LC_COLLATE = cs_CZ.utf8
 a A b B c C č Č d D e E f F g G h H ch i I j J k K l L m M n N ň o O p P q Q r R s S t T u U ů ü v V w W x X y Y z Z и р ф 
LC_CTYPE = C
 a b c d e f g h i j k l m n o p q r s t u v w x y z 
LC_CTYPE = cs_CZ.utf8
 a b c č d e f g h i j k l m n ň o p q r s t u ů ü v w x y z и р ф 
LC_NUMERIC = C
1234567.89
1234567.89
LC_NUMERIC = cs_CZ.utf8
1234567,89
1 234 567,89
--endoutput

--newpage SHV9
--heading Shell variables - LINENO
--color red
LINENO
--color black
The line number in the script or shell function currently executing

--newpage SHV9e
--heading Shell variables - LINENO example
--beginoutput
echo 'START LINENO = '$LINENO

f1() {
echo 'f1 LINENO = '$LINENO
}

f2() {
echo 'f2 LINENO = '$LINENO
}
f1;f2
echo 'END LINENO = '$LINENO
--endoutput

--newpage SHV9o
--heading Shell variables - LINENO example output
--beginoutput
$ ./17-bash-variables8.sh
START LINENO = 2
f1 LINENO = 5
f2 LINENO = 9
END LINENO = 12
--endoutput

--newpage SHV10
--heading Shell variables - PATH
--color red
PATH
--color black
 * colon-separated list of directories
 * bash looks for commands in those directories
 * null length indicates current directory
 * bash uses hash table
 * changing PATH will clear hash

--newpage SHV10e
--heading Shell variables - PATH example
--beginoutput
#!/bin/bash
dir=/tmp/pathtest
rm -rf "$dir"; mkdir -p "$dir"; touch "$dir"/a
opath=$PATH
ppath()
{
  printf 'PATH:\n'
  printf '%s\n' "$PATH"
}

ppath; ls "$dir"
hash; type ls
PATH='/:~/bin'
hash; type ls
ppath; ls "$dir"
hash; type ls
PATH=$opath
hash; type ls
ppath; ls "$dir"
hash; type ls
--endoutput

--newpage SHV10o
--heading Shell variables - PATH example output
--beginoutput
PATH:
/usr/lib64/qt-3.3/bin:/usr/kerberos/sbin:/usr/kerberos/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:/home/rrakus/cov-sa-linux64-5.4.0/bin:/home/rrakus/bin:/home/rrakus/cov-sa-linux64-5.4.0/bin
a
hits    command
   1    /bin/rm
   1    /bin/touch
   1    /bin/mkdir
   1    /bin/ls
ls is hashed (/bin/ls)
hash: hash table empty
PATH:
/:~/bin
hash: hash table empty
hash: hash table empty
ls is /bin/ls
PATH:
/usr/lib64/qt-3.3/bin:/usr/kerberos/sbin:/usr/kerberos/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin:/home/rrakus/cov-sa-linux64-5.4.0/bin:/home/rrakus/bin:/home/rrakus/cov-sa-linux64-5.4.0/bin
a
hits    command
   1    /bin/ls
ls is hashed (/bin/ls)
--endoutput

--newpage SHV11
--heading Shell variables - PIPESTATUS
--color red
PIPESTATUS
--color black
 * array variable
 * list of exit statuses of most recent foreground processes of pipeline
 * single command is also a pipeline

--newpage SHV11e
--heading Shell variables - PIPESTATUS example
--beginoutput
p()
{
  printf '%s\n' "PIPESTATUS:"
  printf '%s\n' "$@"
  printf '%s\n' "++++"
}

p "${PIPESTATUS[@]}"
ls | sort | uniq | grep -q file | wc -l
p "${PIPESTATUS[@]}"
true | false | true | /not/a/command | true
p "${PIPESTATUS[@]}"
printf '%q\n' $(head -n66 /dev/urandom) | head -n1 | cat | sort | uniq | wc -l
p "${PIPESTATUS[@]}"
--endoutput

--newpage SHV11o
--heading Shell variables - PIPESTATUS example output
--beginoutput
PIPESTATUS:

++++
0
PIPESTATUS:
0
0
0
1
0
++++
PIPESTATUS:
0
1
0
127
0
++++
1
PIPESTATUS:
141
0
0
0
0
0
++++
--endoutput

--newpage SHV12
--heading Shell variables - PWD
--color red
PWD
--color black
 * current working directory
 * set by cd builtin (also pushd, ...)

--newpage SHV12e
--heading Shell variables - PWD example
--beginoutput
#!/bin/bash
p() {
  printf 'PWD: %s\n' "$PWD"
}
p
pushd "$HOME"
  p
popd
cd /etc
p
cd -
p
--endoutput

--newpage SHV12o
--heading Shell variables - PWD example output
--beginoutput
$ ./20-bash-variables11.sh
PWD: /home/rrakus/git/bash-talks/bash-course-advanced/scripts
~ ~/git/bash-talks/bash-course-advanced/scripts
PWD: /home/rrakus
~/git/bash-talks/bash-course-advanced/scripts
PWD: /etc
/home/rrakus/git/bash-talks/bash-course-advanced/scripts
PWD: /home/rrakus/git/bash-talks/bash-course-advanced/scripts
--endoutput

--newpage SHV13
--heading Shell variables - RANDOM
--color red
RANDOM
--color black
 * generates random number (0..32767) each time referenced
 * assigning a value seeds RNG

--newpage SHV13e
--heading Shell variables - RANDOM example
--beginoutput
#!/bin/bash
p() {
  printf 'RANDOM: %d\n' "$RANDOM"
}

(($1)) && RANDOM="$1"
p && p
--endoutput

--newpage SHV13o
--heading Shell variables - RANDOM example output
--beginoutput
$ ./21-bash-variables12.sh
RANDOM: 17763
RANDOM: 2427
$ ./21-bash-variables12.sh
RANDOM: 1246
RANDOM: 8837
$ ./21-bash-variables12.sh 666
RANDOM: 19574
RANDOM: 22353
$ ./21-bash-variables12.sh 666
RANDOM: 19574
RANDOM: 22353
--endoutput

--newpage SHV14
--heading Shell variables - SECONDS
--color red
SECONDS
--color black
 * number of seconds since bash started
 * assigning sets counter
  * value then is assigned value plus seconds since assignment
 * unsetting will remove special meaning

--newpage SHV14e
--heading Shell variables - SECONDS example
--beginoutput
#!/bin/bash
p() {
  printf 'SECONDS: %d\n' "$SECONDS"
}

p
sleep 2; p
sleep 2; p
SECONDS=666; p
sleep 2; p
sleep 2; p
unset SECONDS
SECONDS=666; p
sleep 2; p
--endoutput

--newpage SHV14o
--heading Shell variables - SECONDS example output
--beginoutput
$ ./22-bash-variables13.sh
SECONDS: 0
SECONDS: 2
SECONDS: 4
SECONDS: 666
SECONDS: 668
SECONDS: 670
SECONDS: 666
SECONDS: 666
--endoutput

--newpage EVSP
--heading echo vs printf
--color red
echo "$var"
printf '%s\n' "$var"
--color black
echo
 * useful only for basic printing
 * is very simple
 * don't use for values you don't know

printf
 * rather use exclusively
 * you have 100% control of expansions
 * is not that much simple
 * portable

--newpage EVSP1e
--heading echo vs printf example
--beginoutput
#!/bin/bash
_echo()
{
  echo "$@"
}

_printf()
{
  printf '%s\n' "$@"
}
echo ECHO:
_echo "$@"
echo PRINTF:
_printf "$@"
--endoutput

--newpage EVSP1o
--heading echo vs printf example output
--beginoutput
$ ./23-echovsprintf1.sh
ECHO:

PRINTF:

$ ./23-echovsprintf1.sh '-e' '-n' 'WTF?'
ECHO:
WTF?PRINTF:
-e
-n
WTF?
--endoutput

--newpage EVSP2
--heading echo vs printf - printf
--color red
printf [-v var] format [arguments]
--color black
 * very similar to C-like printf
 * along with printf(1) formats also %b, %q, %(datefmt)T
 * format is reused to consume all arguments
 * if format requires more arguments than null value used (or 0)
 * -v only assings output to variable var

 %b - allow to expand backslash escape sequences
 %q - variable printed in format that can be reused as input
 %(datefmt)T - datetime string strftime(3) format
             - argument is number of seconds since the epoch
             - or -1 is current time
             - and -2 is time the shell was invoked

--newpage EVSP2e
--heading echo vs printf - printf example 1
--beginoutput
#!/bin/bash
printf '%s\n' "$@"
--endoutput

--newpage EVSP2o
--heading echo vs printf - printf example 1 output
--beginoutput
$ ./24-echovsprintf2.sh these are just 'simple strings'
these
are
just
simple strings
$ ./24-echovsprintf2.sh $(head -1 /dev/urandom)
%:�X����&%v�
--endoutput

--newpage EVSP3e
--heading echo vs printf - printf example 2
--beginoutput
#!/bin/bash
printf '%q\n' "$@"
--endoutput

--newpage EVSP3o
--heading echo vs printf - printf example 2 output
--beginoutput
$ ./25-echovsprintf3.sh 'String' 'number:' '666' 'escaped:' '^C        ^D'
String
number:
666
escaped:
$'\003\t\004'
$ ./25-echovsprintf3.sh $(head -1 /dev/urandom)
$'lAo\217\\\320\274\004[d'
--endoutput

--newpage EVSP4e
--heading echo vs printf - printf example 3
--beginoutput
#!/bin/bash
red='\e[0;31m'
green='\e[0;32m'
off='\e[0m'

printf 'RED: %b%s%b\n' "$red" "$1" "$off"
printf 'GREEN: %b%s%b\n' "$green" "$1" "$off"
printf '%s\n' ++++
printf 'RED no-off: %b%s\n' "$red" "$1"
printf 'GREEN no-off: %b%s\n' "$green" "$1"
printf '%s\n' ++++
--endoutput

--newpage EVSP4o
--heading echo vs printf - printf example 3 output
--beginoutput
$ ./26-echovsprintf4.sh blablabla
RED: blablabla
GREEN: blablabla
++++
RED no-off: blablabla
GREEN no-off: blablabla
++++
--endoutput

--newpage EVSP5e
--heading echo vs printf - printf example 4
--beginoutput
#!/bin/bash
var="some text"

printf 'Print text in quotes "%s"\n' "$var"
--endoutput

--newpage EVSP5o
--heading echo vs printf - printf example 4 output
--beginoutput
$ ./27-echovsprintf5.sh
Print text in quotes "some text"
--endoutput

--newpage EVSP6e
--heading echo vs printf - printf example 5
--beginoutput
#!/bin/bash
long1=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
long2=bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
long3=645873458735873548736458763845.72456345

printf 'Tabular example\n'
printf '%-15s%-15s%15s\n' Name Surname Value
printf '%-15s%-15s%15s\n' ~~~~~ ~~~~~ ~~~~~
printf '%-15s%-15s%15.2f\n' Roman Rakus 123.456
printf '%-15s%-15s%15.2f\n' Karel Gott  678
printf '%-15s%-15s%15.2f\n' Xyz a
printf '%-15s%-15s%15.2f\n' '' '' ''
printf '%-15s%-15s%15.2f\n' "$long1" "$long2" "$long3"
--endoutput

--newpage EVSP6o
--heading echo vs printf - printf example 5 output
--beginoutput
$ ./28-echovsprintf6.sh
Tabular example
Name           Surname                  Value
~~~~~          ~~~~~                    ~~~~~
Roman          Rakus                   123.46
Karel          Gott                    678.00
Xyz            a                         0.00
                                         0.00
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb645873458735873548740653481984.00
--endoutput

--newpage PME
--heading Extended pattern matching
--color red
[[ expr == pattern ]]
[[ expr != pattern ]]
[[ expr =~ extended pattern ]]
BASH_REMATCH
--color black

 * Word splitting not performed
 * Filename expansion not performed
 * pattern is same like in filename expansion
 * extended pattern same as in regex(3)

--newpage PME1
--heading Extended pattern matching == !=
 * return value 0 if matched, 1 otherwise
 * part of pattern can be quoted - forces to match a string

--newpage PME1e
--heading Extended pattern matching == != example
--beginoutput
#!/bin/bash
if [[ $1 == ?a*U"?*[abc]" ]]; then
  echo MATCH
else
  echo NOT MATCH
fi
--endoutput

--newpage PME1o
--heading Extended pattern matching == != example output
--beginoutput
$ ./29-patmatch1.sh '?a*U"?*[abc]"'
NOT MATCH

$ ./29-patmatch1.sh '?a*U?*[abc]'
MATCH

$ ./29-patmatch1.sh 'zasdvdU?*[abc]'
MATCH

$ ./29-patmatch1.sh 'zasdvdUdsdfsdfa'
NOT MATCH
--endoutput

--newpage PME2
--heading Extended pattern matching =~
 * uses regex(3)
 * pattern matching described in regex(7)
 * parenthesized subexpressions' matches stored in BASH_REMATCH
 * BASH_REMATCH[0] is portion of the string matching the entire regexp
 return value
   0 - matched
   1 - not matched
   2 - syntax error in rexexp

--newpage PME2e
--heading Extended pattern matching =~ example
--beginoutput
#!/bin/bash
re_alnum='^[[:blank:]]*([[:alnum:]]+)[[:blank:]]*'
if [[ $1 =~ $re_alnum ]]; then
  printf 'MATCH: %s\n' "${BASH_REMATCH[1]}"
else
  echo NOT MATCH
fi
--endoutput

--newpage PME2o
--heading Extended pattern matching =~ example output
--beginoutput
$ ./30-patmatch2.sh
NOT MATCH

$ ./30-patmatch2.sh 'hello'
MATCH: hello

$ ./30-patmatch2.sh 'hello world'
MATCH: hello
--endoutput

--newpage PME3e
--heading Extended pattern matching =~ example 2
--beginoutput
#!/bin/bash
re_alnum='([[:alpha:]]+):[[:blank:]]*([[:digit:]]+)'
if [[ $1 =~ $re_alnum ]]; then
  printf 'MATCH\n'
  printf 'String portion: <%s>\n' "${BASH_REMATCH[1]}"
  printf 'Number portion: <%d>\n' "${BASH_REMATCH[2]}"
  printf 'This matched entire regexp: <%s>\n' "${BASH_REMATCH[0]}"
else
  printf '<%s> does not match <%s>\n' "$1" "$re_alnum"
fi
--endoutput

--newpage PME3o
--heading Extended pattern matching =~ example 2 output
--beginoutput
$ ./31-patmatch3.sh 'Hello'
<Hello> does not match <([[:alpha:]]+):[[:blank:]]*([[:digit:]]+)>

$ ./31-patmatch3.sh 'a:3'
MATCH
String portion: <a>
Number portion: <3>
This matched entire regexp: <a:3>

$ ./31-patmatch3.sh '123a:3asd'
MATCH
String portion: <a>
Number portion: <3>
This matched entire regexp: <a:3>
--endoutput

--newpage READ1
--heading read builtin
--color red
read [-ers] [-a aname] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]
--color black
 * read line from stdin
 * 1st word assigned to 1st name, 2nd word to 2nd name...
 * leftover words assigned to last name
 * to leftover names assigned empty values
 * IFS used to split words
 * \ removes special meaning
 * return status
  * 0
  * 1 when EOF
  * >128 on timeout
  * not 0 on invalid fd in -u option

--newpage READ2
--heading read builtin - options
-a aname
 * words assigned to indices of array aname
 * starting from 0
 * elements of aname array are removed
 * name arguments are ignored

-d delim
 * the first char of delim is used to terminat input line, rather than newline

-e
 * use readline to obtain the line

--newpage READ3
--heading read builtin - options cont.
-i text
 * If Readline is being used to read the line, text is placed into the editing buffer before editing begins.

-n nchars
 * returns after reading nchars
 * but honor a delimiter

-N nchars
 * read exactly nchars characters
 * can stop on EOF or timeout

-p prompt
 * display prompt before reading
 * only on terminal input

--newpage READ4
--heading read builtin - options cont.
-r
 * backslash has no special meaning

-s
 * silent mode, only on terminal
 * characters are not echoed

-t timeout
 * fail if complete line is not read within timeout
 * only when readin from terminal, pipe or other special files
 * no effect when reading from regular file

-u fd
 * read from file descriptor fd

--newpage READ5e
--heading read builtin example
--beginoutput
#!/bin/bash
read -p 'Name: ' name
read -p 'Surname: ' surname
read -p 'Age: ' age

printf 'Your name is %s %s and you are %d age old\n' "$name" "$surname" "$age"
--endoutput

--newpage READ5o
--heading read builtin example output
--beginoutput
$ ./32-read1.sh
Name: Roman
Surname: Rakus
Age: 29
Your name is Roman Rakus and you are 29 age old

$ ./32-read1.sh
Name: \t\r\n
Surname: \a\b\c
Age: 1
Your name is trn abc and you are 1 age old
--endoutput

--newpage READ6e
--heading read builtin example 2
--beginoutput
#!/bin/bash
while read -r name surname age
do
  printf 'Your name is %s %s and you are %d age old\n' "$name" "$surname" "$age"
done < 01-readdata
--endoutput

--newpage READ6o
--heading read builtin example 2 output
--beginoutput
$ ./33-read2.sh
Your name is Roman Rakus and you are 29 age old
Your name is \t\r\n \a\b\c and you are 1 age old
./33-read2.sh: line 4: printf: 1 2 3 4: invalid number
Your name is more numbers and you are 1 age old
Your name is without number and you are 0 age old
Your name is nothing follows and you are 0 age old
Your name is   and you are 0 age old
--endoutput

--newpage READ7e
--heading read builtin example 3 example
--beginoutput
#!/bin/bash
while IFS=: read -r name surname age
do
  printf 'field1:<%q> field2:<%q> field3<%d>\n' "$name" "$surname" "$age"
done < 02-readdata
--endoutput

--newpage READ7o
--heading read builtin example 3 example output
--beginoutput
field1:<Roman> field2:<Rakus> field3<29>
field1:<a\ b\ c> field2:<\ tururu> field3<3>
field1:<''> field2:<''> field3<0>
field1:<$' \t'> field2:<$' \t'> field3<1>
--endoutput

--newpage READ8e
--heading read builtin example 4 example
--beginoutput
#!/bin/bash
re_bash_line_comment='^[[:blank:]]*#(.*)$'
while IFS= read -r line
do
  if [[ $line =~ $re_bash_line_comment ]]; then
    continue
  else
    printf '%s\n' "$line"
  fi
done
--endoutput

--newpage READ8o
--heading read builtin example 4 example output
--beginoutput
$ ./35-read4.sh < /etc/fstab

UUID=20c39450-6284-43e6-a21d-955933c32b0f /                       ext4    defaults        1 1
UUID=83e816c6-a297-4163-beb1-03debd6298d6 /boot                   ext4    defaults        1 2
UUID=9741ba0d-53fe-43e8-b0ee-ba89dfbdb427 /home                   ext4    defaults        1 2
UUID=a276fe29-606f-4176-95e6-2e167491d085 swap                    swap    defaults        0 0
--endoutput

--newpage PSUB1
--heading Process substitution
--color red
<(list)
>(list)
--color black
 * some form of temporary file
 * uses named pipe (FIFO) or file in /dev/fd
 * the result is file name (fifo, or fd)
 * >(list) - writing to file will provide stdin for list
 * <(list) - file will contain output of list

--newpage PSUB1e
--heading Process substitution 1 example
--beginoutput
#!/bin/bash
echo <(echo hi)
cat <(echo hi)

tar cf >(bzip2 -c > ./scripts.tar.bz2) *.sh
--endoutput

--newpage PSUB1o
--heading Process substitution 1 example output
--beginoutput
$ ./36-psub1.sh
/dev/fd/63
hi
--endoutput
And file ./scripts.tar.bz2 contains compressed all shell files

--newpage PSUB2e
--heading Process substitution 2 example
--beginoutput
#!/bin/bash
# Show differences between output of 2 programs
pn=bash-4.2-coverity.patch
f1=~/koji/bash/bash.spec
f2=~/brew/bash/bash.spec
diff -up <(grep -n "$pn" "$f1") <(grep -n "$pn" "$f2")
--endoutput

--newpage PSUB2o
--heading Process substitution 2 example output
--beginoutput
 $ ./37-psub2.sh
 --- /dev/fd/63  2013-01-20 19:04:02.067758355 +0100
 +++ /dev/fd/62  2013-01-20 19:04:02.067758355 +0100
 @@ -1 +0,0 @@
 -98:Patch121: bash-4.2-coverity.patch
--endoutput

--newpage PSUB3e
--heading Process substitution 3 example
--beginoutput
#!/bin/bash
# Process output from some program
re_patch='^%patch([[:digit:]]+)[[:space:]]+(.*)'
declare -a patches
while IFS= read -r line
do
#  echo $line
  if [[ $line =~ $re_patch ]]; then
    i="${BASH_REMATCH[1]}"
    opts="${BASH_REMATCH[2]}"
    patches["$((10#$i))"]="$opts"
  fi
done < <(grep -- '\%' ~/koji/bash/bash.spec)

for i in "${!patches[@]}"; do
  printf 'Patch number %d with options <%s>\n' "$i" "${patches[$i]}"
done
--endoutput

--newpage PSUB3o
--heading Process substitution 3 example output
--beginoutput
$ ./38-psub3.sh
Patch number 1 with options <-p0 -b .001>
Patch number 2 with options <-p0 -b .002>
Patch number 3 with options <-p0 -b .003>
Patch number 4 with options <-p0 -b .004>
Patch number 5 with options <-p0 -b .005>
Patch number 6 with options <-p0 -b .006>
Patch number 7 with options <-p0 -b .007>
Patch number 8 with options <-p0 -b .008>
Patch number 9 with options <-p0 -b .009>
Patch number 10 with options <-p0 -b .010>
Patch number 11 with options <-p0 -b .011>
Patch number 12 with options <-p0 -b .012>
Patch number 13 with options <-p0 -b .013>
Patch number 14 with options <-p0 -b .014>
Patch number 15 with options <-p0 -b .015>
...
--endoutput

--newpage TRAP1
--heading trap builtin
--color red
trap [-lp] [arg] [sigspec ...]
--color black
 * arg is read and executed when signal sigspec is received
 * sigspec is signal number or signal name

options
 -l => list signal names and numbers
 -p sigspec => display commands
 -p or none => print commands, may be reused as bash input

--newpage TRAP2
--heading trap builtin cont.
--color red
trap [-lp] [arg] [sigspec ...]
--color black
sigspec is 0 or EXIT
 * arg is executed on shell exit

sigspec is DEBUG
 * arg executed before every simple command, for, case, select, function
 * shopt option extdebug

sigspec is RETURN
 * arg executed when function or shell sourced finishes

sigspec is ERR
 * arg executed when simple command has non-zero exit status
 * not for command in until, while, if, elif, && || list, ! inversion

--newpage TRAP3e
--heading trap builtin 3 example
--beginoutput
#!/bin/bash
trapfpe()
{
  printf 'Floating point exception catched\n'
}

trapterm()
{
  printf 'No no, try harder\n'
}

trap 'trapfpe' SIGFPE
trap 'trapterm' SIGTERM SIGINT
printf 'List of trapped signals:\n'
trap
printf 'Send SIGFPE or SIGTERM to process ID %d\n' "$$"
while :; do
  sleep 9999&
  printf 'Sleep process ID %d\n' "$!"
  wait
done
--endoutput

--newpage TRAP3o
--heading trap builtin 3 example output
--beginoutput
$ ./39-trap1.sh
List of trapped signals:
trap -- 'trapterm' SIGINT
trap -- 'trapfpe' SIGFPE
trap -- 'trapterm' SIGTERM
Send SIGFPE or SIGTERM to process ID 29184
Sleep process ID 29185
^CNo no, try harder
Sleep process ID 29210
^CNo no, try harder
Sleep process ID 29229
Killed
--endoutput

--newpage TRAP4e
--heading trap builtin 4 example
--beginoutput
#!/bin/bash
tempfile=$(mktemp)
clean(){
  printf 'Cleaning\n'
  rm -rf "$tempfile"
}
trap clean EXIT
file "$tempfile"
printf "I'm doing anything\n"
sleep 5
printf "I'm done\n"
--endoutput

--newpage TRAP4o
--heading trap builtin 4 example output
--beginoutput
$ ./40-trap2.sh
/tmp/tmp.mI3WaaUs5H: empty
I'm doing anything
I'm done
Cleaning

$ ./40-trap1.sh
/tmp/tmp.J883MAujFU: empty
I'm doing anything
^CCleaning
--endoutput

--newpage DEBUG1
--heading Debugging
Some usefull tips how to debug
 * set -x
 * set -v
 * trap DEBUG
 * LINENO, BASH_LINENO, BASH_SOURCE, FUNCNAME

--newpage DEBUG2e
--heading Debugging example
--beginoutput
#!/bin/bash
val=0
fce()
{
  local i
  for i in "${!BASH_SOURCE[@]}"; do
    printf '%s[%d]<-' "${BASH_SOURCE[$i]}" "${BASH_LINENO[$i]}"
  done
  printf '\nval = %s\n' "$val"
} >&2
trap 'fce "$LINENO"' DEBUG

for i in a b c
do
  ((++val))
  echo "$i"
done
--endoutput

--newpage DEBUG2o
--heading Debugging example output
--beginoutput
$ ./41-debug1.sh >/dev/null
./41-debug1.sh[13]<-./41-debug1.sh[0]<-
val = 0
./41-debug1.sh[15]<-./41-debug1.sh[0]<-
val = 0
./41-debug1.sh[16]<-./41-debug1.sh[0]<-
val = 1
./41-debug1.sh[13]<-./41-debug1.sh[0]<-
val = 1
./41-debug1.sh[15]<-./41-debug1.sh[0]<-
val = 1
./41-debug1.sh[16]<-./41-debug1.sh[0]<-
val = 2
./41-debug1.sh[13]<-./41-debug1.sh[0]<-
val = 2
./41-debug1.sh[15]<-./41-debug1.sh[0]<-
val = 2
./41-debug1.sh[16]<-./41-debug1.sh[0]<-
val = 3
--endoutput

