#!/bin/bash
cd ../..
docker rmi -f school21/miniverter:1.0 && docker build . -t school21/miniverter:1.0 -f materials/build/Dockerfile && docker run school21/miniverter:1.0 
