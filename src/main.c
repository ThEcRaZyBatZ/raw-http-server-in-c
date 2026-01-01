#include "../headers/main.h"
//server model is getaddrinfo -> socket -> bind -> listen -> accept -> send -> recieve -> close -> free

int main(){

    struct addrinfo hints={0}, *res, *i;

    hints.ai_flags    = AI_PASSIVE; //connects to localhost
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    
    if(getaddrinfo(NULL, "6969", &hints, &res) != 0){
        fprintf( stderr,"error getting address info\n" );
        return -1;
    }
 
    int fd=0;

    for(i=res;i!=NULL;i=i->ai_next){ //checks all combinations until it finds one from the linked list

        fd = socket(i->ai_family, i->ai_socktype, i->ai_protocol); //servers file descriptor 

        if(fd ==-1) continue; 
        if(bind(fd,i->ai_addr,i->ai_addrlen)==-1){ //binds to the fd
            close(fd);
            continue;
        }
        
        break;
    }

    if(i==NULL){ //either the fd cant be assigned or binding issue, check
        fprintf( stderr,"error binding\n" );
        return -1;
    }

    if(listen(fd, BACKLOGS)==-1){ //starts listening to requests, polls if multiple requests are sent
        fprintf( stderr,"error listening\n" );
        return -1;
    }

    freeaddrinfo(res); //frees the linkedlist of structs

    struct sockaddr_storage their_ip; //stores the clients ip details, not used here but idk why i kept it
    socklen_t their_ip_size = sizeof(their_ip);

    int client_fd, bytes;
    char buf[4096],method[8],path[1024];


    while(1){

        client_fd=accept(fd, (struct sockaddr*) &their_ip, &their_ip_size); //accepts the clients req and assigns an fd

        if(client_fd == -1){
            fprintf( stderr,"error accepting\n" );
            return -1;
        }

        bytes=recv(client_fd, buf, sizeof(buf)-1,0);

        if(bytes<=0){
            free_everything(&fd,&client_fd);
            return -1;
        }

        buf[bytes]='\0';
        printf("Request: \n%s\n",buf);

        
        sscanf(buf, "%7s %1023s", method, path);

        do_routing(method,path,client_fd);
        close(client_fd);
    }
}