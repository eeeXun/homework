package main

var (
	Max int = (1 << 63) - 1
)

func main() {
	var (
		graph = map[string]map[string]int{
			"A": {"B": 4, "C": 5, "D": 2, "E": 12},
			"B": {"A": 4, "C": 3, "E": 1},
			"C": {"A": 5, "B": 3, "D": 1, "H": 13},
			"D": {"A": 2, "C": 1, "F": 11},
			"E": {"A": 12, "B": 1, "G": 6, "H": 9},
			"F": {"D": 11, "H": 8},
			"G": {"E": 6, "H": 7},
			"H": {"C": 13, "E": 9, "F": 8, "G": 7},
		}
	)

	data := NewData(graph)
	data.SetSource("A").RunDijkstra().PrintResult()
}
