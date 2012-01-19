dofile "premake/wxwidgets.lua"

solution "wxsqlite3"
  configurations { "Debug", "Release" }

-- wxSQLite3 as static library
project "wxsqlite3lib"
  --uuid "8B4C3E27-674F-6740-B5F8-5E7BB48E1A9F"
  kind "StaticLib"
  language "C++"
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp" }
  }
  files { "src/*.cpp", "include/wx/*.h" }
  includedirs { "include", "sqlite3/include" }
  flags { "Unicode" }  
  links { "sqlite3" }
  libdirs { "sqlite3/secure/aes128/dll/release" }

  location "build/wxsqlite3lib"
  targetname "wxsqlite3"

  defines {
    "WIN32",
    "_WINDOWS",
    "_LIB",
    "WXMAKINGLIB_WXSQLITE3",
    "wxUSE_DYNAMIC_SQLITE3_LOAD=0",
    "WXSQLITE3_HAVE_METADATA=1",
    "WXSQLITE3_HAVE_CODEC=1",
    "WXSQLITE3_HAVE_LOAD_EXTENSION=0",
    "_CRT_SECURE_NO_WARNINGS",
    "_CRT_SECURE_NO_DEPRECATE",
    "_CRT_NONSTDC_NO_DEPRECATE"
  }

  configuration "Debug"
    targetdir "bin/lib/debug"
    defines {
      "DEBUG", 
      "_DEBUG"
    }
    flags { "Symbols" }
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="yes"}
 
  configuration "Release"
    targetdir "bin/lib/release"
    defines { 
      "NDEBUG" 
    }
    flags { "Optimize" }  
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="no"}

-- wxSQLite3 as shared library
project "wxsqlite3dll"
  uuid "8B4C3E27-674F-6740-B5F8-5E7BB48E1A9F"
  kind "SharedLib"
  language "C++"
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp" }
  }
  files { "src/*.cpp", "include/wx/*.h" }
  includedirs { "include", "sqlite3/include" }
  flags { "Unicode" }  
  links { "sqlite3" }
  libdirs { "sqlite3/secure/aes128/dll/release" }

  location "build/wxsqlite3dll"
  targetname "wxsqlite3"

  defines {
    "WIN32",
    "_WINDOWS",
    "_USRDLL",
    "WXMAKINGDLL_WXSQLITE3",
    "wxUSE_DYNAMIC_SQLITE3_LOAD=0",
    "WXSQLITE3_HAVE_METADATA=1",
    "WXSQLITE3_HAVE_CODEC=1",
    "WXSQLITE3_HAVE_LOAD_EXTENSION=0",
    "_CRT_SECURE_NO_WARNINGS",
    "_CRT_SECURE_NO_DEPRECATE",
    "_CRT_NONSTDC_NO_DEPRECATE"
  }

  configuration "Debug"
    targetdir "bin/dll/debug"
    defines {
      "DEBUG", 
      "_DEBUG"
    }
    flags { "Symbols" }
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="yes"}
 
  configuration "Release"
    targetdir "bin/dll/release"
    defines { 
      "NDEBUG" 
    }
    flags { "Optimize" }  
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="no"}

-- Minimal wxSQLite3 sample
project "minimal"
  uuid "2A32F255-01A7-914A-93EF-BEC9D76F3875"
  kind "ConsoleApp"
  language "C++"
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc" }
  }
  files { "samples/*.cpp", "samples/*.rc" }
  includedirs { "include" }
  flags { "Unicode" }  
  links { "wxsqlite3dll" }

  location "build/minimal"

  defines {
    "WIN32",
    "_WINDOWS",
    "WXUSINGDLL_WXSQLITE3",
    "_CRT_SECURE_NO_WARNINGS",
    "_CRT_SECURE_NO_DEPRECATE",
    "_CRT_NONSTDC_NO_DEPRECATE"
  }

  configuration "Debug"
    targetdir "bin/dll/debug"
    defines { "DEBUG" }
    flags { "Symbols" }
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="yes"}
 
  configuration "Release"
    targetdir "bin/dll/release"
    defines { "NDEBUG" }
    flags { "Optimize" }  
    wx_config {Unicode="yes", Version="2.8", Static="no", Debug="no"}
