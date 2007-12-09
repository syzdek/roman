#!/bin/sh

SRCDIR=`dirname ${0}`
SRCDIR=`dirname ${SRCDIR}`

if test "x${1}" = "x";then
   echo "usage: windist.sh <release>"
   exit 1;
fi

RELEASE="${1}-win32"

PREFIX="/tmp/roman-$RELEASE"

rm -Rf ${PREFIX}

${SRCDIR}/configure	--prefix=${PREFIX} --disable-shared \
			--host=i386-mingw32 --enable-strictwarnings || exit 1
make || exit 1
make dist || exit 1
make dist-bzip2 || exit 1
make dist-zip || exit 1
make txtdocs || exit 1
make windist || exit 1


mkdir -p   ~/Desktop/release-${1} || exit 1
mv *.tar.* ~/Desktop/release-${1}/ || exit 1
cp *.zip   ~/Desktop/release-${1}/ || exit 1

rm -fR /tmp/roman-$RELEASE/share || exit 1
cd /tmp || exit 1
zip -r roman-$RELEASE.zip roman-$RELEASE || exit 1
mv roman-$RELEASE.zip ~/Desktop/release-${1}/ || exit 1

date > ~/Desktop/release-${1}/timestamp.txt || exit 1

echo " "
echo " Finished with no errors"
echo " "

