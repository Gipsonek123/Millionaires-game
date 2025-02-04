FROM gcc:latest

WORKDIR /usr/src/app
COPY main.cpp .
COPY Pytania.txt .

RUN g++ -o myapp main.cpp

CMD ["./myapp"]
