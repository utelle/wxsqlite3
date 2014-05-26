/////////////////////////////////////////////////////////////////////////////
// Name:        treeviewapp.h
// Purpose:     
// Author:      Ulrich Telle
// Modified by: 
// Created:     2014-05-11
// Copyright:   (c) Ulrich Telle
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _TREEVIEW_APP_H_
#define _TREEVIEW_APP_H_


/*!
 * Includes
 */

#include <wx/image.h>

#include "treeviewsample.h"

/*!
 * TreeviewSampleApp class declaration
 */

class TreeviewSampleApp: public wxApp
{    
  DECLARE_CLASS( TreeviewSampleApp )
  DECLARE_EVENT_TABLE()

public:
  /// Constructor
  TreeviewSampleApp();

  void Init();

  /// Initialises the application
  virtual bool OnInit();

  /// Called on exit
  virtual int OnExit();

  /// Initialize sample database
  bool InitializeDatabase();

  TreeviewSample* m_mainFrameWindow;
  wxSQLite3Database m_db;
};

/*!
 * Application instance declaration 
 */

DECLARE_APP(TreeviewSampleApp)

#endif
    // _TREEVIEWAPP_H_
