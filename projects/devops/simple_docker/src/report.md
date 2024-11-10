# Simple Docker

## Part 1. Ready-made docker

* Let's take the official docker image `nginx`:
  * `docker pull`:
  Download an image from a registry.
  Usage: `docker pull [OPTIONS] NAME[:TAG|@DIGEST]`.

  * The pulling `nginx` docker image:
  ![Simple Docker](screenshots/docker_pull_nginx.jpg)

* Let's check the docker images:
  * `docker images`:
  List images.
  Usage: `docker images [OPTIONS] [REPOSITORY[:TAG]]`.

  * The docker images:
  ![Simple Docker](screenshots/docker_images.jpg)

* Let's run docker image:
  * `docker run`:
  Create and run a new container from an image.
  Usage: `docker run [OPTIONS] IMAGE [COMMAND] [ARG...]`.
  Options: `-d` run container in background and print container ID.

  * The running docker image:
  ![Simple Docker](screenshots/docker_run_nginx.jpg)

* Let's check that the image is running:
  * `docker ps`:
  The command shows list containers.
  Usage: `docker ps [OPTIONS]`.

  * The result of checking:
  ![Simple Docker](screenshots/docker_ps.jpg)

* Let's view the container information:
  * `docker inspect`:
  Return low-level information on Docker objects.
  Usage: `docker inspect [OPTIONS] NAME|ID [NAME|ID...]`.

  * The viewing container information:
  ![Simple Docker](screenshots/docker_inspect_one.jpg)
  ![Simple Docker](screenshots/docker_inspect_two.jpg)
  ![Simple Docker](screenshots/docker_inspect_three.jpg)
  ![Simple Docker](screenshots/docker_inspect_four.jpg)

  * As we can see:
    * Container size is:
    ![Simple Docker](screenshots/docker_inspect_container_size.jpg)

    * List of mapped ports are:
    ![Simple Docker](screenshots/docker_inspect_container_ports.jpg)

    * Container IP is:
    ![Simple Docker](screenshots/docker_inspect_container_ip.jpg)

* Let's stop the docker image:
  * `docker stop`:
  Stop one or more running containers.
  Usage: `docker stop [OPTIONS] CONTAINER [CONTAINER...]`.

  * The stopping docker image:
  ![Simple Docker](screenshots/docker_stop_nginx.jpg)

* Let's check that the image has stopped:
  * The image has stopped:
  ![Simple Docker](screenshots/docker_ps_nginx.jpg)

* Let's run docker with ports `80` and `443` in container, mapped to the same ports on the local machine:
  * Options: `-p` publish a container's port(s) to the host.

  * The running docker:
  ![Simple Docker](screenshots/docker_run_mapped_ports.jpg)

* Let's check that the `nginx` start page is available:
  * The `nginx` start page:
  ![Simple Docker](screenshots/nginx_start_page.jpg)

* Let's restart the docker container:
  * `docker restart`:
    Restart one or more containers.
    Usage: `docker restart [OPTIONS] CONTAINER [CONTAINER...]`.

  * The restarting container:
  ![Simple Docker](screenshots/docker_restart_nginx.jpg)

* Let's check the container:
  * The container:
  ![Simple Docker](screenshots/docker_restart_nginx_check.jpg)

## Part 2. Operations with container

* Let's read the `nginx.conf` file inside the docker container:
  * `docker exec`:
  Execute a command in a running container.
  Usage: `docker container exec [OPTIONS] CONTAINER COMMAND [ARG...]`.

  * The `nginx.conf` file:
  ![Simple Docker](screenshots/nginx_conf.jpg)

* Let's create a `nginx.conf` file on a local machine:
  * The created `nginx.conf` file:
  ![Simple Docker](screenshots/my_nginx_conf.png)

* Let's configure it on the `/status` path to return the `nginx` server status page:
  * The `nginx.conf` file:
  ![Simple Docker](screenshots/ready_nginx_conf.jpg)

* Let's copy the created file inside the docker image:
  * `docker cp`:
  Copy files/folders between a container and the local filesystem.
  Usage: `docker container cp [OPTIONS] CONTAINER:SRC_PATH DEST_PATH|- docker cp [OPTIONS] SRC_PATH|- CONTAINER:DEST_PATH`.

  * The copying configuration file:
  ![Simple Docker](screenshots/docker_cp_nginx.jpg)

* Let's restart `nginx` inside the docker image:
  * The restarting `nginx`:
  ![Simple Docker](screenshots/restart_nginx.jpg)

* Let's check that `localhost:80/status` returns server status page:
  * The checking `/status` route:
  ![Simple Docker](screenshots/nginx_status_page.jpg)

* Let's export the container to a `container.tar` file:
  * `docker export`:
  Export a container's filesystem as a tar archive.
  Usage: `docker container export [OPTIONS] CONTAINER`.

  * The exporting the container:
  ![Simple Docker](screenshots/docker_export_nginx.jpg)

* Let's stop the container:
  * The stopping the container:
  ![Simple Docker](screenshots/docker_stop_nginx.jpg)

* Let's delete the image without removing the container first:
  * `docker image rm`:
  Remove one or more images.
  Usage: `docker image rm [OPTIONS] IMAGE [IMAGE...]`.
  Options: `-f` force removal of the image.

  * The removing the image:
  ![Simple Docker](screenshots/docker_rmi_nginx.jpg)

* Let's delete the stopped container:
  * `docker container rm`:
  Remove one or more containers.
  Usage: `docker container rm [OPTIONS] CONTAINER [CONTAINER...]`.

  * The deleting container:
  ![Simple Docker](screenshots/docker_rm_nginx.jpg)

* Let's import the container back:
  * `docker import`:
  Import the contents from a tarball to create a filesystem image.
  Usage: `docker image import [OPTIONS] file|URL|- [REPOSITORY[:TAG]]`.
  Options: `-c` apply dockerfile instruction to the created image.

  * The importing container:
  ![Simple Docker](screenshots/docker_import_nginx.png)

* Let's run the imported container:
  * The running the container:
  ![Simple Docker](screenshots/docker_run_tar_nginx.jpg)

* Let's check that `localhost:80/status` returns the server status page:
  * The status page:
  ![Simple Docker](screenshots/nginx_status_page.jpg)

## Part 3. Mini web server

* Let's write a server in `C` and `FastCgi` that will return a simple page:
  * The mini server:
  ![Simple Docker](screenshots/mini_server.jpg)

* Let's run the server on port `8080`:
  * The running mini server:
  ![Simple Docker](screenshots/run_mini_server.jpg)

* Let's write `nginx.conf` file that will proxy all requests from port `81` to `127.0.0.1:8080`:
  * The writting `nginx.conf` file:
  ![Simple Docker](screenshots/nginx_conf_server.jpg)

* Let's check that browser on `localhost:81` returns the page:
  * The checking browser:
  ![Simple Docker](screenshots/server_start_page.jpg)

## Part 4. Your own docker

* Let's write docker image that:
  1) builds mini server sources on `FastCgi`
  2) runs it on port `8080`
  3) copies inside the image written `./nginx/nginx.conf`
  4) runs `nginx`

  * The building the docker file:
  ![Simple Docker](screenshots/server_dockerfile.jpg)

  * The script is:
  ![Simple Docker](screenshots/server_script.jpg)

* Let's build the docker image:
  * `docker build`:
  Build an image from a `Dockerfile`.
  Usage: `docker image build [OPTIONS] PATH | URL | -`.
  Options: `-t` name and optionally a tag in the `name:tag` format.

  * The docker image:
  ![Simple Docker](screenshots/docker_build_server.jpg)

* Let's check that everything is built correctly:
  * The docker image:
  ![Simple Docker](screenshots/docker_check_server.jpg)

* Let's run the built docker image by mapping port `81` to `80` on the local machine and mapping the `./nginx` folder inside the container to the address where the `nginx` configuration files are located and check that the page is available on `localhost:80`:
  * Options: `-v` bind mount a volume.

  * The checking page:
  ![Simple Docker](screenshots/docker_run_server.jpg)

* Let's check that the server is available on `localhost:80`:
  * The checking page:
  ![Simple Docker](screenshots/nginx_status_page.jpg)

* Let's add proxying of `/status` page in `./nginx/nginx.conf` to return the `nginx` server status:
  * The adding page:
  ![Simple Docker](screenshots/last_nginx_conf.jpg)

* Let's restart the docker image:
  * The restarting page:
  ![Simple Docker](screenshots/docker_restart_image.jpg)

* Let's check that `localhost:80/status` returns `nginx` status:
  * The status page:
  ![Simple Docker](screenshots/server_start_page.jpg)

## Part 5. Dockle

* Let's check the image with dockle:
  * `dockle`:
  Usage: `dockle [image_id|repository]`.

  * The dockle checking:
  ![Simple Docker](screenshots/dockle_image.jpg)

* Let's fix the image:
  * The fixed dockerfile:
  ![Simple Docker](screenshots/fixed_dockerfile.jpg)

  * The second dockel checking:
  ![Simple Docker](screenshots/new_dockle_image.jpg)

## Part 6. Basic Docker Compose

* Let's write a `docker-compose.yml` file:
  1) start the docker container
  2) start the docker container with `nginx` which will proxy all requests from port `8080` to port `81` of the first container
  3) map port `8080` of the second container to port `80` of the local machine

  * The `docker-compose.yml` is:
  ![Simple Docker](screenshots/docker_compose.jpg)

* Let's stop running containers:
  * The running containers:
  ![Simple Docker](screenshots/docker_stop_containers.jpg)

* Let's build and run the project:
  * `docker-compose build`:
  Build or rebuild services.
  Usage: `docker compose build [OPTIONS] [SERVICE...]`.

  * The project buildind:
  ![Simple Docker](screenshots/docker_compose_build.jpg)

  * `docker-compose up -d`:
  Create and start containers.
  Usage: `docker compose up [OPTIONS] [SERVICE...]`.
  Options: `-d` run containers in the background.

  * The running project containers:
  ![Simple Docker](screenshots/docker_compose_up.jpg)

* Let's check the `localhost`:
  * The checking:
  ![Simple Docker](screenshots/last_localhost_page.jpg)
