ACPICA_DISPATCHER_OBJ = \
	build/acpi/acpica/dispatcher/dsargs.o \
	build/acpi/acpica/dispatcher/dscontrol.o \
	build/acpi/acpica/dispatcher/dsdebug.o \
	build/acpi/acpica/dispatcher/dsfield.o \
	build/acpi/acpica/dispatcher/dsinit.o \
	build/acpi/acpica/dispatcher/dsmethod.o \
	build/acpi/acpica/dispatcher/dsmthdat.o \
	build/acpi/acpica/dispatcher/dsobject.o \
	build/acpi/acpica/dispatcher/dsopcode.o \
	build/acpi/acpica/dispatcher/dsutils.o \
	build/acpi/acpica/dispatcher/dswexec.o \
	build/acpi/acpica/dispatcher/dswload.o \
	build/acpi/acpica/dispatcher/dswload2.o \
	build/acpi/acpica/dispatcher/dswscope.o \
	build/acpi/acpica/dispatcher/dswstate.o

ACPICA_EVENTS_OBJ = \
	build/acpi/acpica/events/evevent.o \
	build/acpi/acpica/events/evglock.o \
	build/acpi/acpica/events/evgpe.o \
	build/acpi/acpica/events/evgpeblk.o \
	build/acpi/acpica/events/evgpeinit.o \
	build/acpi/acpica/events/evgpeutil.o \
	build/acpi/acpica/events/evhandler.o \
	build/acpi/acpica/events/evmisc.o \
	build/acpi/acpica/events/evregion.o \
	build/acpi/acpica/events/evrgnini.o \
	build/acpi/acpica/events/evsci.o \
	build/acpi/acpica/events/evxface.o \
	build/acpi/acpica/events/evxfevnt.o \
	build/acpi/acpica/events/evxfgpe.o \
	build/acpi/acpica/events/evxfregn.o

ACPICA_EXECUTOR_OBJ = \
	build/acpi/acpica/executer/exconcat.o \
	build/acpi/acpica/executer/exconfig.o \
	build/acpi/acpica/executer/exconvrt.o \
	build/acpi/acpica/executer/excreate.o \
	build/acpi/acpica/executer/exdebug.o \
	build/acpi/acpica/executer/exdump.o \
	build/acpi/acpica/executer/exfield.o \
	build/acpi/acpica/executer/exfldio.o \
	build/acpi/acpica/executer/exmisc.o \
	build/acpi/acpica/executer/exmutex.o \
	build/acpi/acpica/executer/exnames.o \
	build/acpi/acpica/executer/exoparg1.o \
	build/acpi/acpica/executer/exoparg2.o \
	build/acpi/acpica/executer/exoparg3.o \
	build/acpi/acpica/executer/exoparg6.o \
	build/acpi/acpica/executer/exprep.o \
	build/acpi/acpica/executer/exregion.o \
	build/acpi/acpica/executer/exresnte.o \
	build/acpi/acpica/executer/exresolv.o \
	build/acpi/acpica/executer/exresop.o \
	build/acpi/acpica/executer/exstore.o \
	build/acpi/acpica/executer/exstoren.o \
	build/acpi/acpica/executer/exstorob.o \
	build/acpi/acpica/executer/exsystem.o \
	build/acpi/acpica/executer/extrace.o \
	build/acpi/acpica/executer/exutils.o

ACPICA_HARDWARE_OBJ = \
	build/acpi/acpica/hardware/hwacpi.o \
	build/acpi/acpica/hardware/hwesleep.o \
	build/acpi/acpica/hardware/hwgpe.o \
	build/acpi/acpica/hardware/hwpci.o \
	build/acpi/acpica/hardware/hwregs.o \
	build/acpi/acpica/hardware/hwsleep.o \
	build/acpi/acpica/hardware/hwtimer.o \
	build/acpi/acpica/hardware/hwvalid.o \
	build/acpi/acpica/hardware/hwxface.o \
	build/acpi/acpica/hardware/hwxfsleep.o

ACPICA_NAMESPACE_OBJ = \
	build/acpi/acpica/namespace/nsaccess.o \
	build/acpi/acpica/namespace/nsalloc.o \
	build/acpi/acpica/namespace/nsarguments.o \
	build/acpi/acpica/namespace/nsconvert.o \
	build/acpi/acpica/namespace/nsdump.o \
	build/acpi/acpica/namespace/nsdumpdv.o \
	build/acpi/acpica/namespace/nseval.o \
	build/acpi/acpica/namespace/nsinit.o \
	build/acpi/acpica/namespace/nsload.o \
	build/acpi/acpica/namespace/nsnames.o \
	build/acpi/acpica/namespace/nsobject.o \
	build/acpi/acpica/namespace/nsparse.o \
	build/acpi/acpica/namespace/nspredef.o \
	build/acpi/acpica/namespace/nsprepkg.o \
	build/acpi/acpica/namespace/nsrepair2.o \
	build/acpi/acpica/namespace/nsrepair.o \
	build/acpi/acpica/namespace/nssearch.o \
	build/acpi/acpica/namespace/nsutils.o \
	build/acpi/acpica/namespace/nswalk.o \
	build/acpi/acpica/namespace/nsxfeval.o \
	build/acpi/acpica/namespace/nsxfname.o \
	build/acpi/acpica/namespace/nsxfobj.o

ACPICA_PARSER_OBJ = \
	build/acpi/acpica/parser/psargs.o \
	build/acpi/acpica/parser/psloop.o \
	build/acpi/acpica/parser/psobject.o \
	build/acpi/acpica/parser/psopcode.o \
	build/acpi/acpica/parser/psopinfo.o \
	build/acpi/acpica/parser/psparse.o \
	build/acpi/acpica/parser/psscope.o \
	build/acpi/acpica/parser/pstree.o \
	build/acpi/acpica/parser/psutils.o \
	build/acpi/acpica/parser/pswalk.o \
	build/acpi/acpica/parser/psxface.o

ACPICA_RESOURCES_OBJ = \
	build/acpi/acpica/resources/rsaddr.o \
	build/acpi/acpica/resources/rscalc.o \
	build/acpi/acpica/resources/rscreate.o \
	build/acpi/acpica/resources/rsinfo.o \
	build/acpi/acpica/resources/rsio.o \
	build/acpi/acpica/resources/rsirq.o \
	build/acpi/acpica/resources/rslist.o \
	build/acpi/acpica/resources/rsmemory.o \
	build/acpi/acpica/resources/rsmisc.o \
	build/acpi/acpica/resources/rsserial.o \
	build/acpi/acpica/resources/rsutils.o \
	build/acpi/acpica/resources/rsxface.o

#	build/acpi/acpica/resources/rsdump.o \
#	build/acpi/acpica/resources/rsdumpinfo.o \


ACPICA_TABLES_OBJ = \
	build/acpi/acpica/tables/tbdata.o \
	build/acpi/acpica/tables/tbfadt.o \
	build/acpi/acpica/tables/tbfind.o \
	build/acpi/acpica/tables/tbinstal.o \
	build/acpi/acpica/tables/tbprint.o \
	build/acpi/acpica/tables/tbutils.o \
	build/acpi/acpica/tables/tbxface.o \
	build/acpi/acpica/tables/tbxfload.o \
	build/acpi/acpica/tables/tbxfroot.o

ACPICA_UTILITIES_OBJ = \
	build/acpi/acpica/utilities/utaddress.o \
	build/acpi/acpica/utilities/utalloc.o \
	build/acpi/acpica/utilities/utascii.o \
	build/acpi/acpica/utilities/utbuffer.o \
	build/acpi/acpica/utilities/utcache.o \
	build/acpi/acpica/utilities/utclib.o \
	build/acpi/acpica/utilities/utcopy.o \
	build/acpi/acpica/utilities/utdebug.o \
	build/acpi/acpica/utilities/utdecode.o \
	build/acpi/acpica/utilities/utdelete.o \
	build/acpi/acpica/utilities/uterror.o \
	build/acpi/acpica/utilities/uteval.o \
	build/acpi/acpica/utilities/utexcep.o \
	build/acpi/acpica/utilities/utglobal.o \
	build/acpi/acpica/utilities/uthex.o \
	build/acpi/acpica/utilities/utids.o \
	build/acpi/acpica/utilities/utinit.o \
	build/acpi/acpica/utilities/utlock.o \
	build/acpi/acpica/utilities/utmath.o \
	build/acpi/acpica/utilities/utmisc.o \
	build/acpi/acpica/utilities/utmutex.o \
	build/acpi/acpica/utilities/utnonansi.o \
	build/acpi/acpica/utilities/utobject.o \
	build/acpi/acpica/utilities/utosi.o \
	build/acpi/acpica/utilities/utownerid.o \
	build/acpi/acpica/utilities/utpredef.o \
	build/acpi/acpica/utilities/utprint.o \
	build/acpi/acpica/utilities/utresrc.o \
	build/acpi/acpica/utilities/utstate.o \
	build/acpi/acpica/utilities/utstring.o \
	build/acpi/acpica/utilities/utstrtoul64.o \
	build/acpi/acpica/utilities/uttrack.o \
	build/acpi/acpica/utilities/utuuid.o \
	build/acpi/acpica/utilities/utxface.o \
	build/acpi/acpica/utilities/utxferror.o \
	build/acpi/acpica/utilities/utxfinit.o \
	build/acpi/acpica/utilities/utxfmutex.o

ACPOICA_OS_OBJ = \
	build/acpi/acpica/kaos.o

ACPICA_OBJ = \
	$(ACPICA_DISPATCHER_OBJ) \
	$(ACPICA_EVENTS_OBJ) \
	$(ACPICA_EXECUTOR_OBJ) \
	$(ACPICA_HARDWARE_OBJ) \
	$(ACPICA_NAMESPACE_OBJ) \
	$(ACPICA_PARSER_OBJ) \
	$(ACPICA_RESOURCES_OBJ) \
	$(ACPICA_TABLES_OBJ) \
	$(ACPICA_UTILITIES_OBJ) \
	$(ACPOICA_OS_OBJ)

ACPICA_INCLUDE = acpi/acpica/include

build/acpi/acpica/%.o: acpi/acpica/src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c -I$(ACPICA_INCLUDE) -mno-red-zone -mcmodel=large -ffreestanding -O2 --target=x86_64-pc-none-elf $< -MMD -o $@

build/acpi/acpica/%.o: acpi/acpica/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c -I. -I$(ACPICA_INCLUDE) $(LIB_CXX) $(LIB_C) -mno-red-zone -mcmodel=large -ffreestanding -O2 --target=x86_64-pc-none-elf --std=c++1z -fno-exceptions -fno-rtti $< -MMD -o $@
