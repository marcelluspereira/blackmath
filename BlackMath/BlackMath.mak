# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     BlackMath_Debug
#     BlackMath_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 5.1.1


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "BlackMath_Debug" configuration
#

ifeq ($(MAKECMDGOALS),BlackMath_Debug)

BlackMath_Debug : ./Debug/BlackMath.ldr 

Debug/BlackMath.doj :BlackMath.c $(VDSP)/Blackfin/include/cdefBF592-A.h $(VDSP)/Blackfin/include/defBF592-A.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF59x_base.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cdefBF59x_base.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/fract.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fract_math.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/fr2x16_math.h $(VDSP)/Blackfin/include/fr2x16_base.h $(VDSP)/Blackfin/include/r2x16_base.h $(VDSP)/Blackfin/include/fract2float_conv.h $(VDSP)/Blackfin/include/cycles.h $(VDSP)/Blackfin/include/xcycle_count.h $(VDSP)/Blackfin/include/limits.h $(VDSP)/Blackfin/include/cycle_count_bf.h $(VDSP)/Blackfin/include/cycle_count.h twi.h initBoard.h $(VDSP)/Blackfin/include/bfrom.h $(VDSP)/Blackfin/include/services_types.h MicroOLED.h $(VDSP)/Blackfin/include/stdio.h teste_fir/voice2_8kfs_16bit.h teste_fir/filtro1.h $(VDSP)/Blackfin/include/filter.h $(VDSP)/Blackfin/include/complex.h $(VDSP)/Blackfin/include/complex_typedef.h 
	@echo ".\BlackMath.c"
	$(VDSP)/ccblkfn.exe -c .\BlackMath.c -file-attr ProjectName=BlackMath -O -Ov100 -ipa -no-annotate -structs-do-not-overlap -no-multiline -D__PROCESSOR_SPEED__=193000000 -double-size-32 -decls-strong -warn-protos -DDO_CYCLE_COUNTS -si-revision 0.2 -proc ADSP-BF592-A -o .\Debug\BlackMath.doj -MM

./Debug/BlackMath_basiccrt.doj :./BlackMath_basiccrt.s $(VDSP)/Blackfin/include/defBF592-A.h $(VDSP)/Blackfin/include/defBF59x_base.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/sys/_adi_platform.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/platform.h 
	@echo ".\BlackMath_basiccrt.s"
	$(VDSP)/easmblkfn.exe .\BlackMath_basiccrt.s -proc ADSP-BF592-A -file-attr ProjectName=BlackMath -si-revision 0.2 -o .\Debug\BlackMath_basiccrt.doj -MM

Debug/BlackMath_heaptab.doj :BlackMath_heaptab.c 
	@echo ".\BlackMath_heaptab.c"
	$(VDSP)/ccblkfn.exe -c .\BlackMath_heaptab.c -file-attr ProjectName=BlackMath -O -Ov100 -ipa -no-annotate -structs-do-not-overlap -no-multiline -D__PROCESSOR_SPEED__=193000000 -double-size-32 -decls-strong -warn-protos -DDO_CYCLE_COUNTS -si-revision 0.2 -proc ADSP-BF592-A -o .\Debug\BlackMath_heaptab.doj -MM

Debug/initBoard.doj :initBoard.c initBoard.h $(VDSP)/Blackfin/include/cdefBF592-A.h $(VDSP)/Blackfin/include/defBF592-A.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF59x_base.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cdefBF59x_base.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/bfrom.h $(VDSP)/Blackfin/include/services_types.h 
	@echo ".\initBoard.c"
	$(VDSP)/ccblkfn.exe -c .\initBoard.c -file-attr ProjectName=BlackMath -O -Ov100 -ipa -no-annotate -structs-do-not-overlap -no-multiline -D__PROCESSOR_SPEED__=193000000 -double-size-32 -decls-strong -warn-protos -DDO_CYCLE_COUNTS -si-revision 0.2 -proc ADSP-BF592-A -o .\Debug\initBoard.doj -MM

Debug/MicroOLED.doj :MicroOLED.c MicroOLED.h $(VDSP)/Blackfin/include/stdio.h $(VDSP)/Blackfin/include/yvals.h twi.h $(VDSP)/Blackfin/include/cdefBF592-A.h $(VDSP)/Blackfin/include/defBF592-A.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF59x_base.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cdefBF59x_base.h $(VDSP)/Blackfin/include/stdint.h $(VDSP)/Blackfin/include/string.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/stdlib_bf.h util/font5x7.h 
	@echo ".\MicroOLED.c"
	$(VDSP)/ccblkfn.exe -c .\MicroOLED.c -file-attr ProjectName=BlackMath -O -Ov100 -ipa -no-annotate -structs-do-not-overlap -no-multiline -D__PROCESSOR_SPEED__=193000000 -double-size-32 -decls-strong -warn-protos -DDO_CYCLE_COUNTS -si-revision 0.2 -proc ADSP-BF592-A -o .\Debug\MicroOLED.doj -MM

Debug/twi.doj :twi.c $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h twi.h $(VDSP)/Blackfin/include/cdefBF592-A.h $(VDSP)/Blackfin/include/defBF592-A.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/defBF59x_base.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/cdefBF59x_base.h $(VDSP)/Blackfin/include/stdint.h 
	@echo ".\twi.c"
	$(VDSP)/ccblkfn.exe -c .\twi.c -file-attr ProjectName=BlackMath -O -Ov100 -ipa -no-annotate -structs-do-not-overlap -no-multiline -D__PROCESSOR_SPEED__=193000000 -double-size-32 -decls-strong -warn-protos -DDO_CYCLE_COUNTS -si-revision 0.2 -proc ADSP-BF592-A -o .\Debug\twi.doj -MM

./Debug/BlackMath.dxe :$(VDSP)/Blackfin/lib/bf592-a_rev_0.1/ADSP-BF592-A-LDF.h ./BlackMath.ldf ./Debug/BlackMath_basiccrt.doj ./Debug/BlackMath.doj ./Debug/BlackMath_heaptab.doj ./Debug/initBoard.doj ./Debug/MicroOLED.doj ./Debug/twi.doj $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libprofile532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/romdata-BF592-A.doj $(VDSP)/Blackfin/lib/cplbtab592-a.doj $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/crtn532y.doj $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libsmall532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libio532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libc532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libevent532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/Debug/libssl592-ay.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/Debug/libdrv592-ay.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libx532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libcpp532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libf64ieee532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libdsp532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libsftflt532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/libetsi532y.dlb $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/idle532mty.doj $(VDSP)/Blackfin/lib/bf592-a_rev_0.1/librt_fileio532y.dlb 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\BlackMath.doj .\Debug\BlackMath_basiccrt.doj .\Debug\BlackMath_heaptab.doj .\Debug\initBoard.doj .\Debug\MicroOLED.doj .\Debug\twi.doj -T .\BlackMath.ldf -flags-link -s -L .\Debug -flags-link -MDUSER_CRT=ADI_QUOTEBlackMath_basiccrt.dojADI_QUOTE,-MDUSE_FILEIO,-MD__cplusplus -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\BlackMath.dxe -proc ADSP-BF592-A -si-revision 0.2 -flags-link -MM

./Debug/BlackMath.ldr :./Debug/BlackMath.dxe 
	@echo "Creating loader file..."
	$(VDSP)/elfloader.exe .\Debug\BlackMath.dxe -b UART -f BINARY -Width 8 -o .\Debug\BlackMath.ldr -si-revision 0.2 -proc ADSP-BF592-A -MM

endif

ifeq ($(MAKECMDGOALS),BlackMath_Debug_clean)

BlackMath_Debug_clean:
	-$(RM) "Debug\BlackMath.doj"
	-$(RM) ".\Debug\BlackMath_basiccrt.doj"
	-$(RM) "Debug\BlackMath_heaptab.doj"
	-$(RM) "Debug\initBoard.doj"
	-$(RM) "Debug\MicroOLED.doj"
	-$(RM) "Debug\twi.doj"
	-$(RM) ".\Debug\BlackMath.dxe"
	-$(RM) ".\Debug\BlackMath.ldr"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


