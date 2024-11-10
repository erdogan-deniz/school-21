# Simple Docker

Introduction to docker. Developing a simple docker image for your own server.

The russian version of the task can be found in the repository.

## Contents

1. [Chapter I](#chapter-i)
2. [Chapter II](#chapter-ii) \
    2.1. [nginx](#nginx) \
    2.2. [Docker](#docker) \
    2.3. [Dockle](#dockle)
3. [Chapter III](#chapter-iii) \
    3.1. [Ready-made docker](#part-1-ready-made-docker) \
    3.2. [Operations with container](#part-2-operations-with-container) \
    3.3. [Mini web server](#part-3-mini-web-server) \
    3.4. [Your own docker](#part-4-your-own-docker) \
    3.5. [Dockle](#part-5-dockle) \
    3.6. [Basic Docker Compose](#part-6-basic-docker-compose)


## Chapter I

![simple_docker](misc/images/simple_docker.png)

Planet Earth, Atlantic Ocean, Her Majesty's Ship "Hood", heading to London, UK, nowadays.

You never liked moving. A lot of fuss, little action. But you managed to find a great job to delve into DevOps world in Foggy Albion.
And you're not one to let minor difficulties ruin your plans.

From your cabin window you hear the sound of the waves, the ship is peacefully rocking on them and you remember your favorite novel about the sea - "Moby Dick".
Although the flow of the plot is far from straightforward, with many lyrical digressions and philosophical musings, you, like everyone else, associate this book primarily with Moby Dick himself - the white whale.

"Hmm... White whale..." - here you remember that during the long journey you were going to work on docker.


## Chapter II

### **nginx**

**nginx** (pronounced "engine-x") is an open-source reverse proxy server for HTTP, HTTPS, etc. **nginx** is also used as a load balancer, web server and for HTTP caching. The **nginx** project focuses on high parallelism, high performance and low memory usage.


**nginx** has one main process and several worker processes.
The primary task of the main process is to read and check the configuration and manage the worker processes.
The worker processes perform the actual processing of the requests.

How **nginx** and its modules work is defined in the configuration file. By default, the configuration file is called *nginx.conf*

### **Docker**

A container is a new "executable file" that includes all the dependencies the product needs.

The main advantage of containerisation is the isolation of dependencies and a single, simple software start-up point.

Basic terms:
- Docker image - the "package" for the application and dependencies (including system ones).
- Container - an instance of an image, i.e. a 'alive' image.

**Docker** is a platform that is designed to develop, deploy and run applications in containers.
**Docker** is the 'de-facto' standard containerisation tool in the industry, but it is not the first or last among containerisation technologies.

The forerunners of **Docker** containers were virtual machines.
A virtual machine, like a container, isolates the application and its dependencies from the outside environment.
However, **Docker** containers have advantages over virtual machines.
For example, they are very easy to port, consume fewer resources, start and run faster.

A docker image consists of layers. Each layer describes some change to be performed to the data on the running container.
The structure of links between layers is hierarchical. There is a base layer on which the other layers are "overlaid".
The *Dockerfile* is used to create an image. Each instruction in it creates a new layer.

### **Dockle**

**Dockle** is a container image security checking tool that can be used to find vulnerabilities.

Key features and benefits of **Dockle**:
- searches for vulnerabilities in images
- helps in creating a proper Dockerfile
- easy to use, you only need to specify the image name
- support for *CIS Benchmarks*.

### **Docker Compose**

Docker Compose is a tool for handling tasks related to projects deployment.
Docker Compose can be helpful if several services are used to keep the project running.

Docker Compose is used to simultaneously manage multiple containers that are part of an application.
This tool offers the same features as Docker, but allows to work with more complex distributed applications, e.g. microservices.


## Chapter III

As a result of the work you should provide a report on the first two tasks. Each part of the task describe what should be added to the report once it has been completed. This can be answers to questions, screenshots, etc.

As a result of the third task you should provide source files for running the web server.

As a result of the fourth and fifth tasks you should provide dockerfiles.

As a result of the sixth task you should provide a *docker-compose.yml* file and the dockerfiles needed to run it (if not provided earlier).

- A report with a .md extension must be uploaded to the repository, in the src folder.
- All parts of the task should be highlighted in the report as level 2 headings.
- Within one part of the task, everything that is added to the report must be in the form of the list.
- Each screenshot in the report must be briefly captioned (what’s in the screenshot).
- All screenshots must be cropped so that only the relevant part of the screen is shown.
- It’s allowed to have several task points shown in one screenshot, but they must all be described in the caption.
- Source files for running the web server from the third task should be uploaded to the repository, in the src/server folder.
- Dockerfiles from the fourth and fifth tasks should be uploaded to the repository, in the src folder.
- *docker-compose.yml* from the sixth task should be uploaded to the repository, in the src folder.
- Be prepared to demonstrate your work if necessary.

## Part 1. Ready-made docker

As the final goal of your little practice you have immediately chosen to write a docker image for your own web server, so first you need to deal with a ready-made docker image for the server.
You chose a pretty simple **nginx**.

**== Task ==**

##### Take the official docker image from **nginx** and download it using `docker pull`.
##### Check for the docker image with `docker images`
##### Run docker image with `docker run -d [image_id|repository]`
##### Check that the image is running with `docker ps`
##### View container information with `docker inspect [container_id|container_name]`
##### From the command output define and write in the report the container size, list of mapped ports and container ip
##### Stop docker image with `docker stop [container_id|container_name]`
##### Check that the image has stopped with `docker ps`
##### Run docker with ports 80 and 443 in container, mapped to the same ports on the local machine, with *run* command
##### Check that the **nginx** start page is available in the browser at *localhost:80*
##### Restart docker container with `docker restart [container_id|container_name]`
##### Check in any way that the container is running

- Add the following screenshots to the report:
    - the call and output of all commands used in this part of the task;
    - **nginx** start page at *localhost:80* (address must be shown).
    
*Note:* **Don't upload heavy files (>10 mb) to git.**

## Part 2. Operations with container

Docker image and container are ready. Now we can look into **nginx** configuration and display page status.

**== Task ==**

##### Read the *nginx.conf* configuration file inside the docker container with the *exec* command
##### Create a *nginx.conf* file on a local machine
##### Configure it on the */status* path to return the **nginx** server status page
##### Copy the created *nginx.conf* file inside the docker image using the `docker cp` command
##### Restart **nginx** inside the docker image with *exec*
##### Check that *localhost:80/status* returns the **nginx** server status page
##### Export the container to a *container.tar* file with the *export* command
##### Stop the container
##### Delete the image with `docker rmi [image_id|repository]`without removing the container first
##### Delete stopped container
##### Import the container back using the *import*command
##### Run the imported container
##### Check that *localhost:80/status* returns the **nginx** server status page

- Add the following screenshots to the report:
    - the call and output of all commands used in this part of the task;
    - the contents of the created *nginx.conf* file;
    - the **nginx** server status page at *localhost:80/status*.


## Part 3. Mini web server

It's time to take a little break from the docker to prepare for the last stage. It's time to write your own server.

**== Task ==**

##### Write a mini server in **C** and **FastCgi** that will return a simple page saying `Hello World!`
##### Run the written mini server via *spawn-fcgi* on port 8080
##### Write your own *nginx.conf* that will proxy all requests from port 81 to *127.0.0.1:8080*
##### Check that browser on *localhost:81* returns the page you wrote
##### Put the *nginx.conf* file under *./nginx/nginx.conf* (you will need this later)

## Part 4. Your own docker

Now everything is ready. You can start writing the docker image for the created server.

**== Task ==**

*When writing a docker image avoid multiple calls of RUN instructions*

#### Write your own docker image that:
##### 1) builds mini server sources on FastCgi from [Part 3](#part-3-mini- web-server)
##### 2) runs it on port 8080
##### 3) copies inside the image written *./nginx/nginx.conf*
##### 4) runs **nginx**.
_**nginx** can be installed inside the docker itself, or you can use a ready-made image with **nginx** as base._
##### Build the written docker image with `docker build`, specifying the name and tag
##### Check with `docker images` that everything is built correctly
##### Run the built docker image by mapping port 81 to 80 on the local machine and mapping the *./nginx* folder inside the container to the address where the **nginx** configuration files are located (see [Part 2](#part-2-operations-with-container))
##### Check that the page of the written mini server is available on localhost:80
##### Add proxying of */status* page in *./nginx/nginx.conf* to return the **nginx** server status
##### Restart docker image
*If everything is done correctly, after saving the file and restarting the container, the configuration file inside the docker image should update itself without any extra steps
##### Check that *localhost:80/status* now returns a page with **nginx** status

## Part 5. **Dockle**

Once you've written the image, it's never a bad idea to check it for security.

**== Task ==**

##### Check the image from the previous task with `dockle [image_id|repository]`
##### Fix the image so that there are no errors or warnings when checking with **dockle**


## Part 6. Basic **Docker Compose**

There, you've finished your warm-up. Wait a minute though...
Why not try experimenting with deploying a project consisting of several docker images at once?

**== Task ==**

##### Write a *docker-compose.yml* file, using which:
##### 1) Start the docker container from [Part 5](#part-5-dockle) _(it must work on local network, i.e., you don't need to use **EXPOSE** instruction and map ports to local machine)_
##### 2) Start the docker container with **nginx** which will proxy all requests from port 8080 to port 81 of the first container
##### Map port 8080 of the second container to port 80 of the local machine
##### Stop all running containers
##### Build and run the project with the `docker-compose build` and `docker-compose up` commands
##### Check that the browser returns the page you wrote on *localhost:80* as before


💡 [Tap here](https://forms.yandex.ru/cloud/6418195450569020f1f159c4/) **to leave your feedback on the project**. Pedago Team really tries to make your educational experience better.
