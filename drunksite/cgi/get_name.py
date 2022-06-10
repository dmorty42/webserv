#!/usr/bin/python

# Import modules for CGI handling
import cgi, cgitb

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
first_name = form.getvalue('first_name')
last_name  = form.getvalue('last_name')


print ('HTTP/1.1 200 OK')
print ('Content-Type: text/html\r\n\r\n')
#print 'LoCatIon:/foo/jbcgi.pl/path/info?query=string\r\n\r\n'
#print 'LoCatIon:http://Bim/Bam/Boumm\r\n\r\n'

#print '<!DOCTYPE html>'
print ('<html>')
print ('<head>')
print ('<title>checkbox problem</title>')
print ('</head>')
print ('<body  bgcolor="a2a2a2">') 
print ('<h2 align="center"> Hello you... Do you wonder what are your name & last name ? Check it out below</h2>')
print ('<h2 align="center">  Your name is: ')
print ('<h1 align="center">')
print (" %s %s. </h1>" % (first_name, last_name))
print ('<h2 align="center">  Try to remember </h2>')
print ('</body>')
print ('</html>')