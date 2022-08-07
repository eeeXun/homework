package main

import (
	"os"
)

func main() {
	if len(os.Args) != 4 {
		panic(WrongMSG)
	} else {
		ip := os.Args[2]
		port := os.Args[3]

		switch os.Args[1] {
		case "server":
			server(ip, port)
		case "client":
			client(ip, port)
		default:
			panic(WrongMSG)
		}
	}
}
