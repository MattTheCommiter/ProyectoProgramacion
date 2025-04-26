make ${2:-tests}
if [ "${1}" = "0" ]; then
	make ${2}_run
else
	make ${2}_runV
fi
exit 0
