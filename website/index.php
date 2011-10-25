<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?php
  ////////////////////////////////////////////////////////////////////////////////////////////
  // Author: Ulrich Telle
  // Creation date: 17/07/2005
  // RCS-ID: $Id: index.php,v 1.14 2008/01/05 22:35:32 utelle Exp $
  // Notes: the index page of the website of this component
  ////////////////////////////////////////////////////////////////////////////////////////////
?>

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en-AU">
	<?php
      $compname = "wxSQLite3";
      $subdir = "wxsqlite3";
      require("compwebsite.inc.php");
  ?>

  <br/><?php write_h1("Documentation"); ?>
  <p>The doxygen-generated documentation for this component is available online
  <a href="../../docs/wxsqlite3/">here</a>. Please let me know if you think something is missing.</p>

	<br/><?php write_h1("Known bugs"); ?>
<p><ul>
<li><p><b><u>Symptom</u></b>: Endless recursion in method <b><i>wxSQLite3StringCollection::operator=</i></b> on assignment.
<br><b><u>Affected version(s)</u></b>: 2.0.0 &#150;  2.1.3
<br><b>Solution:</b>
<br><b>Fixed in wxCode SVN</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Method <b><i>wxSQLite3Table::GetDouble</i></b> fails to convert strings to double values in non-US locales.
<br><b><u>Affected version(s)</u></b>: all up to 1.9.2
<br><b>Solution:</b>
<br>Upgrade to version 1.9.3.<br>
<br><b>Fixed in version 1.9.3</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Method <b><i>TableExists</i></b> sometimes fails to find a table due to case sensitive search.
<br><b><u>Affected version(s)</u></b>: 1.4.1 &#150; 1.8.3
<br><b>Solution:</b>
<br>Upgrade to version 1.8.4.<br>
<br><b>Fixed in version 1.8.4</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Included Windows SQLite DLLs and SQLite shell crash on initialization due to build error in FTS3 extension.
<br><b><u>Affected version(s)</u></b>: 1.8.2
<br><b>Solution:</b>
<br>Please download the fixed SQLite DLLs from CVS or build the SQLite DLL yourself.
<br><b>Fixed in version 1.8.3</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Wrong type of transaction is issued in method <b>wxSQLite3Database::Begin</b> when requesting an exclusive transaction.
<br><b><u>Affected version(s)</u></b>: 1.4.1 &#150; 1.8.1
<br><b>Solution:</b>
<br>Change the following 2 lines in method <b>wxSQLite3Database::Begin</b> in <b>wxsqlite3.cpp</b>:
<br>&nbsp;&nbsp;&nbsp;&nbsp;case WXSQLITE_TRANSACTION_EXCLUSIVE:
<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sql &lt;&lt; _T("begin immediate transaction");
<br>to
<br>&nbsp;&nbsp;&nbsp;&nbsp;case WXSQLITE_TRANSACTION_EXCLUSIVE:
<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sql &lt;&lt; _T("begin <font color="red"><b>exclusive</b></font> transaction");<br>
<br><b>Fixed in version 1.8.2</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Compile time error in method <b>wxSQLite3Database::GetBlob</b> when using <b>gcc</b> compiler.
<br><b><u>Affected version(s)</u></b>: 1.8.0
<br><b>Solution:</b>
<br>Make the following change in <b>wxsqlite3.cpp</b>:
<br>Add explicit type cast in line 2018: const char* localDbName = (!dbName.IsEmpty()) ? <font color="red"><b>(const char*)</b></font> strDbName : (const char*) NULL;<br>
<br><b>Fixed in version 1.8.1</b>
</p></li>

<li><p><b><u>Symptom</u></b>: Reusing a wxSQLite3Database instance of an encrypted database
for a unencrypted database causes problems, since the instance is still flagged as encrypted.
<br><b><u>Affected version(s)</u></b>: 1.7.x &#150; 1.8.0
<br><b>Solution:</b>
<br>Make the following change in <b>wxsqlite3.cpp</b>:
<br>Add the following statement after line 1773: <b>m_isEncrypted = false;</b><br>
<br><b>Fixed in version 1.8.1</b>
</p></li>

<li><p><b><u>Symptom</u></b>: On <b><font color="red">big endian platforms</font></b>
the <b>SQLite encryption extension</b> included in wxSQLite3 unfortunately creates
<b><font color="red">non-portable database files</font></b> since the used MD5 algorithm
does not take endianess into account as it should.
<br><b><u>Affected version(s)</u></b>: 1.7.x
<br><b>Solution:</b>
<br>Upgrade to version 1.7.3.<br>
<br><b>Fixed in version 1.7.3</b>
</p></li>

<li><p><b><u>Symptom</u></b>: In the minimal sample application meta data and encryption support
is always enabled.
<br><b><u>Affected version(s)</u></b>: 1.7.1
<br><b>Solution:</b>
<br>Make the following changes in <b>minimal.cpp</b>:
<br>Line 236: Change <b>#if<font color="red">def</font> WXSQLITE3_HAVE_METADATA</b> to <b>#if WXSQLITE3_HAVE_METADATA</b>.
<br>Line 159 and 403: Change <b>#if<font color="red">def</font> WXSQLITE3_HAVE_CODEC</b> to <b>#if WXSQLITE3_HAVE_CODEC</b>.<br>
<br><b>Fixed in version 1.7.2</b>
</p></li>

<li><p><b><u>Symptom</u></b>: The call to <b>sqlite3_rekey</b> in <b>wxSQLite3Database::ReKey</b>
could cause a program crash, when used to encrypt a previously unencrypted database due to a NULL
pointer exception.
<br><b><u>Affected version(s)</u></b>: 1.7.0
<br><b>Solution:</b>
<br>Upgrade to version 1.7.1.<br>
<br><b>Fixed in version 1.7.1</b>
</p></li>

<li><p><b><u>Symptom</u></b>: In method <b>wxSQLite3Database::TableExists</b>
<b>mingw</b> reports a warning, program crashes when calling the method.
<br><b><u>Affected version(s)</u></b>: 1.0 &#150; 1.4.0
<br><b>Solution:</b>
<br>In call to <b>sprintf</b> replace <b>localTableName</b> by <b>(const char*) localTableName</b>,
that is, add an explicit cast of <b>(const char*)</b> for the sprintf argument <i>localTableName</i>.<br>
<br><b>Fixed in version 1.4.1</b>
</p></li>
</ul></p>
<p>To submit a bug report please look at <a href="../../support.php">wxCode support page</a>.</p>

    
	<br/><?php write_h1("Future enhancements"); ?>
  <p>None. To submit a feature request please look at <a href="../../support.php">wxCode support page</a>.</p>
    
	<br/><?php write_h1("Links"); ?>
<p>
<ul>
<li><p>Thanks to <b><i>Hakki Dogusan</i></b> dynamic loading of the SQLite library was introduced in version 1.4 of <b>wxSQLite3</b>.
Additionally <b><i>Hakki Dogusan</i></b> has created a <a href="http://www.dynaset.org/dogusanh/download.html">Lua binding for wxSQLite3</a>.</p></li>

</ul>
</p>

	<br/><?php write_h1("Supporting further development"); ?>
<table><tr><td valign="center">
<form action="https://www.paypal.com/cgi-bin/webscr" method="post">
<input type="hidden" name="cmd" value="_s-xclick">
<input type="image" src="https://www.paypal.com/de_DE/i/btn/x-click-but04.gif" border="0" name="submit" alt="Make a donation through PayPal - fast, free of charge and secure!">
<img alt="" border="0" src="https://www.paypal.com/de_DE/i/scr/pixel.gif" width="1" height="1">
<input type="hidden" name="encrypted" value="-----BEGIN PKCS7-----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-----END PKCS7-----">
</form>
</td><td valign="top"><p>If you find <b>wxSQLite3</b> useful and would like to support the further development of this <b>wxWidgets</b> component, you may make a <b>donation</b> by clicking on the button on the left.</p></td></tr></table>

	<br/><?php require("footer.inc.php"); ?>
</html>
