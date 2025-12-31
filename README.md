# raw-http-server-in-c

A minimal HTTP server written in C using raw POSIX sockets.

This project is built to understand how HTTP works at a low level without using any frameworks or libraries.

## Features
- TCP server using `socket`, `bind`, `listen`, `accept`
- Manual HTTP request parsing
- Basic GET routing
- Static HTML file serving
- Proper HTTP response formatting

## Status
- GET requests implemented
- Routing and static pages working
- Raw POST parsing is in progress and will be pushed soon

## Run
```bash
gcc -o ./output/http main.c fun.c
./http
```

#### Open in Browser http://localhost:6969 and see it work!
