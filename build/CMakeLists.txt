cmake_minimum_required(VERSION 3.6)

project(wxSQLite3)

option(STATIC_RUNTIME "link with c++ runtime statically" "ON")
option(WXSQLITE3_BUILD_SHARED "Build wxSQLite3 as shared library" ON)
option(BUILD_SHARED_LIBS "Link with shared wxWidgets library" ON)

if((CMAKE_SIZEOF_VOID_P EQUAL 8) AND CMAKE_COMPILER_IS_GNUCC)
    option(USE_32 "create 32 bit binaries" "OFF")
endif()

option(SQLITE_DEBUG "enable SQLite debug" "OFF")
option(PEDANTIC_COMPILER_FLAGS "Enable additional checking for ill-formed code" "ON")
if(MSVC)
    option(CPP_EXCEPTIONS_ONLY "Catch only C++ exceptions(/EHsc) instead of catching all exceptions(/EHa)" "ON")
    option(THREAD_SAVE_STATIC_INIT "Enable thread safe initialization of static variables" "OFF")
endif(MSVC)
option(RELEASE_DEBUG_SYMBOLS "Generate debugging symbols for optimized build" "OFF")
set(SQLITE_CODEC_TYPE "DEFAULT" CACHE STRING "DB Codec(AES128, AES256, CHACHA20, SQLCIPHER, RC4, DEFAULT)")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set(LIBRARY_SOURCES
    "../include/wx/wxsqlite3_version.h"
    "../include/wx/wxsqlite3def.h"
    "../include/wx/wxsqlite3opt.h"
    "../src/sqlite3mc_amalgamation.h"
    
    "../src/sqlite3mc_amalgamation.c"
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
                        /J      # use unsigned char
                        /Gd     # use cdecl
                        /MP     # multiprocessor compilation
                        /utf-8  # utf-8 source
                        /GF     # eliminate duplicate strings
                        /wd4996 # disable 'The POSIX name for this item is deprecated ...'
    )
                        
    if(PEDANTIC_COMPILER_FLAGS)
        add_compile_options(# treat warnings as errors
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
        )
    endif(PEDANTIC_COMPILER_FLAGS)
    
    if(CPP_EXCEPTIONS_ONLY)
        add_compile_options(/EHsc) # exceptions: sync
    else()
        add_compile_options(/EHa) # exceptions: sync
    endif(CPP_EXCEPTIONS_ONLY)
    
    if((NOT THREAD_SAVE_STATIC_INIT) AND (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 19.00))
        add_compile_options(/Zc:threadSafeInit-) # https://connect.microsoft.com/VisualStudio/feedback/details/1789709/visual-c-2015-runtime-broken-on-windows-server-2003-c-11-magic-statics
    endif()
    
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
    
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    
    if(STATIC_RUNTIME)
        set(RELEASE_RUNTIME "/MT")
        set(DEBUG_RUNTIME "/MTd")
    else()
        set(RELEASE_RUNTIME "/MD")
        set(DEBUG_RUNTIME "/MDd")
    endif(STATIC_RUNTIME)
    
    if(RELEASE_DEBUG_SYMBOLS)
        set(DBG_LINKER_FLAG /DEBUG)
    endif(RELEASE_DEBUG_SYMBOLS)
    
    set(CMAKE_EXE_LINKER_FLAGS "/LARGEADDRESSAWARE /SUBSYSTEM:WINDOWS")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF,ICF ${DBG_LINKER_FLAG}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF,ICF ${DBG_LINKER_FLAG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG /Ox /Ob2 /Oi /Ot /Oy /GS- /Gy /GR- /GL /Gw ${RELEASE_RUNTIME}")
    set(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /GS -D_DEBUG ${DEBUG_RUNTIME}")
    set(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
elseif(CMAKE_COMPILER_IS_GNUCC)
    add_compile_options(-pipe
                        -funsigned-char
                        -fno-rtti
                        -W
                        -Wall
                        )
                        
    if(PEDANTIC_COMPILER_FLAGS)
        add_compile_options(-Wextra
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
                            
                            -Werror=return-type
                            -Werror=pointer-arith
                            -Werror=unused-value
                            -Werror=sizeof-pointer-memaccess
                            -Werror=implicit-function-declaration
                            
#                            -Werror=missing-declarations
#                            -Werror=missing-prototypes
                            -Werror=reorder
                            -Werror=declaration-after-statement
                            -Werror=stringop-overflow
        )
        
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=delete-non-virtual-dtor")       
        set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wimplicit-int -Werror=implicit-int")
    endif(PEDANTIC_COMPILER_FLAGS)

    if(RELEASE_DEBUG_SYMBOLS)
        set(DBG_FLAG -g)
    else()
        set(DBG_FLAG -s)
    endif(RELEASE_DEBUG_SYMBOLS)

    set(CMAKE_CXX_FLAGS_RELEASE  "-O2 ${DBG_FLAG} -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE    ${CMAKE_CXX_FLAGS_RELEASE})
    set(CMAKE_CXX_FLAGS_DEBUG    "-O0 -g -D_DEBUG -D__DEBUG__ -DDEBUG_LEVEL=3 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC")
    set(CMAKE_C_FLAGS_DEBUG      ${CMAKE_CXX_FLAGS_DEBUG})
    
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "${CMAKE_EXE_LINKER_FLAGS} -g")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS} -g")
    
    set(CMAKE_EXE_LINKER_FLAGS_VALGRIND     "${CMAKE_EXE_LINKER_FLAGS} -g")
    set(CMAKE_SHARED_LINKER_FLAGS_VALGRIND  "${CMAKE_SHARED_LINKER_FLAGS} -g")
    
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE    "${CMAKE_EXE_LINKER_FLAGS} ${DBG_FLAG}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS} ${DBG_FLAG}")
    
    if(USE_32)
        add_compile_options (-m32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
    endif(USE_32)
    
    if(STATIC_RUNTIME)
        if(MINGW)
            set(STATIC_LINKER_FLAGS "-static -Wl,--allow-multiple-definition")
        else()
            set(STATIC_LINKER_FLAGS "-static-libgcc -static-libstdc++")
        endif(MINGW)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${STATIC_LINKER_FLAGS}")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${STATIC_LINKER_FLAGS}")
    endif(STATIC_RUNTIME)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'" )
endif(MSVC)

include_directories(
    "../include/"
    "../src/"
)

if (WXSQLITE3_BUILD_SHARED)
    set(WXSQLITE3_LIBRARY_TYPE SHARED)
    set(WXSQLITE3_MAKING_DEF "WXMAKINGDLL_WXSQLITE3")
    set(WXSQLITE3_USING_DEF "WXUSINGDLL_WXSQLITE3")
else()
    set(WXSQLITE3_LIBRARY_TYPE STATIC)
    set(WXSQLITE3_MAKING_DEF "WXMAKINGLIB_WXSQLITE3")
    set(WXSQLITE3_USING_DEF "WXUSINGLIB_WXSQLITE3")
endif(WXSQLITE3_BUILD_SHARED)

add_library(
    wxsqlite3
    ${WXSQLITE3_LIBRARY_TYPE}

    ${LIBRARY_SOURCES}
)

if(SQLITE_DEBUG)
    set(SQLITE_DEBUG_MACRO "-DSQLITE_ENABLE_DEBUG=1")
endif(SQLITE_DEBUG)

set_target_properties(wxsqlite3 PROPERTIES COMPILE_FLAGS "-D_LIB \
                                                          -D${WXSQLITE3_MAKING_DEF} \
                                                          -DSQLITE_THREADSAFE=1 \
                                                          -DSQLITE_MAX_ATTACHED=10 \
                                                          -DSQLITE_DQS=0 \
                                                          -DSQLITE_ENABLE_EXPLAIN_COMMENTS=1 \
                                                          -DSQLITE_SOUNDEX=1 \
                                                          -DSQLITE_ENABLE_COLUMN_METADATA=1 \
                                                          -DSQLITE_SECURE_DELETE=1 \
                                                          -DSQLITE_ENABLE_DESERIALIZE=1 \
                                                          -DSQLITE_ENABLE_FTS3=1 \
                                                          -DSQLITE_ENABLE_FTS3_PARENTHESIS=1 \
                                                          -DSQLITE_ENABLE_FTS4=1 \
                                                          -DSQLITE_ENABLE_FTS5=1 \
                                                          -DSQLITE_ENABLE_JSON1=1 \
                                                          -DSQLITE_ENABLE_RTREE=1 \
                                                          -DSQLITE_ENABLE_GEOPOLY=1 \
                                                          -DSQLITE_CORE=1 \
                                                          -DSQLITE_ENABLE_EXTFUNC=1 \
                                                          -DSQLITE_ENABLE_CSV=1 \
                                                          -DSQLITE_ENABLE_SHA3=1 \
                                                          -DSQLITE_ENABLE_CARRAY=1 \
                                                          -DSQLITE_ENABLE_FILEIO=1 \
                                                          -DSQLITE_ENABLE_SERIES=1 \
                                                          -DSQLITE_ENABLE_UUID=1 \
                                                          -DSQLITE_ENABLE_REGEXP=1 \
                                                          -DSQLITE_TEMP_STORE=2 \
                                                          -DSQLITE_USE_URI=1 \
                                                          -DSQLITE_USER_AUTHENTICATION=1 \
                                                          -DCODEC_TYPE=CODEC_TYPE_${SQLITE_CODEC_TYPE} \
                                                          ${SQLITE_DEBUG_MACRO}")

add_executable(
    treeview
    WIN32
    ${TREEVIEW_SOURCES}
)

set_target_properties(treeview PROPERTIES COMPILE_FLAGS -D${WXSQLITE3_USING_DEF})

add_executable(
    minimal

    ${MINIMAL_SOURCES}
)

set_target_properties(minimal PROPERTIES COMPILE_FLAGS -D${WXSQLITE3_USING_DEF})

add_dependencies(treeview wxsqlite3)
add_dependencies(minimal wxsqlite3)
target_link_libraries(treeview wxsqlite3)
target_link_libraries(minimal wxsqlite3)

IF(MSVC)
    set_target_properties(minimal PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
ENDIF(MSVC)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT treeview)

message("//===--- current configuration ---===//")

if(MSVC)
    set(COMPILER_SPECIFIC_OPTIONS  CPP_EXCEPTIONS_ONLY
                                   THREAD_SAVE_STATIC_INIT
    )
elseif(CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER_SPECIFIC_OPTIONS  CPP_EXCEPTIONS_ONLY)
endif(MSVC)

option(SQLITE_DEBUG "enable SQLite debug" "OFF")
option(PEDANTIC_COMPILER_FLAGS "Enable additional checking for ill-formed code" "ON")
option(THREAD_SAVE_STATIC_INIT "Enable thread safe initialization of static variables" "OFF")
option(RELEASE_DEBUG_SYMBOLS "Generate debugging symbols for optimized build" "OFF")
set(SQLITE_CODEC_TYPE "DEFAULT" CACHE STRING "DB Codec(AES128, AES256, CHACHA20, SQLCIPHER, RC4, DEFAULT)")

foreach(V   ${COMPILER_SPECIFIC_OPTIONS}
            STATIC_RUNTIME
            SQLITE_DEBUG
            PEDANTIC_COMPILER_FLAGS
            THREAD_SAVE_STATIC_INIT
            RELEASE_DEBUG_SYMBOLS
            SQLITE_CODEC_TYPE
            WXSQLITE3_BUILD_SHARED
       )
    message("${V}: ${${V}}")
endforeach()

message("")

find_package (wxWidgets REQUIRED core base adv)
if(wxWidgets_FOUND)
    set(WXDEFS "wxWidgets definitions:")
    foreach(F ${wxWidgets_DEFINITIONS})
        add_definitions("-D${F}")
        set(WXDEFS "${WXDEFS} ${F}")
    endforeach()

    set(WXFLAGS "wxWidgets compiler flags:")
    foreach(F ${wxWidgets_CXX_FLAGS})
        set(CMAKE_CXX_FLAGS "${COMMON_CXX_FLAGS} ${F}")
        set(WXFLAGS "${WXFLAGS} ${F}")
    endforeach()
  
    include_directories(${wxWidgets_INCLUDE_DIRS})
    target_link_libraries (treeview ${wxWidgets_LIBRARIES})
    target_link_libraries (minimal ${wxWidgets_LIBRARIES})
    if (WXSQLITE3_BUILD_SHARED)
        target_link_libraries (wxsqlite3 ${wxWidgets_LIBRARIES})
    endif(WXSQLITE3_BUILD_SHARED)
    
    message(${WXDEFS})
    message(${WXFLAGS})
    message("wxWidgets include directories: ${wxWidgets_INCLUDE_DIRS}")
    message("wxWidgets libraries: ${wxWidgets_LIBRARIES}")
endif(wxWidgets_FOUND)

message("")
message("//===---          ***          ---===//")
