#!/usr/bin/python

import os
# Import modules for CGI handling
import cgi, cgitb

print 'HTTP/1.1 200 OK'
print 'Content-Type: text/html\r\n\r\n'

print '<html>'
print '<head>'
print '<title>CGI environment</title>'
print '</head>'
print '<body bgcolor="a2a2a2" leftmargin="42" topmargin="42">'
print '<h2>Below are all environment variables given to printenv.py</h2>'
print "<font size=+1>Environment</font><br>"
for param in os.environ.keys():
   print "<b>%20s</b>: %s<br>" % (param, os.environ[param])
print '</body>'
print '</html>'
