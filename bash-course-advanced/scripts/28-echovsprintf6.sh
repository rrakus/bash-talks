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
