FROM quay.io/school21/alpine:3.16

RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
    build-base \
    python3 \
    valgrind \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools

RUN mkdir /test 

COPY . /project
COPY materials/build/scripts /project/ci-scripts
COPY materials/build/scripts /project/tests
COPY materials/linters /project/tests/linters

WORKDIR "/project"

ENTRYPOINT ["/bin/bash","ci-scripts/test.sh"]
