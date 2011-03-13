/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : specgrid.h                                                      */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 07/09/2007 */
/* email   : softinthebox@free.fr                      Révision : 01/03/2009 */
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
#ifndef _SPECGRID_H_
#define _SPECGRID_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "specgrid.h"
#endif
/*---------------------------------------------------------------------------*/
#include <wx/grid.h>
#include <wx/generic/gridctrl.h>
#include <wx/dynarray.h>
#include <wx/arrimpl.cpp>
/*---------------------------------------------------------------------------*/
#ifdef WXMAKINGDLL_WXSCPECGRID
    #define WXDLLIMPEXP_SCPECGRID WXEXPORT
#elif defined(WXUSINGDLL_WXSCPECGRID)
    #define WXDLLIMPEXP_SCPECGRID WXIMPORT
#else // not making nor using DLL
    #define WXDLLIMPEXP_SCPECGRID
#endif
/*---------------------------------------------------------------------------*/
class wxSQLite3Database;
class WXDLLIMPEXP_SCPECGRID wxGridCellBlobEditorEvent;
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxCellsBlock
{
   public:

      wxCellsBlock()
      {
         m_LeftTop.Set(-1, -1);
         m_RightBottom.Set(-1, -1);
      }

      wxCellsBlock(int left, int top, int right, int bottom)
      {
         m_LeftTop.Set(top, left);
         m_RightBottom.Set(bottom, right);
      }

      wxCellsBlock(const wxGridCellCoords& topleft,
                   const wxGridCellCoords& bottomright)
      {
         m_LeftTop = topleft;
         m_RightBottom = bottomright;
      }

      wxCellsBlock(const wxCellsBlock& cellsblock)
      {
         m_LeftTop = cellsblock.m_LeftTop;
         m_RightBottom = cellsblock.m_RightBottom;
      }

      bool IsOk(){return (m_LeftTop.GetRow() < 0)||
                         (m_RightBottom.GetRow() < 0)||
                         (m_LeftTop.GetCol() < 0)||
                         (m_RightBottom.GetCol() < 0);}

      inline wxCellsBlock& operator=(const wxCellsBlock& cellsblock)
      {
         m_LeftTop = cellsblock.m_LeftTop;
         m_RightBottom = cellsblock.m_RightBottom;
         return *this;
      }

      inline bool operator<(const wxCellsBlock& cellsblock) const
      {
         return (m_LeftTop.GetRow() < cellsblock.m_LeftTop.GetRow())||
                ((m_LeftTop.GetRow() == cellsblock.m_LeftTop.GetRow())&&
                 (m_RightBottom.GetCol() < cellsblock.m_RightBottom.GetCol()));
      }

      inline bool operator>(const wxCellsBlock& cellsblock) const
      {
         return (m_LeftTop.GetRow() > cellsblock.m_LeftTop.GetRow())||
                ((m_LeftTop.GetRow() == cellsblock.m_LeftTop.GetRow())&&
                 (m_RightBottom.GetCol() > cellsblock.m_RightBottom.GetCol()));
      }

      inline bool operator<=(const wxCellsBlock& cellsblock) const
      {
         return (m_LeftTop.GetRow() < cellsblock.m_LeftTop.GetRow())||
                ((m_LeftTop.GetRow() == cellsblock.m_LeftTop.GetRow())&&
                 (m_RightBottom.GetCol() <= cellsblock.m_RightBottom.GetCol()));
      }

      inline bool operator>=(const wxCellsBlock& cellsblock) const
      {
         return (m_LeftTop.GetRow() > cellsblock.m_LeftTop.GetRow())||
                ((m_LeftTop.GetRow() == cellsblock.m_LeftTop.GetRow())&&
                 (m_RightBottom.GetCol() >= cellsblock.m_RightBottom.GetCol()));
      }

      inline bool operator==(const wxCellsBlock& cellsblock) const
      {
         return (m_LeftTop.GetCol() == cellsblock.m_LeftTop.GetCol())&&
                (m_LeftTop.GetRow() == cellsblock.m_LeftTop.GetRow())&&
                (m_RightBottom.GetCol() == cellsblock.m_RightBottom.GetCol())&&
                (m_RightBottom.GetRow() == cellsblock.m_RightBottom.GetRow());
      }

      wxGridCellCoords GetLeftTop(){return m_LeftTop;}
      wxGridCellCoords GetRightBottom(){return m_RightBottom;}

      int GetLeft(){return m_LeftTop.GetCol();}
      int GetTop(){return m_LeftTop.GetRow();}
      int GetRight(){return m_RightBottom.GetCol();}
      int GetBottom(){return m_RightBottom.GetRow();}

   private:

      wxGridCellCoords m_LeftTop;
      wxGridCellCoords m_RightBottom;
};
/*---------------------------------------------------------------------------*/
WX_DECLARE_OBJARRAY(wxCellsBlock, wxArrayOfCellsBlock);
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxSpecGrid : public wxGrid
{
   DECLARE_DYNAMIC_CLASS(wxSpecGrid)
   DECLARE_EVENT_TABLE()

   public:

      wxSpecGrid() : wxGrid(){}
      virtual ~wxSpecGrid(){}

      wxSpecGrid(wxWindow* parent, wxWindowID id,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxWANTS_CHARS,
                 const wxString& name = wxPanelNameStr) : wxGrid(parent, id,
                                                                 pos, size,
                                                                 style, name){}

      void SetDefaultSelection(int row = -1, int col = -1);

      bool HasFocus();

   protected:

      void OnCopy(wxCommandEvent& event);
      void OnCopyUpdate(wxUpdateUIEvent& event);
      void OnSelectAll(wxCommandEvent& event);
      void OnSelectAllUpdate(wxUpdateUIEvent& event);
      void OnRightDown(wxGridEvent& event);
      void OnSelectCell(wxGridEvent& event);
      void OnBlodEdit(wxGridCellBlobEditorEvent& event);

      virtual wxMenu* CreateRightMenu();

   private:

      wxString GetDataBlock(const wxGridCellCoords& topleft,
                            const wxGridCellCoords& bottomright);
      wxString GetDataBlock(const wxArrayOfCellsBlock& array);

};
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxDataGrid : public wxSpecGrid
{
   DECLARE_DYNAMIC_CLASS(wxDataGrid)
   DECLARE_EVENT_TABLE()

   public:

      wxDataGrid() : wxSpecGrid()
         {m_IsFiltered = m_IsSorted = false;}
      virtual ~wxDataGrid(){}

      wxDataGrid(wxWindow* parent, wxWindowID id,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize) :
                 wxSpecGrid(parent, id, pos, size, wxHSCROLL|wxVSCROLL)
                 {m_IsFiltered = m_IsSorted = false;}

      void SetDbTableViewName(wxSQLite3Database* db,
                              const wxString objectname,
                              const wxString& base = wxEmptyString);

      void DoRefresh(bool usefilter = false);
      void DoSort();
      void DoFilter();

      bool IsFiltered(){return m_IsFiltered;}
      bool IsSorted(){return m_IsSorted;}

   protected:

      void OnFilter(wxCommandEvent& event);
      void OnSort(wxCommandEvent& event);
      void OnRefresh(wxCommandEvent& event);
      void OnFilterSortUpdate(wxUpdateUIEvent& event);

      virtual wxMenu* CreateRightMenu();

   private:

      wxSQLite3Database*   m_db;
      wxString             m_Base;
      wxString             m_TableViewName;

      wxArrayString        m_StringsOrder;
      wxString             m_StringWhere;
      bool                 m_IsFiltered;
      bool                 m_IsSorted;
};
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxGridCellBlobRenderer : public wxGridCellStringRenderer
{
   public:

      wxGridCellBlobRenderer(bool displaynullvalue = true,
                             const wxString& defaultstring = _T("(blob)"));

      virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc,
                        const wxRect& rect, int row, int col, bool isSelected);

      virtual wxSize GetBestSize(wxGrid& grid, wxGridCellAttr& attr,
                                 wxDC& dc, int row, int col);

   protected:

      wxString GetString(const wxGrid& grid, int row, int col);

   private:

      bool m_IsNullValueDisplayed;
      wxString m_DefaultString;
};
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxGridCellBlobEditor : public wxGridCellEditor, public wxEvtHandler
{
   DECLARE_EVENT_TABLE()

   public:

      wxGridCellBlobEditor();

      virtual void Create(wxWindow* parent, wxWindowID id,
                          wxEvtHandler* evtHandler);

      virtual void PaintBackground(const wxRect& rectCell, wxGridCellAttr *attr);

      virtual void BeginEdit(int row, int col, wxGrid* grid);
  
#if wxCHECK_VERSION(2,9,0)
      virtual bool EndEdit(int row, int col, const wxGrid* grid,
                           const wxString& oldval, wxString* newval);

      virtual void ApplyEdit(int row, int col, wxGrid* grid);
#else
      virtual bool EndEdit(int row, int col, wxGrid* grid);
#endif
      virtual void Reset();

      virtual wxGridCellEditor *Clone() const;

      virtual wxString GetValue() const;

      virtual void SetSize(const wxRect& rectOrig);

   protected:

      void OnBtnClick(wxCommandEvent& event);

   private:

      int m_Row;
      int m_Col;
      wxGrid* m_Grid;
};
/*---------------------------------------------------------------------------*/
class WXDLLIMPEXP_SCPECGRID wxGridCellBlobEditorEvent : public wxNotifyEvent
{
   DECLARE_DYNAMIC_CLASS(wxGridCellBlobEditorEvent)

   public:

      wxGridCellBlobEditorEvent(wxEventType commandType = 0, int id = 0);
      wxGridCellBlobEditorEvent(const wxGridCellBlobEditorEvent& event);

      ~wxGridCellBlobEditorEvent() {}

      void SetRow(int val)       {m_Row = val;}
      void SetCol(int val)       {m_Col = val;}
      void SetGrid(wxGrid* val)  {m_Grid = val;}

      int GetRow()      const {return m_Row;}
      int GetCol()      const {return m_Col;}
      wxGrid* GetGrid() const {return m_Grid;}

      virtual wxEvent* Clone() const {return new wxGridCellBlobEditorEvent(*this);}

   private:

      int m_Row;        // Row number
      int m_Col;        // Col number
      wxGrid* m_Grid;   // Grid control

};
/*---------------------------------------------------------------------------*/
BEGIN_DECLARE_EVENT_TYPES()
   DECLARE_EXPORTED_EVENT_TYPE(WXDLLIMPEXP_SCPECGRID, wxEVT_GRID_BLOBEDIT,   1670) // wxGridCellBlobEditorEventFunction
END_DECLARE_EVENT_TYPES()

typedef void (wxEvtHandler::*wxGridCellBlobEditorEventFunction)(wxGridCellBlobEditorEvent&);

#define EVT_GRID_BLOBEDIT(id, fn) DECLARE_EVENT_TABLE_ENTRY(wxEVT_GRID_BLOBEDIT, id, wxID_ANY, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxGridCellBlobEditorEventFunction, & fn ), (wxObject *) NULL ),
/*---------------------------------------------------------------------------*/
#endif   // _SPECGRID_H_
