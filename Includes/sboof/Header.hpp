/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:25:36 by amaach            #+#    #+#             */
/*   Updated: 2022/08/16 13:30:15 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Response.hpp"
#include "server.hpp"

class   Header
{
    private:
        std::map<std::string, std::string>  _Header;
        std::string     _Server;
        std::string     _Date;
        std::string     _FirstLine;

    public:
        Header();
        Header(server sev, Request req);
        ~Header();

        void                                setFirstLine(std::string FirstLine );
        void                                setHeader(std::string Key, std::string Value);
        std::string                         getHeader( void );
        std::map<std::string, std::string>  getHeaderMap( void );

};