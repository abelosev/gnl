FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc -Wall -Wextra -Werror -g -o gnl_exec main.c get_next_line.c get_next_line_outils.c

CMD ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "./gnl_exec"]