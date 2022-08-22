
#include "../Includes/tt.hpp"
#include "../Includes/server.hpp"
#include "../Includes/sboof/Response.hpp"
#include <vector>
#include <sstream>



bool isnumber(const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		char current = str[i];
		if (current >= '0' && current <= '9')
			continue;
		return false;
	}
	return true;
}
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
 * STILL BUG , ACCEPTS MULTIPLE SERVER_NAMES  SENSIBLE A LA CASSE SPACE DE FOU
 * 
 */
std::string removespace(std::string s)
{
    //traversing the string
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            //using in-built function to erase element
            s.erase(s.begin() + i);
            i--;
        }
    }
    return (s);
}
std::vector<std::string > extract_server_names(std::vector<std::string> text_vector,int index)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string> correct_names;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
        // if (index == 2)
        // std::cout << "=> " << text_vector[i].size()  << " " << text_vector[i] << " " << std::endl;
        if(text_vector[i].compare("server") == 0)
     {
                //std::cerr << "E*********************************** !" << std::endl;
           count++;
    }
        if ( count == index)
        {
              //  std::cerr << "E------------------------------------- !" << std::endl;

        parser = ft_split(text_vector[i]," ");
        y = 0;
        while (y < parser.size())
        {
            parser[y] = removespace(parser[y]);
       // std::cout << " WW SALUT KEIP" << count << text_vector[i] << " | " << parser[y]  << " " << y << std::endl;
        // if (parser[y].compare("server_names" )== 0)
        // std::cout << "WHY THE FUCK " << std::endl;
            if (parser[y] == "server_names")
            {
                
                if(index == 2)
                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many server_names in config files !" << std::endl;
                exit(1);
            }
            //std::cout << "HELLO HELLO HELLO " << std::endl;
                server_names = split (text_vector[i]," ",(char *)"server_names");
        // std::cout << "=> " << server_names.size()  << " " << server_names[1] << " " << std::endl;
        // std::cout << "=> " << server_names.size()  << " " << server_names[1] << " "  << std::endl;
        if(!server_names.empty() && server_names.size() > 1 )
        {
            server_names.erase(server_names.begin());
          return (server_names);
        }
        else 
        {
            std::cout << " Config file error :  No servernames found ! , IDX " << index << std::endl;
            exit(1);
        }
            }
            y++;
        }
        }
    i++;
    }
   
    return (correct_names);
}

int extract_server_port(std::vector<std::string> text_vector,int index)
{
 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = -1;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"listen");
        y = 0;
        while (y < parser.size())
        {
       // std::cout << "SIZE = " << parser.size() << std::endl;

            if (parser[y].compare("listen") == 0)
            {

                if (inside == 1)
             {
                std::cerr << "ERROR ! Too many Port in config files !" << std::endl;
            exit(1);
            }
             if( parser[y + 1].find(":") != std::string::npos)
             {
                 std::vector<std::string > port;
                 port = ft_split(parser[1],":");
               //std::cerr << "=>  !" <<  port.size()  << " " << parser[1] << "=>  " << port[1] << std::endl;

                if(!port[1].empty() && isnumber(port[1]))
                    num = std::stoi(port[1]);
                else
                {
                    std::cout << "Error ! Port not defined or is not a number !" << std::endl;
                    exit(1);
                }
                // // delimitier = parser[1].find(':');
                // // parser[1].erase(parser[1].begin(),parser[1].end() - delimitier + 3); 
                // if(port.size == 1)
                // {
                //     std::cout << "Something went Wrong in config file ! No port" << std::endl;
                //     exit(1);
                // }
               // ss << port[1];
            }
           inside = 1;
            }
            
            y++;
        }
        }
    i++;
    }
//ss >> num;
    return (num);
}



std::string extract_server_host(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> tmp;
std::string server_host;

    int i = 0;
    int y = 0;
    int inside = 0;
    int delimitier = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"listen");
        y = 0;
        while (y < parser.size())
        {

            if (parser[y].compare("listen") == 0)
            {

                  if (inside == 1)
             {
                std::cerr << "ERROR ! Too many host or port  in config files ! " << std::endl;
            exit(1);
            }
                //std::cout << "INSIDE HOST" << std::endl;
             if( parser[y + 1].find(":") != std::string::npos)
             {
                //s////td::cout << "INSIDE HOST" << std::endl;
                 std::vector<std::string > port;
                 port = ft_split(parser[1],":");
                 if (!port[0].empty())
                server_host = port[0];
              
             }
               else
                server_host = parser[y + 1];

        }
            y++;

        }
        }
    i++;
    }

    return (server_host);
}


std::string extract_server_root(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string > tmp;
 std::string root;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
             if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
                 if(text_vector[i].find("location") != std::string::npos)
                 {
                    return (root);
                 }
        parser = split(text_vector[i]," ",(char *)"");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("root") == 0)
            {   
                server_names = split (text_vector[i]," ",(char *)"root");
                tmp = server_names;
                tmp.erase(tmp.begin());
                if (tmp.size() > 0)
                {
                    root = tmp[0];
                    return (root);
                }
                else
                {
                    std::cout << "root is defined but nothing is put in it !  server : " << index << std::endl;
                    exit(1);
                }
               
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }
    return (root);

}

int    specified_methods(std::string &tmp)
{
    std::string err;
    err = "Error: ";
    err += tmp;
    err += " is not a valid word";
    if (tmp != "DELETE" && tmp != "POST" && tmp != "GET")
        {
            std::cout << "Method not allowed in config file !" << tmp  << std::endl;
            exit(1);    
        }
        return (0);
}

std::vector<std::string> extract_allowed_methods(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> allowed_methods;
 std::vector <std::string > correct_methods;
  std::vector <std::string> tmp;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        if(text_vector[i].find("location") != std::string::npos)
        return (correct_methods);
        parser = split(text_vector[i]," ",(char *)"allow_methods");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("allow_methods") == 0)
            {
                tmp.push_back(text_vector[i]);
            
                // if(!tmp[0].empty())  
                // tmp.erase(tmp.begin());
                allowed_methods = split_by_space(tmp);
                // allowed_methods.erase(allowed_methods.begin());
             
              correct_methods = allowed_methods;
                tmp.clear();
                // std::vector<std::string>::iterator pos = std::find(allowed_methods.begin(),allowed_methods.end(),"allow_methods");
                // if(pos != allowed_methods.end())
                correct_methods.erase(std::remove(correct_methods.begin(),correct_methods.end(),"allow_methods"));
                // correct_methods.assign(allowed_methods.begin() + 1,allowed_methods.end());
                if(correct_methods.empty())
                {
                    std::cout<< " Error ! Allowed methods is defined in server but no value is put in it !" << std::endl;
                    exit(1);
                }
                for(std::vector<std::string>::iterator it = correct_methods.begin();it != correct_methods.end();it++)
             {  
               
                   specified_methods(*it);
                }
                return(correct_methods);
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }

    return (correct_methods);
}


std::vector<std::string> extract_server_index(std::vector<std::string> text_vector,int index)
{
     std::vector<std::string> parser;
 std::vector <std::string> server_index;
  std::vector <std::string> correct_index;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        if(text_vector[i].find("location") != std::string::npos)
        return (correct_index);
        //  size_t found = text_vector[i].find("index.html");
        // // found = std::find(text_vector[i].begin(),text_vector[i].end(),"index.html") ;
        // if ( found != std::string::npos)
        // parser = split(text_vector[i]," ",(char *)"index.html");
        // else
        parser = split(text_vector[i]," ",(char *)"index");
        y = 0;
        while (y < parser.size())
        {
            int i = 0;
              for(std::vector<std::string>::iterator it = parser.begin();it != parser.end();it++)
                {
                    std::cout  << " i : " << i << " PARSER => " << *it << std::endl;
                    if(i > 0)
                    correct_index.push_back(*it);
                    i++;
                }
                std::cout << " CORRECT_INDEX SIZE : " << correct_index.size() << std::endl;
                return(correct_index);
                inside = 1;
            // }
            y++;
        }
        }
    i++;
    }
   
    return (correct_index);

}

std::string extract_server_upload_path(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
 std::vector <std::string> server_upload_path;
 std::vector<std::string> tmp;
 std::string upload_path;
    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
                 if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {
         if (inside == 1)
    return (server_upload_path.at(1));
        }
        parser = split(text_vector[i]," ",(char *)"upload_path");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("upload_path") == 0)
            {   
                server_upload_path = split (text_vector[i]," ",(char *)"upload_path");
                tmp = server_upload_path;
                tmp.erase(tmp.begin());
                if(tmp.size() > 0)
                upload_path = server_upload_path[1];
                else
                {
                    std::cout << "upload path defined but nothing is put in it !" << std::endl;
                    exit(1);
                }
                inside = 1;
            }
            y++;
        }
        }
    i++;
    }
    return (upload_path);
}

std::map <std::string,std::string > extract_server_errors_page1(std::vector<std::string > text_vector,int index,std::map<std::string,std::string > default_errors_page)
{
    int i = 0;
    int count = 0;
    std::map <std::string,std::string > errors_page;
    std::vector<std::string > parser;
    std::vector < std::string >test;
    errors_page = default_errors_page;
    int inside = 1;
    int y = 0;
       while ( i < text_vector.size())
    {  
            if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
       // if(text_vector[i].find("location") != std::string::npos)
        //return (correct_index);
        parser = split(text_vector[i]," ",(char *)"error_page");
        y = 0;
        while (y < parser.size())
        {
           // i++;
            if (parser[y].compare("error_page") == 0)
            {

                test = split (text_vector[i]," ",(char *)"error_page");

           //correct_index.assign(server_index.begin() + 1,server_index.end());
                // errors_pages.assign(test.begin() + 1,test.end())
                if (test.size()  == 3)
                {
                    errors_page[test[1]] = test[2];
                //    errors_page.insert(std::make_pair<std::string,std::string>({test[1],test[2]}));
                // std::cout << "erros_page:1 " << test[1] << " " <<  test[2] << std::endl;
            }
            else if ( test.size() < 3)
            {
                std::cout << " Config file : No Error code  or error link  ! !,IDX :" << index  << std::endl;
                exit(1);
            }
            else if (test.size() > 3)
            {
                std::cout << "Config file : Error too many links or errors code !, IDX :" << index << std::endl;
                exit(1);
            }
                
                inside = 1;
                // server_error_pages.push_back(errors_pages);
                test.clear();
            }
            y++;
        }
        }
    i++;
    }
    //correct_server_error_pages.assign(correct_server_error_pages.begin(),server_error_pages.begin() + 1,server_error_pages.end());
    //if(!server_error_pages.size())
  // server_error_pages.assign(server_error_pages.begin() + 1,server_error_pages.end());

    return (errors_page);
}
// }
// std::vector<std::vector<std::string > > extract_server_errors_page(std::vector<std::string> text_vector,int index)
// {
//      std::vector<std::string> parser;
//      std::vector <std::string> test;
//      std::vector <std::string > errors_pages;
//  std::vector <std::vector<std::string> > server_error_pages;
//  std::vector <std::vector<std::string> > correct_server_error_pages;

//     int i = 0;
//     int y = 0;
//     int inside = 0;
//     int count = 0;
//     while ( i < text_vector.size())
//     {  
//             if(text_vector[i].compare("server") == 0)
//      {
//            count++;
//     }
//         if ( count == index)
//         {
//        // if(text_vector[i].find("location") != std::string::npos)
//         //return (correct_index);
//         parser = split(text_vector[i]," ","error_page");
//         y = 0;
//         while (y < parser.size())
//         {
//            // i++;
//             if (parser[y].compare("error_page") == 0)
//             {

//                 test = split (text_vector[i]," ","error_page");
//            //correct_index.assign(server_index.begin() + 1,server_index.end());
//                 errors_pages.assign(test.begin() + 1,test.end());
                
//                 inside = 1;
//                 server_error_pages.push_back(errors_pages);
//                 test.clear();
//             }
//             y++;
//         }
//         }
//     i++;
//     }
//     //correct_server_error_pages.assign(correct_server_error_pages.begin(),server_error_pages.begin() + 1,server_error_pages.end());
//     //if(!server_error_pages.size())
//   // server_error_pages.assign(server_error_pages.begin() + 1,server_error_pages.end());

//     return (server_error_pages);
// }



std::map <std::string,std::string > extract_server_redirections1(std::vector<std::string > text_vector,int index)
{
    int i = 0;
    int count = 0;
    std::map <std::string,std::string > redirections;
    std::vector<std::string > parser;
    std::vector < std::string >test;

    int inside = 1;
    int y = 0;
       while ( i < text_vector.size())
    {  
            if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
       // if(text_vector[i].find("location") != std::string::npos)
        //return (correct_index);
        parser = split(text_vector[i]," ",(char *)"redirection");
        y = 0;
                // std::cout << "WWWWWWW__________WW__W_W_Wred/irection : "  << std::endl;
        while (y < parser.size())
        {
           // i++;
            if (parser[y].compare("redirection") == 0)
            {

                test = split (text_vector[i]," ",(char *)"redirection");


                if (test.size()  == 3)
                {
                    redirections[test[1]] = test[2];
                //    errors_page.insert(std::make_pair<std::string,std::string>({test[1],test[2]}));
                // std::cout << "redirection : " << test[1] << " " <<  test[2] << std::endl;
            }
            else if ( test.size() < 3)
            {
                std::cout << " Config file : No redirection   link  ! !,IDX :" << index  << std::endl;
                exit(1);
            }
            else if (test.size() > 3)
            {
                std::cout << "Config file :  too many  redirections links on code !, IDX :" << index << std::endl;
                exit(1);
            }
                // std::cout << "redirection : " << test[1] << " " <<  test[2] << std::endl;
                inside = 1;
                // server_error_pages.push_back(errors_pages);
                test.clear();
            }
            y++;
        }
        }
    i++;
    }
    //correct_server_error_pages.assign(correct_server_error_pages.begin(),server_error_pages.begin() + 1,server_error_pages.end());
    //if(!server_error_pages.size())
  // server_error_pages.assign(server_error_pages.begin() + 1,server_error_pages.end());

    return (redirections);
}

// std::vector<std::vector<std::string > > extract_server_redirections(std::vector<std::string> text_vector,int index)
// {
//      std::vector<std::string> parser;
//      std::vector <std::string> test;
//      std::vector <std::string > redirections;
//  std::vector <std::vector<std::string> > server_redirections;
//   std::vector <std::string> correct_server_redirections;
//     int i = 0;
//     int y = 0;
//     int inside = 0;
//     int count = 0;
//     while ( i < text_vector.size())
//     {  
//        // if(text_vector[i].find("location") != std::string::npos)
//         //return (correct_index);

//             if(text_vector[i].compare("server") == 0)
//      {
//            count++;
//     }
//         if ( count == index)
//         {
//         parser = split(text_vector[i]," ","(char *)redirection");
//         y = 0;
//         while (y < parser.size())
//         {
//             if (parser[y].compare("redirection") == 0)
//             {
//                 test = split (text_vector[i]," ",(char *)"redirection");
//                 redirections.assign(test.begin() + 1,test.end());
//            //correct_index.assign(server_index.begin() + 1,server_index.end());
//                 inside = 1;
//                 server_redirections.push_back(redirections);
//                 test.clear();
//             }
//             y++;
//         }
//         }
//     i++;
//     }
   
//     return (server_redirections);
// }

long long int extract_server_max_body_size(std::vector<std::string> text_vector,int index)
{

 std::vector<std::string> parser;
 std::vector <std::string> server_names;
 std::vector <std::string > tmp;
std::string test;
 std::stringstream ss;

 int delimitier = 0;
    int i = 0;
    int y = 0;
    int inside = 0;
    int num = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
        
         if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {

        return ( num);
        }
        parser = split(text_vector[i]," ",(char *)"client_max_body_size");
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("client_max_body_size") == 0)
            {
                tmp = parser;
                tmp.erase(tmp.begin());
             if(tmp.size() > 0)
            {
                if(isnumber(tmp[0]))
                {
                    num = std::stoi(tmp[0]);
                return(num);
                }
                else
                {
                    std::cout << " Error ! A char is present in client_max_body_size" << std::endl;
                    exit(1);
                }
            }
            else if(tmp.size() == 0)
            {
                std::cout << "client_max_body_size is defined but no value is put in it ! server index : " << index << std::endl; 
                exit(1);
                num = -1;
            }
      


            //     if (!parser[1].empty() &&  isnumber(parser[1]))
            //    {
            //     std::cout << "hh" << std::endl;

            //    }
            //    else
            //    std::cout << "WWWWWWWWWWWWWW C VIDE  EXTRACT SERVER BODY SIZE"<< std::endl;

                
            }
            y++;
        }
        }
    i++;
    }

if (inside == 0)
num = -1;
//std::cout << "EXITING HERE AT RETURN-------------=>>>>>>>>>>>>>>>" << index  << std::endl;
    return (num);
}

bool extract_server_autoindex(std::vector<std::string > text_vector,int index)
{

 std::vector<std::string> parser;

    int i = 0;
    int y = 0;
    int inside = 0;
    bool autoindex = false;
    std::vector<std::string> tmp;
    int count = 0;
    while ( i < text_vector.size())
    {  
                 if(text_vector[i].compare("server") == 0)
     {
           count++;
    }
        if ( count == index)
        {
        parser = split(text_vector[i]," ",(char *)"autoindex");
        if(text_vector[i].find("location") != std::string::npos)
            inside = 1 ;
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("autoindex") == 0)
            {
                if ( inside == 0)
            {
                tmp = parser;
                tmp.erase(tmp.begin());
    //std::cout << "TMP SIZE" << tmp.size()  <<"index : " << index << std::endl;
             if(tmp.size() > 0)
             {
               if(tmp[0].compare("on") == 0)
               autoindex = true;
               else if (tmp[0].compare("off") == 0)
               autoindex = false;
               else
               {
                std::cout << "Error ! autoindex can only take on or off as values  not " << tmp[0] << std::endl;
                exit(1); 
               }
             }
            else if(tmp.size() == 0)
            {
                std::cout << "autoindex is defined but no value is put in it ! server index : " << index << std::endl;
                exit(1);
            }
            }
            }
            y++;
        }
        }
    i++;
    
        }
    return (autoindex);
  
    }



int extract_number_of_locations(std::vector <std::string> text_vector,int index)
{

    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int find_right_server = 0;
    bool autoindex = false;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if (find_right_server == index)
        {
    if(text_vector[i].find("location") != std::string::npos)
            count++;
    }
        i++;

}
// std::cout << "Number of locations  :" << count << " Server Index : " << index << std::endl;
    return (count);
}
void check_cgi(std::string tmp)
{
    int i = 0;
    while (tmp[i])
    {
    if (tmp[0] != '.')
        break;
        if(tmp[0] == '.')
        {
            if(tmp[1] == 'p' && tmp[2] == 'y' && tmp[3] == '\0')
                return ;
            else if (tmp[1] == 'p' && tmp[2] == 'h' && tmp[3] == 'p' && tmp[i + 4] == '\0')
            return ;
        }
    i++;
    }
    if(!tmp.empty())
    std::cout << " Error ! cgi extension "  << std::endl;
    exit(1);
}
// TO FIXE ERRORS CASE : if no path is specified
std::vector<cgi> extract_server_cgi(std::vector<std::string > text_vector,int index)
{
    std::vector<cgi> vector_cgi;
    std::vector<cgi> tt;

    cgi tmp;
    std::vector<std::string > parser;
    std::vector<std::string > cgi_path;
    std::vector<std::string> cgi_name;

    int i = 0;
    int count = 0;
    int vector_size = 0;
    int accolade = 0;
    int find_right_server = 0;
    int inside = 0;
    int path = 0;
    int name = 0;
    while ( i < text_vector.size())
    {  
        
           if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if (find_right_server == index)
        {
            parser = split(text_vector[i]," ",(char *)"cgi");
            if (parser.size() > 0 )
            inside = 1;
            if ( inside == 1)
            {
                // parser[1] = removespace(parser[1]);
            //     if(!parser[1].empty())
            //    {
                    check_cgi(parser[1]);
                     tmp.set_cgi_name(parser[1]);
                     name = 1;
            //    }

                // while ( i < text_vector.size())
                // {
                    cgi_path = split(text_vector[i]," ",(char *)"cgi_path");
                //     if()
                // {
                    if(cgi_path.size() == 2)
                   {
                    tmp.set_cgi_path(cgi_path[1]);
                     path = 1;
                  }
                  else if (cgi_path.size() == 1)
                  {
                    std::cout << " Error ! Cgi_Path defined but nothing  is put in it !" << std::endl;
                    exit(1);
                  }
                  else if (cgi_path.size() > 2)
                  {
                         std::cout << " Error ! Cgi_Path  Too many path in config file  !" << std::endl;
                    exit(1);
                  }

                //     cgi_name = split(text_vector[i]," ",(char *)"cgi_name");
                //     if(cgi_name.size() ==  2)
                //    {
                    
                //     name = 1;
                //     }
                //     else if (cgi_name.size() == 1)
                //     {
                //             std::cout << " Error ! Cgi_name defined but nothing  is put in it !" << std::endl;
                //     exit(1);
                //     }
                //     else if (cgi_name.size() > 2)
                //     {
                //                std::cout << " Error ! Too many cgi names defined in Config file !" << std::endl;
                //     exit(1);
                //     }
                    if (path == 1 && name == 1)
                    {
                        vector_cgi.push_back(tmp);
                        //  std::cout << "tmp => " << tmp.get_cgi_name() << std::endl;
                        // std::cout << "tmp => " << tmp.get_cgi_path() << std::endl;
                        // parser.clear();
                        cgi_name.clear();
                        cgi_path.clear();
                        path = 0;
                        name = 0;
                    }
                    
                // }
            }
         


        }
        i++;

    }
    return(vector_cgi);
}