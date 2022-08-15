
#include "../Includes/tt.hpp"
#include <vector>
#include <sstream>

// for string delimiter
std::vector<std::string> split (std::string s, std::string delimiter,char *compare) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
   std:: vector<std::string> res;
   std::string val;
   std::stringstream streamData(s);
   const char separator = ' ';
/**
 * @brief 
 * 
 *
    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }
    res.push_back (s.substr (pos_start));
    return res;
    */
   int done = 0;
   while (std::getline(streamData,val,separator))
   {
    
    int value = val.compare(compare);
    if (value == 0)
    done = 1;
     if(val.size() > 0  && done == 1)
    res.push_back(val);
   //res.push_back(val);
   
   }
   return (res);
}
/**
 * @brief 
 * 
 * @param text_vector 
 * @return std::vector<std::string > 
 * STILL BUG , ACCEPTS MULTIPLE SERVER_NAMES 
 */
std::vector<std::string > extract_server_names(std::vector<std::string> text_vector)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
        // std::cout << "|" <<  text_vector[i] << std::endl;
        parser = split(text_vector[i]," ","server_names");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("server_names") == 0)
            {

                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many server_names in config files !" << std::endl;
            exit(1);
            }
                server_names = split (text_vector[i]," ","server_names");
             
                inside = 1;
            }
            y++;
        }
    i++;
    }
    std::vector <std::string> correct_names(server_names.begin() + 1,server_names.end());
    return (correct_names);
}

int extract_server_port(std::vector<std::string> text_vector)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = 0;
    while ( i < text_vector.size())
    {  
        parser = split(text_vector[i]," ","listen");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("listen") == 0)
            {
                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many Port in config files !" << std::endl;
            exit(1);
            }
                delimitier = parser[1].find(':');
                parser[1].erase(parser[1].begin(),parser[1].end() - delimitier + 3); 
                ss << parser[1];
            }
            y++;
        }
    i++;
    }
ss >> num;
    return (num);
}



std::string extract_server_host(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
 std::vector <std::string> tmp;
std::string server_host;

    int i = 0;
    int y = 0;
    int inside = 0;
    int delimitier = 0;
    while ( i < text_vector.size())
    {  
      
        parser = split(text_vector[i]," ","listen");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("listen") == 0)
            {
                delimitier = parser[1].find(':');
                parser[1].erase(delimitier);
                server_host  =  parser[1].c_str();
                //parser[1].erase(std::remove(parser[1].begin(),parser[1].end(),':',parser[1].end()));
                inside = 1;
            }
            y++;
        }
    i++;
    }

    return (server_host);
}


std::string extract_server_root(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_names;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
        parser = split(text_vector[i]," ","");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("root") == 0)
            {   
                server_names = split (text_vector[i]," ","root");

                inside = 1;
            }
            y++;
        }
    i++;
    }
    return (server_names[1]);

}



std::vector<std::string> extract_allowed_methods(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
 std::vector <std::string> allowed_methods;
  std::vector <std::string> correct_methods;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].find("location") != std::string::npos)
        return (correct_methods);
        parser = split(text_vector[i]," ","allow_methods");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("allow_methods") == 0)
            {
                allowed_methods = split (text_vector[i]," ","allow_methods");
                correct_methods.assign(allowed_methods.begin() + 1,allowed_methods.end());
                inside = 1;
            }
            y++;
        }
    i++;
    }

    return (correct_methods);
}


std::vector<std::string> extract_server_index(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_index;
  std::vector <std::string> correct_index;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
        if(text_vector[i].find("location") != std::string::npos)
        return (correct_index);
        parser = split(text_vector[i]," ","index");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("index") == 0)
            {
                server_index = split (text_vector[i]," ","index");
           correct_index.assign(server_index.begin() + 1,server_index.end());
                inside = 1;
            }
            y++;
        }
    i++;
    }
   
    return (correct_index);

}

std::string extract_server_upload_path(std::vector<std::string> text_vector)
{
std::vector<std::string> parser;
 std::vector <std::string> server_upload_path;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
         if (inside == 1)
    return (server_upload_path.at(1));
        }
        parser = split(text_vector[i]," ","upload_path");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("upload_path") == 0)
            {   
                server_upload_path = split (text_vector[i]," ","upload_path");

                inside = 1;
            }
            y++;
        }
    i++;
    }
    return (server_upload_path[1]);
}

std::vector<std::vector<std::string > > extract_server_errors_page(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
     std::vector <std::string> test;
     std::vector <std::string > errors_pages;
 std::vector <std::vector<std::string> > server_error_pages;
 std::vector <std::vector<std::string> > correct_server_error_pages;

    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
       // if(text_vector[i].find("location") != std::string::npos)
        //return (correct_index);
        parser = split(text_vector[i]," ","error_page");
        y = 0;
        while (y < parser.size())
        {
           // i++;
            if (parser[y].compare("error_page") == 0)
            {

                test = split (text_vector[i]," ","error_page");
           //correct_index.assign(server_index.begin() + 1,server_index.end());
                errors_pages.assign(test.begin() + 1,test.end());
                inside = 1;
                server_error_pages.push_back(errors_pages);
                test.clear();
            }
            y++;
        }
    i++;
    }
    //correct_server_error_pages.assign(correct_server_error_pages.begin(),server_error_pages.begin() + 1,server_error_pages.end());
    //if(!server_error_pages.size())
  // server_error_pages.assign(server_error_pages.begin() + 1,server_error_pages.end());

    return (server_error_pages);
}




std::vector<std::vector<std::string > > extract_server_redirections(std::vector<std::string> text_vector)
{
     std::vector<std::string> parser;
     std::vector <std::string> test;
     std::vector <std::string > redirections;
 std::vector <std::vector<std::string> > server_redirections;
  std::vector <std::string> correct_server_redirections;
    int i = 0;
    int y = 0;
    int inside = 0;
    while ( i < text_vector.size())
    {  
       // if(text_vector[i].find("location") != std::string::npos)
        //return (correct_index);
        parser = split(text_vector[i]," ","redirection");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("redirection") == 0)
            {
                test = split (text_vector[i]," ","redirection");
                redirections.assign(test.begin() + 1,test.end());
           //correct_index.assign(server_index.begin() + 1,server_index.end());
                inside = 1;
                server_redirections.push_back(redirections);
                test.clear();
            }
            y++;
        }
    i++;
    }
   
    return (server_redirections);
}

long long int extract_server_max_body_size(std::vector<std::string> text_vector)
{

 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = 0;
    while ( i < text_vector.size())
    {  
        
          if(text_vector[i].find("location") != std::string::npos)
        {
         if (inside == 1)
         {
            ss >> num;
        return ( num);
         }
        }
        parser = split(text_vector[i]," ","client_max_body_size");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("client_max_body_size") == 0)
            {
       
                ss << parser[1];
              //  std::cout << "parser 1 => " << parser[1] << std::endl;
                inside = 1 ;
            }
            y++;
        }
    i++;
    }
ss >> num;
    return (num);
}

bool extract_server_autoindex(std::vector<std::string > text_vector)
{

 std::vector<std::string> parser;

    int i = 0;
    int y = 0;
    int inside = 0;
    bool autoindex = false;
    while ( i < text_vector.size())
    {  
        
        parser = split(text_vector[i]," ","autoindex");
        if(text_vector[i].find("location") != std::string::npos)
            inside = 1 ;
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("autoindex") == 0)
            {
                if ( inside == 0)
            {
            if (parser[1].compare("on") == 0)
                   autoindex = true;
            }
            }
            y++;
        }
    i++;
    }

    return (autoindex);
}

int extract_number_of_locations(std::vector <std::string> text_vector)
{

    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    bool autoindex = false;
    while ( i < text_vector.size())
    {  
        
    if(text_vector[i].find("location") != std::string::npos)
            count++;
        i++;
    }
    return (count);
}