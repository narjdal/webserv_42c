#include "../Includes/location.hpp"
#include "../Includes/tt.hpp"
#include <sstream>
location::location()
{

}

location::~location()
{

}

location::location(const location &obj)
{
    if (this != &obj)
    {
        *this = obj;
    }
}


location    &location::operator=(location const &rhs)
{
    this->_locations_path = rhs._locations_path;
    this->_allow_methods = rhs._allow_methods;
    this->_root = rhs._root;
    this->_autoindex = rhs._autoindex;
    this->_client_max_body_size = rhs._client_max_body_size;
    this->_index = rhs._index;
    this->_upload_path = rhs._upload_path;
    return *this;
}

std::string extract_location_name(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::string name;
    int i = 0;
    int y = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
             parser = split(text_vector[i]," ","upload_path");
                }
        }
    i++;
    }

        /**
         * @brief 
         * 
         *
        }
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
    return (server_upload_path[1]);*/
    return (name);
}



std::string extract_location_path(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::string location_path;
    int i = 0;
    int y = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
             parser = split(text_vector[i]," ","location");
            return (parser[1]);
            }
        count++;
        }
    i++;
    }
    return (location_path);
}

std::vector<std::string> extract_location_allowed_methods(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::vector<std::string> allowed_methods;
std::vector <std::string > correct_methods;
    int i = 0;
    int y = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
             parser = split(text_vector[y]," ","allow_methods");
                if (!parser.empty())
                {
                    correct_methods.assign(parser.begin() + 1,parser.end());
                    break;
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }
    return (correct_methods);
}
std::string extract_location_root(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::string location_path;
    int i = 0;
    int y = 0;
    int count = 0;
   while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
             parser = split(text_vector[y]," ","root");
                if (!parser.empty())
                {
                    return (parser[1]);
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }
  //  std::cerr << " No root found in location !" << std::endl;
    return (location_path);
}

long long int extract_location_max_body_size(std::vector<std::string> text_vector,int index)
{

std::vector<std::string> parser;
std::vector<std::string> location_limit;
std::string location_path;
 std::stringstream ss;
    int i = 0;
    int y = 0;
    int count = 0;
    int num = 0;
    int inside = 0;
   while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
       
             parser = split(text_vector[y]," ","client_max_body_size");
             if ( y != i)
              {
                location_limit = split(text_vector[y]," ","location");
               if(location_limit.size() > 0 && location_limit[0].compare("location") == 0)
                break;
                    }
             inside = 1;
                if (!parser.empty())
                {
                ss << parser[1];
                ss >> num;
                    return (num);
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }
    //std::cerr << " No client_max_body_size  !" << std::endl;
    return (num);
}
std::vector<std::string> extract_location_index(std::vector<std::string> text_vector,int index)
{

  std::vector<std::string> parser;
  std::vector <std::string> server_index;
  std::vector <std::string> correct_index;
std::vector<std::string> location_limit;

    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;

   while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
            if ( y != i)
              {
                location_limit = split(text_vector[y]," ","location");
               if(location_limit.size() > 0 && location_limit[0].compare("location") == 0)
                break;
                    }
             parser = split(text_vector[y]," ","index");
                if (!parser.empty())
                {
                    correct_index.assign(parser.begin() + 1,parser.end());
                    return (correct_index);
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }
   // std::cout << " No Index in location !" << std::endl;
    return (server_index);
}
bool extract_location_autoindex(std::vector<std::string > text_vector,int index)
{

 std::vector<std::string> parser;
    int i = 0;
    int y = 0;
    int inside = 0;
    bool autoindex = false;
    int count = 0;
std::vector<std::string> location_limit;
   while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
            if ( y != i)
              {
                location_limit = split(text_vector[y]," ","location");
               if(location_limit.size() > 0 && location_limit[0].compare("location") == 0)
                break;
                    }
             parser = split(text_vector[y]," ","autoindex");
                if (!parser.empty() && parser[1].compare("on") == 0)
                {
                    return (true);
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }

    return (false);
}

std::string extract_location_upload_path(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::string location_path;
std::vector<std::string> location_limit;
    int i = 0;
    int y = 0;
    int count = 0;
   while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size())
                    {
                 if ( y != i)
              {
                location_limit = split(text_vector[y]," ","location");
               if(location_limit.size() > 0 && location_limit[0].compare("location") == 0)
                break;
                    }
             parser = split(text_vector[y]," ","upload_path");
                if (!parser.empty())
                {
                    return (parser[1]);
                }
            y++;
            }
                }
        count++;
        }
    i++;
    }
    //std::cerr << " No upload_path found in location !" << std::endl;
    return (location_path);
}

location::location(std::vector<std::string> text_vector,int index)
{
    this->_name = extract_location_path(text_vector,index);
    this->_locations_path = extract_location_path(text_vector,index);
    this->_allow_methods = extract_location_allowed_methods(text_vector,index);
    this->_root = extract_location_root(text_vector,index);
    this->_client_max_body_size = extract_location_max_body_size(text_vector,index);
    this->_index = extract_location_index(text_vector,index);
    this->_autoindex = extract_location_autoindex(text_vector,index);
    this->_upload_path = extract_location_upload_path(text_vector,index);

   // std::cout << this->_locations_path << std::endl;
      // std::cout << "-----------------------Location index  | Index :  " << index << " <<  ------------------"  << std::endl;
   //  for (std::vector<std::string>::iterator it2 = this->_index.begin();it2 != this->_index.end();it2++)
     //    std::cout << *it2 << std::endl;
   //std::cout << "-----------------------Location PATH  | Index :  " << index << " <<  ------------------"  << std::endl;
   /**
  * @brief 
  * 
  *
    std::cout << this->_locations_path << std::endl;
   std::cout << "-----------------------Location allowed moethods | Index :  " << index << " <<  ------------------"  << std::endl;
     for (std::vector<std::string>::iterator it1 = this->_allow_methods.begin();it1 != this->_allow_methods.end();it1++)
         std::cout << *it1 << std::endl;
     std::cout << "-----------------------Location Root | Index :  " << index << " <<  ------------------"  << std::endl;
    std::cout << this->_root << std::endl;
         std::cout << "-----------------------Location Max Body Size | Index :  " << index << " <<  ------------------"  << std::endl;
    std::cout << this->_client_max_body_size << std::endl;
     std::cout << "-----------------------Location index  | Index :  " << index << " <<  ------------------"  << std::endl;
     for (std::vector<std::string>::iterator it2 = this->_index.begin();it2 != this->_index.end();it2++)
         std::cout << *it2 << std::endl;
        std::cout << "-----------------------Server  AutoIndex    : ------------------"  << std::endl;
        if (this->_autoindex == true)
        std::cout << "autoindex on " << std::endl;
        else if (this->_autoindex == false)
        std::cout << "autoindex off " << std::endl;
   std::cout << "-----------------------Location _upload_path | Index :  " << index << " <<  ------------------"  << std::endl;
    std::cout << this->_upload_path << std::endl;
      
*/
         
}


std::string location::get_upload_path() const
{
    return (this->_upload_path);
}

std::string location::get_name() const
{
    return (this->_name);
}

std::string location::get_locations_path() const
{
    return (this->_locations_path);
}

std::vector<std::string> location::get_methods() const
{
    return (this->_allow_methods);
}

unsigned int location::get_methods_size() const
{
    return (this->_allow_methods.size());
}
std::string location::get_root() const
{
    return (this->_root);
}
    bool                        location::get_autoindex() const
    {
        return (this->_autoindex);
    }

    long long int               location::get_client_max_body_size() const
    {
        return (this->_client_max_body_size);
    }

    unsigned int                location::get_index_size() const
    {
        return (this->_index.size());
    }
    std::vector<std::string>    location::get_index() const
    {
        return(this->_index);   
    }
