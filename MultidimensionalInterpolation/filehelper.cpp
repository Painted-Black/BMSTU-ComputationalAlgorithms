#include "filehelper.h"

filehelper::filehelper()
{

}

TwoVariablesFunction* filehelper::readTable(const string filename)
{
    TwoVariablesFunction *table;
    ifstream in(filename);
    if (in.is_open())
    {
        string buf;
        getline(in, buf);
        size_t sizeX, sizeY;
        char *p;
        sizeX = strtoul(buf.c_str(), &p, 10);
        sizeY = strtoul(buf.c_str(), &p, 10);
        table = new TwoVariablesFunction(sizeX, sizeY);
        double startX, startY;
        getline(in, buf);
        startX = strtod(buf.c_str(), &p);
        startY = strtod(buf.c_str(), &p);
        table->setStartX(startX);
        table->setStartY(startY);

        while (getline(in, buf))
        {
            //vector<string> numbers = split(buf, ' ');
            char *pEnd;
            double x = strtod(buf.c_str(), &pEnd);
            double y = strtod(pEnd, &pEnd);
            double z = strtod(pEnd, nullptr);
            table->add(x, y, z);
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
