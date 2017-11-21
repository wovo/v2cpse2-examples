# ===========================================================================
# 
# This tool must be run in an MSVC 2015 solution directory that contains
# its projects in subdirectories.
# It renames the projects subdirectories to reflect the name 
# of the project, and deletes junk found around.
#
# Hence to rename projects (or to prepare for distribution):
# - rename the projects in MSVC
# - quit MSVC
# - run this tool
# - restart MSVC
#
# (c) Wouter van Ooijen (wouter@voti.nl)
# 2016-11-02 version 1.0 work-in-progress
# license: Boost Software License - Version 1.0
#
# ===========================================================================
#
# Notes
# 
# - error handling is minimal
# - tested only on my setup...
# - should report directories that do not correspond to a project?
# - root namespace of a project is not renamed (cosmetic)
# - would be nice if the processing was in alphabetical order
# - should remove the .vs directory (what is in there?)
# - replace tabs by spaces??
#
# ===========================================================================

import os, sys, shutil

def check( condition, message ):
   "abort with the message when the condition is not true"
   
   if not condition:
      print( "fatal error: " )
      print( "   %s" % message )
      sys.exit( -1 )

def file_from_text( file_name, lines ):
   "write the lines in text to the file_name"
   
   try:
      with open( file_name, "w" ) as myfile:
         for line in lines: 
            myfile.write( line.replace( "\n", "" ) + "\n" )
   except:
      check( 0, "Output file [%s] could not be opened." % file_name )

def text_from_file( file_name ):
   "reads the text file and returns its content as a list of lines"
   
   try:
      with open( file_name, "r" ) as myfile:
         return myfile.readlines()
   except:
      check( 0, "Input file [%s] could not be opened." % file_name )
      
def entries( path = ".", match = None ):
   "the list of directory entries that contain the match as part of the name"
   
   try:
      #print( path, match, os.listdir( path ) )
      list = []
      for entry in os.listdir( path ):
         #print( entry )
         if ( match == None ) or ( entry.find( match ) > -1 ):
            list.append( entry )
      list.sort()      
      return list
   except:
      return []  
   
   
# =========================================================================== 
     
def real_project_name( project_file ):
   "extract the project name from the <ProjectName> entry in a project file"
   
   for line in text_from_file( project_file ):
      if line.find( "<ProjectName>" ) > -1:
         return line.split( '>' )[ 1 ].split( '<' )[ 0 ]
   check( 0, "No project name found in file [%s]" % project_file )           
   
def process_project( line ):
   "cleanup a project entry line, and its directory and files"
   
   parts = line.split( '"' )
   some_name = parts[ 3 ]
   project_file_full_name = parts[ 5 ]
   real_name = real_project_name( project_file_full_name )
   directory_name = project_file_full_name.split( '\\' )[ 0 ]
   project_file_name = project_file_full_name.split( '\\' )[ 1 ]

   print( "   check [%s]" % real_name )
   
   if( some_name != real_name ):
      print( "      change name (was [%s])" % some_name )
      line = line.replace( some_name, real_name )
   
   if( directory_name != real_name ):
      print( "      change directory (was [%s])" % directory_name )
      line = line.replace( directory_name + "\\", real_name + "\\" )
      os.rename( directory_name, real_name )     
      
   if( project_file_name.replace( ".vcxproj", "" ) != real_name ):
      print( "      change project file name entry (was [%s])" % project_file_name )   
      line = line.replace( project_file_name, real_name + ".vcxproj" )
      
      print( "      renaming project files" ) 
      os.rename( 
         os.path.join( real_name, project_file_name ),
         os.path.join( real_name, real_name + ".vcxproj" ))
      os.rename( 
         os.path.join( real_name, project_file_name + ".filters" ),
         os.path.join( real_name, real_name + ".vcxproj.filters" ))   

   if "Debug" in entries( real_name, "Debug" ):
      dir = real_name + "/Debug"
      print( "      delete [%s]" % dir )
      shutil.rmtree( dir ) 
         
   return line   
   
def run():

   # get the (one) solution file
   sln_files = entries( ".", ".sln" )
   check( 
      len( sln_files ) == 1, 
      "The current directory must contain a single .sln file" )   
   sln_file_name = sln_files[ 0 ]
   print( "processing project [%s]" % sln_file_name.replace( ".sln", "" ))
   
   # go over all projects mentioned in the solution file
   sln_lines = []
   for line in text_from_file( sln_file_name ):
      if line.startswith( 'Project("' ):
         line = process_project( line )
      sln_lines.append( line )
   # sln_file_name = sln_file_name.replace( ".sln", ".xxx" )   
   file_from_text( sln_file_name, sln_lines )
   
   # remove a Debug en Release directories
   for d in [ "Debug", "Release" ]:
      if d in entries():
         print( "delete %s directory" % d )
         shutil.rmtree( d )           
      
   # remove a <solution>.VC.db file
   # no idea what is in it, but it is apparently re-created automatically
   for file in entries( ".", "VC.db" ):
      print( "delete [%s]" % file )
      os.remove( file )     
      

# =========================================================================== 

run()