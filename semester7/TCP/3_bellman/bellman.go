package main

import (
	"fmt"
)

type BellmanData struct {
	node   []string
	path   [][]int
	dist   []int
	source string
	passby []string
}

func NewData(graph map[string]map[string]int) *BellmanData {
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

	return &BellmanData{
		node:   node,
		path:   path,
		dist:   make([]int, len(graph)),
		passby: make([]string, len(graph)),
	}
}

func (data *BellmanData) SetSource(source string) *BellmanData {
	data.source = source
	for node_index := 0; node_index < len(data.node); node_index++ {
		data.dist[node_index] = data.path[IndexOf(data.node, source)][node_index]
		data.passby[node_index] = data.source
	}

	return data
}

func (data *BellmanData) RunBellman() *BellmanData {
	// relax edges
	for choose_times := 0; choose_times < len(data.node)-1; choose_times++ {
		for node_index := 0; node_index < len(data.node); node_index++ {
			if data.dist[node_index] != Max {
				for dest_index := 0; dest_index < len(data.node); dest_index++ {
					if data.path[node_index][dest_index] != Max &&
						(data.dist[node_index]+data.path[node_index][dest_index] <
							data.dist[dest_index]) {
						data.passby[dest_index] = data.node[node_index]
						data.dist[dest_index] = data.dist[node_index] + data.path[node_index][dest_index]
					}
				}
			}
		}
	}

	return data
}

func (data *BellmanData) PrintResult() {
	for node_index := 0; node_index < len(data.node); node_index++ {
		if data.node[node_index] != data.source {
			record := "->" + data.node[node_index]
			tmp_index := node_index
			for data.passby[tmp_index] != data.source {
				record = "->" + data.passby[tmp_index] + record
				tmp_index = IndexOf(data.node, data.passby[tmp_index])
			}
			fmt.Printf("%s%s: %d\n", data.source, record, data.dist[node_index])

		}
	}
}
