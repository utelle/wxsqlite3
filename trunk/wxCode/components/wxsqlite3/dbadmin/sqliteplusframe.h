/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : sqliteplusframe.h                                               */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 04/07/2007 */
/* email   : softinthebox@free.fr                      Révision : 16/05/2008 */
/*---------------------------------------------------------------------------*/
/* Copyright (C) Fred Cailleau-Lepetit 2007                                  */
/* Licence GNU General Public License  http://www.fsf.org/copyleft/gpl.html  */
/*---------------------------------------------------------------------------*/
/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation (version 3).

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Ce programme est libre, vous pouvez le redistribuer et/ou le modifier
selon les termes de la Licence Publique Générale GNU publiée par la
Free Software Foundation (version 3).

Ce programme est distribué car potentiellement utile, mais
SANS AUCUNE GARANTIE, ni explicite ni implicite, y compris
les garanties de commercialisation ou d'adaptation dans un but
spécifique. Reportez-vous à la Licence Publique Générale GNU
pour plus de détails.
*/
#ifndef _SQLITEPLUSFRAME_H_
#define _SQLITEPLUSFRAME_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "sqliteplusframe.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/wxsqlite3.h>
#include <wx/treectrl.h>
#include <wx/aui/auibook.h>
#include <wx/socket.h>
#include <wx/imaglist.h>
#include "sqlite3table.h"
/*---------------------------------------------------------------------------*/
class wxTreeCtrl;
class wxAuiNotebook;
class wxMenu;
/*---------------------------------------------------------------------------*/
enum wxSQLiteObjectType {otNone = -1, otTable = 0, otView, otIndex,
                         otTrigger, otTableAndView};
/*---------------------------------------------------------------------------*/
class wxSQLitePlusFrame: public wxFrame
{
   DECLARE_DYNAMIC_CLASS(wxSQLitePlusFrame)
   DECLARE_EVENT_TABLE()

   public:

      wxSQLitePlusFrame();
      wxSQLitePlusFrame(wxWindow* parent, wxWindowID id = -1,
                        const wxString& caption = _("wxSQLite+"),
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxSize(725, 550),
                        long style = wxDEFAULT_FRAME_STYLE);

      bool Create(wxWindow* parent, wxWindowID id = -1,
                  const wxString& caption = _("wxSQLite+"),
                  const wxPoint& pos = wxDefaultPosition,
                  const wxSize& size = wxSize(725, 550),
                  long style = wxDEFAULT_FRAME_STYLE);

      ~wxSQLitePlusFrame();

      wxString GetObjTypeName(wxSQLiteObjectType objtype);
      wxSQLiteObjectType GetObjNameType(const wxString& name);
      wxSQLite3ResultSet GetObjNameList(wxSQLiteObjectType objtype,
                                        const wxString& dbname = wxEmptyString);
      bool ExistDbObject(wxSQLiteObjectType objtype, const wxString& name,
                         const wxString& dbname = wxEmptyString);
      wxString GetDbObjectDDL(wxSQLiteObjectType objtype, const wxString& name,
                              const wxString& dbname = wxEmptyString);

      bool DoFinishTransaction();

      void CmdOpen(const wxString& file);

      void LaunchServer();

   protected:

      void Init();
      void CreateControls();
      void CreateToolbars();
      void CreateMenus();

      void OnServerEvent(wxSocketEvent& event);
      void OnSrvSocketEvent(wxSocketEvent& event);

      void OnCloseWindow(wxCloseEvent& event);
      void OnDbtreeItemRightClick(wxTreeEvent& event);
      void OnDbtreeItemSelChanged(wxTreeEvent& event);
      void OnDbtreeItemActivated(wxTreeEvent& event);
      void OnOpenCreateClick(wxCommandEvent& event);
      void OnAttachDbClick(wxCommandEvent& event);
      void OnReKeyDbClick(wxCommandEvent& event);
      void OnMnuCloseDbClick(wxCommandEvent& event);
      void OnMnuCloseDbUpdate(wxUpdateUIEvent& event);
      void OnMnuBackupDbClick(wxCommandEvent& event);
      void OnMnuRestoreDbClick(wxCommandEvent& event);
      void OnDetachDbClick(wxCommandEvent& event);
      void OnDetachDbUpdate(wxUpdateUIEvent& event);
      void OnRefreshClick(wxCommandEvent& event);
      void OnRefreshAllClick(wxCommandEvent& event);
      void OnPreferencesClick(wxCommandEvent& event);
      void OnExitClick(wxCommandEvent& event);
      void OnEventClick(wxCommandEvent& event);
      void OnEventUpdate(wxUpdateUIEvent& event);
      void OnCopyClick(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnMnuAddTableClick(wxCommandEvent& event);
      void OnMnuDelTableClick(wxCommandEvent& event);
      void OnMnuAddViewClick(wxCommandEvent& event);
      void OnMnuDelViewClick(wxCommandEvent& event);
      void OnMnuAddIndexClick(wxCommandEvent& event);
      void OnMnuAddIndexUpdate(wxUpdateUIEvent& event);
      void OnMnuDelIndexClick(wxCommandEvent& event);
      void OnMnuAddTriggerClick(wxCommandEvent& event);
      void OnMnuAddTriggerUpdate(wxUpdateUIEvent& event);
      void OnMnuDelTriggerClick(wxCommandEvent& event);
      void OnMnuAddColumnsClick(wxCommandEvent& event);
      void OnMnuAutotransactClick(wxCommandEvent& event);
      void OnMnuShowTreeClick(wxCommandEvent& event);
      void OnMnuTbFileClick(wxCommandEvent& event);
      void OnMnuTbEditClick(wxCommandEvent& event);
      void OnMnuTbDatabaseClick(wxCommandEvent& event);
      void OnMnuTbQueryClick(wxCommandEvent& event);
      void OnMnuTbTransactClick(wxCommandEvent& event);
      void OnHelpClick(wxCommandEvent& event);
      void OnAboutClick(wxCommandEvent& event);
      void OnMnuDropObjectClick(wxCommandEvent& event);
      void OnMnuExploreClick(wxCommandEvent& event);
      void OnMnuExploreUpdate(wxUpdateUIEvent& event);
      void OnMnuShowTreeUpdate(wxUpdateUIEvent& event);
      void OnMnuTbFileUpdate(wxUpdateUIEvent& event);
      void OnMnuTbEditUpdate(wxUpdateUIEvent& event);
      void OnMnuTbDatabaseUpdate(wxUpdateUIEvent& event);
      void OnMnuTbQueryUpdate(wxUpdateUIEvent& event);
      void OnMnuTbTransactUpdate(wxUpdateUIEvent& event);

      void OnNotebookPageClose(wxAuiNotebookEvent& evt);

      wxAuiManager& GetAuiManager() {return m_auiManager;}

      static bool ShowToolTips();

   private:

      wxSocketServer* m_Server;
      wxAuiManager m_auiManager;
      wxTreeCtrl* m_TreeCtrl;
      wxAuiNotebook* m_CenterNotebook;
      wxMenu* m_MnuFile;
      wxMenu* m_MnuEdit;
      wxMenu* m_MnuDatabase;
      wxMenu* m_MnuTransact;
      wxMenu* m_MnuWindow;
      wxMenu* m_MnuHelp;
      wxToolBar* m_TbFile;
      wxToolBar* m_TbEdit;
      wxToolBar* m_TbQuery;
      wxToolBar* m_TbTransact;
      wxToolBar* m_TbDatabase;

      wxSQLite3Database m_db;
      SQLite3HookForCount m_Hook;
      wxImageList m_TreeImageList;
      wxString m_DbName;
      int m_NodeType;
      wxString m_NodeText;
      wxString m_NodeDbName;

      void InitTree();

      bool CloseDatabase();
      bool OpenDatabase(const wxString& dbfullname, const wxString& name);
      bool AttachDatabase(const wxString& dbfile, const wxString& dbalias,
                          const wxString& dbkey = wxEmptyString);
      bool EncryptDatabase(const wxString& dbkey);
      wxWindow* GetPage(const wxString& name);
      void DropDbObject(wxSQLiteObjectType type = otNone);
      void CreateIndex(const wxString& dbname,
                       const wxString& tablename = wxEmptyString);
      void CreateTable(const wxString& dbname);
      void CreateView(const wxString& dbname);
      void CreateTrigger(const wxString& dbname, bool useobj = false,
                         bool istable = true,
                         const wxString& objname = wxEmptyString);
      void AddColumns(const wxString& dbname,
                      const wxString& tablename = wxEmptyString);

      wxTreeItemId GetItem(const wxString& dbname, int imageId);
      wxString GetDbNameFromItem(wxTreeItemId item);
      wxTreeItemId GetItemFromDbName(const wxString& dbname);
      bool DatabaseExist(const wxString& dbname, bool alias = true,
                         wxString* val = NULL);
      void InitNodeParams();
      bool TryToRefresh();
      void HideShowPane(wxWindow* win);
      bool IsShownPane(wxWindow* win);
      bool HaveAttachedDatabase();

      void DoRefresh(bool refreshall = false);
      void RefreshDatabase(const wxString& dbname, bool forceexpand = true);
      void RefreshTables(const wxString& dbname);
      void RefreshViews(const wxString& dbname);
      void RefreshIndexes(const wxString& dbname);
      void RefreshTriggers(const wxString& dbname);

      static wxMenu* GetPopupMenu(int type);
      static wxMenu* CreateMenuDatabase();
      static wxMenu* CreateMenuTables();
      static wxMenu* CreateMenuIndexes();
      static wxMenu* CreateMenuViews();
      static wxMenu* CreateMenuTriggers();
};
/*---------------------------------------------------------------------------*/
#endif   // _SQLITEPLUSFRAME_H_
