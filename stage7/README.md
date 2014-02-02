
torify wget http://q4utgdi2n4m4uim5.onion

gpgv < index.html

cat index.html | tail -n +4 | head -n -17 | xxd -r -p > index.mp3

sudo apt-get install libmpg123-dev

gcc -lmpg123 /usr/share/doc/libmpg123-dev/examples/extract_frames.c -o extract_frames

./extract_frames --no-info < index.mp3 > index.frames


