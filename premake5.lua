-- wxSQLite3 configuration file for premake5
--
-- Copyright (C) 2017-2020 Ulrich Telle <ulrich@telle-online.de>
--
-- This file is covered by the same licence as the entire wxsqlite3 package. 

dofile "premake/wxwidgets.lua"

BUILDDIR = _OPTIONS["builddir"] or "build"

workspace "wxsqlite3"
  configurations { "Debug", "Release", "Debug wxDLL", "Release wxDLL", "Debug DLL", "Release DLL" }
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

-- wxSQLite3
project "wxsqlite3"
  location(BUILDDIR)
  language "C++"

  if (is_msvc) then
    local prj = project()
    prj.filename = "wxsqlite3_" .. vc_with_ver .. "_wxsqlite3"
  else
    buildoptions { "-msse4.2 -maes" }
  end
  
  if wxMonolithic then
    local prj = project()
    prj.filename = "wxsqlite3_mono"
  end

  make_filters( "WXSQLITE3", "wxsqlite3", "core" )

  defines {
    "CODEC_TYPE=$(CODEC_TYPE)",
    "SQLITE_ENABLE_DEBUG=$(SQLITE_ENABLE_DEBUG)",
    "SQLITE_THREADSAFE=1",
    "SQLITE_DQS=0",
    "SQLITE_MAX_ATTACHED=10",
    "SQLITE_ENABLE_EXPLAIN_COMMENTS=1",
    "SQLITE_SOUNDEX=1",
    "SQLITE_ENABLE_COLUMN_METADATA=1",
    "SQLITE_SECURE_DELETE=1",
    "SQLITE_ENABLE_DESERIALIZE=1",
    "SQLITE_ENABLE_FTS3=1",
    "SQLITE_ENABLE_FTS3_PARENTHESIS=1",
    "SQLITE_ENABLE_FTS4=1",
    "SQLITE_ENABLE_FTS5=1",
    "SQLITE_ENABLE_JSON1=1",
    "SQLITE_ENABLE_RTREE=1",
    "SQLITE_ENABLE_GEOPOLY=1",
    "SQLITE_CORE=1",
    "SQLITE_ENABLE_EXTFUNC=1",
    "SQLITE_ENABLE_CSV=1",
    "SQLITE_ENABLE_VSV=1",
    "SQLITE_ENABLE_SHA3=1",
    "SQLITE_ENABLE_CARRAY=1",
    "SQLITE_ENABLE_FILEIO=1",
    "SQLITE_ENABLE_SERIES=1",
    "SQLITE_ENABLE_UUID=1",
    "SQLITE_ENABLE_REGEXP=1",
    "SQLITE_TEMP_STORE=2",
    "SQLITE_USE_URI=1",
    "SQLITE_USER_AUTHENTICATION=1"
  }

  files { "src/*.cpp", "src/*.rc", "include/wx/*.h",
          "src/sqlite3mc*.c", "src/*.h" }
  vpaths {
    ["Header Files"] = { "**.h" },
    ["Source Files"] = { "**.cpp", "**.rc", "**/sqlite3mc*.c", "**.def" }
  }
  includedirs { "include", "src" }
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
  entrypoint "WinMainCRTStartup"
  links { "wxsqlite3" }
