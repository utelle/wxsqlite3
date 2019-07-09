cmake_minimum_required(VERSION 3.6)

project(wxSQLite3)

option(STATIC_RUNTIME "link with c++ runtime statically" "ON")
option(USE_32 "create 32 bit binaries (64 bit unix only)" "OFF")
option(SQLITE_DEBUG "enable SQLite debug" "OFF")
set(SQLITE_CODEC_TYPE "DEFAULT" CACHE STRING "DB Codec(AES128, AES256, CHACHA20, DEFAULT)")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(LIBRARY_SOURCES
    "../include/wx/wxsqlite3_version.h"
    "../include/wx/wxsqlite3def.h"
    "../include/wx/wxsqlite3dyn.h"
    "../include/wx/wxsqlite3opt.h"
    "../sqlite3secure/src/codec.h"
    "../sqlite3secure/src/fastpbkdf2.h"
    "../sqlite3secure/src/rijndael.h"
    "../sqlite3secure/src/sha1.h"
    "../sqlite3secure/src/sha2.h"
    "../sqlite3secure/src/sqlite3.h"
    "../sqlite3secure/src/sqlite3ext.h"
    "../sqlite3secure/src/sqlite3secure.h"
    "../sqlite3secure/src/sqlite3userauth.h"
    "../sqlite3secure/src/test_windirent.h"
    
    "../sqlite3secure/src/sqlite3secure.c"
    "../src/wxsqlite3.cpp"
)


set(TREEVIEW_SOURCES
    "../samples/treeview/foldertree.cpp"
    "../samples/treeview/projectlist.cpp"
    "../samples/treeview/treeviewapp.cpp"
    "../samples/treeview/treeviewsample.cpp"
)

set(MINIMAL_SOURCES
    "../samples/minimal.cpp"
)

if(WIN32)
    set(LIBRARY_SOURCES
    
        ${LIBRARY_SOURCES}
        "../src/wxsqlite3_version.rc"
    )
    
    set(TREEVIEW_SOURCES
    
        ${TREEVIEW_SOURCES}
        "../samples/treeview/treeview.rc"
    )
    
    set(MINIMAL_SOURCES
    
        ${MINIMAL_SOURCES}
        "../samples/minimal.rc"
    )
endif(WIN32)

if(MSVC)
    add_compile_options(/Zi     # pdb
                        /W4     # warning level 4
                        /EHsc   # exceptions: sync
                        /J      # use unsigned char
                        /Gd     # use cdecl
                        # treat warnings as errors
                        /we4715 # not all control paths return a value
                        /we4828 # disallow invalid characters
                        # prinf-like functions: format mismatch
                        /we4473 # <function> : not enough arguments passed for format string 
                        /we4474 # <function> : too many arguments passed for format string 
                        /we4475 # <function> : length modifier <length> cannot be used with type field character <conversion-specifier> in format specifier 
                        /we4476 # <function> : unknown type field character <conversion-specifier> in format specifier 
                        /we4477 # <function> : format string <format-string> requires an argument of type <type>, but variadic argument <position> has type <type>
                        /we4478 # <function> : positional and non-positional placeholders cannot be mixed in the same format string 
                        /we4775 # nonstandard extension used in format string <format-string> of function <function>
                        /we4776 # %<conversion-specifier> is not allowed in the format string of function <function> 
                        /we4777 # <function> : format string <format-string> requires an argument of type <type>, but variadic argument <position> has type <type>
                        /we4778 # <function> : unterminated format string <format-string>
                        # macro arg mismatch
                        /we4002 # too many actual parameters for macro 'identifier'
                        /we4003 # not enough actual parameters for macro 'identifier'
                        /Zc:threadSafeInit- # https://connect.microsoft.com/VisualStudio/feedback/details/1789709/visual-c-2015-runtime-broken-on-windows-server-2003-c-11-magic-statics
                        /MP     # multiprocessor compilation
                        /utf-8  # utf-8 source & exec
                        /GF)    # eliminate duplicate strings
    
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
    
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    
    if(STATIC_RUNTIME)
        set(RELEASE_RUNTIME "/MT")
        set(DEBUG_RUNTIME "/MTd")
    else()
        set(RELEASE_RUNTIME "/MD")
        set(DEBUG_RUNTIME "/MDd")
    endif(STATIC_RUNTIME)
    
    set(CMAKE_EXE_LINKER_FLAGS "/LARGEADDRESSAWARE /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF,ICF /DEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG /Ox /Ob2 /Oi /Ot /Oy /GS- /Gy /GR- /GL /Gw ${RELEASE_RUNTIME}")
    set(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /GS -D_DEBUG ${DEBUG_RUNTIME}")
    set(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
else()
    add_compile_options(-pipe
                        -W
                        -Wall

                        -Wextra
                        -Wwrite-strings
                        -Wframe-larger-than=16384
                        -Wstack-usage=16384
                        -fdiagnostics-show-option
                        -Wmissing-declarations
                        -Wredundant-decls
                        -Wcast-qual
                        -Wsuggest-attribute=noreturn
                        -Wunused-but-set-variable
                        -Wunused-but-set-parameter

                        -Wframe-larger-than=4096

                        -Wno-multichar
                        -Wno-strict-aliasing
                        -Wno-missing-field-initializers

                        -Werror=return-type
                        -Werror=pointer-arith
                        -Werror=unused-value
                        -Werror=sizeof-pointer-memaccess
                        -Werror=implicit-function-declaration

#                        -Werror=missing-declarations
#                        -Werror=missing-prototypes
                        -Werror=reorder
                        -Werror=declaration-after-statement
                        
                        -funsigned-char

                        -fno-rtti
                        )
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=delete-non-virtual-dtor -U__STRICT_ANSI__ -fno-operator-names")       
    set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wimplicit-int -Wmissing-prototypes -Werror=implicit-int")

    set(CMAKE_CXX_FLAGS_RELEASE  "-O2 -s -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE    ${CMAKE_CXX_FLAGS_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG    "-O0 -g -D_DEBUG -D__DEBUG__ -DDEBUG_LEVEL=3 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
    set(CMAKE_C_FLAGS_DEBUG      ${CMAKE_CXX_FLAGS_DEBUG})
    
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "${CMAKE_EXE_LINKER_FLAGS} -g")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS} -g")
    
    set(CMAKE_EXE_LINKER_FLAGS_VALGRIND     "${CMAKE_EXE_LINKER_FLAGS} -g")
    set(CMAKE_SHARED_LINKER_FLAGS_VALGRIND  "${CMAKE_SHARED_LINKER_FLAGS} -g")
    
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${CMAKE_EXE_LINKER_FLAGS} -s")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} -s")
    
    if(USE_32)
        add_compile_options (-m32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
    endif(USE_32)
    
    if(STATIC_RUNTIME)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif(STATIC_RUNTIME)
endif(MSVC)

string(TIMESTAMP BUILD_YEAR "%Y")
add_definitions(-DBUILD_YEAR="${BUILD_YEAR}")

add_definitions(-DPVOID_SIZE=${CMAKE_SIZEOF_VOID_P})

if(WIN32)
    add_definitions(-D__NT__)
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )
endif()

include_directories(
    "../include/"
    "../sqlite3secure/src/"
)

add_library(
    wxsqlite3
    STATIC

    ${LIBRARY_SOURCES}
)

if(SQLITE_DEBUG)
set(SQLITE_DEBUG_MACRO "-DSQLITE_ENABLE_DEBUG=1")
endif(SQLITE_DEBUG)

set_target_properties(wxsqlite3 PROPERTIES COMPILE_FLAGS "-D_LIB \
                                                          -DWXMAKINGLIB_WXSQLITE3 \
                                                          -DwxUSE_DYNAMIC_SQLITE3_LOAD=0 \
                                                          -DWXSQLITE3_HAVE_METADATA=1 \
                                                          -DWXSQLITE3_USER_AUTHENTICATION=1 \
                                                          -DWXSQLITE3_HAVE_CODEC=1 \
                                                          -DWXSQLITE3_HAVE_LOAD_EXTENSION=0 \
                                                          -DTHREADSAFE=1 \
                                                          -DSQLITE_MAX_ATTACHED=10 \
                                                          -DSQLITE_ENABLE_EXPLAIN_COMMENTS \
                                                          -DSQLITE_SOUNDEX \
                                                          -DSQLITE_ENABLE_COLUMN_METADATA \
                                                          -DSQLITE_HAS_CODEC=1 \
                                                          -DSQLITE_SECURE_DELETE \
                                                          -DSQLITE_ENABLE_FTS3 \
                                                          -DSQLITE_ENABLE_FTS3_PARENTHESIS \
                                                          -DSQLITE_ENABLE_FTS4 \
                                                          -DSQLITE_ENABLE_FTS5 \
                                                          -DSQLITE_ENABLE_JSON1 \
                                                          -DSQLITE_ENABLE_RTREE \
                                                          -DSQLITE_ENABLE_GEOPOLY \
                                                          -DSQLITE_CORE \
                                                          -DSQLITE_ENABLE_EXTFUNC \
                                                          -DSQLITE_ENABLE_CSV \
                                                          -DSQLITE_ENABLE_SHA3 \
                                                          -DSQLITE_ENABLE_CARRAY \
                                                          -DSQLITE_ENABLE_FILEIO \
                                                          -DSQLITE_ENABLE_SERIES \
                                                          -DSQLITE_TEMP_STORE=2 \
                                                          -DSQLITE_USE_URI \
                                                          -DSQLITE_USER_AUTHENTICATION \
                                                          -DCODEC_TYPE=CODEC_TYPE_${SQLITE_CODEC_TYPE} \
                                                          ${SQLITE_DEBUG_MACRO}")

add_executable(
    treeview
    
    ${TREEVIEW_SOURCES}
)

set_target_properties(treeview PROPERTIES COMPILE_FLAGS -DWXUSINGLIB_WXSQLITE3)

add_executable(
    minimal

    ${MINIMAL_SOURCES}
)

set_target_properties(minimal PROPERTIES COMPILE_FLAGS -DWXUSINGLIB_WXSQLITE3)

add_dependencies(treeview wxsqlite3)
add_dependencies(minimal wxsqlite3)
target_link_libraries(treeview wxsqlite3)
target_link_libraries(minimal wxsqlite3)

IF(MSVC)
    set_target_properties(minimal PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
ENDIF()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT treeview)

find_package (wxWidgets REQUIRED core base adv)
if(wxWidgets_FOUND)
    foreach(F ${wxWidgets_DEFINITIONS})
        add_definitions("-D${F}")
    endforeach()

    foreach(F ${wxWidgets_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} ${F}")
    endforeach()
  
    include_directories(${wxWidgets_INCLUDE_DIRS})
    target_link_libraries (treeview ${wxWidgets_LIBRARIES})
    target_link_libraries (minimal ${wxWidgets_LIBRARIES})
endif(wxWidgets_FOUND)

