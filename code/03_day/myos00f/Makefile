TOOLPATH = ../z_tools/
MAKE	 = $(TOOLPATH)make.exe -r
NASK	 = $(TOOLPATH)nask.exe
EDIMG	 = $(TOOLPATH)edimg.exe
IMGTOL	 = $(TOOLPATH)imgtol.com
COPY	 = copy
DEL		 = del


default :
	$(MAKE) img

ipl.bin : ipl.nas Makefile
	$(NASK) ipl.nas ipl.bin ipl.lst
	
weekendos.sys : weekendos.nas Makefile
	$(NASK) weekendos.nas weekendos.sys weekendos.lst

weekendos.img : ipl.bin weekendos.sys Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek   \
	wbinimg src:ipl.bin len:512 from:0 to:0  \
	copy from:weekendos.sys to:@: \
	imgout:weekendos.img


img :
	$(MAKE) weekendos.img

run :
	$(MAKE) img
	$(COPY) weekendos.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install :
	$(MAKE) img
	$(IMGTOL) w a: weekendos.img

clean :
	-$(DEL) ipl.bin
	-$(DEL) ipl.lst
	-$(DEL) weekendos.sys
	-$(DEL) weekendos.lst

src_only :
	$(MAKE) clean
	-$(DEL) weekendos.img