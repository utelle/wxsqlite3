-- wxSQLite3 configuration file for premake5
--
-- Copyright (C) 2017 Ulrich Telle <ulrich@telle-online.de>
--
-- This file is covered by the same licence as the entire wxsqlite3 package. 

dofile "premake/wxwidgets.lua"

BUILDDIR = _OPTIONS["builddir"] or "build"

workspace "wxsqlite3"
  configurations { "Debug", "Release", "Debug wxDLL", "Release wxDLL", "DLL Debug", "DLL Release" }
  platforms { "x32", "x64" }
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

-- wxSQLite3
project "wxsqlite3"
  location(BUILDDIR)
  language "C++"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_wxsqlite3"
  end
  if wxMonolithic then
    local prj = project()
    prj.filename = "wxsqlite3_mono"
  end

  make_filters( "WXSQLITE3", "wxsqlite3", "core" )

  defines {
    "wxUSE_DYNAMIC_SQLITE3_LOAD=0",
    "WXSQLITE3_HAVE_METADATA=1",
    "WXSQLITE3_USER_AUTHENTICATION=1",
    "WXSQLITE3_HAVE_CODEC=1",
    "WXSQLITE3_HAVE_LOAD_EXTENSION=0",
    "THREADSAFE=1",
    "SQLITE_SOUNDEX",
    "SQLITE_ENABLE_COLUMN_METADATA",
    "SQLITE_HAS_CODEC",
    "CODEC_TYPE=$(CODEC_TYPE)",
    "SQLITE_ENABLE_DEBUG=$(SQLITE_ENABLE_DEBUG)",
    "SQLITE_SECURE_DELETE",
    "SQLITE_ENABLE_FTS3",
    "SQLITE_ENABLE_FTS3_PARENTHESIS",
    "SQLITE_ENABLE_FTS4",
    "SQLITE_ENABLE_FTS5",
    "SQLITE_ENABLE_JSON1",
    "SQLITE_ENABLE_RTREE",
    "SQLITE_CORE",
    "SQLITE_ENABLE_EXTFUNC",
    "SQLITE_ENABLE_CSV",
    "SQLITE_ENABLE_SHA3",
    "SQLITE_USE_URI",
    "SQLITE_USER_AUTHENTICATION"
  }

  files { "src/*.cpp", "src/*.rc", "include/wx/*.h",
          "sqlite3/secure/src/sqlite3secure.c", "sqlite3/secure/src/*.h" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc", "**/sqlite3secure.c", "**.def" }
  }
  includedirs { "include", "sqlite3/secure/src" }
  characterset "Unicode"

-- Minimal wxSQLite3 sample
project "minimal"
  location(BUILDDIR)
  language "C++"
  kind "ConsoleApp"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_minimal"
  end
  if wxMonolithic then
    local prj = project()
    prj.filename = "minimal_mono"
  end

  use_filters( "WXSQLITE3", "samples", "core" )

  files { "samples/*.cpp", "samples/*.rc" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc" }
  }
  includedirs { "samples", "include" }
  characterset "Unicode"
  flags { "WinMain" }  
  links { "wxsqlite3" }

-- Minimal wxSQLite3 sample
project "treeview"
  location(BUILDDIR)
  language "C++"
  kind "WindowedApp"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_treeview"
  end
  if wxMonolithic then
    local prj = project()
    prj.filename = "treeview_mono"
  end

  use_filters( "WXSQLITE3", "samples/treeview", "adv,core,xml" )

  files { "samples/treeview/*.cpp", "samples/treeview/*.rc" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc" }
  }
  includedirs { "samples/treeview", "include" }
  characterset "Unicode"
  flags { "WinMain" }  
  links { "wxsqlite3" }
