package main

import (
	"bufio"
	"fmt"
	"io"
	"net"
	"os"
)

const (
	WrongMSG = "Wrong format ( server/client ip port )"
)

func send(conn net.Conn) {
	reader := bufio.NewReader(os.Stdin)

	for {
		input, err := reader.ReadString('\n')
		if err == io.EOF || input == "exit"+"\n" || input == "quit"+"\n" {
			return
		} else if len(input) == 1 {
			continue
		}

		_, err = conn.Write([]byte(input))
		if err != nil {
			panic(err)
		}
	}
}

func recv(conn net.Conn) {
	buffer := make([]byte, 1024)
	defer conn.Close()

	for {
		mLen, err := conn.Read(buffer)

		if err != nil {
			if err == io.EOF {
				fmt.Printf("%s Closed\n", conn.RemoteAddr().String())
				return
			} else {
				panic(err)
			}
		} else {
			fmt.Printf("From %s: %s\n",
				conn.RemoteAddr().String(),
				string(buffer[:mLen]))
		}
	}
}

func server(ip, port string) {
	ln, _ := net.Listen("tcp", ip+":"+port)
	defer ln.Close()

	fmt.Println("Waiting for connection")
	for {
		conn, _ := ln.Accept()
		fmt.Printf("%s Connected\n", conn.RemoteAddr().String())

		go recv(conn)
	}
}

func client(ip, port string) {
	conn, _ := net.Dial("tcp", ip+":"+port)
	defer conn.Close()
	fmt.Println("Connect success")

	send(conn)
}
