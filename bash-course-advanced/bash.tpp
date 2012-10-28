--title Bash advanced
--author Roman Rakus <rrakus@redhat.com>
--date today
--fgcolor black
--bgcolor white

--## TODO:
--## advanced parameter expansion ${var:-par} etc.
--## IFS, PATH and maybe other shell variables
--## echo vs printf
--## [[ ={=,~} ]] regexp pattern matching, BASH_REMATCH
--## read builtin - while read with < redirection, TMOUT
--## <() >() substitutions
--## trap builtin
--## debugging?

--newpage agenda
--heading Agenda
 * Advanced parameter expansion
 * Shell variables - IFS, PATH, PIPESTATUS, FUNCNEST, GLOBIGNORE
 * echo vs printf
 * Pattern matching in [[ expression ]]
 * read, mapfile builtins
 * Process substitution <() and >()
 * trap builtin
 * a bit of debugging

--newpage advanced_parameter_expansion
--heading Advanced parameter expansion
Example: ${parameter:-word}
On word is performed
 * tilde expansion
 * parameter expansion
 * arithmetic expansion
 * command substituion

Nested quoting has unspecified effect
"${var:-"$var"}"

--newpage advanced_parameter_expansion_2
--heading Advanced parameter expansion II
--color red
${parameter:-word}
--color black
If parameter is unset or null, the expansion of word is substituted. Otherwise, the value of parameter is substituted.

Ommit colon and bash tests only for existence (unset).

--newpage advanced_parameter_expansion_2_example
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

--newpage advanced_parameter_expansion_2_example_output
--heading Advanced parameter expansion II example output
--beginoutput
$ ./01-parameter-expansion1.sh
set and have value
word used
word used
set and have value

word used
--endoutput

--newpage advanced_parameter_expansion_3
--heading Advanced parameter expansion III
--color red
${parameter:=word}
--color black
If parameter unset or null, assign word to parameter. Substitute parameter.
In other words, assign if have not value and substitute.

Cannot use special parameters nor positional parameters to assign to.
Ommit colon and bash tests only for existence (unset).

--newpage advanced_parameter_expansion_3_example
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

--newpage advanced_parameter_expansion_3_example output
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

--newpage advanced_parameter_expansion_4
--heading Advanced parameter expansion IV
--color red
${parameter:?word}
--color black
If parameter is unset (or null), on stderr print word message and shell exits. Otherwise parameter is substituted.

--newpage advanced_parameter_expansion_4_example
--heading Advanced parameter expansion IV example
--beginoutput
echo "The 1st parameter is: ${1:?Parameter 1 is not set}"
echo "The 2nd parameter is: ${2:?}"
--endoutput

--newpage advanced_parameter_expansion_4_example output
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

--newpage advanced_parameter_expansion_5
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

--newpage advanced_parameter_expansion_5_example
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

--newpage advanced_parameter_expansion_5_example output
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

--newpage advanced_parameter_expansion_6
--heading Advanced parameter expansion VI
--color red
${#parameter}
--color black
The length of parameter in characters.
Can use @ or * - number of positional parameters
Can use array with @ or * subscript - number of elements in array

--newpage advanced_parameter_expansion_6_example
--heading Advanced parameter expansion VI example
--beginoutput
var="123456789" # string with length 9
arr=(1th 2th 3th 4th 5th 6th 7th 8th) # indexed array with 8 elements - how Red Hat number the floors
printf '[%s]\n' "${#var}"
printf '[%s]\n' "${#arr}" # length of the first element
printf '[%s]\n' "${#arr[@]}"
printf '[%s]\n' "${#@}"
--endoutput

--newpage advanced_parameter_expansion_6_example_output
--heading Advanced parameter expansion VI example output
--beginoutput
$ ./05-parameter-expansion5.sh 'one parameter'
[9]
[3]
[8]
[1]
--endoutput

--newpage advanced_parameter_expansion_7
--heading Advanced parameter expansion VII
--color red
${!prefix*}
${!prefix@}
--color black
Expands to variable names beginning with prefix

--newpage advanced_parameter_expansion_8
--heading Advanced parameter expansion VIII
--color red
${!name[@]}
${!name[*]}
--color black
Expands to the list of array indices (keys)

--newpage advanced_parameter_expansion_9
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

--newpage advanced_parameter_expansion_9_example
--heading Advanced parameter expansion IX example
--beginoutput
var="foofoobarbaz"
printf '%s\n' "${var#foo}"
printf '%s\n' "${var##foo}"
printf '%s\n' "${var#*a}"
printf '%s\n' "${var##*a}"
printf '%s\n' "${@#?[a-c]*?}"
--endoutput

--newpage advanced_parameter_expansion_9_example_output
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

--newpage advanced_parameter_expansion_10
--heading Advanced parameter expansion X
--color red
${parameter%word}
${parameter%word}
--color black
* similar to # and ##
* match the trailing portion

--newpage advanced_parameter_expansion_10_example
--heading Advanced parameter expansion X example
--beginoutput
var="foofoobarbazbaz"
printf '%s\n' "${var%baz}"
printf '%s\n' "${var%%baz}"
printf '%s\n' "${var%o*}"
printf '%s\n' "${var%%o*}"
printf '%s\n' "${@%?*[a-c]*?}"
--endoutput

--newpage advanced_parameter_expansion_10_example_output
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

--newpage advanced_parameter_expansion_11
--heading Advanced parameter expansion XI
--beginoutput
${parameter/pattern/string}
--endoutput

