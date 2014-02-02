
torify wget http://sigmaninestudios.com/3301/avowyfgl5lkzfj3n.onion.htm

cat index.html | xxd -r -p > index.gz

gzip -d index.gz

dd if=index.bin of=index.1.jpg bs=1 skip=0 count=823807

dd if=index.bin of=index.2.jpg bs=1 skip=823807 count=823514

dd if=index.bin of=index.3.rev.jpg bs=1 skip=1647321 count=724576

dd if=index.bin of=index.4.rev.jpg bs=1 skip=2371898 
