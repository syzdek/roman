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
			--host=i386-mingw32 --enable-strictwarnings
make
make dist
make dist-bzip2
make dist-zip
make txtdocs
make windist


mkdir -p   ~/Desktop/release-${1}
mv *.tar.* ~/Desktop/release-${1}/
cp *.zip   ~/Desktop/release-${1}/

rm -fR /tmp/roman-$RELEASE/share
cd /tmp
zip -r roman-$RELEASE.zip roman-$RELEASE
mv roman-$RELEASE.zip ~/Desktop/release-${1}/

date > ~/Desktop/release-${1}/timestamp.txt

