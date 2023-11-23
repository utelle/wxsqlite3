/*
** Name:        treeviewapp.cpp
** Purpose:     Treeview sample application
** Author:      Ulrich Telle
** Created:     2014-05-11
** Copyright:   (c) 2014-2018 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "treeviewapp.h"

/*
 * Application instance implementation
 */

IMPLEMENT_APP( TreeviewSampleApp )

/*
 * TreeviewSampleApp type definition
 */

IMPLEMENT_CLASS( TreeviewSampleApp, wxApp )


/*
 * TreeviewSampleApp event table definition
 */

BEGIN_EVENT_TABLE( TreeviewSampleApp, wxApp )

END_EVENT_TABLE()


/*
 * Constructor for TreeviewSampleApp
 */

TreeviewSampleApp::TreeviewSampleApp()
{
  Init();
}


/*
 * Member initialisation
 */

void
TreeviewSampleApp::Init()
{
}

/*
 * Initialisation for TreeviewSampleApp
 */

bool
TreeviewSampleApp::OnInit()
{    
  bool ok = true;

#if wxUSE_XPM
  wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
  wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
  wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
  wxImage::AddHandler(new wxGIFHandler);
#endif
  wxSQLite3Database::InitializeSQLite();
  ok = InitializeDatabase();
  if (ok)
  {
    m_mainFrameWindow = new TreeviewSample(&m_db, NULL);
    m_mainFrameWindow->Show(true);
    SetTopWindow(m_mainFrameWindow);
  }

  return ok;
}


/*
 * Cleanup for TreeviewSampleApp
 */

int
TreeviewSampleApp::OnExit()
{
  try
  {
    m_db.Close();
  }
  catch (wxSQLite3Exception& e)
  {
  }

  wxSQLite3Database::ShutdownSQLite();
  return wxApp::OnExit();
}

bool
TreeviewSampleApp::InitializeDatabase()
{
  bool ok = true;
  const char* sqlCommands[] = {
    "pragma foreign_keys=1;",
    "CREATE TABLE IF NOT EXISTS projects (\
       pid         integer not null,\
       prjtitle    varchar(72),\
       primary key (pid));",
    "CREATE TABLE IF NOT EXISTS folders (\
       fid     int         not null,\
       fname   varchar(64) not null,\
       fparent int         not null,\
       primary key (fid),\
       foreign key (fparent) references folders(fid) on delete cascade,\
       unique (fname, fparent));",
    "CREATE TABLE IF NOT EXISTS folderprojects (\
       fid  int not null,\
       pid  int not null,\
       foreign key (fid) references folders(fid) on delete restrict,\
       unique (fid,pid));",
    "CREATE TABLE IF NOT EXISTS folderclosure (\
       ancestor    int not null,\
       descendant  int not null,\
       distance    int not null,\
       primary key (ancestor, descendant),\
       foreign key (ancestor) references folders(fid),\
       foreign key (descendant) references folders(fid));",
    "CREATE TRIGGER IF NOT EXISTS ait_folders AFTER INSERT ON folders FOR EACH ROW\
       BEGIN\
         INSERT INTO folderclosure (ancestor, descendant, distance)\
         SELECT ancestor, NEW.fid, distance+1 FROM folderclosure\
           WHERE descendant = NEW.fparent\
           UNION ALL SELECT NEW.fid, NEW.fid, 0;\
       END;",
    "CREATE TRIGGER IF NOT EXISTS but_folders BEFORE UPDATE ON folders FOR EACH ROW\
       WHEN OLD.fparent != NEW.fparent\
       BEGIN\
         DELETE FROM folderclosure\
           WHERE descendant IN (SELECT descendant FROM folderclosure WHERE ancestor = OLD.fid)\
           AND ancestor NOT IN (SELECT descendant FROM folderclosure WHERE ancestor = OLD.fid);\
         INSERT INTO folderclosure (ancestor, descendant, distance)\
           SELECT supertree.ancestor, subtree.descendant, supertree.distance+subtree.distance+1\
             FROM folderclosure AS supertree JOIN folderclosure AS subtree\
            WHERE subtree.ancestor = OLD.fid\
              AND supertree.descendant = NEW.fparent;\
       END;",
    "CREATE TRIGGER IF NOT EXISTS bdt_folders BEFORE DELETE ON folders FOR EACH ROW\
       BEGIN\
         DELETE FROM folderclosure\
          WHERE descendant IN (SELECT descendant FROM folderclosure WHERE ancestor = OLD.fid);\
       END;",
    "INSERT OR IGNORE INTO folders (fid, fname, fparent) VALUES (1, 'root', 1);",
    NULL };

  int state = 0;
  int count;
  int j = 0;
  try
  {
    m_db.Open(wxT("tvtest.db3"));
    while (sqlCommands[j] != NULL)
    {
      m_db.ExecuteUpdate(sqlCommands[j]);
      ++j;
    }
    state = 1;
    count = m_db.ExecuteScalar("SELECT COUNT(*) FROM folderprojects;");
    if (count == 0)
    {
      m_db.ExecuteUpdate("INSERT OR IGNORE INTO projects VALUES (1,'Test project');");
      m_db.ExecuteUpdate("INSERT INTO folderprojects (fid, pid) SELECT 1, pid FROM projects;");
    }
  }
  catch (wxSQLite3Exception& e)
  {
    wxString msg;
    if (state == 0) msg = wxString(wxT("Error on creating the Treeview Sample database\n"));
    if (state == 0) msg = wxString(wxT("Error on initializing the Treeview Sample database\n"));
    msg += e.GetMessage();
    wxMessageBox(msg, wxT("Treeview Sample Database Error"), wxOK | wxCENTRE | wxICON_ERROR);
    ok = false;
  }
  return ok;
}
