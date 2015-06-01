TOOLPATH = ../z_tools/
MAKE	 = $(TOOLPATH)make.exe -r
NASK	 = $(TOOLPATH)nask.exe
EDIMG	 = $(TOOLPATH)edimg.exe
IMGTOL	 = $(TOOLPATH)imgtol.com
COPY	 = copy
DEL		 = del


default :
	$(MAKE) img

ipl10.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl10.bin ipl10.lst
	
weekendos.sys : weekendos.nas Makefile
	$(NASK) weekendos.nas weekendos.sys weekendos.lst

weekendos.img : ipl10.bin weekendos.sys Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek   \
	wbinimg src:ipl10.bin len:512 from:0 to:0  \
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
	-$(DEL) ipl10.bin
	-$(DEL) ipl10.lst
	-$(DEL) weekendos.sys
	-$(DEL) weekendos.lst

src_only :
	$(MAKE) clean
	-$(DEL) weekendos.img