# webserv_42c
https://www.notion.so/Documentation-Webserv-320727979ffd4176a7dd5ba41aaadf46#1037875184a04a8a852a2f334941406e

https://maroislife.notion.site/maroislife/Web-Server-d3c265446b2b488cadfe7204fc9933d6


TODO
CONNECTIONS  ( Accept multiple connection  on the same server )
            Accept connection on different server ( one client at the time ) -> fine 
PARSING:

REDIRE
EXIT IF SMTH ENPTY
CHECK REQ
CHECK LOC
 RE-CHECK ALLOWED METHODS 
 
SGV RESPONSE:

Request Location : http://localhost:150/ Sgv if : index defined in config file for example index index00002.html
                                                index0002.html don´t exist on the machine -> SGV
                                                index0002.html exist on the machine -> fine 
                                                     No index defined : fine 
                                                    
                                                