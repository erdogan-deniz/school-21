## ngx_http_stub_status_module

The ngx_http_stub_status_module provides access to basic server status information.

This module is not built by default, its building must be enabled using the configuration parameter *--with-http_stub_status_module*.

An example of the configuration:
```
location = /basic_status {
    stub_status;
}
```

In this configuration, a simple web page is created with basic status information, which might look as follows:
```
Active connections: 291
server accepts handled requests
 16630948 16630948 31070465
Reading: 6 Writing: 179 Waiting: 106
```
