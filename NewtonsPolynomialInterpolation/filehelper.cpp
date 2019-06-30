#include "filehelper.h"

filehelper::filehelper()
{

}

FunctionTable filehelper::readTable(const string filename)
{
    FunctionTable table;

    ifstream in(filename);
    if (in.is_open())
    {
        string buf;

        while (getline(in, buf))
        {
            //vector<string> numbers = split(buf, ' ');
            char *pEnd;
            double arg = strtod(buf.c_str(), &pEnd);
            double val = strtod(pEnd, nullptr);
            table.add(arg, val);
        }
    }
    in.close();

    return table;
}

vector<string> filehelper::split(string text, char splitter)
{
  string buffer;
  vector<string> strings;
  for (const char c : text)
  {
      if (c != splitter) buffer.push_back(c);
      else
      {
          strings.push_back(buffer);
          buffer.clear();
      }
    }
  if(!buffer.empty()) strings.push_back(buffer);
  return strings;
}
