default :
	../z_tools/make.exe img

ipl.bin : ipl.nas Makefile
	../z_tools/nask.exe ipl.nas ipl.bin ipl.lst

weekendos.img : ipl.bin Makefile
	../z_tools/edimg.exe   imgin:../z_tools/fdimg0at.tek   \
	wbinimg src:ipl.bin len:512 from:0 to:0    imgout:weekendos.img

asm :
	../z_tools/make.exe -r ipl.bin

img :
	../z_tools/make.exe -r weekendos.img

run :
	../z_tools/make.exe img
	copy weekendos.img ..\z_tools\qemu\fdimage0.bin
	../z_tools/make.exe -C ../z_tools/qemu

install :
	../z_tools/make.exe img
	../z_tools/imgtol.com w a: weekendos.img

clean :
	-del ipl.bin
	-del ipl.lst

src_only :
	../z_tools/make.exe clean
	-del weekendos.img