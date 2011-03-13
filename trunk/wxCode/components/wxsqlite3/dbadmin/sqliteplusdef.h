/*---------------------------------------------------------------------------*/
/* Logiciel de gestion de fichier de base de donnéesSQLite                   */
/*---------------------------------------------------------------------------*/
/* Projet  : wxSQLitePlus                              Version  : 0.3.0.0    */
/* Fichier : sqliteplusdef.h                                                 */
/* Auteur  : Fred Cailleau-Lepetit                     Date     : 17/08/2007 */
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
#ifndef _SQLITEPLUSDEF_H_
#define _SQLITEPLUSDEF_H_
/*---------------------------------------------------------------------------*/
#if wxUSE_UNICODE
   #define ToUTF8(str) str
#else
   #define ToUTF8(str) wxString(wxConvCurrent->cMB2WC(str), wxConvUTF8)
#endif /* Unicode */
/*---------------------------------------------------------------------------*/
#define IPC_VERB_OPEN _T("OPEN")
#define IPC_VERB_SHOW _T("SHOW")
/*---------------------------------------------------------------------------*/
#define ID_BMP_ADD               14101
#define ID_BMP_REMOVE            14102
#define ID_BMP_COLUP             14103
#define ID_BMP_COLDOWN           14104
#define ID_BMP_DBNEW             14105
#define ID_BMP_OPENDB            14106
#define ID_BMP_COMPACTDB         14107
#define ID_BMP_REFRESH           14108
#define ID_BMP_UNDO              14109
#define ID_BMP_REDO              14110
#define ID_BMP_CUT               14111
#define ID_BMP_COPY              14112
#define ID_BMP_PASTE             14113
#define ID_BMP_CLEAR             14114
#define ID_BMP_RUNSQL            14115
#define ID_BMP_RUNSCRIPT         14116
#define ID_BMP_EXPLAIN           14117
#define ID_BMP_STARTTRANSACT     14118
#define ID_BMP_STOPTRANSACT      14119
#define ID_BMP_COMMIT            14120
#define ID_BMP_ROLLBACK          14121
#define ID_BMP_AUTOTRANSACT      14122
#define ID_BMP_TABLECREATE       14123
#define ID_BMP_TABLEDROP         14124
#define ID_BMP_VIEWCREATE        14125
#define ID_BMP_VIEWDROP          14126
#define ID_BMP_INDEXECREATE      14127
#define ID_BMP_INDEXEDROP        14128
#define ID_BMP_TRIGGERCREATE     14129
#define ID_BMP_TRIGGERDROP       14130
#define ID_BMP_INDEXE            14131
#define ID_BMP_INDEXE_TMP        14132
#define ID_BMP_INDEXES           14133
#define ID_BMP_TABLE             14134
#define ID_BMP_TABLE_TMP         14135
#define ID_BMP_TABLES            14136
#define ID_BMP_TRIGGER2          14137
#define ID_BMP_TRIGGER2_TMP      14138
#define ID_BMP_TRIGGERS2         14139
#define ID_BMP_VIEW              14140
#define ID_BMP_VIEW_TMP          14141
#define ID_BMP_VIEWS             14142
#define ID_BMP_LOG               14143
#define ID_BMP_DATABASE          14144
#define ID_BMP_FIELD             14145
#define ID_BMP_FIELD2            14146
#define ID_BMP_RIGHTARROW1       14147
#define ID_BMP_RIGHTARROW2       14148
#define ID_BMP_LEFTARROW1        14149
#define ID_BMP_LEFTARROW2        14150
#define ID_BMP_LOGO32            14151
#define ID_BMP_POWEREDBYSQLITE   14152
#define ID_BMP_ATTACH            14153
#define ID_BMP_ALLTOLEFT         14154
#define ID_BMP_ALLTORIGHT        14155
#define ID_BMP_LEFT              14156
#define ID_BMP_RIGHT             14157
#define ID_BMP_FIRST             14158
#define ID_BMP_LAST              14159
#define ID_BMP_UP                14160
#define ID_BMP_DOWN              14161
#define ID_BMP_FILTER            14162
#define ID_BMP_SORT              14163
/*---------------------------------------------------------------------------*/
#define ID_ICO_INDEXE   14201
#define ID_ICO_SQLICON  14202
#define ID_ICO_TABLE    14203
#define ID_ICO_VIEW     14204
#define ID_ICO_TRIGGER2 14205
#define ID_ICO_LOGO32   14206
#define ID_ICO_SQLHISTO 14207
#define ID_ICO_FIELD2   14208
#define ID_ICO_DATABASE 14209
#define ID_ICO_FILTER   14210
#define ID_ICO_SORT     14211
/*---------------------------------------------------------------------------*/
#define ID_MNU_ATTACH_DB      11101
#define ID_MNU_CLOSE_DB       11102
#define ID_MNU_DETACH_DB      11103
#define ID_MNU_COMPACT        11104
#define ID_MNU_REKEY          11105
#define ID_MNU_REFRESHALL     11106
#define ID_MNU_BACKUP         11107
#define ID_MNU_RESTORE        11108

#define ID_MNU_CLEAR_ALL      11201

#define ID_MNU_ADD_TABLE      11301
#define ID_MNU_DEL_TABLE      11302
#define ID_MNU_ADD_VIEW       11303
#define ID_MNU_DEL_VIEW       11304
#define ID_MNU_ADD_INDEX      11305
#define ID_MNU_DEL_INDEX      11306
#define ID_MNU_ADD_TRIGGER    11307
#define ID_MNU_DEL_TRIGGER    11308
#define ID_MNU_ADD_COLUMNS    11309

#define ID_MNU_DROP_OBJECT    11401
#define ID_MNU_EXPLORE        11402

#define ID_MNU_EXECUTESQL     11501
#define ID_MNU_EXECUTESCRIPT  11502
#define ID_MNU_EXPLAIN        11503
#define ID_MNU_DESCRIBE       11504

#define ID_MNU_BEGINTRANSACT  11601
#define ID_MNU_ENDTRANSACT    11602
#define ID_MNU_COMMIT         11603
#define ID_MNU_ROLLBACK       11604
#define ID_MNU_AUTOTRANSACT   11605

#define ID_MNU_SHOWTREE       11701
#define ID_MNU_SHOWHISTORY    11702
#define ID_MNU_TOOLBAR        11800
#define ID_MNU_TB_FILE        11801
#define ID_MNU_TB_EDIT        11802
#define ID_MNU_TB_DATABASE    11803
#define ID_MNU_TB_QUERY       11804
#define ID_MNU_TB_TRANSACT    11805

#define ID_MNU_FILTER         11901
#define ID_MNU_SORT           11902
#define ID_MNU_REFRESH        11903

#define ID_CMD_ED_REFRESH     12100
#define ID_CMD_LAUNCH_CLT     12200

#define ID_IPC_SERVER         25100
#define ID_IPC_SRV_SOCK       25101
/*---------------------------------------------------------------------------*/
#define PARAM_FRAME_XPOS         20001
#define PARAM_FRAME_YPOS         20002
#define PARAM_FRAME_WIDTH        20003
#define PARAM_FRAME_HEIGHT       20004
#define PARAM_FRAME_MAXIMIZED    20005
#define PARAM_FRAME_PERSPECTIVE  20006
#define PARAM_SQL_PERSPECTIVE    20007
#define PARAM_AUTOTRANSACT       20008
#define PARAM_ODDROWCOLOR        20009
#define PARAM_SQLHISTOCOUNT      20010
#define PARAM_SAVEWINPOSITION    20011
#define PARAM_SAVEWINPERSPECTIVE 20012
#define PARAM_STYLE_FONTNAME     20013
#define PARAM_STYLE_FONTSIZE     20014
#define PARAM_STYLE_EDGELINE     20015
#define PARAM_ST_BOLD_DEF        20016
#define PARAM_ST_ITALIC_DEF      20017
#define PARAM_ST_UNDER_DEF       20018
#define PARAM_ST_FORE_DEF        20019
#define PARAM_ST_BACK_DEF        20020
#define PARAM_ST_CASE_DEF        20021
#define PARAM_ST_BOLD_COM        20022
#define PARAM_ST_ITALIC_COM      20023
#define PARAM_ST_UNDER_COM       20024
#define PARAM_ST_FORE_COM        20025
#define PARAM_ST_BACK_COM        20026
#define PARAM_ST_CASE_COM        20027
#define PARAM_ST_BOLD_COML       20028
#define PARAM_ST_ITALIC_COML     20029
#define PARAM_ST_UNDER_COML      20030
#define PARAM_ST_FORE_COML       20031
#define PARAM_ST_BACK_COML       20032
#define PARAM_ST_CASE_COML       20033
#define PARAM_ST_BOLD_NUM        20034
#define PARAM_ST_ITALIC_NUM      20035
#define PARAM_ST_UNDER_NUM       20036
#define PARAM_ST_FORE_NUM        20037
#define PARAM_ST_BACK_NUM        20038
#define PARAM_ST_CASE_NUM        20039
#define PARAM_ST_BOLD_KEY1       20040
#define PARAM_ST_ITALIC_KEY1     20041
#define PARAM_ST_UNDER_KEY1      20042
#define PARAM_ST_FORE_KEY1       20043
#define PARAM_ST_BACK_KEY1       20044
#define PARAM_ST_CASE_KEY1       20045
#define PARAM_ST_BOLD_STR        20046
#define PARAM_ST_ITALIC_STR      20047
#define PARAM_ST_UNDER_STR       20048
#define PARAM_ST_FORE_STR        20049
#define PARAM_ST_BACK_STR        20050
#define PARAM_ST_CASE_STR        20051
#define PARAM_ST_BOLD_CHAR       20052
#define PARAM_ST_ITALIC_CHAR     20053
#define PARAM_ST_UNDER_CHAR      20054
#define PARAM_ST_FORE_CHAR       20055
#define PARAM_ST_BACK_CHAR       20056
#define PARAM_ST_CASE_CHAR       20057
#define PARAM_ST_BOLD_OPE        20058
#define PARAM_ST_ITALIC_OPE      20059
#define PARAM_ST_UNDER_OPE       20060
#define PARAM_ST_FORE_OPE        20061
#define PARAM_ST_BACK_OPE        20062
#define PARAM_ST_CASE_OPE        20063
#define PARAM_ST_BOLD_IDE        20064
#define PARAM_ST_ITALIC_IDE      20065
#define PARAM_ST_UNDER_IDE       20066
#define PARAM_ST_FORE_IDE        20067
#define PARAM_ST_BACK_IDE        20068
#define PARAM_ST_CASE_IDE        20069
#define PARAM_ST_BOLD_KEY2       20070
#define PARAM_ST_ITALIC_KEY2     20071
#define PARAM_ST_UNDER_KEY2      20072
#define PARAM_ST_FORE_KEY2       20073
#define PARAM_ST_BACK_KEY2       20074
#define PARAM_ST_CASE_KEY2       20075
#define PARAM_ST_BOLD_KEY3       20076
#define PARAM_ST_ITALIC_KEY3     20077
#define PARAM_ST_UNDER_KEY3      20078
#define PARAM_ST_FORE_KEY3       20079
#define PARAM_ST_BACK_KEY3       20080
#define PARAM_ST_CASE_KEY3       20081
#define PARAM_ST_BOLD_KEY4       20082
#define PARAM_ST_ITALIC_KEY4     20083
#define PARAM_ST_UNDER_KEY4      20084
#define PARAM_ST_FORE_KEY4       20085
#define PARAM_ST_BACK_KEY4       20086
#define PARAM_ST_CASE_KEY4       20087
#define PARAM_ST_TAB_WIDTH       20088
#define PARAM_ST_USE_TAB         20089
#define PARAM_ST_TAB_INDENT      20090
#define PARAM_ST_BACKSP_UNINDT   20091
#define PARAM_ST_INDENT_WIDTH    20092
#define PARAM_ST_FORE_LINENUM    20093
#define PARAM_ST_BACK_LINENUM    20094
#define PARAM_ST_SHOW_LINENUM    20095
/*---------------------------------------------------------------------------*/
#define STYLE_DEFAULT      0
#define STYLE_COMMENT      1
#define STYLE_COMMENTLINE  2
#define STYLE_NUMBER       3
#define STYLE_WORD1        4
#define STYLE_STRING       5
#define STYLE_CHARACTER    6
#define STYLE_OPERATOR     7
#define STYLE_IDENTIFIER   8
#define STYLE_WORD2        9
#define STYLE_WORD3        10
#define STYLE_WORD4        11
#define STYLE_COUNT        12
/*---------------------------------------------------------------------------*/
#endif   // _SQLITEPLUSDEF_H_
