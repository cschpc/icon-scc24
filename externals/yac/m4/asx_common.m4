# ASX_TR_ARG(EXPRESSION)
# -----------------------------------------------------------------------------
# Transforms EXPRESSION into shell code that generates a name for a command
# line argument. The result is literal when possible at M4 time, but must be
# used with eval if EXPRESSION causes shell indirections.
#
AC_DEFUN([ASX_TR_ARG],
  [AS_LITERAL_IF([$1],
     [m4_translit(AS_TR_SH([$1]), [_A-Z], [-a-z])],
     [m4_bpatsubst(AS_TR_SH([$1]), [`$],
        [ | tr '_[]m4_cr_LETTERS[]' '-[]m4_cr_letters[]'`])])])

# ASX_VAR_APPEND_UNIQ(VARIABLE,
#                     [TEXT],
#                     [SEPARATOR])
# -----------------------------------------------------------------------------
# Emits shell code to append the shell expansion of TEXT to the end of the
# current contents of the polymorphic shell variable VARIABLE without
# duplicating substrings. The TEXT can optionally be prepended with the shell
# expansion of SEPARATOR. The SEPARATOR is not appended if VARIABLE is empty or
# unset. Both TEXT and SEPARATOR need to be quoted properly to avoid field
# splitting and file name expansion.
#
AC_DEFUN([ASX_VAR_APPEND_UNIQ],
  [AS_CASE([$3[]AS_VAR_GET([$1])$3],
     [*m4_ifnblank([$3], [$3$2$3], [$2])*], [],
     [m4_ifnblank([$3],[$3$3],[''])], [AS_VAR_APPEND([$1], [$2])],
     [AS_VAR_APPEND([$1], [$3]); AS_VAR_APPEND([$1], [$2])])])

# ASX_PREPEND_LDFLAGS([LDFLAGS],
#                     [LIBS],
#                     ...)
# -----------------------------------------------------------------------------
# Prepends the first argument LDFLAGS to each of the rest of the arguments
# LIBS and expands into a space separated list of the resulting strings. Each
# element of the resulting list is shell-quoted with double quotation marks.
#
AC_DEFUN([ASX_PREPEND_LDFLAGS], [m4_foreach([arg], m4_cdr($@), [ "$1 arg"])])

# ASX_EXTRACT_ARGS(VARIABLE,
#                  ARGUMENTS,
#                  FLAG-PATTERN)
# -----------------------------------------------------------------------------
# Emits shell code to extract values of arguments that match sed-like pattern
# FLAG-PATTERN from the string ARGUMENTS and set the result to the shell
# variable VARIABLE. Both ARGUMENTS and FLAG-PATTERN must be shell-quoted.
#
# For example, the following extract library paths from the linking command:
#     ASX_EXTRACT_ARGS([FC_LIB_PATHS],
#                      ["$FCFLAGS $LDFLAGS $LIBS"],
#                      ['-L@<:@ @:>@*'])
#
AC_DEFUN([ASX_EXTRACT_ARGS],
  [AS_VAR_SET([$1])
   asx_extract_args_args=$2
   asx_extract_args_args=`AS_ECHO(["$asx_extract_args_args"]) | dnl
sed 's%'$3'%_ASX_EXTRACT_ARGS_MARKER_%g'`
   for asx_extract_args_arg in $asx_extract_args_args; do
     AS_CASE([$asx_extract_args_arg],
       [_ASX_EXTRACT_ARGS_MARKER_*],
       [asx_extract_args_value=`AS_ECHO(["$asx_extract_args_arg"]) | dnl
sed 's%^_ASX_EXTRACT_ARGS_MARKER_%%'`
        AS_VAR_APPEND([$1], [" $asx_extract_args_value"])])
   done])

# ASX_ESCAPE_SINGLE_QUOTE(VARIABLE)
# -----------------------------------------------------------------------------
# Emits shell code that replaces any occurrence of the single-quote (') in the
# shell variable VARIABLE with the following string: '\'', which is required
# when contents of the VARIABLE must be passed literally to a subprocess, e.g.
# eval \$SHELL -c "'$VARIABLE'".
#
AC_DEFUN([ASX_ESCAPE_SINGLE_QUOTE],
  [AS_CASE([AS_VAR_GET([$1])], [*\'*],
     [AS_VAR_SET([$1], [`AS_ECHO(["AS_VAR_GET([$1])"]) | dnl
sed "s/'/'\\\\\\\\''/g"`])])])

# ASX_SRCDIRS(BUILD-DIR-NAME)
# -----------------------------------------------------------------------------
# Receives a normalized (i.e. does not contain '/./', '..', etc.) path
# BUILD-DIR-NAME to a directory relative to the top build directory and emits
# shell code that sets the following variables:
#     1) ac_builddir - path to BUILD-DIR-NAME relative to BUILD-DIR-NAME
#                      (i.e. always equals to '.');
#     2) ac_abs_builddir - absolute path to BUILD-DIR-NAME;
#     3) ac_top_builddir_sub - path to the top build directory relative to
#                              BUILD-DIR-NAME (i.e. equals to '.' if
#                              BUILD-DIR-NAME is the top build directory);
#     4) ac_top_build_prefix - empty if ac_top_builddir_sub equals to '.' and
#                              path to the top build directory relative to
#                              BUILD-DIR-NAME with a trailing slash, otherwise;
#     5) ac_abs_top_builddir - absolute path to the top build directory;
#     6) ac_srcdir - path to <top-srcdir>/BUILD-DIR-NAME relative to
#                    BUILD-DIR-NAME where <top-srcdir> is the top source
#                    directory (i.e. equals to the path from BUILD-DIR-NAME to
#                    its respective source directory);
#     7) ac_abs_srcdir - absolute path to <top-srcdir>/BUILD-DIR-NAME where
#                        <top-srcdir> is the top source directory (i.e. equals
#                        to the absolute path to the source directory that
#                        corresponds to BUILD-DIR-NAME);
#     8) ac_top_srcdir - path to the top source directory relative to
#                        BUILD-DIR-NAME;
#     9) ac_abs_top_srcdir - absolute path to the top source directory.
#
AC_DEFUN([ASX_SRCDIRS],
  [AC_REQUIRE_SHELL_FN([acx_subdir_srcdirs_fn], [], [_AC_SRCDIRS(["$[]1"])])dnl
   acx_subdir_srcdirs_fn $1])