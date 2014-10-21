#!/bin/bash
################################################################################
# build_abs.sh
#
# Build an ABS package from the source code.
# We'll assume GNU tar, not bsdtar or anything else.
# Note: update this file and PKGBUILD for each version.
#
# Maintained By: Ryan Jacobs <ryan.mjacobs@gmail.com>
# Sept. 22, 2014 -> File creation.
#  Oct. 20, 2014 -> Change file names to global variables.
################################################################################

# Global Variables
version=0.03
pkgname=avgtime

build() {
    # Create source tarball
    printf "Creating source tarball... "
    tar cf "$pkgname-$version.tar" --transform="s/src/$pkgname-$version/g" src/
    gzip -9 "$pkgname-$version.tar"
    printf "                done!\n"

    # Creating ABS tarball
    printf "Creating ABS tarball... "
    cd ABS
    mv ../"$pkgname-$version.tar.gz" .
    sum="$(makepkg -g 2>/dev/null)"
    sed -i "s/md5sum.*/$sum/g" PKGBUILD
    makepkg &>/dev/null
    rm "$pkgname-$version.tar.gz"
    rm -rf src pkg
    cd ..
    printf "                   done!\n"

    # Move ABS package to current directory
    printf "Moving ABS package to current directory... "
    mv "ABS/$pkgname"*.pkg.tar.xz .
    printf "done!\n"

    return 0
}

clean() {
    # Remove ABS package
    printf "Removing ABS package... "
    rm "$pkgname"*.pkg.tar.xz
    printf "                   done!\n"

    return 0
}

###
## Mainline
#
if [ $# -ne 1 ]; then
    printf "Build an ABS package from the source code.\n"
    printf "Usage: %s <build|clean>\n" $0
    exit 1
fi

case $1 in
    build)
        build || exit 1
        ;;
    clean)
        clean || exit 1
        ;;
    *)
        printf "%s: %s is not a valid option.\n" $0 "$1"
        exit 1
        ;;
esac

exit 0
