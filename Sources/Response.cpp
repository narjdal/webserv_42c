/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:23:20 by amaach            #+#    #+#             */
/*   Updated: 2022/08/14 15:32:20 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"



//********************************************OUTILS*********************************************//

std::vector<std::string>     ft_split(std::string s1, std::string delim)
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

int     return_loc(std::vector<string> vec1, std::vector<string> vec2)
{
    std::vector<string>::iterator it2 = vec2.begin();
    int     compt = 0;

    for(std::vector<string>::iterator it = vec1.begin(); it != vec1.end(); it++)
    {
        if (it2 != vec2.end())
        {
            if (*it == *it2)
                compt++;
            else
                return (compt);
        }
        else
            return (0);
        it2++;
    }

    return (compt);
}

std::string     skip_slash( std::string str)
{
    std::vector<std::string> vector = ft_split(str, "/");
    std::string tmp;

    for(std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
        tmp += *it;
    return (tmp);
}

std::string     extension(std::string str)
{
    std::vector<std::string>  vector;

    vector = ft_split(str, ".");
    
    return (vector.back());
}

std::string     file_to_string(std::string location)
{
    std::string buffer;

    std::ifstream fin(location.c_str());
    getline(fin, buffer, char(-1));
    fin.close();
    //std::cout << "BUFFER => " << buffer << std::endl;
      return buffer;
}

void     Response::errorsPages( int Status_Code)
{
    std::string tmp = "./sboof/errorpages/" + to_string(Status_Code) + "/" + to_string(Status_Code) + ".html";
    this->_header->setHeader("Content-Type", (extension(tmp)));
    this->_Body = file_to_string(tmp);
    this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
}

std::string RandomWord( void )
{
    std::string StrWord;
    int len = rand () % 10 + 1;

    for (int i = 0; i < len; i++)
        StrWord.push_back('a' + (rand () % 26));

    return StrWord;
}

//***************************************MEMBER FUNCTIONS***************************************//

Response::Response(Request &request, server &Serv)
{
    this->_header = new Header(Serv, request);
    this->_request = request;
    this->_Serv = Serv;
    this->_Body = "";
    this->_location = "";
    this->_is_chanked = false;
    this->_location_index = -404;
    this->_location_type = -404;
}

Response::~Response()
{
    delete this->_header;
}

bool    Response::check_path()
{
    struct stat s;

    if (this->_request.get_method() == "POST")
        return (true);
    if( stat(this->_location.c_str(), &s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
            this->_location_type = 2;
        else if( s.st_mode & S_IFREG )
        {
            this->_location_type = 1;
            if (s.st_size > MAX_BUFFER)
                this->_is_chanked = true;
        }
        else
        {
            this->_location_type = 0;
            return (false);
        }
        return (true);
    }
    return (false);
}

bool    Response::check_location()
{
    int pos = 0;
    std::string loc;
    std::vector<std::string> help = ft_split(this->_request.get_location(), "/");
    std::vector<location> tmp = this->_Serv.get_location();
    int tmp1 = 0;

    for (std::vector<location>::iterator  it = tmp.begin(); it != tmp.end(); it++)
    {
        int tmp = return_loc(help, ft_split(it->get_locations_path(), "/"));
        if (pos < tmp)
        {
            pos = tmp;
            loc = it->get_root();
            loc = skip_slash(loc);
            this->_location_index = tmp1;
        }
        tmp1++;
    }
    if (pos == 0)
    {
        loc = this->_Serv.get_root();
        this->_location_index = -1;
    }
    for (std::vector<std::string>::iterator it = help.begin() + pos; it != help.end(); it++)
        loc += *it;
    this->_location = loc;
    this->_location = skip_slash(this->_location);

    return (check_path());
}

//**********************************************GET**********************************************//

std::string     autoindex_generator( std::string path, std::string req_loc)
{
    std::string str;
    DIR *dr;
    struct dirent *e;

    dr = opendir(path.c_str());
    str = "<html>\n<head>\n<body>\n<table>\n";

        while((e = readdir(dr)) != false)
        {
            if(e->d_name != std::string(".") && e->d_name != std::string(".."))
            {
                str += std::string("<br>") ;
                str += std::string("<a href=\"") + req_loc  + e->d_name + std::string("\">")+ e->d_name + string("</a>");    
            }
        }   
    str += "</table>\n</body>\n</head>\n</html>\n";
    closedir(dr);

   return (str);
}

int     Response::handle_GET_autoindex( void )
{
    bool tmp;

    if (this->_location_index == -1)
        tmp = this->_Serv.get_autoindex();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_autoindex();
    if (tmp)
    {
        this->_header->setHeader("Content-Type", "Text/html");
        this->_Body = autoindex_generator(this->_location, this->_request.get_location());
        this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
        return (200);
    }
    else
        return (403);
}

std::string    handle_index( std::vector<std::string> vector, std::string root)
{
    std::string     tmp;

    for(std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
    {
        tmp = root + *it;
        if (open(tmp.c_str(), O_RDONLY) != -1)
            return (tmp);
    }
    return (NULL);
}

int     Response::file_GET( void )
{
    std::string     tmp;
    std::cout << "I M IN FILE  GET  AND :   " << this->_location_type << std::endl;
    if (this->_location_type == 1)
        tmp = this->_location;
    else if (this->_location_type == 2)
        tmp = handle_index(this->_Serv.get_index(), this->_location);
    std::cout << "loc:   =>" << tmp << "|" << std::endl;
    this->_header->setHeader("Content-Type", (extension(tmp)));
    this->_Body = file_to_string(tmp);
    this->_header->setHeader("Content-Length", to_string(this->_Body.size()));
    std::cout << "INSIDE FILE GET body: => " <<  this->_Body << std::endl;
    return (200);
}

int     Response::cgi_GET( void )
{
    if (this->_Serv.get_cgi().size() > 0)
    {
        std::cout << " I M IN CGI" << std::endl;
        // CGI FUNCTION
        return (200);
    }
    else
        return (file_GET());
}

int     Response::handle_GET_Dir( void )
{
    std::vector<std::string> tmp;

    std::cout << "I M IN HANDLE GET DIR : AND  loca index is :  " << this->_location_index << std::endl;
    if (this->_location_index == -1)
        tmp = this->_Serv.get_index();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_index();
    if (tmp.size() > 0)
        return (cgi_GET());
    else
        return (handle_GET_autoindex());

}

int     Response::check_GET( void )
{
    std::cout << "I M IN CHECK GET and : " << this->_location_type << std::endl;
    if (this->_location_type == 1)
        return (cgi_GET());
    else
    {
        if (this->_location[this->_location.size() - 1] != '/')
        {
            this->_header->setHeader("Location", this->_location + "/");
            return (301);
        }
        else
            return (handle_GET_Dir());
    }
}

//**********************************************POST**********************************************//

int     Response::cgi_POST( void )
{
    if (this->_Serv.get_cgi().size() > 0)
    {
        std::cout << " I M IN CGI" << std::endl;
        // CGI FUNCTION
        return (200);
    }
    else
        return (403);
}

int     Response::handle_POST_Dir( void )
{
    bool tmp;

    tmp = (this->_location_index == -1) ? this->_Serv.get_autoindex() : this->_Serv.get_location(this->_location_index).get_autoindex();
    if (tmp)
        return (cgi_POST());
    else
        return (403);
}

int     Response::check_POST( void )
{
    if (this->_location_type == 1)
        return (cgi_POST());
    else
    {
        if (this->_location[this->_location.size() - 1] != '/')
        {
            this->_header->setHeader("Location", this->_location + "/");
            return (301);
        }
        else
            return (handle_POST_Dir());
    }
}

int     Response::Upload_file( std::string upload_path )
{
    std::cout << "THE TYPE IS " << this->_request.get_headrs()["Content-Type"] << std::endl;
    std::string tmp = StatusCode(this->_request.get_headrs()["Content-Type"], 2);
    std::cout << "HIS EXTENSION IS " << tmp << std::endl;

    tmp.clear();
    tmp = upload_path + RandomWord() + "." + StatusCode(this->_request.get_headrs()["Content-Type"], 2);
    std::cout << "the hole file is " << tmp << std::endl;
    
    ofstream    FILE(tmp);

    FILE << this->_request.get_body();

    FILE.close();
    return (201);
}

int     Response::check_POST_upload( void )
{
    std::string tmp;

    tmp = (this->_location_index == -1) ? this->_Serv.get_upload_path() : this->_Serv.get_location(this->_location_index).get_upload_path();
    if (tmp.size())
        return (Upload_file(tmp));
    else
        return (check_POST());
}

//*********************************************DELETE*********************************************//

int     Response::file_DELETE( void )
{
    std::string tmp = "rm " + this->_location;
    if (system(tmp.c_str()))
    {
        std::cout << " IM IN A ZBI" << std::endl;
        return (500);
    }
    return (204);
}

int     Response::cgi_DELETE( void )
{
    if (this->_Serv.get_cgi().size() > 0)
    {
        std::cout << " I M IN CGI" << std::endl;
        // CGI FUNCTION
        return (204);
    }
    else
        return (file_DELETE());
}

int     Response::DELETE_all_Folder( void )
{
    std::string tmp = "rm -rf " + this->_location;
    if (system(tmp.c_str()))
        return (403);
    return (204);
}

int     Response::handle_DELETE_Dir( void )
{
    if (this->_Serv.get_cgi().size() > 0)
    {
        std::vector<std::string> tmp;

        if (this->_location_index == -1)
            tmp = this->_Serv.get_index();
        else
            tmp = this->_Serv.get_location(this->_location_index).get_index();
        if (tmp.size() > 0)
            return (204); // CGI FUNCTION
        else
            return (403);
    }
    else
        return (DELETE_all_Folder());
}

int     Response::check_DELETE( void )
{
    std::cout << "I M IN !!! and : " << this->_location_type << std::endl;
    if (this->_location_type == 1) // file
        return (cgi_DELETE());
    else if (this->_location_type == 2) // directory
    {
            std::cout << "I M IN" << std::endl;
        if (this->_location[this->_location.size() - 1] != '/')
            return (409);
        else
            return (handle_DELETE_Dir());
    }
    return (404);
}

//************************************************************************************************//

int    Response::check_methods( void )
{
    std::string             methods[3] = {"GET", "POST", "DELETE"};
    int                     (Response::*funct[3])( void ) = {&Response::check_GET, &Response::check_POST_upload, &Response::check_DELETE};
    std::vector<string>     tmp;

    if (this->_location_index == -1)
        tmp = this->_Serv.get_allowed_methods();
    else
        tmp = this->_Serv.get_location(this->_location_index).get_methods();
    for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); it++)
    {
        if ( this->_request.get_method() == *it )
        {
            for (int i = 0; i < 3; i++)
            {
                std::cout << "inside check methods" << std::endl;
                if (this->_request.get_method() == methods[i])
                    return ((this->*funct[i])());
            }
        }
    }

    return (405);
}

int    Response::statuscode( void )
{
    if (this->_request.body_len == -1)
        return (400);
    else if (!check_location())
        return (404);
    else
        return (check_methods());
}

std::string Response::get_Response( Request rq )
{
    FirstLine   FirstLine(this->_request);

    this->_Body = "<html><body><h1>SBOOF</h1></body></html>";
    this->_header->setHeader("Content-Length", std::to_string(this->_Body.size()));
    this->_header->setHeader("Content-Type", "text/html");

    int i = statuscode();
    std::cout << "ytyyy status code = " << i << std::endl;
    //errorsPages(i);
    //TO FIXE HEADERS;
    std::string rep;
    rep = FirstLine.First_Line(i) + this->_header->getHeader() + this->_Body;
    std::cout << "get_Response :final body b4 return : " << this->_Body << std::endl;
    return (rep);
}
