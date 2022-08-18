#include "../Includes/tt.hpp"
#include <string.h> //getline
#include <fstream>
#include <sstream>
#include "../Includes/server.hpp"
#include "../Includes/location.hpp"
#include "../Includes/sboof/Response.hpp"
#include "../Includes/request.hpp"
#include <vector>
#include <iterator>
#include <errno.h>
/**
 * @brief 
 * 
 * @param ac 
 * @param av 
 * @return int 
 * as defined in the POSIX standard for communication between processes on the same host.
 *  For communicating between processes on different hosts connected by IPV4, 
 * we use AF_INET and AF_I NET 6 for processes connected by IPV6.
 * sockfd: socket descriptor, an integer (like a file-handle)
domain: integer, specifies communication domain. We use AF_ LOCAL as defined in the POSIX standard for communication between processes on the same host. 
For communicating between processes on different hosts connected by IPV4, we use AF_INET and AF_I NET 6 for processes connected by IPV6.
type: communication type
SOCK_STREAM: TCP(reliable, connection oriented)
SOCK_DGRAM: UDP(unreliable, connectionless)
protocol: Protocol value for Internet Protocol(IP), which is 0. s the same number which appears on protocol field in the IP header of a packet
.(man protocols for more details)
 */





/**
 * @brief 
 * 
 * @param ac 
 * @param av 
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

After creation of the socket, bind function binds the socket to the address and port number specified in addr(custom data structure). In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.

int listen(int sockfd, int backlog);

It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection. 
The backlog, defines the maximum length to which the queue of pending connections for sockfd may grow. If a connection request arrives when the queue is full
, the client may receive an error with an indication of ECONNREFUSED.
 * @return int 
 int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. At oint, connection is established between client and server, and they are ready to transfer data.


 */
#define PORT 8080

void test_leaks()
{
    system("leaks webserv");
}

char *get_first_line(char *buffer)
{
    int i = 0;
    char *str = NULL;
    str =  (char * )malloc(sizeof(char ) * strlen(buffer) + 1);
    while (buffer[i] && buffer[i] != '\n')
    {
        str[i] = buffer[i];
        i++;

    }
    str[i] = '\0';
    return (str);
}
std::string get_data(std::string line)
{

    std::fstream my_file;
    std::stringstream buffer;
    line.insert(0,"./Files");// un . est necessaire pour trouver le file 
   // std::cout <<"|"<<line<<"|" << std::endl;
    my_file.open(line,std::ios::in);
    	if (!my_file) {
		std::cout << "File not Found !" << std::endl;
       
	}
	else {
		buffer << my_file.rdbuf();
	//	std::cout << "File Found = > " << buffer.str() << std::endl;

}
return (buffer.str());
}
std::string get_file(char *first_line)
{
    std::string line(first_line);
    std::string delim = " ";
    std::string correct_line;
    size_t pos = 0;
    int i = 0;
    std::string token;
    while ((pos = line.find(delim) ) != std::string::npos)
    {
        token = line.substr(0,pos);
        if (i == 1)
        {
            correct_line = token;
        }
        line.erase(0,pos + delim.length());
        i++;
    }
    return (correct_line);
}
int look_file(std::string line)
{
    std::fstream my_file;
    line.insert(0,"./Files");// un . est necessaire pour trouver le file 
   // std::cout <<"|"<<line<<"|" << std::endl;
    my_file.open(line,std::ios::in);
    	if (!my_file) {
		std::cout << "File not Found !" << std::endl;
        return (2);
	}
	else {
		//std::cout << "File Found !" << std::endl;
        return (1);
}
return (0);
}

std::string get_server_reponse(char *buffer)
{
      
    char *first_line = NULL;
            std::string server_reponse = "HTTP/1.1 ";
      first_line = get_first_line(buffer);
        std::string test(first_line);
        std::string data_file;
      //  std::cout << test << std::endl;
        std::string line_one;
        line_one = get_file(first_line);// get file in line one 
        if (look_file(line_one) == 1)
        {
           std::stringstream converter;
            int length = 0;
            data_file = get_data(line_one);
            length = data_file.length();
            converter << length;
            std::string file_length = converter.str();
            server_reponse.insert(server_reponse.size(),"200 OK\nContent-Type: text/plain\nContent-Length: ");
           server_reponse.insert(server_reponse.size(),file_length);
            server_reponse.insert(server_reponse.size(),"\n\n");
            server_reponse.insert(server_reponse.size(),data_file);
        } else  if (look_file(line_one) == 2)
        {
            server_reponse.insert(server_reponse.size() ,"404 Not Found\nContent-Type: text/plain\nContent-Length: 19\n\n 404 Not found !");
        }
        //std::cout << "=> " << server_reponse << std::endl;
return (server_reponse);
}
std::string get_content_type(std::vector<std::string> full_request)
{
    int i = 0;
std::vector<std::string> content_type;
std::string tt;
    while ( i < full_request.size())
    {
        if (full_request[i].find("Content-Type:") == 0)
            content_type = split(full_request[i]," ","Content-Type:");
        i++;
    }

 //  std::cout << "content_type => " << content_type[1] << std::endl;
    if(content_type.size() > 0)
    return (content_type[1]);
    else
    return (tt);
}

std::string get_server_reponse_post(char *buffer,std::vector<std::string> full_request)
{
      
     char *first_line = NULL;
        std::string server_reponse = "HTTP/1.1 ";
      first_line = get_first_line(buffer);
      std::string content_type;
        std::string test(first_line);
        std::string data_file;
        std::cout << test << std::endl;
        std::string line_one;
        line_one = get_file(first_line);// get file in line one 
        if (look_file(line_one) == 1)
        {
           std::stringstream converter;
            int length = 0;
            data_file = get_data(line_one);
            length = data_file.length();
            converter << length;
            std::string file_length = converter.str();
            content_type = get_content_type(full_request);
            server_reponse.insert(server_reponse.size(),"200 OK\nContent-Type: ");
            server_reponse.insert(server_reponse.size(),content_type);
            server_reponse.insert(server_reponse.size(),"Content-Length: ");
           server_reponse.insert(server_reponse.size(),file_length);
            server_reponse.insert(server_reponse.size(),"\n\n");
            server_reponse.insert(server_reponse.size(),data_file);
        } else  if (look_file(line_one) == 2)
        {
            content_type = get_content_type(full_request);
              server_reponse.insert(server_reponse.size(),"404 Not Found\nContent-Type: ");
            server_reponse.insert(server_reponse.size(),content_type);
            server_reponse.insert(server_reponse.size(),"Content-Length: 0");
            server_reponse.insert(server_reponse.size(),"\n\n");
        }
      //  std::cout << "=> " << server_reponse << std::endl;
return (server_reponse);
}

int check_url_length(std::string first_line,int method)
{
    int i = 0;

    if (method == 1)
    {
        if (first_line.length() - 4 > 2048)

            return (2);
    }
   // std::cout << first_line << std::endl;
  //  std::cout << first_line.length() << std::endl;
    return (0);
}
int getnextline(int fd, string &line)
{
    char delim;
    char nl = 0;
    int enf = 0;

    // std::cout << "fd : " << fd << "delin : " << delim << "   => " <<   recv(fd, &delim, 1, 0)<< std::endl;
    // std::cout << strerror(errno) << errno << std::endl;
    // size_t size;
    // if((size == recv(fd, &delim, 1, 0)) == -1)
    // {
    //     std::cout << " recv :" << strerror(errno) << std::endl;
    // }
    while ((enf += recv(fd, &delim, 1, 0))> 0 && delim != 0)
    {

        // std::cout << "??????" << std::endl;
        // std::cout << "inside gnl " << std::endl;
        if (delim == 13)
        {
            if ((enf += recv(fd, &nl, 1, 0)) > 0 && (nl == '\n' || nl == 0))
               {
                // std::cout << "Operation wouuld nlock !" << std::endl;
                 break;}
            line.push_back(delim); 
            line.push_back(nl); 
        }
        else
            line.push_back(delim); 
    }
    return (nl == 0||delim == 0 || line.size() == 0 ? 0 : enf);
}


int get_highest_fd(std::vector <int > fds)
{
    int high_fd = 0;
    for ( int i = 0;i < fds.size();i++)
    {
        if (high_fd < fds[i])
        high_fd = fds[i];
    }
    return (high_fd);
}

void is_socket_ready(std::vector<int > fds,std::vector <server> multi_server , int server_index)
{
    

       fd_set set;
       FD_CLR(fds[server_index],&set);

    struct timeval      time;
	time.tv_sec = 3;
	time.tv_usec = 0;
	FD_ZERO(&set);
    FD_SET(fds[server_index],&set);
    select(fds[server_index] + 1 ,&set,NULL,NULL,&time);
  
}


void init_server(server myserver,std::vector<server> multi_server,std::vector<int > fds)
{
int server_fd,new_socket,valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *helloo = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    std::string hello = "Hello from the server";
    std::vector<std::string > full_request;
  
//     char *first_line = NULL;
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) 
// {
//         std::cerr<< "(“cannot create socket”);  " << std::endl;
//         exit(EXIT_FAILURE);
// }
    
//   if (setsockopt(server_fd, SOL_SOCKET,
//                    SO_REUSEADDR , &opt,
//                    sizeof(opt))) {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }
    
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(myserver.get_listen_port());
//     fcntl(server_fd,F_SETFL,O_NONBLOCK);
//     //  memset(address.sin_zero, '\0', sizeof address.sin_zero);
//      if (bind(server_fd, (struct sockaddr*)&address,
//              sizeof(address))
//         < 0) {
//         std::cerr << ("bind failed") << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     if (listen(server_fd, 3) < 0) {
//         std::cerr << ("listen") << std::endl;
//         exit(EXIT_FAILURE);
//     }
    while(1)
    {
          int valread = 0;
  int new_socket = 0;
 //test_leaks();
 for ( int i = 0;i < fds.size() ; i++)
{   
        struct sockaddr_in sockaddr = {0};
             sockaddr = multi_server[i].get_sock_ader();
               int addrlen = sizeof(sockaddr);
           struct timeval      time;
	time.tv_sec = 1;
	time.tv_usec = 0;
        fd_set set;
    //  is_socket_ready(fds,multi_server,i);
    FD_ZERO(&set);
    FD_SET(fds[i],&set);
    select(get_highest_fd(fds) + 1 ,&set,NULL,NULL,&time);
     if(FD_ISSET(fds[i],&set))
    {
        std::cout << "Data is coming ! Accepting ... "<<  i << std::endl;
        if ((new_socket = accept(fds[i], (struct sockaddr *)&sockaddr, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
         fd_set read_set2;
   
        // for (int i = 0;j  = getnextline(server_fd,line) > 0;i++)
        // {

        // }
        int final_reponse_length = 0;
        char buffer[30000] = {0};
    FD_ZERO(&read_set2);
    FD_SET(new_socket,&read_set2);
    select (new_socket + 1,&read_set2,NULL,NULL,&time);
    if (FD_ISSET(new_socket,&read_set2))
    {
        std::cout << "Data is coming ! ... "<< std::endl;
        valread = read( new_socket , buffer, 30000);
        int method = 0;
    //    getline(new_socket,server_reponse);
    //   printf("%s\n",buffer );
       int length = strlen(buffer);
        std::vector <std::string > full_request;
        full_request = parsing_request(buffer);
        Request parsed_request(full_request);
       std::cout << "---------------------------BUFFER-------------------"  << std::endl;

    //   printf("%s\n",buffer );
        
        std::cout << "---------------------------MAIN-------------------"  << std::endl;
        printf("------------------ message -------------------");
        printf("------------------ CREATING SBOOF RESPONSE HERE  -------------------");
    
       //  std::cout << "WHAT THE FUCK IS HAPPENING " << std::endl;
       Response response(parsed_request,multi_server[i]);
      std::string sboof_response(response.get_Response());
        printf("------------------ FINAL RESPONSE -------------------");
    //    std::cout << sboof_response << std::endl;

        // std::string sboof_response;
       
       printf("------------------ MINE  -------------------");
     int datalen = sboof_response.size();
    int pp = 0;
    //    while ( datalen > 0) 
    //    {
        if(pp = send(new_socket ,sboof_response.c_str(),sboof_response.size(),0) == -1)
        {
            std::cout << "error : Response to client !" << std::endl;
            exit(1);
        }
        if ( pp   == -1)
            std::cout << " smth wrong happend in send " << std::endl;
        datalen -= pp;
      
     //  }
        printf("------------------Hello message sent-------------------");
        std::cout << "++++++Responding SERVER :  ++++++++ ... sv index : "  << i  << "server 1st name " << multi_server[i].get_name(0) << std::endl;
       
       FD_CLR(fds[i],&read_set2);
        close(new_socket);
    }
    }
    else
    {
        std::cout << "++++++ Waiting for new connection ++++++++ ... sv index : "  << i  << "server 1st name " << multi_server[i].get_name(0) << std::endl;
    }
       FD_CLR(fds[i],&set);
}
    }
    }
    // shutdown(server_fd, SHUT_RDWR);



void print_parsing_infos(server myserver)
{
     std::cout << "-----------------------Server Names : ------------------"  << std::endl;
        std::cout << myserver.get_name(0) << "    " << myserver.get_name(1) << "   " << myserver.get_name(2) << std::endl;
         std::cout << "-----------------------Server Port : ------------------"  << std::endl;
         std::cout << myserver.get_listen_port() << std::endl;
           std::cout << "-----------------------Server Host : ------------------"  << std::endl;
         std::cout << myserver.get_listen_host() << std::endl;
            std::cout << "-----------------------Server root : ------------------"  << std::endl;
         std::cout << myserver.get_root() << std::endl;
                   std::cout << "-----------------------Server allowed methods : ------------------"  << std::endl;
     for (std::vector<std::string>::iterator it1 = myserver.get_allowed_methods().begin();it1 != myserver.get_allowed_methods().end();it1++)
         std::cout << *it1 << std::endl;
     std::cout << "-----------------------Server  Index : | ------------------"  << std::endl;
     for (std::vector<std::string>::iterator it2 = myserver.get_index() .begin();it2 != myserver.get_index() .end();it2++)
         std::cout << *it2 << std::endl;
     std::cout << "-----------------------Server  upload path : ------------------"  << std::endl;
    std::cout << myserver.get_upload_path() << std::endl;
     std::cout << "-----------------------Server  error pages  : ------------------"  << std::endl;
        try
        {
        for (std::vector<std::string>::iterator it3 = myserver.get_error_pages(0).begin();it3 != myserver.get_error_pages(0).end();it3++)
         std::cout << *it3 << std::endl;
           std::cout << "-----------------------------------------------"  << std::endl;

        for (std::vector<std::string>::iterator it4 = myserver.get_error_pages(1).begin();it4 != myserver.get_error_pages(1).end();it4++)
         std::cout << *it4 << std::endl;
           std::cout << "-----------------------------------------------"  << std::endl;
         
          //for (std::vector<std::string>::iterator it5 = myserver.get_error_pages(2).begin();it5 != myserver.get_error_pages(2).end();it5++)
        // std::cout << *it5 << std::endl;
        } 
        catch (const std::string & exception)
        {
            std::cout << "error pages exception !" << std::endl;
        }
       try {
           std::cout << "-----------------------Server  redirections  pages  : ------------------"  << std::endl;
         for (std::vector<std::string>::iterator it3 = myserver.get_redirections()[0].begin();it3 != myserver.get_redirections()[0].end();it3++)
         std::cout << *it3 << std::endl;
           std::cout << "-----------------------------------------------"  << std::endl;
     
        for (std::vector<std::string>::iterator it4 = myserver.get_redirections().at(1).begin();it4 != myserver.get_redirections()[1].end();it4++)
         std::cout << *it4 << std::endl;
         
         // for (std::vector<std::string>::iterator it5 = myserver..at(2).begin();it5 != myserver..at(2).end();it5++)
         //std::cout << *it5 << std::endl;
       }
       catch (const std::string & exception )
       {
        std::cout << "redirections pages exception ! " << std::endl;
       }
           std::cout << "-----------------------Server  Client Max Body Size   : ------------------"  << std::endl;
        std::cout << myserver.get_client_max_body_size() << std::endl;
        std::cout << "-----------------------Server  AutoIndex    : ------------------"  << std::endl;
        if (myserver.get_autoindex() == true)
        std::cout << "autoindex on " << std::endl;
        else if (myserver.get_autoindex() == false)
        std::cout << "autoindex off " << std::endl;

}
int number_of_servers(std::vector <std::string > words)
{
    int i = 0;
    int count = 0;
    int accolade = 0;
    while ( i < words.size())
    {
          if (words[i] == "server" && accolade == 0)
             count++;
        if (words[i] == "{")
        ++accolade;
        if (words[i] == "}")
        --accolade;
      
        i++;
        
    }
    std::cout << "NUMBER OF SERVERS => " << count << std::endl;
    return (count);
}
server fill_server(std::vector <std::string > text_vector,int nb_of_servers)
{
    server server(text_vector,nb_of_servers);

    //if(!check_server())
    // {
    //     std::cout << " Error !  Config file not well formated ! Server missing some infos " std::endl;
    //     exit (1);
    // }
    return (server);

}
int is_binded_server(vector<server> ss, int i)
{
    server serv = ss[i];

    for (int j = 0; j < i; j++)
    {
        if(ss[j].get_listen_port() == -1)
        {
            std::cout << " Listen port not well defined !" << std::endl;
            return(1);
        }
        if (serv.get_listen_port()== ss[j].get_listen_port() && serv.get_listen_host()== ss[j].get_listen_host())
            return 0;
    }
    return 1;
}
void servers (std::vector <server> ss,std::vector <int> &fds)
{
    int fd = 0;
    int set = 1;
    int opt = 1;
    for ( int i = 0;i < ss.size();i++)
    {
        if (is_binded_server(ss,i))
        {
            if(ss[i].get_listen_port() == -1)
          {  std::cout << " Listen port not well defined !" << std::endl;
            break;}
            struct sockaddr_in sockaddr = {0};
             sockaddr = ss[i].get_sock_ader();
        int socket_fd = 0;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) 
        std::cerr<< "(“cannot create socket”);  " << std::endl;            
         if (setsockopt(socket_fd, SOL_SOCKET,
                   SO_REUSEADDR , &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(ss[i].get_listen_port());
    fcntl(socket_fd,F_SETFL,O_NONBLOCK);
     memset(sockaddr.sin_zero, '\0', sizeof sockaddr.sin_zero);
    std::cout  << " " << ss[i].get_listen_host()<< "------------" << ss[i].get_listen_port() << std::endl;
     if (bind(socket_fd, (struct sockaddr*)&sockaddr,
             sizeof(sockaddr))
        < 0) {
        std::cout << ("bind failed")  << strerror(errno)<< std::endl;
        // exit(EXIT_FAILURE);
    }
    std::cout << " BEFORE LISTEN" << std::endl;
    if (listen(socket_fd, 255) < 0) {
        std::cerr << ("listen") << std::endl;
        exit(EXIT_FAILURE);
    }
    fds.push_back(socket_fd);
    // test_fds.insert(std::make_pair(socket_fd,"garbage"));
        std::cout << ("Adding a new fd ...")  << socket_fd << std::endl;
    
        }
        else
        {
            std::cout << "Smth wrong !server not binded !" << std::endl;
        }
    }
}

int main(int ac,char **av)
{
   
        if(check_errors(ac,av) == 0)
        {
    
        std::ifstream indata;
        indata.open(av[1]);
        std::string text;
        server s;
        std::vector<std::string> text_vector;
        std::vector <std::string > words;
        std::vector <server> multi_server;
        int nb_of_servers = 0;
        int count  = 0;
        if (!indata)
        {
            std::cerr << "error :file could not be opened ! " << std::endl;
            exit (1);
        }
        while(getline(indata,text))
        {
            text_vector.push_back(text);
           // std::cout << text << std::endl;
        }
        words = parse_config_file(text_vector);
       nb_of_servers =  number_of_servers(words);
    int length = 1;
    std::cout << "=>"<<  nb_of_servers << std::endl;
        while ( length <= nb_of_servers )
        {
        server myserver(text_vector,length);
        multi_server.push_back(myserver);
        length++;
        }
        //server tt(text_vector,4);
    std::vector<int > fds;
    std::vector<server> tmp;
    // std::map < int , std::string > test_fds;
    // tmp =multi_server; // Only temporary otherwiese binds failed on server 0 cause already bind 
    // tmp.erase(tmp.begin());
      servers(multi_server,fds);
    //   int kk = 0;
    // std::sort(fds.begin(),fds.end(),greater<int>());
      for (int kk = 0;kk < fds.size();kk++)
      std::cout <<  "fds => " <<fds[kk] << " "<< kk <<  std::endl;
    // for(std::map<int,std::string>::iterator it = test_fds.begin();it != test_fds.end();it++)
    // std::cout << it->first << std::endl;
        // server myserver4(text_vector,5);
        // server myserver5(text_vector,6);
        // server myserver6(text_vector,7);
        // server myserver7(text_vector,8);


        // while ( count < nb_of_servers)
        // {  
        //     s = fill_server(text_vector,count);
        //     multi_server.push_back(s);
        // }
        //print_parsing_infos(myserver);
       //for (std::vector<std::string>::iterator it = text_vector.begin();it != text_vector.end();it++)
        // std::cout << *it << std::endl;
   // std::cout << av[1] << std::endl;
       init_server(multi_server[0],multi_server,fds);
    }
    
  // closing the connected socket
  // closing the listening socket
        return 0; 

}  

// ANCIEN RESPONSE 
/**
 * @brief 
 * 
 *   // for (std::vector<std::string>::iterator it3 = full_request.begin();it3 != full_request.end();it3++)
      
      //std::cout << *it3;
   //   std::cout << std::endl;
      //  std::cout << "-----------------------------------------------"  << std::endl;
        method = get_request_method(full_request);
        if(method == 1)
      {
        server_reponse = get_server_reponse(buffer);
         if ( check_url_length(full_request[0],1) == 2)
            {
            server_reponse.clear();
            server_reponse.insert(server_reponse.size() ,"HTTP/1.1 414 OK\n");
            server_reponse.insert(server_reponse.size(),"Content-Type: text/html\nContent-Length: 25\n\n 414 Request-URL Too Long");
        final_reponse_length = server_reponse.length();
            }
      }
      else if (method == 2)
      {
      server_reponse = get_server_reponse_post(buffer,full_request);
      if (check_post_request(full_request) == 0)
      {
       // std::cout << "CHECK_POST" << std::endl;
        server_reponse.clear();
            server_reponse.insert(server_reponse.size() ,"HTTP/1.1 400 OK\nContent-Type: text/html\nContent-Length: 16\n\n 400 Bad Request");
        final_reponse_length = server_reponse.length();
      }
        }
        else if (method == 3)
        server_reponse = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";       
        if (length > myserver.get_client_max_body_size())
        {
            server_reponse.clear();
            server_reponse.insert(server_reponse.size() ,"HTTP/1.1 413 OK\nContent-Type: text/html\nContent-Length: 28\n\n413 Request Entry Too Large");
        final_reponse_length = server_reponse.length();
        }
        final_reponse_length = server_reponse.length();
        char final_reponse[final_reponse_length + 1];
        */