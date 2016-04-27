# touch NEWS README AUTHORS ChangeLog; autoreconf --install --verbose --force

#./configure CXXFLAGS=-std=c++11 CFLAGS=-g CPPFLAGS=-D__MY_DEBUG__ --prefix=/home/shehu/wip/RooStat/dev/MultiNestPlugin/local --with-rootsys=/home/shehu/wip/npflavour/gnubuilds_SMonly/builds/local --with-multinest=/home/shehu/wip/RooStat/dev/MultiNest_v2.18/

#make -j 2 distcheck DISTCHECK_CONFIGURE_FLAGS="CXXFLAGS=-std=c++11 CFLAGS=-g CPPFLAGS=-D__MY_DEBUG__ --prefix=/home/shehu/wip/RooStat/dev/MultiNestPlugin/local --with-rootsys=/home/shehu/wip/npflavour/gnubuilds_SMonly/builds/local --with-multinest=/home/shehu/wip/RooStat/dev/MultiNest_v2.18/"

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4 --install
AUTOMAKE_OPTIONS = subdir-objects

AM_CXXFLAGS = -I$(top_srcdir)/inc/RooStats/MultiNestPlugin \
-I$(top_srcdir)/inc

pkginclude_HEADERS = inc/RooStats/MultiNestPlugin/TMultiNest.h \
inc/RooStats/MultiNestPlugin/MultiNest.h \
inc/RooStats/MultiNestCalculator.h \
inc/RooStats/MultiNestInterface.h

themySOURCES = src/MultiNest.cxx \
src/TMultiNest.cxx \
src/MultiNestCalculator.cxx 

nodist_themySOURCES = G__MultiNestPlugin.cxx  # to be generated
EXTRA_DIST = inc/LinkDef.h

#########################################################################
pkglib_LTLIBRARIES = libMultiNestPlugin-@MNP_API_VERSION@.la
libMultiNestPlugin_@MNP_API_VERSION@_la_SOURCES = $(themySOURCES) 
nodist_libMultiNestPlugin_@MNP_API_VERSION@_la_SOURCES = $(nodist_themySOURCES) 

#libMultiNestPlugin_@MNP_API_VERSION@_la_LDFLAGS  = -version-info $(MNP_SO_VERSION)
libMultiNestPlugin_@MNP_API_VERSION@_la_LDFLAGS  = $(MNP_SO_VERSION)
libMultiNestPlugin_@MNP_API_VERSION@_la_CPPFLAGS = $(MNP_CFLAGS) -I@ROOTINCDIR@
libMultiNestPlugin_@MNP_API_VERSION@_la_LIBADD   = $(MNP_LIBS) -L@ROOTLIBDIR@  @ROOTGLIBS@ -lRooFit -lRooFitCore -lTree -lRIO -lMatrix -lHist -lMathMore -lMathCore -lGraf -lGpad -lMinuit -lFoam -lRooStats @ROOTAUXLIBS@ $(GSL_LIBS) -llapack $(MN_LIBS) $(FLIBS) -lgfortran 


#########################################################################
MULTINESTPLUGINH = $(pkginclude_HEADERS) inc/LinkDef.h
G__MultiNestPlugin.cxx: $(MULTINESTPLUGINH) 
	@echo " "
	@echo "Generating dictionary $@..."
	@echo " "
	$(ROOTCLING) -f $@ -s libMultiNestPlugin_@MNP_API_VERSION@ -c -I$(top_srcdir) -I$(top_srcdir)/inc $(MULTINESTPLUGINH)  

CLEANFILES = *_rdict* G__*
