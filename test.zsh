#!/bin/bash

test () {
    if [ "$1" = "$2" ]; then
        echo OK
    else
        echo "Test number $3 failed."
        echo "$1"
        echo '---'
        echo "$2"
    fi
}

echo Buiding.
make

output=(
    "`./ft_ssl`"
    #"`./ft_ssl foobar`"
    #MD5
    "`echo "pickle rick" | ./ft_ssl md5`"
    "`echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p`"
    "`echo "Pity the living." | ./ft_ssl md5 -q -r`"
    "`echo "And above all," > file && ./ft_ssl md5 file`"
    "`./ft_ssl md5 -r file`"
    "`./ft_ssl md5 -s "pity those that aren't following baerista on spotify."`"
    "`echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file`"
    "`echo "some of this will not make sense at first" | ./ft_ssl md5 file`"
    "`echo "but eventually you will understand" | ./ft_ssl md5 -p -r file`"
    "`echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file`"
    "`echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"`"
    "`echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file`"
    #SHA256
    "`echo "pickle rick" | ./ft_ssl sha256`"
    "`echo "Do not pity the dead, Harry." | ./ft_ssl sha256 -p`"
    "`echo "Pity the living." | ./ft_ssl sha256 -q -r`"
    "`echo "And above all," > file && ./ft_ssl sha256 file`"
    "`./ft_ssl sha256 -r file`"
    "`./ft_ssl sha256 -s "pity those that aren't following baerista on spotify."`"
    "`echo "be sure to handle edge cases carefully" | ./ft_ssl sha256 -p file`"
    "`echo "some of this will not make sense at first" | ./ft_ssl sha256 file`"
    "`echo "but eventually you will understand" | ./ft_ssl sha256 -p -r file`"
    "`echo "GL HF let's go" | ./ft_ssl sha256 -p -s "foo" file`"
    "`echo "one more thing" | ./ft_ssl sha256 -r -p -s "foo" file -s "bar"`"
    "`echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" file`"
)

expected=(
    "usage: ft_ssl command [command opts] [command args]"
    #"ft_ssl: Error: 'foobar' is an invalid command."
    #MD5
    "c5e433c1dbd7ba01e3763a9483e74b04"
    $'Do not pity the dead, Harry.\n2d95365bc44bf0a298e09a3ab7b34d2f'
    "e20c3b973f63482a778f3fd1869b7f25"
    "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
    "53d53ea94217b259c11a5a2d104ec58a file"
    $'MD5 ("pity those that aren\'t following baerista on spotify.") = a3c990a1964705d9bf0e602f44572f5f'
    $'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a\nbe sure to handle edge cases carefully\n3553dc7dc5963b583c056d1b9fa3349c'
    "MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
    $'53d53ea94217b259c11a5a2d104ec58a file\nbut eventually you will understand\ndcdd84e0f635694d2a943fa8d3905281'
    $'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a\nGL HF let\'s go\nd1e3cc342b6da09480b27ec57ff243e2\nMD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8'
    $'ft_ssl/md5: -s argument given more than one time. (illegal action)\n53d53ea94217b259c11a5a2d104ec58a file\nCould not open file: bar\none more thing\na0bd1876c6f011dd50fae52827f445f5\nacbd18db4cc2f85cedef654fccc4a4d8 "foo"'
    $'53d53ea94217b259c11a5a2d104ec58a\njust to be extra clear\n3ba35f1ea0d170cb3b9a752e3360286c\nacbd18db4cc2f85cedef654fccc4a4d8'
    #SHA256
    "a9c55180c67a4bc62753d836843f46fa47af28874600cdc637de921d711937ed"
    $'Do not pity the dead, Harry.\n7197000d32ca5a13cf923ba196286a72daa06e9f168c4dd5753f917568ea373f'
    "40133cfe543247c1cae0ffb0003c1179ce9fb0046bee19f9fca167380643ba45"
    "SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
    "f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file"
    $'SHA256 ("pity those that aren\'t following baerista on spotify.") = 7838c25c9debff86c584245d67b429186d3850c89da31c0b49b8d0380a3e14bf'
    $'SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\nbe sure to handle edge cases carefully\nef9241f878a1da676104a81239792a2817bc0390a427ca20bad1a59030fd20c2'
    "SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705"
    $'f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\nbut eventually you will understand\n43da940057fd3b7453ee91b3a056a41343e6f0bce315570ed27e06c993a539da'
    $'SHA256 (file) = f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\nGL HF let\'s go\nf33201f3d70c9dccccec022e2ff0df2006e016f153f600407917d14955fbec22\nSHA256 ("foo") = 2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae'
    $'ft_ssl/sha256: -s argument given more than one time. (illegal action)\nf9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705 file\nCould not open file: bar\none more thing\n720bbf63077e0bea3b70c87954123daa6fcf32f973f4d646622bd016b140ec75\n2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae "foo"'
    $'f9eb9a5a063eb386a18525c074e1065c316ec434f911e0d7d59ba2d9fd134705\njust to be extra clear\n41c3da28172faf72bb777d6a428b6d801427d02513c56cd9e3672f44383f8eee\n2c26b46b68ffc68ff99b453c1d30413413422d706483bfa0f98a5e886266e7ae'
)

echo 'Beginning tests.'
for ((i=0; i<${#output[@]}; i++)); do
    test "${output[$i]}" "${expected[$i]}" $i
done
echo 'Test end.'