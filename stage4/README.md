
$ torify wget http://fv7lyucmeozzd5j4.onion/

$ torify wget http://fv7lyucmeozzd5j4.onion/server-status

# reverse hexdump to get server-status.jpg

$ dd if=server-status.jpg of=server-status.data bs=1 skip=336353 count=360

$ cat server-status.data  | perl -0777e 'print scalar reverse <>' | xxd -r -p > matrix

