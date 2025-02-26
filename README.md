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

job 1 (Tom Hanks for a depth of 2): 6724ms
job 2 (Clint Eastwood for a depth of 3): 45741ms
job 3 (Morgan Freeman for a depth of 4): 1433198ms
job 4 (Uma Thurman for a depth of 5): 4719792ms

The reason why larger traversals take longer is due to the exponential increase in quantity from each neighbor. If we traverse the initial node and we get N neighbors. Each of those N neighbors may have C neighors themselves, and then those C neighbors may have K neighbors. Thus, we are expanding arbitrarily but also non-monotonically. 

For the first traversal to the second traversal we have a growth factor of of approx. 6.8x. Then 31.3x for the third and then 3.3x for the fourth.

There is a strange oddity with the miniscule divergence separating 4 and 5. I wonder why this is the case. Could it be due to caching? Did we hit more visited elements than non-visited? If our cache was big enough we could technically persist many of these actors per cache block. Maybe they were still in the cache and thus the fourth traveral yielded many cache hits?
---


## References
1. [BFS](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
2. [curl](https://curl.se/libcurl/)
3. [rapidjson](https://rapidjson.org/)

---

**Author:** Andrew T. Praskala 
**Date:** Februrary 26, 2025 
