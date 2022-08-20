#include "../Includes/server.hpp"
#include "../Includes/tt.hpp"
#include "../Includes/location.hpp"

server::server():
    _name(),
    _listen_port(-1),
    _listen_host(),
    _allowed_methods(std::vector<std::string>()),
    _index(),
    _error_pages(std::map<std::string,std::string>()),
    _redirections(),
    _root(""),
    _client_max_body_size(-1),
    _autoindex(false),
    response_chuncked(false)
{

}


server::server (const server &src)
{
    if (this != &src)
    {
        *this = src;
    }

}
int check_listen_host(std::string tmp)
{
    int i = 0;
    int count = 0;
    std::string check_if_number;
    if (tmp != "localhost")
    {
    while (tmp[i])
    {
        if(tmp[i] == '.')
       { 
        std::cout << check_if_number << std::endl;
        if(isnumber(check_if_number.c_str()) == false)
        {
            std::cout << " host not well defined ! Host should be all numeric" << tmp << std::endl;
            exit(1);
        }
        check_if_number.clear();
        count++;
        }
        else
        check_if_number += tmp[i];
        i++;
    }
    if (count != 3)
    {
        std::cout << "host not well defined !" << count << " "<< tmp <<std::endl;
        exit(1);
    }
    }
    return (0);
    
}
server    &server::operator=(server const &rhs)
{
  if (this != &rhs)
    {
        _name = rhs._name;
        _listen_host = rhs._listen_host;
        _listen_port = rhs._listen_port;
        _index = rhs._index;
        _autoindex = rhs._autoindex;
        _client_max_body_size = rhs._client_max_body_size;
        _allowed_methods = rhs._allowed_methods;
        _location = rhs._location;
        _cgi = rhs._cgi;
        _redirections = rhs._redirections;
        _upload_path = rhs._upload_path;
        _root = rhs._root;
        _error_pages = rhs._error_pages;
    }
    return *this;
}
std::map<std::string, std::string>  fill_error_page( void )
{
    std::map<std::string, std::string> tmp;

    tmp["204"] = "./errorpages/204/204.html";
    tmp["301"] = "./errorpages/301/301.html";
    tmp["400"] = "./errorpages/400/400.html";
    tmp["403"] = "./errorpages/403/403.html";
    tmp["404"] = "./errorpages/404/404.html";
    tmp["405"] = "./errorpages/405/405.html";
    tmp["413"] = "./errorpages/413/413.html";
    tmp["414"] = "./errorpages/414/414.html";
    tmp["500"] = "./errorpages/500/500.html";
    tmp["501"] = "./errorpages/501/501.html";

    return (tmp);
}

server::server(std::vector<std::string> text_vector,int helper)
{
   
   int number_of_locations = 0;
    this->_autoindex = false;
    this->_listen_port = -1;
    std::map <std::string,std::string> default_error_pages;
    // std::vector <std::string> allowed_methods;
    // allowed_methods.push_back("GET");
    // allowed_methods.push_back("DELETE");
    // allowed_methods.push_back("POST");
   this->_name = extract_server_names(text_vector,helper);
   
   this->_listen_port = extract_server_port(text_vector,helper);;
   // this->_listen_port = extract_server_port(text_vector,helper);
    this->_listen_host = extract_server_host(text_vector,helper);
    // this->_allowed_methods = allowed_methods;
        this->_allowed_methods = extract_allowed_methods(text_vector,helper);
        this->_index = extract_server_index(text_vector,helper);
   this->_upload_path = extract_server_upload_path(text_vector,helper);
//    this->_error_pages = extract_server_errors_page(text_vector,helper);
default_error_pages= fill_error_page();
   this->_error_pages = extract_server_errors_page1(text_vector,helper,default_error_pages);
//    this->_redirections = extract_server_redirections(text_vector,helper);
   this->_redirections = extract_server_redirections1(text_vector,helper);
   this->_root = extract_server_root(text_vector, helper);  
//     //this->_location = extract_server_location(text_vector);
 this->_cgi = extract_server_cgi(text_vector,helper);
//    // this->_cgi = extract_server_cgi(text_vector);
    this->_client_max_body_size = extract_server_max_body_size(text_vector,helper);
   this->_autoindex = extract_server_autoindex(text_vector,helper);
   //this->_name = split(text_vector[2]," ");
    //std::cout << test[0] << std::endl << test[1] << std::endl;
//      std::cout << "----------------------------************S************* ------------------"  << std::endl;

//     std::cout << "-----------------------Server Names : ------------------"  << std::endl;
// for (std::vector<std::string>::iterator it = this->_name .begin();it != this->_name .end();it++)
//          std::cout << *it << std::endl;
       
//          std::cout << "-----------------------Server Port : ------------------"  << std::endl;
//          std::cout << this->_listen_port << std::endl;

//            std::cout << "-----------------------Server Host : ------------------"  << std::endl;
//          std::cout << this->_listen_host << std::endl;
//             std::cout << "-----------------------Server root : ------------------"  << std::endl;
//          std::cout << this->_root << std::endl;
//                    std::cout << "-----------------------Server allowed methods : ------------------"  << std::endl;
//      for (std::vector<std::string>::iterator it1 = this->_allowed_methods .begin();it1 != this->_allowed_methods .end();it1++)
//          std::cout << *it1 << std::endl;
//      std::cout << "-----------------------Server  Index : | ------------------"  << std::endl;
//      for (std::vector<std::string>::iterator it2 = this->_index .begin();it2 != this->_index .end();it2++)
//          std::cout << *it2 << std::endl;
//      std::cout << "-----------------------Server  upload path : ------------------"  << std::endl;
//     std::cout << this->_upload_path << std::endl;
//      std::cout << "-----------------------Server  error pages  : ------------------"  << std::endl;
//         try
//         {
//             int length = 0;
//             while (length < this->_error_pages.size())
//             {
//                    for (std::vector<std::string>::iterator it3 = this->_error_pages[length].begin();it3 != this->_error_pages[length].end();it3++)
//          std::cout << *it3 << std::endl;
//            std::cout << "-----------------------------------------------"  << std::endl;
//            length++;
//             }
     

//         // for (std::vector<std::string>::iterator it4 = this->_error_pages[1].begin();it4 != this->_error_pages[1].end();it4++)
//         //  std::cout << *it4 << std::endl;
//         //    std::cout << "-----------------------------------------------"  << std::endl;
         
//         //   for (std::vector<std::string>::iterator it5 = this->_error_pages.at(2).begin();it5 != this->_error_pages.at(2).end();it5++)
//         //  std::cout << *it5 << std::endl;
//         // } 
//         }
//         catch (const std::string & exception)
//         {
//             std::cout << "error pages exception !" << std::endl;
//         }
//        try {
//            std::cout << "-----------------------Server  redirections  pages  : ------------------"  << std::endl;
//            int length = 0;
//             while (length < this->_redirections.size())
//             {
//                    for (std::vector<std::string>::iterator it3 = this->_redirections[length].begin();it3 != this->_redirections[length].end();it3++)
//          std::cout << *it3 << std::endl;
//            std::cout << "-----------------------------------------------"  << std::endl;
//            length++;
//             }
//         //  for (std::vector<std::string>::iterator it3 = this->_redirections[0].begin();it3 != this->_redirections[0].end();it3++)
//         //  std::cout << *it3 << std::endl;
//         //    std::cout << "-----------------------------------------------"  << std::endl;
     
//         // for (std::vector<std::string>::iterator it4 = this->_redirections[1].begin();it4 != this->_redirections[1].end();it4++)
//         //  std::cout << *it4 << std::endl;
         
//          // for (std::vector<std::string>::iterator it5 = this->_redirections.at(2).begin();it5 != this->_redirections.at(2).end();it5++)
//          //std::cout << *it5 << std::endl;
//        }
//        catch (const std::string & exception )
//        {
//         std::cout << "redirections pages exception ! " << std::endl;
//        }
//            std::cout << "-----------------------Server  Client Max Body Size   : ------------------"  << std::endl;
//         std::cout << this->_client_max_body_size << std::endl;
//         std::cout << "-----------------------Server  AutoIndex    : ------------------"  << std::endl;
//         if (this->_autoindex == true)
//         std::cout << "autoindex on ! server : " << helper  << std::endl;
//         else if (this->_autoindex == false)
//         std::cout << "autoindex off  ! server : " << helper << std::endl;

  
//            std::cout << "-----------------------Server   CGI     : ------------------"  << std::endl;

//     for (std::vector<cgi>::iterator it = this->_cgi.begin();it != this->_cgi.end();it++)
//     std::cout << "cgi_name : " <<it->get_cgi_name() << " cgi_path : " << it->get_cgi_path() << std::endl;

   int index = 0;
   number_of_locations = extract_number_of_locations(text_vector,helper);
   while ( index  < number_of_locations)
   {
   location  mylocation(text_vector,index,helper);
  //  std::cout << "=> HM"<< mylocation.get_locations_path() << std::endl;
    this->_location.push_back(mylocation);
    index++;
   }
   if(this->_listen_port == -1)
  {
     std::cout << "Port not well defined ! server index " << helper << std::endl;
    exit(1);
    }
    check_listen_host(this->_listen_host);
}   

server::~server()
{

}

    std::string                  server::get_name(int i) const
    {
        return (this->_name[i]);
    }
    unsigned int                  server::get_name_size() const
    {
        return (this->_name.size());
    }

    std::string                   server::get_listen_host() const
    {
        return (this->_listen_host);
    }

    int                          server::get_listen_port() const
    {
        return (this->_listen_port);
    }
    std::vector<std::string>     server::get_allowed_methods() const
    {
        return (this->_allowed_methods);
    }
    unsigned int                 server::get_allowed_methods_size() const
    {
        return (this->_allowed_methods.size());
    }
    std::vector<std::string>     server::get_index() const
    {
        return(this->_index);
    }
    unsigned int                 server::get_index_size() const
    {
        return (this->_index.size());
    }
    // std::vector<std::string>     server::get_error_pages(int i) const
    // {
    //     return(this->_error_pages[i]);
    // }
    unsigned int                 server::get_error_pages_size() const
    {
        return (this->_error_pages.size());
    }
    unsigned int                 server::get_redirections_size() const
    {
        return(this->_redirections.size());
    }
    // std::vector<std::string>     server::get_redirections(int i) const
    // {
    //     return(this->_redirections.at(i));
    // }
    // std::vector<std::vector<std::string> > server::get_redirections() const
    // {
    //     return(this->_redirections);
    // }
    std::string                  server::get_root() const
    {
        return(this->_root);
    }
    std::string                  server::get_upload_path() const
    {
        return(this->_upload_path);
    }
     std::vector<location>        server::get_location() const
     {
        return (this->_location);
     }
    location                     server::get_location(int i) const
    {
        return (this->_location[i]);
    }
    unsigned int                 server::get_location_size() const
    {
        return (this->_location.size());
    }
   unsigned int                 server::get_cgi_size() const
   {
    return (this->_cgi.size());
   }
    long long int                server::get_client_max_body_size() const
    {
        return(this->_client_max_body_size);
    }
    bool                         server::get_autoindex() const
    {
        return(this->_autoindex);
    }

    
   std::vector<cgi>             server::get_cgi() const
   {
    return(this->_cgi);
   }

   cgi                          server::get_cgi(int i) const
   {
    return (this->_cgi[i]);
   }







sockaddr_in                  server::get_sock_ader()
{
    sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(get_listen_host().c_str());
    sockaddr.sin_port = htons(get_listen_port());
    return sockaddr;
}