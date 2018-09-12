#/bin/bash

gcc -o serv serv.c
scp serv root@${SERVERIP}:/usr/local/bin/serv
rm serv
