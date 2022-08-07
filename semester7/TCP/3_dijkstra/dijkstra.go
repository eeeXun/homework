package main

import (
	"fmt"
)

type DijkstraData struct {
	node    []string
	visited []bool
	path    [][]int
	source  string
	passby  []string
}

func NewData(graph map[string]map[string]int) *DijkstraData {
	var (
		node = make([]string, len(graph))
		path = make([][]int, len(graph))
	)

	tmp_index := 0
	for key := range graph {
		node[tmp_index] = key
		tmp_index++
	}

	for source_index := 0; source_index < len(graph); source_index++ {
		path[source_index] = make([]int, len(graph))
		for dest_index := 0; dest_index < len(graph); dest_index++ {
			if source_index == dest_index {
				path[source_index][dest_index] = 0
			} else {
				path[source_index][dest_index] = Max
			}
		}
	}

	for source, roads := range graph {
		for dest, distance := range roads {
			path[IndexOf(node, source)][IndexOf(node, dest)] = distance
		}
	}

	return &DijkstraData{
		node:    node,
		path:    path,
		visited: make([]bool, len(node)),
		passby:  make([]string, len(node)),
	}
}

func (data *DijkstraData) SetSource(source string) *DijkstraData {
	data.source = source
	for node_index := 0; node_index < len(data.node); node_index++ {
		data.passby[node_index] = data.source
	}

	return data
}

func (data *DijkstraData) RunDijkstra() *DijkstraData {
	data.visited[IndexOf(data.node, data.source)] = true

	for choose_times := 0; choose_times < len(data.node)-1; choose_times++ {
		min_distance := Max
		var min_index int

		for node_index := 0; node_index < len(data.node); node_index++ {
			if data.node[node_index] != data.source && !data.visited[node_index] {
				if data.path[IndexOf(data.node, data.source)][node_index] < min_distance {
					min_distance = data.path[IndexOf(data.node, data.source)][node_index]
					min_index = node_index
				}
			}
		}

		// update data
		for node_index := 0; node_index < len(data.node); node_index++ {
			if data.path[min_index][node_index] != Max {
				tmp_distance := min_distance + data.path[min_index][node_index]
				if tmp_distance < data.path[IndexOf(data.node, data.source)][node_index] {
					data.path[IndexOf(data.node, data.source)][node_index] = tmp_distance
					data.passby[node_index] = data.node[min_index]
				}
			}
		}
		data.visited[min_index] = true
	}

	return data
}

func (data *DijkstraData) PrintResult() {
	for node_index := 0; node_index < len(data.node); node_index++ {
		if data.node[node_index] != data.source {
			record := "->" + data.node[node_index]
			tmp_index := node_index
			for data.passby[tmp_index] != data.source {
				record = "->" + data.passby[tmp_index] + record
				tmp_index = IndexOf(data.node, data.passby[tmp_index])
			}
			fmt.Printf("%s%s: %d\n", data.source, record, data.path[IndexOf(data.node, data.source)][node_index])
		}
	}
}
