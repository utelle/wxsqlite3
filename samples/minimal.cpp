/*
** Name:        minimal.cpp
** Purpose:     Test program for the wxSQLite3 class
**              This example is based on the CppSQLite example.
** Author:      Ulrich Telle
** Created:     2005-07-14
** Copyright:   (c) 2005-2018 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// Enable to activate leak detection with Visual Leak Detector
#if 0
#include <vld.h>
#endif

#include <wx/cmdline.h>

#include "wx/wxsqlite3.h"
#include <ctime>
#include <iostream>

using namespace std;

// Test of RAII transaction class

wxSQLite3Database* initDB(void)
{
	wxString testDBName = wxGetCwd() + wxS("/test2.db");
	if (wxFileExists(testDBName))
	{
		wxRemoveFile(testDBName);
	}
	wxSQLite3Database* db = new wxSQLite3Database();
	db->Open(testDBName);
	db->ExecuteUpdate(wxS("CREATE TABLE test (col1 INTEGER)"));
	return db;
}

void clearDB(wxSQLite3Database* db)
{
	assert(db != NULL);
	db->Close();
	delete db;
}

void testTransaction()
{
  bool exceptionCaught = false;
  wxSQLite3Database* db = initDB();
  try
  {
		wxSQLite3Transaction t(db);
    cout << "AutoCommit? " << !db->GetAutoCommit() << endl;
		cout << "Transaction active? " << t.IsActive() << endl;
		db->ExecuteUpdate(wxS("INSERT INTO test (col1) VALUES (2)"));
		t.Commit();
    cout << "AutoCommit? " << db->GetAutoCommit() << endl;
		cout << "Transaction not active? " << !t.IsActive() << endl;
	}
  catch (...)
  {
		cout << "Exception should not happen here" << endl;
	}
	// Check whether value exists in table
	wxSQLite3ResultSet set = db->ExecuteQuery(wxS("SELECT * FROM test"));
	
	int count = 0;
	while (set.NextRow())
	{
		wxString s = set.GetAsString(0);
		count++;
	}
	set.Finalize();
	cout << "Is count == 1? " << (count == 1) << endl;
		
	// failed transaction
	try
	{
		wxSQLite3Transaction t(db);
		db->ExecuteUpdate(wxS("INSERT INTO test (col1) VALUES (3)"));

		throw "Abort commit";
//  ...
//  t.Commit();
	}
  catch (...)
  {
		exceptionCaught = true;
	}
	if (exceptionCaught)
  {
		// check whether the value 3 exists in table
    // (it shouldn't since the transaction was aborted)
		set = db->ExecuteQuery(wxS("SELECT * FROM test"));
	
		int count = 0;
		while (set.NextRow())
		{
			++count;
      if (set.GetInt(0) ==3)
      {
        cout << "Error! 3 must not exist in table." << endl;
      }
		}
		set.Finalize();
		cout << "Is count == 1? " << (count==1) << endl;
	}
  else
  {
		cout << "Exception not caught" << endl;
	}
	clearDB(db);
}

void testUserAuthentication()
{
  wxString testDBName = wxGetCwd() + wxS("/test3.db");
  if (wxFileExists(testDBName))
  {
    wxRemoveFile(testDBName);
  }
  wxSQLite3Database* db = new wxSQLite3Database();
  try
  {
    db->Open(testDBName);
    db->UserAdd(wxS("testuser"), wxS("testpswd"), true);
    cout << "User authentication enabled for database using 'testuser'." << endl;
    if (db->UserLogin(wxS("sampleuser"), wxS("samplepswd")))
    {
      cout << "'sampleuser' successfully logged in, but this shouldn't happen due to enabled user authentication." << endl;
    }
    else
    {
      cout << "Login of 'sampleuser' rejected." << endl;
    }
    if (db->UserLogin(wxS("testuser"), wxS("testpswd")))
    {
      cout << "Login of 'testuser' succeeded." << endl;
      db->ExecuteUpdate(wxS("CREATE TABLE test (col1 INTEGER)"));
      db->ExecuteUpdate(wxS("INSERT INTO test (col1) VALUES (2)"));
      db->UserAdd(wxS("myuser"), wxS("mypswd"), false);
      cout << "Added 'myuser' without privileges." << endl;
      if (db->UserIsPrivileged(wxS("myuser")))
      {
        cout << "'myuser' is privileged." << endl;
      }
      else
      {
        cout << "'myuser' is NOT privileged." << endl;
      }
      db->UserChange(wxS("myuser"), wxS("mypswd"), true);
      cout << "Make 'myuser' privileged." << endl;
      if (db->UserIsPrivileged(wxS("myuser")))
      {
        cout << "'myuser' is now privileged." << endl;
      }
      else
      {
        cout << "'myuser' is still NOT privileged." << endl;
      }
      db->UserDelete(wxS("myuser"));
      cout << "'myuser' deleted." << endl;
    }
    else
    {
      cout << "Login of 'testuser' failed unexpectedly." << endl;
    }
    db->Close();
  }
  catch (wxSQLite3Exception& e)
  {
    cerr << e.GetErrorCode() << ":" << (const char*)(e.GetMessage().mb_str()) << endl;
  }

  delete db;
}

// User defined aggregate function
class MyAggregateFunction : public wxSQLite3AggregateFunction
{
public:
  // Concatenate all values
  virtual void Aggregate(wxSQLite3FunctionContext& ctx)
  {
    // Get the temporary memory for storing the intermediate result
    wxString** acc = (wxString**) ctx.GetAggregateStruct(sizeof (wxString**));

    // Allocate a wxString instance in the first aggregate step
    if (*acc == NULL) {
      *acc = new wxString(wxS(""));
    }

    // Concatenate all arguments
    for (int i = 0; i < ctx.GetArgCount(); i++) {
       (*acc)->Append(ctx.GetString(i));
       (*acc)->Append(wxS(" "));
    }
  }

  // Set the result of the aggregate function
  virtual void Finalize(wxSQLite3FunctionContext& ctx)
  {
    // Get the temporary memory conatining the result
    wxString** acc = (wxString**) ctx.GetAggregateStruct(sizeof (wxString**));

    // Set the result
    ctx.SetResult(*(*acc));

    cout << "MyAggregateFunction: count=" << ctx.GetAggregateCount() << endl;

    // Important: Free the allocated wxString
    delete *acc;
    *acc = 0;
  }
};

// Dummy authorizer logging only when the function is called
class MyAuthorizer : public wxSQLite3Authorizer
{
public:
  virtual wxAuthorizationResult Authorize(wxAuthorizationCode type, 
                                          const wxString& arg1, const wxString& arg2, 
                                          const wxString& arg3, const wxString& arg4,
                                          const wxString& arg5)
  {
    cout << "AUTH: " 
         << (const char*) AuthorizationCodeToString(type).mb_str(wxConvUTF8) << ","
         << (const char*) arg1.mb_str(wxConvUTF8) << ","
         << (const char*) arg2.mb_str(wxConvUTF8) << ","
         << (const char*) arg3.mb_str(wxConvUTF8) << ","
         << (const char*) arg4.mb_str(wxConvUTF8) << ","
         << (const char*) arg5.mb_str(wxConvUTF8) << endl;
    return wxSQLite3Authorizer::SQLITE_OK;
  }
};

class MyCallback : public wxSQLite3Hook
{
public:
  virtual bool CommitCallback()
  {
    cout << "Here is the COMMIT callback" << endl;
    return false;
  }

  virtual void RollbackCallback()
  {
    cout << "Here is the ROLLBACK callback" << endl;
  }

  virtual void UpdateCallback(wxUpdateType type,
                              const wxString& database, const wxString& table,
                              wxLongLong rowid)
  {
    const char* strType;
    cout << "Here is the UPDATE callback" << endl;
    switch (type)
    {
      case SQLITE_DELETE:
        strType = "DELETE row ";
        break;
      case SQLITE_INSERT:
        strType = "INSERT row ";
        break;
      case SQLITE_UPDATE:
        strType = "UPDATE row ";
        break;
      default:
        strType = "Unknown change row ";
        break;
    }
    cout << strType << (const char*) rowid.ToString().mb_str()
         << " in table " << (const char*) table.mb_str()
         << " of database " << (const char*) database.mb_str() << endl;
  }
  virtual void Dummy() {}
};

class MyCollation : public wxSQLite3Collation
{
public:
  virtual int Compare(const wxString& text1, const wxString& text2)
  {
    wxString loc1;
    wxString loc2;
    size_t j1 = text1.Length();
    size_t j2 = text2.Length();
    size_t j;
    loc1.Alloc(j1);
    loc2.Alloc(j2);
    for (j = 0; j < j1; j++) loc1 += text1[j1-1-j];
    for (j = 0; j < j2; j++) loc2 += text2[j2-1-j];
    return loc1.Cmp(loc2);
  }
};

class MyProgress : public wxSQLite3BackupProgress
{
public:
  virtual bool Progress(int total, int remaining)
  {
    double percent = (total - remaining) / ((double) total) * 100.;
    cout.precision(2);
    cout << "Backup/Restore: " << std::fixed << percent << " % completed." << endl;
    return true;
  }
};

class Minimal : public wxAppConsole
{
public:
  bool OnInit();
  int OnRun();
  int OnExit();
  void TestSQLCipher(wxSQLite3Cipher& cipher, const wxString& dbFileName, const wxString& dbKey);
  void TestCiphers();
private:
  wxString m_workDirectory;
  bool     m_testMode;
  int      m_rc;
};

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
#if wxCHECK_VERSION(2,9,0)
  { wxCMD_LINE_OPTION, "s", "sampledir", "wxSQLite3 samples directory", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, "t", "testmode",  "Non-interactive testmode",    wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
#else
  { wxCMD_LINE_OPTION, wxS("s"), wxS("sampledir"), wxS("wxSQLite3 samples directory"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_SWITCH, wxS("t"), wxS("testmode"),  wxS("Non-interactive testmode"),    wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL },
#endif
  { wxCMD_LINE_NONE }
};


bool Minimal::OnInit()
{
  // Gets the parameters from cmd line
  wxCmdLineParser parser(cmdLineDesc, argc, argv);
  wxString logo = wxS("wxSQLite3 Minimal Sample\n");
  parser.SetLogo(logo);
  bool ok = parser.Parse() == 0;
  if (ok)
  {
    parser.Found(wxS("sampledir"), &m_workDirectory);
    m_testMode = parser.Found(wxS("testmode"));
    m_rc = 0;
  }
  else
  {
    m_rc = -1;
  }

  if (ok)
  {
    // Set the working directory
    if (!m_workDirectory.IsEmpty())
    {
      wxSetWorkingDirectory(m_workDirectory);
    }
    m_workDirectory = wxGetCwd();
  }

  return ok;
}

int Minimal::OnExit()
{
  return m_rc;
}

int Minimal::OnRun()
{
  m_rc = 0;
  const wxString dbFile = wxGetCwd() + wxS("/test.db");
  const wxString dbBackup = wxGetCwd() + wxS("/test-backup.db");

  const char* rawUTF8 = "\xe2\x8c\x88\x30\x2e\x35\x6e\xe2\x8c\x89\x2b\x6e\x2b\x32\x36";
  wxString tt = wxString::FromUTF8(rawUTF8);

  MyAggregateFunction myAggregate;
  MyAuthorizer myAuthorizer;
  MyCallback myCallback;
  MyCollation myCollation;
#if wxUSE_REGEX
  wxSQLite3RegExpOperator myRegExpOp;
#endif

  try
  {
    wxSQLite3Database::InitializeSQLite();
    int i, fld;
    time_t tmStart, tmEnd;
    wxSQLite3Database db;

    cout << "wxSQLite3 Version:    " << (const char*) wxSQLite3Database::GetWrapperVersion().mb_str(wxConvUTF8) << endl;
    cout << "SQLite3 Version:      " << (const char*) db.GetVersion().mb_str(wxConvUTF8) << endl;
    cout << "SQLite3 Source Id:    " << (const char*) db.GetSourceId().mb_str(wxConvUTF8) << endl;

    int optionIndex;
    wxString optionName;
    for (optionIndex = 0; ; ++optionIndex)
    {
      optionName = wxSQLite3Database::GetCompileOptionName(optionIndex);
      if (optionName.IsEmpty()) break;
      cout << "SQLite3 compile option '" << (const char*) optionName.mb_str(wxConvUTF8)
           << "'=" << wxSQLite3Database::CompileOptionUsed(optionName) << endl;
    }

    // Remove existing sample database files
    if (wxFileExists(dbFile))
    {
      wxRemoveFile(dbFile);
    }
    if (wxFileExists(dbBackup))
    {
      wxRemoveFile(dbBackup);
    }

    if (wxSQLite3Database::HasEncryptionSupport())
    {
      cout << "Cipher (default) : " << (const char*) wxSQLite3Cipher::GetCipherName(wxSQLite3Cipher::GetGlobalCipherDefault()).mb_str(wxConvUTF8) << endl;
      db.Open(dbFile, wxString(wxS("password")));
    }
    else
    {
      db.Open(dbFile);
    }

    cout << "SQLite3 Journal Mode: " << (const char*) wxSQLite3Database::ConvertJournalMode(db.GetJournalMode()).mb_str(wxConvUTF8) << endl;
    // Check status of support for foreign key constraints
    bool foreignKeysEnabled = db.EnableForeignKeySupport(true);
    cout << endl << "Foreign key constraints are ";
    if (foreignKeysEnabled)
      cout << "enabled.";
    else
      cout << "not enforced.";
    cout << endl;

    cout << endl << "Table 'emp' exists=" << (db.TableExists(wxS("EmP")) ? "TRUE":"FALSE") << endl;
    cout << "Creating table 'emp'" << endl;
    db.ExecuteUpdate(wxS("create table emp(empno int, empname char(20), salary double);"));
    cout << "Table 'emp' exists=" << (db.TableExists(wxS("emp")) ? "TRUE":"FALSE") << endl;
    
    // Attach the current database under different name and
    // check table existance in any open database.
    // The table emp will be found in 'main' and in 'dbattached'
    db.AttachDatabase(dbFile, wxS("dbattached"));
    cout << endl << "Filename of database 'dbattached': " << (const char*) db.GetDatabaseFilename(wxS("dbattached")).mb_str(wxConvUTF8) << endl;

    wxArrayString databaseList;
    db.TableExists(wxS("emp"), databaseList);
    cout << "Table 'emp' exists in the following databases:" << endl;
    size_t j;
    for (j = 0; j < databaseList.GetCount(); ++j)
    {
      cout << j << ": " << (const char*)databaseList.Item(j).mb_str(wxConvUTF8) << endl;
    }

    if (wxSQLite3Database::HasEncryptionSupport())
    {
      wxSQLite3CipherSQLCipher sqlCipher3;
      sqlCipher3.InitializeVersionDefault(3);
      db.AttachDatabase(wxS("sqlcipher-3.0-testkey.db"), wxS("dbsqlcipher"), sqlCipher3, wxS("testkey"));
      cout << endl << "Filename of database 'dbsqlcipher': " << (const char*)db.GetDatabaseFilename(wxS("dbsqlcipher")).mb_str(wxConvUTF8) << endl;

      databaseList.Empty();
      db.TableExists(wxS("t1"), databaseList);
      cout << "Table 't1' exists in the following databases:" << endl;
      size_t k;
      for (k = 0; k < databaseList.GetCount(); ++k)
      {
        cout << k << ": " << (const char*) databaseList.Item(k).mb_str(wxConvUTF8) << endl;
      }
    }

    if (wxSQLite3Database::HasEncryptionSupport())
    {
      db.DetachDatabase(wxS("dbsqlcipher"));
    }

    db.DetachDatabase(wxS("dbattached"));

    // Execute some DML, and print number of rows affected by each one

    db.SetUpdateHook(&myCallback);

    cout << endl << "DML tests" << endl;
    wxString insertCmd(wxS("insert into emp values (7, 'Franz Beckenbauer', 2000.10);"));
    int nRows = db.ExecuteUpdate(insertCmd);
    cout << nRows << " rows inserted" << endl;

    wxSQLite3ResultSet q1 = db.ExecuteQuery("select empname from emp order by 1;");

    while (q1.NextRow())
    {
      cout << (const char*)(q1.GetString(0).mb_str()) << endl;
    }

    nRows = db.ExecuteUpdate("update emp set empname = 'Lukas Podolski' where empno = 7;");
    cout << nRows << " rows updated" << endl;

    nRows = db.ExecuteUpdate("delete from emp where empno = 7;");
    cout << nRows << " rows deleted" << endl;

    db.SetUpdateHook(NULL);

    // Transaction Demo
    
    int nRowsToCreate(50000);
    cout << endl << "Transaction test, creating " << nRowsToCreate;
    cout << " rows please wait..." << endl;
    tmStart = time(0);
    db.Begin();

    for (i = 0; i < nRowsToCreate; i++)
    {
      char buf[128];
      sprintf(buf, "insert into emp values (%d, 'empname%06d', %d.50);", i, i, i);
      db.ExecuteUpdate(buf);
    }

    db.Commit();
    tmEnd = time(0);

    // Demonstrate scalar query

    cout << db.ExecuteScalar("select count(*) from emp;") << " rows in emp table in ";
    cout << tmEnd-tmStart << " seconds" << endl;

    // Demonstrate use of named collection (if available)

    if (db.HasNamedCollectionSupport())
    {
      cout << endl << "Named collection test" << endl;
      wxSQLite3IntegerCollection ic = db.CreateIntegerCollection(wxS("ic"));
      wxSQLite3StringCollection sc = db.CreateStringCollection(wxS("sc"));
      int icList[] = { 26, 39, 47, 64 };
      ic.Bind(4, icList);

      wxSQLite3ResultSet q1 = db.ExecuteQuery("select empname from emp where empno in ic;");
      while (q1.NextRow())
      {
        cout << (const char*)(q1.GetString(0).mb_str()) << endl;
      }

      wxArrayString scList;
      scList.Add(wxS("empname000048"));
      scList.Add(wxS("empname000194"));
      sc.Bind(scList);

      wxSQLite3ResultSet q2 = db.ExecuteQuery("select empno from emp where empname in sc;");
      while (q2.NextRow())
      {
        cout << q2.GetInt(0) << endl;
      }
    }

    // Re-create emp table with auto-increment field

    cout << endl << "Auto increment test" << endl;
    db.ExecuteUpdate("drop table emp;");
    db.ExecuteUpdate("create table emp(empno integer primary key, empname char(20), salary double);");
    cout << nRows << " rows deleted" << endl;

    for (i = 0; i < 5; i++)
    {
      char buf[128];
      sprintf(buf, "insert into emp (empname,salary) values ('empname%06d',%d.57);", i+1,(i+1)*10000);
      db.ExecuteUpdate(buf);
      cout << " primary key: " << db.GetLastRowId().ToLong() << endl;
    }

    // Query data and also show results of inserts into auto-increment field

    wxSQLite3ResultSet q = db.ExecuteQuery("select * from emp order by 1;");

    if (wxSQLite3Database::HasMetaDataSupport())
    {
      cout << endl << "Meta data test" << endl;

      wxString dataType;
      wxString collation;
      bool notNull;
      bool primaryKey;
      bool autoIncrement;
      db.GetMetaData(wxEmptyString, wxS("emp"), wxS("empname"), &dataType, &collation, &notNull, &primaryKey, &autoIncrement);
      cout << "Meta data of table 'emp', column 'empname'" << endl 
           << "Data type: " << (const char*) dataType.mb_str(wxConvUTF8)
           << ", Collation: " << (const char*) collation.mb_str(wxConvUTF8)
           << ", Not Null: " << notNull
           << ", Primary Key: " << primaryKey
           << ", Auto Increment: " << autoIncrement << endl;

      for (fld = 0; fld < q.GetColumnCount(); fld++)
      {
        cout << (fld+1) << ". field:" << endl 
             << "database = (" << (const char*) q.GetDatabaseName(fld).mb_str(wxConvUTF8) << ")" << endl
             << "table    = (" << (const char*) q.GetTableName(fld).mb_str(wxConvUTF8) << ")" << endl
             << "origin   = (" << (const char*) q.GetOriginName(fld).mb_str(wxConvUTF8) << ")" << endl;
      }
      cout << endl;
    }

    cout << endl << "Select statement test" << endl;
    for (fld = 0; fld < q.GetColumnCount(); fld++)
    {
      cout << (const char*) q.GetColumnName(fld).mb_str(wxConvUTF8)
           << "(" << (const char*) q.GetDeclaredColumnType(fld).mb_str(wxConvUTF8)
           << ")|";
    }
    cout << endl;

    while (q.NextRow())
    {
      cout << q.GetInt(0) << "|";
      cout << (const char*)(q.GetString(1).mb_str()) << "|" << endl;
    }
    cout << "SQL: " << (const char*) q.GetSQL().mb_str(wxConvUTF8) << endl;

    // SQLite3's printf() functionality. Handles embedded quotes and NULLs

    cout << endl << "SQLite sprintf test" << endl;
    wxSQLite3StatementBuffer bufSQL;
    bufSQL.Format("insert into emp (empname) values (%Q);", "He's bad");
    cout << (const char*)bufSQL << endl;
    db.ExecuteUpdate(bufSQL);

    bufSQL.Format("insert into emp (empname) values (%Q);", NULL);
    cout << (const char*)bufSQL << endl;
    db.ExecuteUpdate(bufSQL);

    // Fetch table at once

    cout << endl << "getTable() test" << endl;
    wxSQLite3Table t = db.GetTable("select * from emp order by 1;");

    for (fld = 0; fld < t.GetColumnCount(); fld++)
    {
      cout << (const char*) t.GetColumnName(fld).mb_str(wxConvUTF8) << "|";
    }
    cout << endl;
    for (int row = 0; row < t.GetRowCount(); row++)
    {
      t.SetRow(row);
      for (int fld = 0; fld < t.GetColumnCount(); fld++)
      {
        if (!t.IsNull(fld))
        {
          if (fld != 2)
            cout << (const char*) t.GetAsString(fld).mb_str(wxConvUTF8) << "|";
          else
            cout << t.GetDouble(fld) << "|";
        }
        else
        {
          cout << "NULL" << "|";
        }
      }
      cout << endl;
    }

    db.CreateFunction(wxS("myagg"), 1, myAggregate);

    cout << endl << "Select statement test" << endl;
    wxSQLite3ResultSet q2 = db.ExecuteQuery("select myagg(empname) from emp order by 1;");

    while (q2.NextRow())
    {
      cout << (const char*)(q2.GetString(0).mb_str()) << endl;
    }

#if wxUSE_REGEX
    db.CreateFunction(wxS("regexp"), 2, myRegExpOp);

    cout << endl << "Regular expression test" << endl;
    wxSQLite3ResultSet q3 = db.ExecuteQuery("select empname from emp where empname regexp '^[A-Z].*$' order by 1;");

    while (q3.NextRow())
    {
      cout << (const char*)(q3.GetString(0).mb_str()) << endl;
    }
#endif

    // Test storing/retrieving some binary data, checking
    // it afterwards to make sure it is the same

    cout << endl << "Binary data test" << endl;
    db.ExecuteUpdate("create table bindata(desc char(10), data blob);");


    int binSize = 256;
    unsigned char* binData = new unsigned char[binSize];
    for (i = 0; i < binSize; i++)
    {
      binData[i] = i;
    }
    wxSQLite3Statement stmt = db.PrepareStatement("insert into bindata values ('testing', ?);");
    stmt.Bind(1, binData, binSize);
    stmt.ExecuteUpdate();
    cout << "Stored binary Length: " << binSize << endl;

    q = db.ExecuteQuery("select data from bindata where desc = 'testing';");

    const unsigned char* pbin = binData;
    if (q.NextRow())
    {
      int blobLen;
      const wxString columnName(wxS("data"));
      pbin = q.GetBlob(wxString(wxS("data")),blobLen);
      cout << "Retrieved binary Length: " << blobLen << endl;
    }

    for (i = 0; i < sizeof binData; i++)
    {
      if (pbin[i] != i)
      {
        cout << "Problem: i: ," << i << " bin[i]: " << pbin[i] << endl;
      }
    }
    q.Finalize();
    delete[] binData;

    if (wxSQLite3Database::HasPointerParamsSupport())
    {
      static int aX[] = { 53, 9, 17, 2231, 4, 99 };
      cout << endl << "Pointer parameter test" << endl;
      wxSQLite3Statement stmt = db.PrepareStatement("SELECT * FROM carray(?,5);");
      stmt.Bind(1, aX, wxString(wxS("carray")));
      wxSQLite3ResultSet set = stmt.ExecuteQuery();

      int count = 0;
      while (set.NextRow())
      {
        int element = set.GetInt(0);
        cout << "carray[" << count << "] = " << element << endl;
        count++;
      }
      set.Finalize();
      cout << "Is count == 5? " << (count == 5) << endl;
    }

    // Activate authorizer
    db.SetAuthorizer(myAuthorizer);

    // Pre-compiled Statements Demo

    cout << endl << "Transaction test, creating " << nRowsToCreate;
    cout << " rows please wait..." << endl;
    db.ExecuteUpdate("drop table emp;");
    db.ExecuteUpdate("create table emp(empno int, empname char(20), salary double);");
    tmStart = time(0);
    db.Begin();

    wxSQLite3Statement stmt2 = db.PrepareStatement("insert into emp values (?, ?, ?);");
    for (i = 0; i < nRowsToCreate; i++)
    {
      char buf[16];
      sprintf(buf, "EmpName%06d", i);
      stmt2.Bind(1, i);
      stmt2.Bind(2, buf);
      stmt2.Bind(3, (double) (i + 0.5));
      stmt2.ExecuteUpdate();
      stmt2.Reset();
    }

    db.Commit();
    tmEnd = time(0);

    cout << db.ExecuteScalar("select count(*) from emp;") << " rows in emp table in ";
    cout << tmEnd-tmStart << " seconds" << endl;

    // Deactivate authorizer
    db.RemoveAuthorizer();

    cout << endl << "User Defined Collation Sequence Test" << endl;
    db.SetCollation(wxS("reversed"), &myCollation);
    db.ExecuteUpdate(wxS("create table testcol(textcol char(20) collate reversed);"));
    db.ExecuteUpdate(wxS("insert into testcol values ('anton');"));
    db.ExecuteUpdate(wxS("insert into testcol values ('berta');"));
    db.ExecuteUpdate(wxS("insert into testcol values ('cesar');"));

    wxSQLite3ResultSet q4 = db.ExecuteQuery("select textcol from testcol order by 1 desc;");

    while (q4.NextRow())
    {
      cout << (const char*)(q4.GetString(0).mb_str()) << endl;
    }

    if (wxSQLite3Database::HasBackupSupport())
    {
      db.SetBackupRestorePageCount(100);
      MyProgress myProgress;
      cout << endl << "Backup and restore database" << endl;
      if (wxSQLite3Database::HasEncryptionSupport())
      {
        db.Backup(&myProgress, wxGetCwd() + wxS("/test-backup.db"), wxS("password"));
      }
      else
      {
        db.Backup(&myProgress, wxGetCwd() + wxS("/test-backup.db"));
      }
      cout << endl << "... backup completed." << endl;
      if (wxSQLite3Database::HasEncryptionSupport())
      {
        db.Restore(wxGetCwd() + wxS("/test-backup.db"), wxS("password"));
      }
      else
      {
        db.Restore(wxGetCwd() + wxS("/test-backup.db"));
      }
      cout << endl << "... restore completed." << endl;
    }

    if (wxSQLite3Database::HasEncryptionSupport())
    {
      cout << endl << "Rekey the database (that is, decrypt it)" << endl;
      db.ReKey(wxEmptyString);
    }

    if (wxSQLite3Database::HasIncrementalBlobSupport())
    {
      cout << endl << "Incremental BLOB test" << endl;
      db.ExecuteUpdate(wxS("create table testblob(blobkey int, blobdata blob);"));
      db.ExecuteUpdate(wxS("insert into testblob values (1, zeroblob(100));"));
      wxSQLite3Blob incBlob = db.GetWritableBlob(1, wxS("blobdata"), wxS("testblob"));
      int blobSize = incBlob.GetSize();
      int offset = 12;
      wxMemoryBuffer memBuffer;
      const char* myData = "my data";
      memBuffer.AppendData(myData, strlen(myData)+1);
      incBlob.Write(memBuffer, 12);
      incBlob.Finalize();
      incBlob = db.GetReadOnlyBlob(1, wxS("blobdata"), wxS("testblob"));
      incBlob.Read(memBuffer, (int) strlen(myData)+1, 12);
      incBlob.Finalize();
      char* readBlobData = (char*) memBuffer.GetData();
      cout << "Incremental BLOB of size " << blobSize << " with value <"
           << readBlobData << "> at offset " << offset << endl;
    }

    cout << endl << "Database limits" << endl;
    wxSQLite3LimitType limitType;
    for (limitType = WXSQLITE_LIMIT_LENGTH; limitType <= WXSQLITE_LIMIT_VARIABLE_NUMBER; ++limitType)
    {
      cout << (const char*) wxSQLite3Database::LimitTypeToString(limitType).mb_str()
           << ": " << db.GetLimit(limitType) << endl;
    }

    cout << "Release memory " << endl;
    db.ReleaseMemory();

    cout << endl << "Test of RAII transactions" << endl;
    testTransaction();

    if (wxSQLite3Database::HasUserAuthenticationSupport())
    {
      cout << endl << "Test of user authentication" << endl;
      testUserAuthentication();
    }

    // Test accessing encrypted database files (currently SQLCipher only)
    TestCiphers();

    cout << endl << "End of tests" << endl;
    db.Close();
  }
  catch (wxSQLite3Exception& e)
  {
    cerr << e.GetErrorCode() << ":" << (const char*)(e.GetMessage().mb_str()) << endl;
    m_rc = e.GetErrorCode();
  }
  
  try
  {
    // Before shutdown of SQLite ALL database connections should be closed.
    wxSQLite3Database::ShutdownSQLite();
  }
  catch (wxSQLite3Exception& e)
  {
    cerr << e.GetErrorCode() << ":" << (const char*)(e.GetMessage().mb_str()) << endl;
    m_rc = e.GetErrorCode();
  }

  if (!m_testMode)
  {
    // Loop until user enters q or Q

    char c(' ');
    while (c != 'q' && c != 'Q')
    {
      cout << "Press q then enter to quit: ";
      cin >> c;
    }
  }
  return m_rc;
}

void Minimal::TestSQLCipher(wxSQLite3Cipher& cipher, const wxString& dbFileName, const wxString& dbKey)
{
  try
  {
    wxSQLite3Database db;
    cout << endl << "Open database '" << (const char*) (dbFileName.mb_str()) << "'" << endl;
    db.Open(dbFileName, cipher, dbKey);
    wxString keySalt = db.GetKeySalt();
    cout << "Key salt: " << (const char*) (keySalt.mb_str()) << endl;
    int numRows = db.ExecuteScalar("SELECT COUNT(*) FROM t1");
    cout << "Total number of rows = " << numRows << endl;
    cout << "Distinct tuples:" << endl;
    wxSQLite3ResultSet set = db.ExecuteQuery("SELECT DISTINCT * FROM t1");
    int count = 0;
    while (set.NextRow())
    {
      ++count;
      wxString col1 = set.GetString(0);
      wxString col2 = set.GetString(1);
      cout << count << ": " << (const char*) (col1.mb_str()) << ", " << (const char*) (col2.mb_str()) << endl;
    }
    db.Close();
  }
  catch (wxSQLite3Exception& e)
  {
    cerr << e.GetErrorCode() << ":" << (const char*) (e.GetMessage().mb_str()) << endl;
  }
}

void Minimal::TestCiphers()
{
  cout << endl << "Start testing ciphers" << endl;

  // Test to access database encrypted with SQLCipher version 1
  // Result: 75709 1 1 one one 1 2 one two 1 2
  wxSQLite3CipherSQLCipher sqlCipher1;
  sqlCipher1.InitializeVersionDefault(1);
  TestSQLCipher(sqlCipher1, wxS("sqlcipher-1.1.8-testkey.db"), wxS("testkey"));

  // Test to access database encrypted with SQLCipher version 2
  // using 4000 iterations for the HMAC key derivation and a HMAC salt mask of zero
  // Result: 38768 test-0-0 test-0-1 test-1-0 test-1-1
  wxSQLite3CipherSQLCipher sqlCipher2;
  sqlCipher2.InitializeVersionDefault(2);
  sqlCipher2.SetFastKdfIter(4000);
  sqlCipher2.SetHmacSaltMask(0);
  TestSQLCipher(sqlCipher2, wxS("sqlcipher-2.0-beta-testkey.db"), wxS("testkey"));

  // Test to access database encrypted with SQLCipher version 2
  // using the page number in big endian form (BE) for the HMAC calculation
  // Result: 78536 1 1 one one 1 2 one two
  wxSQLite3CipherSQLCipher sqlCipher2be;
  sqlCipher2be.InitializeVersionDefault(2);
  sqlCipher2be.SetHmacPgNo(2);
  TestSQLCipher(sqlCipher2be, wxS("sqlcipher-2.0-be-testkey.db"), wxS("testkey"));

  // Test to access database encrypted with SQLCipher version 2
  // using the page number in little endian form (LE) for the HMAC calculation
  // Note: No change to the default initialization necessary
  // Result: 78536 1 1 one one 1 2 one two
  wxSQLite3CipherSQLCipher sqlCipher2le;
  sqlCipher2le.InitializeVersionDefault(2);
  TestSQLCipher(sqlCipher2le, wxS("sqlcipher-2.0-le-testkey.db"), wxS("testkey"));

  // Test to access database encrypted with SQLCipher version 3
  // Result: 78536 1 1 one one 1 2 one two
  wxSQLite3CipherSQLCipher sqlCipher3;
  sqlCipher3.InitializeVersionDefault(3);
  TestSQLCipher(sqlCipher3, wxS("sqlcipher-3.0-testkey.db"), wxS("testkey"));

  cout << endl << "Finish testing ciphers" << endl;
}

IMPLEMENT_APP_CONSOLE(Minimal)
