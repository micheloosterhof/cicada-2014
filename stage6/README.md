
	torify wget http://sigmaninestudios.com/3301/avowyfgl5lkzfj3n.onion.htm

	cat index.html | xxd -r -p > index.gz

	gzip -d index.gz

	dd if=index.bin of=index.1.jpg bs=1 skip=0 count=823807
	dd if=index.bin of=index.2.jpg bs=1 skip=823807 count=823514
	dd if=index.bin of=index.3.rev.jpg bs=1 skip=1647321 count=724576
	dd if=index.bin of=index.4.rev.jpg bs=1 skip=2371898 

	outguess -r index.1.jpg index.1.outguess
	outguess -r index.2.jpg index.2.outguess
	outguess -r index.3.jpg index.3.outguess
	outguess -r index.4.jpg index.4.outguess

TOBELIEVETRUTHISTODESTROYPOSSIBILITYQ4UTGDI2N4M4UIM59133
