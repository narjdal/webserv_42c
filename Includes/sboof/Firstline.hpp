/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Firstline.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:50:24 by amaach            #+#    #+#             */
/*   Updated: 2022/07/21 17:16:41 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Response.hpp"


class FirstLine
{
private:
    std::map<int, std::string> _StatusCode;
    Request&    _req;
public:
    FirstLine(Request& request);
    ~FirstLine();

    std::string     First_Line(int  Key);
};
