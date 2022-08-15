/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:23:12 by amaach            #+#    #+#             */
/*   Updated: 2022/08/14 14:56:16 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "request.hpp"
//#include "../Client.hpp"
#include "Header.hpp"
#include "Firstline.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "server.hpp"
class   Header;
class server;
#define MAX_BUFFER 10000

class Response
{
private:
    Header      *_header;
    Request     _request;
    server      _Serv;
    std::string _Body;
    std::string _location;
    int         _location_index;
    int         _location_type; // 0 nothing 1 file 2 directory
    bool        _is_chanked;
    Response();

public:
    Response(Request &request, server &Serv);
    ~Response();
    std::string get_Response(Request rq );
    
private:
 
    void        errorsPages( int Status_code );
    int         statuscode( void ); 
    bool        check_location( void );
    bool        check_path( void );
    int         check_methods( void );
    int         check_request( void );
    
    //*************************
    int         check_GET( void );
    int         check_POST_upload( void );
    int         check_DELETE( void );

    //***********GET***********
    int         handle_GET_Dir( void );
    int         handle_GET_autoindex( void );
    int         cgi_GET( void );
    int         file_GET( void );
    //**********DELETE*********
    int         cgi_DELETE( void );
    int         file_DELETE( void );
    int         handle_DELETE_Dir( void );
    int         DELETE_all_Folder( void );
    //***********POST**********
    int         cgi_POST( void );
    int         handle_POST_Dir( void );
    int         check_POST( void );
    int         Upload_file( std::string upload_path );
    
};

std::string StatusCode(string location, int i);
std::string     file_to_string(std::string location);
