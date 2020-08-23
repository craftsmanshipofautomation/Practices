/*
workflow:
   - parse markdown, get headers with level larger than 1, return a new toc
   - while parsing, a temp file is created, containing every line except toc if it exists
   - write that new toc to the output, altogether with contents in the temp file
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include "encoding.h"

using namespace std;

#define TEMPFILE "content.temp"
#define DEFAULT_DEST "dest.markdown"

static int insert_at_line = 0;
static bool need_newline = true;

void copy(const string &dest, const string &src)
{
   ofstream write(dest);
   ifstream read(src);
   string line;
   while (getline(read, line))
   {
      write << line << endl;
   }
   write.close();
   read.close();
}

void write(ofstream &dest, const string &toc)
{
   ifstream read(TEMPFILE);
   string line;
   for (int i = 0; i < insert_at_line; ++i)
   {
      getline(read, line);
      dest << line << endl;
   }
   if (!toc.empty())
   {
      if (need_newline)
         dest << endl;
      dest << toc;
      if (need_newline)
         dest << endl;
   }
   while (getline(read, line))
      dest << line << endl;
   read.close();
}

bool is_special_char_for_title(char c)
{

}

string construct_entry(int header_level, const string &title)
{
   string ret;
   char hex[2];   
   for (int i = 1; i < header_level; ++i)
   {
      ret += "    ";
   }
   ret += '-';
   ret += ' ';
   ret += '[';
   for (auto& i: title)
   {
      if (i == 91 || i == 92 || i == 93)
         ret += '\\';
      ret += i;
   }
   ret += ']';
   ret += '(';
   ret += '#';
   for (auto& i : title)
   {
      if (i == ' ')
         ret += '-';
      else if ((i >= 65 && i <= 90))
         ret += tolower(i);
      else if (i == '_' || i >= 97 && i <= 122 || isdigit(i))
         ret += i;
      else if ((unsigned int)(i) < 127)
         /* pass */;
      else
      {
         hexify(i, hex);
         ret += '%';
         ret += hex[0];
         ret += hex[1];         
      }
   }
   ret += ')';
   ret += '\n';
   return ret;
}

string generate_toc(ifstream &src)
{
   insert_at_line = 0;
   int line_num = 0;
   ofstream temp_out(TEMPFILE);
   string toc_header{"## **Table of Contents**\n"};
   string ret;
   string line;
   bool in_code_block = false;
   bool toc_already_exists = false;
loop:
   while (getline(src, line))
   {
      ++line_num;
      if (line.rfind("```", 0) == 0)
      {
         in_code_block = !in_code_block;
         goto write;
      }
      // start from ##
      if (line.rfind("##", 0) == 0)
      {
         if (in_code_block)
            goto write;
         if (!toc_already_exists && line.find("**Table of Contents**") != string::npos)
         {
            // toc already exists, wipe out
            toc_already_exists = true;
            need_newline = false;
            if (!insert_at_line)
               insert_at_line = line_num - 1;
            --line_num;
            while (getline(src, line))
            {
               if (line.rfind("-------", 0) == 0)
               {
                  goto loop;
               }
            }
         }
         int header_level = 0;
         auto i = line.cbegin();
         if (!insert_at_line)
            insert_at_line = line_num - 1;
         while (*++i == '#')
            ++header_level;
         if (*i != ' ')
            break;
         while (*++i == ' ')
            ;
         string title(i, line.cend());
         title = construct_entry(header_level, title);
         ret += title;
         goto write;
      }
   write:
      temp_out << line << endl;
   }
   temp_out.close();
   if (!ret.empty())
   {
      ret = toc_header + ret;
      ret += "\n-------\n";
   }
   return ret;
}

void help()
{
   cout << "Usage: toc [Options] file" << endl;
   cout << "Options:" << endl;
   cout << "   -h       Display this information." << endl;
   cout << "   -o       Output file" << endl;
}

int main(int argc, char **argv)
{
   string src_path, dest_path;
   for (int i = 1; i < argc; ++i)
   {
      if (0 == strcmp(argv[i], "-h"))
      {
         help();
         ::exit(0);
      }
      if (0 == strcmp(argv[i], "-o"))
      {
         dest_path = argv[++i];
         continue;
      }
      src_path = argv[i];
   }
   if (dest_path.empty())
   {
      dest_path = DEFAULT_DEST;
   }
   if (src_path.empty())
   {
      help();
      ::exit(-1);
   }
   ifstream src(src_path);
   if (!src.good())
   {
      cout << src_path << ": No such file" << endl;
      ::exit(-2);
   }
   ofstream dest(dest_path);
   auto r = generate_toc(src);
   write(dest, r);
   ::remove(TEMPFILE);
   if (dest_path == DEFAULT_DEST)
   {
      copy(src_path, DEFAULT_DEST);
      ::remove(DEFAULT_DEST);
   }
   src.close();
   dest.close();
}