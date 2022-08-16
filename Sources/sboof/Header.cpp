/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:01:09 by amaach            #+#    #+#             */
/*   Updated: 2022/07/23 16:07:20 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/sboof/Header.hpp"

std::string     get_curentTime1(void)
{
    time_t now = time(0);
    string dt = ctime(&now);

    dt.pop_back();

    return dt;
}

Header::Header(server sev, Request req)
{
    this->_Server = sev.get_name(0);
    this->_Date = get_curentTime1();
}


Header::~Header()
{
}

void        Header::setFirstLine(std::string FisrtLine)
{
    this->_FirstLine = FisrtLine;
}

void        Header::setHeader(std::string Key, std::string Value)
{
    this->_Header[Key] = Value;
}

std::string     Header::getHeader(void)
{
    std::string header;
    header = this->_FirstLine;
    header += "Date: " + this->_Date + " \r\n";
    header += "Server: " + this->_Server + "\r\n";
    std::map <std::string,std::string > tmp_headers;
    for (map<string,string>::iterator it = this->_Header.begin(); it != this->_Header.end(); it++)
    {
        header += it->first + ": " + it->second + "\r\n";
    }
    header += "\r\n";
    return(header); // return the header as string to send
}
