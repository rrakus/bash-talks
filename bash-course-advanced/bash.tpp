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
--##  - trap?
--##  - ???

--## Du - cetnost slov? cetnost znaku
--## du - neco jako basename, 

--newpage schedule
--heading Schedule
 * 2 lecters, each 3 hours long
 * 3rd lecture for questions
 * Ask whenever you want
 * Course will consist of theory-example-exercise parts
 * 2 homeworks

--newpage agenda
--heading Agenda
 * Advanced parameter expansion
 * Shell variables - IFS, PATH, PIPESTATUS, FUNCNEST, GLOBIGNORE...
 * echo vs printf
 * Pattern matching in [[ expression ]]
 * read, mapfile builtins
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
--heading Shell variables - LANG LC_*
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
--heading Shell variables - LANG LC_*
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

