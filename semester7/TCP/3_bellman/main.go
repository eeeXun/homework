package main

var (
	Max  int = (1 << 63) - 1
)

func main() {
	var (
		graph = map[string]map[string]int{
			"A": {"B": 6, "C": 5, "D": 5},
			"B": {"E": -1},
			"C": {"B": -2, "E": 1},
			"D": {"C": -2, "F": -1},
			"E": {"G": 3},
			"F": {"G": 3},
			"G": {},
		}
	)
	data := NewData(graph)
	data.SetSource("A").RunBellman().PrintResult()
}
