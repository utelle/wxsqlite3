dofile "premake/wxwidgets.lua"

BUILDDIR = _OPTIONS["builddir"] or "build"

workspace "wxsqlite3"
  configurations { "Debug", "Release", "DLL Debug", "DLL Release" }
  platforms { "Win32", "Win64" }
  location(BUILDDIR)

  if (is_msvc) then
    local wks = workspace()
    wks.filename = "wxsqlite3_" .. vc_with_ver
  end

  defines {
    "_WINDOWS",
    "_CRT_SECURE_NO_WARNINGS",
    "_CRT_SECURE_NO_DEPRECATE",
    "_CRT_NONSTDC_NO_DEPRECATE"
  }

  init_filters()

-- wxSQLite3 as static library
project "wxsqlite3"
  location(BUILDDIR)
  language "C++"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_wxsqlite3"
  end

  make_filters( "WXSQLITE3" )

  defines {
    "wxUSE_DYNAMIC_SQLITE3_LOAD=0",
    "WXSQLITE3_HAVE_METADATA=1",
    "WXSQLITE3_HAVE_CODEC=1",
    "WXSQLITE3_HAVE_LOAD_EXTENSION=0"
  }

  files { "src/*.cpp", "include/wx/*.h" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp" }
  }
  includedirs { "include", "sqlite3/include" }
  flags { "Unicode" }  
  links { "sqlite3" }
  libdirs { "sqlite3/secure/aes128/dll/release" }

-- Minimal wxSQLite3 sample
project "minimal"
  location(BUILDDIR)
  language "C++"
  kind "ConsoleApp"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_minimal"
  end

  use_filters( "WXSQLITE3" )

  files { "samples/*.cpp", "samples/*.rc" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc" }
  }
  includedirs { "samples", "include" }
  flags { "Unicode", "WinMain" }  
  links { "wxsqlite3" }
  links { "sqlite3" }
  libdirs { "sqlite3/secure/aes128/dll/release" }
  targetdir "samples"
