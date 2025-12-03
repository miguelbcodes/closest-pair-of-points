# Closest Pair of Points

Efficient O(n log n) implementation of the divide-and-conquer algorithm to find the closest pair of points in a 2D plane.

## Algorithm

The implementation uses the classic divide-and-conquer approach:

1. Sort points by x and y coordinates
2. Recursively divide the point set into left and right halves
3. Find closest pairs in each half
4. Check the strip near the dividing line for closer pairs
5. Return the overall closest pair

**Time Complexity:** O(n log n)  
**Space Complexity:** O(n)

## Build

```bash
cmake -B build
cmake --build build
```

## Usage

```bash
./build/closest_pair <dataset_file> <results_file>
```

### Arguments

- `dataset_file`: Input file containing points (one point per line: `x y`)
- `results_file`: CSV file to append results to

### Example

```bash
./build/closest_pair dataset-1000points.txt results.csv
```

## Generate Datasets

Use the included Python script to generate test datasets:

```bash
python3 generate_datasets.py
```

This creates:
- `dataset-20points.txt` (20 points)
- `dataset-100points.txt` (100 points)
- `dataset-500points.txt` (500 points)
- `dataset-1000points.txt` (1000 points)
- `dataset-10000points.txt` (10000 points)

## Results Format

The output CSV contains:
- Dataset name
- Point 1 coordinates (x, y)
- Point 2 coordinates (x, y)
- Distance between the points
- Execution time in milliseconds

## Run All Tests

```bash
for dataset in dataset-*.txt; do
    ./build/closest_pair "$dataset" results.csv
done
```
