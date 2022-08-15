
#include "../Includes/request.hpp"
#include "../Includes/tt.hpp"
std::vector<std::string> parsing_request(char* buffer)
{
    int i  = 0;
    std::string str;
    std::vector<std::string> request;
    while (buffer[i])
    {
        
        str.push_back(buffer[i]);
          if(buffer[i] == '\n' || buffer[i + 1] == '\0') // this is too form string not send char by char
          {
            request.push_back(str);
            str.clear();
          }
            //i++;
        i++;
    }
return (request);
}
int check_post_request(std::vector<std::string > request)
{
    int i = 0;
    int transfer_encoding = 0;
    int Content_length = 0;
    std::cout << "INSIDE POST REQUEST" << std::endl;
    while ( i < request.size())
    {
        if (request[i].find("transfer_encoding:") == 0)
       transfer_encoding = 1;
        if (request[i].find("Content-Length:") == 0)
     {   
        Content_length = 1;
     }
        i++;

    }
    std::cout << "=>>>>>" << Content_length << "   " << transfer_encoding << std::endl;
    if (Content_length == 1 || transfer_encoding == 1)
        return (1);
    return (0);
}
int get_request_method(std::vector<std::string > request)
{
   // std::string request;
 std::vector<std::string> method;

    size_t found = request[0].find("GET");
    if(found != string::npos)
    {
    method = split(request[0]," ","GET");
    std::cout << method[0] << std::endl;
    return(1);
    }
    found = request[0].find("POST");
     if(found != string::npos)
    {
    method = split(request[0]," ","POST");
    std::cout << method[0] << std::endl;
    return (2);
    }
      found = request[0].find("DELETE");
     if(found != string::npos)
    {
    method = split(request[0]," ","DELETE");
    std::cout << method[0] << std::endl;
    return (3);
    }
   // std::cout << method[0] << std::endl;
    return (0);
}

int get_location_length(std::string first_line)

{
std::string s = first_line;
std::string delimiter = " ";

size_t pos = 0;
int count = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
    if (count == 1)
    {
        return (token.size());
    }
    count++;
}
return (0);

}
int get_vrs_length(std::string first_line,int found)
{
    int count = 0;
    for (int i = found;i < first_line.length();i++)
    {

      count++;
    }
    return (count);
}
std::vector<std::string>     split_sboof(std::string s1, std::string delim)
{
    std::vector<std::string>     vector;
    std::size_t found = s1.find(delim, 1);
    std::size_t help = 0;

    while (found != std::string::npos)
    {
        if (s1.substr(help, found - help) != "/")
            vector.push_back(s1.substr(help, found - help));
        help = found;
        (delim != "/") ? help++ : help;
        found = s1.find(delim, help + 1);
    }
    vector.push_back(s1.substr(help, s1.size()));

    return (vector);
}
std::string get_request_location(std::vector<std::string > request)
{
    std::string location;
    std::vector <std::string > method;
    std::vector <std::string > parsing_helper;

  
         if(request[0].find("?") != std::string::npos)
         {
          //std::cout << "HHEHEHEHEHHEHHEHE" << std::endl;
          method = split_sboof(request[0]," ");
           if(!method[1].empty())
           {
            parsing_helper = split_sboof(method[1],"?");
            location = parsing_helper[0];
           }
         }
       else
       {
      method = split_sboof(request[0]," ");
        if(!method[1].empty())
        location = method[1];
        else
        location = "EMPTY CHECK REQUEST LOCA" ;
       }
     //   location_length = get_location_length(request[0]);
      //  location.insert(0,request[0],found + 4,11);

    
 
  //  method = split(request[0]," ","POST");
  //  std::cout << method[0] << std::endl;
 
    
    return location;
}
std::string get_request_query(std::vector<std::string > request)
{
   std::string qwery;
    std::vector <std::string > method;
    std::vector <std::string > parsing_helper;

  
         if(request[0].find("?") != std::string::npos)
         {
          //std::cout << "HHEHEHEHEHHEHHEHE" << std::endl;
          method = split_sboof(request[0]," ");
           if(!method[1].empty())
           {
            parsing_helper = split_sboof(method[1],"?");
            qwery = parsing_helper[1];
           }
         }
     //   location_length = get_location_length(request[0]);
      //  location.insert(0,request[0],found + 4,11);

    
 
  //  method = split(request[0]," ","POST");
  //  std::cout << method[0] << std::endl;
 
  //  std::cout << method[0] << std::endl;
    
    return qwery;
}


std::string get_request_vrs(std::string first_line)
{
   
    std::string vrs;
    std::vector <std::string > method;
      size_t found = first_line.find("HTTP");
      int vrs_length = 0;
    if(found != string::npos)
    {
        vrs_length = get_vrs_length(first_line,found);
        vrs.insert(0,first_line,found,vrs_length - 1);
       //std::cout << "GG =>  " << vrs_length << " " << vrs  << "|" << std::endl;

    }
    return vrs;
}
std::vector<std::string > splitv2(std::string line,std::string delim)
{
std::string s = line;
std::string delimiter = delim;
std::vector<std::string> splited;
size_t pos = 0;
int count = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
    splited.push_back(token);
}
return (splited);
}

 std::map<std::string, std::string> get_request_headers(std::vector <std::string > full_request)
 {
    int i = 0;
    std::map<std::string ,std::string > headers;
    std::vector <std::string > get_headers;
    std::string head;
    std::string tail;
    int length = 0;
       size_t found ;
    full_request.assign(full_request.begin() + 1,full_request.end());
  //  std::cout << "------------Request Headers----------------"  << std::endl;
    while ( i < full_request.size())
    {   
        if (full_request[i].compare("\n")  == 0)
        {
    std::cout << "------------------PPPPPPPPPPPPP------------"  << std::endl;
        return (headers); // to TEST
        }
      found = full_request[i].find(":");
        if(found != string::npos)
    {
      length = full_request[i].size() - found;
      head.insert(0,full_request[i],0,found);
      tail.insert(0,full_request[i],found + 2,length - 4);
      //std::cout << "tail=" <<  tail <<"|" << std::endl;
    headers[head] = tail;
    head.clear();
    tail.clear();

    }  

        i++;
    }

    return (headers);
 }

 std::string get_request_body(std::vector < std::string > full_request)
 {
    int i = 0;
    int inside = 0;
    std::string body;
    
       // std::cout << "INSIDE BODY REQUEST" << std::endl;

    while ( i < full_request.size())
    {
           if (inside == 1)
        {
            body = body + full_request[i];
          //  std::cout << "AAAAA" << body <<  full_request[i] << std::endl;
        }
        if (full_request[i].size() == 2)
        inside = 1;
         // std::cout << "|"  <<  full_request[i + 1]  << "|"<< std::endl;

     
        i++;
    }
    return (body);
 }