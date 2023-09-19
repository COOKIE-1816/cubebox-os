rm -f build/obj/* 2> /dev/null
rm -f build/bin/* 2> /dev/null

sh ./scripts/assemble.sh
sh ./scripts/compile.sh

sh ./scripts/link.sh

sh ./scripts/generate-iso.sh



