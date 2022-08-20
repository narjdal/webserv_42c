#include "../Includes/tt.hpp"
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "../Includes/sboof/Response.hpp"
#include <iterator>

int check_errors(int ac,char **av)
{
    std::ifstream file;
    struct stat buffer;
    if (ac < 2)
    {
        std::cout << "Usage: ./webserv <path_to_config_file>" << std::endl;
        exit (1);
    }
    if ( ac == 2 )
    {
         int i = stat(av[1], &buffer);
        if (i == -1)
        {
            std::cout << "Error: this config file not found" << std::endl;
            exit (1);
        }
	    file.open(av[1]);
        if (!file.is_open())
        {
        std::cout << "Error: file " << av[1] << " not found"  << std::endl;
         exit(2);
        }
    }
    else
    {
        file.open("./conf.conf");
        if (!file.is_open())
            {
        std::cout << "default conf not found "   << std::endl;
                exit (3);
            }
    }
    return(0);
}

void check_file_accolade(std::vector <std::string > words)
{
    int i = 0;
    int count = 0;

    while ( i < words.size())
    {
        if (words[i] == "{")
        ++count;
        else if (words[i] == "}")
        --count;
        i++;
    }
    // std::cout << "INSIDE ACCOLADE COUNT" << count << std::endl;
    if (count != 0)
    {
        std::cout << "Error:File Not Well Formated (accolade)" << std::endl;
        exit(1);
    }

}
void specified_words(std::string word)
{
     std::string err;
      err = "Error: ";
     err += word;
    err += " is not a valid word";
    if (word != "server_names" && word != "server" && word != "cgi_path" && word != "root" &&
        word != "allow_methods" && word != "upload_path" && word != "index"
         && word != "index.html" && word != "error_page" && word != "autoindex" && word != "redirection"
        && word != "client_max_body_size" && word != "location" && word != "cgi"
        && word != "{" && word != "}" && word != "listen")
        {
            // if(err)
            std::cout << err << std::endl;
            exit(1);    
        }
}

void specified_wordsv2(std::string word)
{
     std::string err;
      err = "Error: Loc:  ";
     err += word;
    err += " is not a valid word";
    if (word != "cgi_path" && word != "root" &&
        word != "allow_methods" && word != "upload_path" && word != "index"
         && word != "index.html"&& word != "autoindex" && word != "redirection"
        && word != "client_max_body_size" && word != "location" && word != "cgi"
        && word != "{" && word != "}")
        {
            // if(err)
            std::cout << err << std::endl;
            exit(1);    
        }
}

void check_syntax_error(std::vector <std::string > text_vector)
{
  for (std::vector<std::string>::iterator it = text_vector.begin(); it != text_vector.end(); ++it)
    {
        std::string line = *it;
        std::stringstream ss(line);
        std::string tmp;
        if (!line.empty())
        {
            while (std::getline(ss, tmp, ' '))
            {
                if (tmp == "")
                    continue;
                break;
            }
            specified_words(tmp);
        }
    }
}


std::vector <std::string > split_by_space(std::vector <std::string > text_vector)
{
    std::vector <std::string > _words;
    std::vector<std::string> tmp = text_vector;
      for (std::vector<std::string>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        std::string line = *it;
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ' '))
        {
            if (word == "")
                continue;
            _words.push_back(word);
        }
    }
    return (_words);
}
//!!!!//
std::vector <std::string > parse_config_file(std::vector <std::string > text_vector)
{
    std::vector<std::string > words;
    words = split_by_space(text_vector);
      for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it)
    {
        // std::cout << *it << "|" ;
    }
    if (words.size() == 0)
    {
        std::cout << "Error:File Not Well Formated(no word)" << std::endl;
        exit(1);
    }
    check_file_accolade(words);
//    check_syntax_error(words);
   /**
    * 
    * 
      for (unsigned int i = 0; i < words.size(); i++)
    {
		if (words[i] == "server" && ((i + 1) < words.size()))
        {
			i++;
			if (words[i] == "{")
				
		}
		else
        {
            std::cout <<"Error: every server configuration must be startes by server" << std::endl;
            exit(1);
        }
        */
  //  }
return (words);
}

void check_words_config_file(std::vector<std::string > text_vector)
{
    int i = 0;
    std::vector <std::string> tmp;
    std::vector <std::string > first_word;
    int inside = 0;
    std::vector<std::string> tmp_iterator = text_vector;
    for(std::vector<std::string>::iterator it = tmp_iterator.begin();it != tmp_iterator.end();it++)
    {
        // tmp = ft_split(*it," ");
        tmp.push_back(*it);
        first_word = split_by_space(tmp);
        // std::cout << first_word.size() << first_word[0] << std::endl;
         if(first_word[0] == "location" || inside == 1)
         {
            // std::cout << " THIS IS GOOOOOOOOOOD" << first_word[0] << std::endl;
            specified_wordsv2(first_word[0]);
            inside = 1;
         }
         if(inside == 1 && first_word[0] == "}")
         inside = 0;
        if (inside == 0)
         specified_words(first_word[0]);
        tmp.clear();
        first_word.clear();
        // if(!tmp[0].empty())
        // std::cout << tmp.at(0) << std::endl;
        // std::cout << *it << std::endl;
    }
    // while (i < text_vector.size())
    // {
    //     tmp = ft_split(text_vector[i]," ");
    //     std::cout << text_vector[i] << std::endl;
    //     if(!tmp[0].empty())
    //     std::cout << tmp[0] << std::endl;
    //     tmp.clear();
    //     // specified_words(tmp[0]);
    //     i++;
    // }
}