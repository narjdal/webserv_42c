#pragma once


#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <map>
#include <random>
#include <fstream>
#include <sstream>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
//#include "parse_confile/config_file.hpp"

using namespace std;

class Request
{
    public :                //private members
        std::string rqmethod;
        std::string location;
        std::string vrs;
        map<std::string, std::string> headers;
        std::string body;
        std::string query;
        int body_len;

    public :

        Request();
        ~Request();
        Request(Request const& other);
        Request &operator=(Request const& other);
        Request(std::vector<std::string > text_vector);
        std::string get_method();
        std::string  get_location();
        std::string get_version();
        std::map<std::string, std::string> get_headrs();
        std::string& get_body();
        int get_body_len();

};