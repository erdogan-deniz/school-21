## Running **C** code using **FastCGI** & **nginx**

By using the API provided by <fcgiapp.h> header, the socket details can be specified, which spawning via external means does for you.

A TCP socket file descriptor can be got like this:
`int sockfd = FCGX_OpenSocket("127.0.0.1:9000", 100);`

...or using Unix sockets:
`int sockfd = FCGX_OpenSocket("/var/run/fcgi.sock", 100);`

With the socket it can be written then:
```
FCGX_Request req;
FCGX_InitRequest(&req, sockfd, 0);

while (FCGX_Accept_r(&req) >= 0) {
FCGX_FPrintF(req.out, "Content-Type: text/html\n\n");
FCGX_FPrintF(req.out, "hello world");
FCGX_Finish_r(&req);
}
```

Once compile, the binary can be executed directly without using *spawn-fcgi* or *cgi-fcgi*.
