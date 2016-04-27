dnl ###### MN PATH ######
AC_DEFUN([MULTINEST_PATH],
[
AC_MSG_CHECKING([for MultiNest location])

AC_ARG_WITH(multinest,
        AC_HELP_STRING([--with-multinest=DIR],[location of MultiNest installation @<:@default=system libs@:>@]),
        [],
	[with_multinest=system])

if test "x$with_multinest" = "xno"; then
AC_MSG_ERROR([libnest3 is required. Please install MultiNest.])
fi

if test "x$with_multinest" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(nest3,main,[],
			[
			AC_MSG_ERROR([Cannot find libnest3.a. Please install MultiNest or use --with-multinest=.])
			]
		     )
	multinestLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_multinest/libnest3.a"; then
		AC_MSG_RESULT([found in $with_multinest])
		multinestLIBS="-L$with_multinest -R$with_multinest -lnest3"
	elif test -e "$with_multinest/lib/libnest3.a"; then
		AC_MSG_RESULT([found in $with_multinest])
		multinestLIBS="-L$with_multinest -R$with_multinest -lnest3"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_multinest/libnest3.a])
	fi
fi

MN_LIBS="$MN_LIBS $multinestLIBS"
])
