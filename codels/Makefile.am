lib_LTLIBRARIES = libQR2matlab_codels.la

libQR2matlab_codels_la_SOURCES=	QR2matlab_c_types.h
libQR2matlab_codels_la_SOURCES+=	QR2matlab_codels.c
libQR2matlab_codels_la_SOURCES+=	QR2matlab_publish_codels.c

libQR2matlab_codels_la_CPPFLAGS=	$(requires_CFLAGS)
libQR2matlab_codels_la_LDFLAGS=	$(requires_LIBS)
libQR2matlab_codels_la_LDFLAGS+=	-release $(PACKAGE_VERSION)


# idl  mappings
BUILT_SOURCES=	QR2matlab_c_types.h
CLEANFILES=	${BUILT_SOURCES}
QR2matlab_c_types.h: ${top_srcdir}/QR2matlab.gen
	${GENOM3}  mappings \
	  -MD -MF .deps/$@.d -MT $@ --signature -l c $< >$@

-include .deps/QR2matlab_c_types.h.d
