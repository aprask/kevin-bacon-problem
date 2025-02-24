# BFS (Kevin Bacon) in C++

## Introduction
The goal of this program is to measure the performance of a BFS algorithm on Centaurus.

---

## Table of Contents
1. [Running](#running)
2. [Requirements](#requirements)
3. [Benchmark](#benchmark)
4. [References](#references)

---

## Running

- To enter project use the `cd <path>` command
- You can run the project by running `Make` followed by the name of the executable `./bacon <node> <depth>`
- Note: if the node has spaces like "Tom Hanks", separate each space with an underscore.

---

## Requirements
- g++ compiler
- libcurl
- [rapdijson](https://rapidjson.org/) -- Make sure to clone the repository from rapidjson into your project's root directory.
- Centaurus

---

## Benchmark

job 1 (Tom Hanks for a depth of 2): 7017ms
job 2 (Clint Eastwood for a depth of 4): 1319316ms
job 3 (Morgan Freeman for a depth of 4): 3579892ms

I noticed that different actors will yield different completion times. This is primary due to their "relevance" in the movie industry and how much their reach is (the quantity of their neighbors).

I timed out when attempting to run an actor, such as Morgan Freeman, with a depth of ~8. This could be partially due to my O(n^2) inefficiency when determing if a node has been visited.
---


## References
1. [BFS](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
2. [curl](https://curl.se/libcurl/)
3. [rapidjson](https://rapidjson.org/)

---

**Author:** Andrew T. Praskala 
**Date:** Februrary 24, 2025 
