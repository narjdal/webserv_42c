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

int check_url_length(std::string first_line,int method)
{
    int i = 0;

    if (method == 1)
    {
        if (first_line.length() - 4 > 2048)

            return (2);
    }
    return (0);
}
int getnextline(int fd, string &line)
{
    char delim;
    char nl = 0;
    int enf = 0;

    while ((enf += recv(fd, &delim, 1, 0))> 0 && delim != 0)
    {

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


void init_server(std::vector<server> multi_server,std::vector<int > fds)
{
    std::vector <std::string > full_request;
    int max_clients = 30;
    int sd = 0;
    int client_socket[30];
    std::vector <int> clients_fds;
     while(1)
    {
    int valread = 0;
  int new_socket = 0;
  int server_fd = 0;
  int activity = 0;
 //test_leaks();
    for ( int i = 0;i < fds.size() ; i++)
        {   
     struct sockaddr_in sockaddr = {0};
    sockaddr = multi_server[i].get_sock_ader();
    int addrlen = sizeof(sockaddr);
    struct timeval      time;
	time.tv_sec = 1; // Time before time out of select 
	time.tv_usec = 100;
    fd_set set; // Read_set
    //  is_socket_ready(fds,multi_server,i);
    FD_ZERO(&set);
    FD_SET(fds[i],&set);
    activity = select(get_highest_fd(fds) + 1 ,&set,NULL,NULL,&time); // Sending highest fd  + 1 to select
    if ((activity < 0))
    {
        std::cout << " AN ERROR OCCURED IN SELECT " << std::endl;
    }
     if(FD_ISSET(fds[i],&set))
    {
        std::cout << "Data is coming ! Accepting ... "<<  get_highest_fd(fds)<<  i << std::endl;
     std::cout << "New connection , socket fd is " << new_socket << " , ip is" <<   inet_ntoa(sockaddr.sin_addr) << ":  , port : "   <<   ntohs(sockaddr.sin_port) << std::endl;
        if ((new_socket = accept(fds[i], (struct sockaddr *)&sockaddr, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        std::vector<int>::iterator it = std::find(clients_fds.begin(),clients_fds.end(),new_socket);
        if (it == clients_fds.end())
        clients_fds.push_back(new_socket);

        // for ( int help = 0;help < max_clients;help++)
        // {
        //     if(client_socket[help] == 0)
        //     {
        //         client_socket[help] = new_socket;
        //         std::cout << " Client addes succesffuly to the list ! " << std::endl;
        //         break;
        //     }
        // }
        // for ( int help = 0;help < max_clients ; help++)
        // {
        //     sd  = client_socket[help];
        //     if (FD_ISSET(sd,&set))
        //     {

        //     }
        // }
        for (int help = 0;help < clients_fds.size();help++)
        {
            sd = clients_fds[help];
    fd_set write_set; // write set
    char buffer[30000] = {0};
    FD_ZERO(&write_set);
    FD_SET(sd,&write_set);
    select (get_highest_fd(clients_fds) + 1,&write_set,NULL,NULL,&time);
    if (FD_ISSET(sd,&write_set))
    {
        std::cout << "Data is coming ! ... "<< std::endl;
        valread = read( sd , buffer, 30000);
        full_request = parsing_request(buffer);
        Request parsed_request(full_request);
        if(parsed_request.get_location() == "/favicon.ico")
            {
                // std::cout << " Ignoring this request ... ( this line will be removed " << std::endl;
                close(sd);
                break;
            }
       std::cout << "---------------------------BUFFER-------------------"  << std::endl;
        // std::cout << buffer << std::endl;
        std::cout << "---------------------------MAIN-------------------"  << std::endl;
                 // for (std::vector<std::string>::iterator itv = mu->get_methods().begin(); itv != it->get_methods().end(); itv++)
            //     std::cout << "The allowed_methods : " << *itv << std::endl;
                 std::cout << "-----------------------Server allowed methods : ------------------"  << std::endl;
    int savior = 0;
   
    while (  savior < multi_server[i].get_allowed_methods().size())
    {
        std::cout << " Server allowed methods : " << multi_server[i].get_allowed_methods()[savior] << " IDX: " << i << std::endl;
        savior++;
    }
    // for (std::vector<std::string>::iterator it1 = multi_server[i].get_allowed_methods().begin();it1 != multi_server[i].get_allowed_methods().end();it1++)
    //      std::cout << *it1 << std::endl;
            std::cout << "-----------------------LOCATION allowed methods : ------------------"  << std::endl;
         
         int counteur = 0;
         int ww = 0;
           {
        std::vector<location> tmp = multi_server[i].get_location();
        while ( counteur < tmp.size())
        {

            std::cout << "The name : " << multi_server[i].get_location(counteur).get_name() << counteur << std::endl;
            std::cout << "The location path : " << multi_server[i].get_location(counteur).get_locations_path() << std::endl;
            ww = 0;
            while ( ww < multi_server[i].get_location(counteur).get_methods().size())
            {
                std::cout << "loc allowed_methods : " << multi_server[i].get_location(counteur).get_methods()[ww] << i <<  std::endl;
                ww++;

            }
            // for (std::vector<std::string>::iterator itv = multi_server->get_methods().begin(); itv != it->get_methods().end(); itv++)
            // std::cout << "The root : " << it->get_root() << std::endl;
            // std::cout << "The client max body size : " << it->get_client_max_body_size() << std::endl;
            // std::cout << "The autoindex : " << bool(it->get_autoindex()) << std::endl;
            // std::cout << "The upload path : " << it->get_upload_path() << std::endl << std::endl;
            // std::cout << "*****************************************" << std::endl;
            
             counteur++;
      
        // for (std::vector<location>::iterator it = tmp.begin(); it != tmp.end(); it++)
        // {
        //     counteur++;
        //     std::cout << "The name : " << it->get_name() << counteur << std::endl;
        //     std::cout << "The location path : " << it->get_locations_path() << std::endl;
        //     for (std::vector<std::string>::iterator itv = it->get_methods().begin(); itv != it->get_methods().end(); itv++)
        //         std::cout << "The allowed_methods : " << *itv << i <<  std::endl;
        //     std::cout << "The root : " << it->get_root() << std::endl;
        //     std::cout << "The client max body size : " << it->get_client_max_body_size() << std::endl;
        //     std::cout << "The autoindex : " << bool(it->get_autoindex()) << std::endl;
        //     std::cout << "The upload path : " << it->get_upload_path() << std::endl << std::endl;
        //     std::cout << "*****************************************" << std::endl;
        }
    }
        std::cout << ("------------------ message -------------------") << std::endl;
        std::cout << ("------------------ CREATING SBOOF RESPONSE HERE  -------------------") << std::endl;
       Response response(parsed_request,multi_server[i]);
      std::string sboof_response(response.get_Response());
        std::cout << ("------------------ FINAL RESPONSE -------------------") << std::endl;
     int datalen = sboof_response.size();
    int pp = 0;
    //    while ( datalen > 0) 
    //    {
        
        if((pp = send(sd ,sboof_response.c_str(),sboof_response.size(),0) == -1))
        {
            std::cout << "error : Response to client !" << std::endl;
            close(sd);
        }
        if ( pp   == -1)
            {
                close(sd);
            std::cout << " smth wrong happend in send " << std::endl;
            }
            if ( pp == 0)
            {
                std::cout << " CLIENT GOT DISCONNECTED " << std::endl;
                close(sd);
                
            }
        datalen -= pp;
     //  }
     std::cout << multi_server[i].get_listen_host() << std::endl;
        printf("------------------Hello message sent-------------------");
        std::cout << "++++++Responding SERVER :  ++++++++ ... sv index : "  << i  << "server 1st name " << multi_server[i].get_name(0) << std::endl;
       
        close(sd);
    }
    //    FD_CLR(fds[i],&write_set);
        }
    }
    else
    {
        std::cout << "++++++ Waiting for new connection ++++++++ ... sv index : "  << i  << "server 1st name " << multi_server[i].get_name(0) << std::endl;
    }
    //    FD_CLR(fds[i],&set);
}
    }
    }
    // shutdown(server_fd, SHUT_RDWR);

int is_server_inside(server srv,std::vector <server> ss )
{

for ( int i = 0;i < ss.size();i++)
{
    if(srv.get_listen_port() == ss[i].get_listen_port())
    {
        std::cout << "  Error : Listen port already defined  ! this server will not be accessible. " << srv.get_name(0) << std::endl;
        return (1);
    }
}
return (0);
}
int is_binded_server(std::vector<server> ss, int i)
{
    server serv = ss[i];


    for (int j = 0; j < i; j++)
    {
        if(serv.get_listen_port() == -1)
        {
            std::cout << " Listen port not well defined !" << std::endl;
            return(0);
        }
        else if (serv.get_listen_port() == 0)
        {
            std::cout << " Listen port can't be equal to 0 ! " << std::endl;
            return (0);
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
        if (is_binded_server(ss,i) == 1)
        {
            if(ss[i].get_listen_port() == -1)
          {  std::cout << " Listen port not well defined !" << std::endl;
           
            break;
            }
         struct sockaddr_in sockaddr = {0};
         sockaddr = ss[i].get_sock_ader();
        int socket_fd = 0;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) 
        std::cout<< "(“cannot create socket”);  " << std::endl;            
         if (setsockopt(socket_fd, SOL_SOCKET,
                   SO_REUSEADDR , &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(ss[i].get_listen_port());
    
    if (fcntl(socket_fd,F_SETFL,O_NONBLOCK) < 0)
    std::cout <<" could not set TCP listening socket to be non-blocking" << std::endl;
    //  memset(sockaddr.sin_zero, '\0', sizeof sockaddr.sin_zero);
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
        std::cout << ("Adding a new fd ...")  << socket_fd  << ss[i].get_name(0) << std::endl;
    
        }
        else
        {
            std::cout << " Careful ! server not binded ! , this server  will not be accessible. " << ss[i].get_name(0) << std::endl;
            // i++;
            // ss.erase(ss.begin() + i);
            // fds.clear();
            // servers(ss,fds);
        }
    }
}

int main(int ac,char **av)
{
    std::string text;
    server s;
    std::vector<std::string> text_vector;
    std::vector <std::string > words;
    std::vector <server> multi_server;

        if(check_errors(ac,av) == 0)
        {
        std::ifstream indata;
        indata.open(av[1]);
     
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
            // std::cout << "  "  << text << std::endl;
        }
        words = parse_config_file(text_vector);
        check_words_config_file(text_vector);
     multi_server = fill_server(text_vector,number_of_servers(words));
    std::vector<int > fds;
      servers(multi_server,fds);
      for (int kk = 0;kk < fds.size();kk++)
      std::cout <<  "fds => " <<fds[kk] << " "<< kk <<  std::endl;
      std::cout << " HIGHEST FD" << get_highest_fd(fds) << std::endl;
       init_server(multi_server,fds);
    }
    
  // closing the connected socket
  // closing the listening socket
        return 0; 

}  
