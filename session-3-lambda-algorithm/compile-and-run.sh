#!/usr/bin/env bash
f="$1"
shift
[ -z "$f" ] && echo "No file given" && exit 1

tmp_file=$(mktemp "./$f.out.XXXXX")
function cleanup {
	rm -f "$tmp_file"
}
trap cleanup EXIT
echo "${CXX:-g++}" -o "$tmp_file" "$f" "$@"
if "${CXX:-g++}" -o "$tmp_file" "$f" "$@"; then
	echo "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"
	"$tmp_file"
fi
exit
