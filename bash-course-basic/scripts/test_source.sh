lib_version="0.0.1"
is_running() {
  if [[ $# -eq 0 ]]; then return 127
  else pidof "$1" &>/dev/null
  fi
}
