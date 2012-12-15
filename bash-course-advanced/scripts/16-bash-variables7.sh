#!/bin/bash
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
