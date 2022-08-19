#include "../Includes/request.hpp"
#include "../Includes/tt.hpp"
#include <map>
Request::Request():
            rqmethod(),
            location(),
            vrs(),
            headers(),
            body(),
            body_len(-1)
{

}

Request::Request(Request const &copy)
{
     *this = copy;
}
Request& Request::operator=(Request const &copy)
{

  if (this != &copy)
    {
        rqmethod = copy.rqmethod;
        location = copy.location;
        vrs = copy.vrs;
        headers = copy.headers;
        body = copy.body;
        body_len = copy.body_len;
    }

    return *this;
}
Request::Request(std::vector<std::string > full_request)
{
    int method = 0;
    method = get_request_method(full_request);
    if (method == 1)
    this->rqmethod = "GET";
    if(method == 2)
    this->rqmethod = "POST";
    if (method == 3)
    this->rqmethod = "DELETE";
    this->location = get_request_location(full_request);// HERE ERROR , if no location is sent , takes HTTP as location to fix
    if(this->location == "/favicon.ico")
    {
        std::cout << " location is " << this->location << " ignoring ... this line will be removed" << std::endl;
        return ;
    }
    std::cout << "------------------REQUEST FIRSDT LINE ---------------------" << std::endl;
    std::cout << full_request[0] << std::endl;
    std::cout << "Request method => " << this->rqmethod << std::endl;
    //std::cout << "---------------------------------------" << std::endl;
    std::cout << "Request Location=> " << this->location << std::endl;
    
    std::cout << "---------------------------------------" << std::endl;
    this->vrs = get_request_vrs(full_request[0]);
    std::cout << "Request vrs=> " << this->vrs << "|"<< std::endl;
    std::cout << "---------------------------------------" << std::endl;
    this->headers = get_request_headers(full_request);
    std::cout << "HEADERS      "  << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Number of Headers : " <<  headers.size() << std::endl;

    for(std::map<std::string ,std::string > ::iterator it = this->headers.begin();it != this->headers.end();it++)
   {
       std::cout << it->first << ":" <<  it->second  << std::endl;
    }
    std::cout << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    this->body = get_request_body(full_request);
    std::cout << "Request body => " << this->body << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    this->query = get_request_query(full_request);
    std::cout << "Request qwuery => " << this->query << std::endl;
    this->body_len = this->body.size();
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Request body_len => " << this->body_len << std::endl;

}
Request::~Request()
{

}

//*************************************** GETTERS FUNCTIONS*************************************** 

std::string Request::get_method()
{
    // std::cout << "INSIDE  GETTER FCT => "  << this->rqmethod << std::endl;
    return (this->rqmethod);
}

std::string Request::get_location()
{
    return(this->location);
}

std::string Request::get_version()
{
    return(this->vrs);
}

std::map <std::string,std::string >Request::get_headrs()
{
    return(this->headers);
}
std::string&    Request::get_body()
{
    return(this->body);
}
int Request::get_body_len()
{
    return(this->body_len);
}
std::string&    Request::get_query()
{
    return(this->query);
}