package main

func IndexOf(arr []string, candidate string) int {
	for index, element := range arr {
		if element == candidate {
			return index
		}
	}
	return -1
}
