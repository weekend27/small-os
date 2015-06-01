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
	
asmhead.sys : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.sys asmhead.lst

asmhead.img : ipl10.bin asmhead.sys Makefile
	$(EDIMG)   imgin:../z_tools/fdimg0at.tek   \
	wbinimg src:ipl10.bin len:512 from:0 to:0  \
	copy from:asmhead.sys to:@: \
	imgout:asmhead.img


img :
	$(MAKE) asmhead.img

run :
	$(MAKE) img
	$(COPY) asmhead.img ..\z_tools\qemu\fdimage0.bin
	$(MAKE) -C ../z_tools/qemu

install :
	$(MAKE) img
	$(IMGTOL) w a: asmhead.img

clean :
	-$(DEL) ipl10.bin
	-$(DEL) ipl10.lst
	-$(DEL) asmhead.sys
	-$(DEL) asmhead.lst

src_only :
	$(MAKE) clean
	-$(DEL) asmhead.img