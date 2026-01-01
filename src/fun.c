#include "../headers/main.h"


char* get_body_from_file(char *filepath){ //gets html files 
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fseek(fp,0,SEEK_SET);

    char *buffer = malloc(size+1);
    if(buffer){
        fread(buffer,1,size,fp);
        buffer[size]='\0';
    }

    fclose(fp);
    return buffer;

}

void set_header_and_respond(int client_fd,int status_code, char* filepath){ //handles sending responses to client
    const char *status_line;
    char header[512];
    char *body;

    body=get_body_from_file(filepath);
    if(body==NULL) return;
    
    switch(status_code){
        case 200: status_line = "HTTP/1.1 200 OK\r\n"; break;
        case 404: status_line = "HTTP/1.1 404 Not Found\r\n"; break;
        case 405: status_line = "HTTP/1.1 405 Method Not Allowed\r\n"; break;
        default:  status_line = "HTTP/1.1 400 Bad Request\r\n"; break;
    }

    snprintf(header, sizeof header,
        "%s"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        status_line,
        strlen(body)
    );

    
    send(client_fd, header, strlen(header), 0);
    send(client_fd, body, strlen(body), 0);
    free(body);
}

void do_routing(char* method,char* path, int client_fd){ //handles routing

    if(strcmp(method,"GET")==0){
        if(strcmp(path,"/")==0)                  set_header_and_respond(client_fd, 200, "../response_html/root.html");
        else if(strcmp(path,"/another_page")==0) set_header_and_respond(client_fd, 200, "../response_html/another_page.html");
        else                                     set_header_and_respond(client_fd, 404, "../response_html/page_not_found.html");
    }
    else{
        set_header_and_respond(client_fd,405,"../response_html/not_allowed.html");
    }
    
}

void free_everything(int *fd, int *client_fd){
    close(*fd);
    close(*client_fd);
}
