import random

random.seed(42)

def generate_dataset(filename, num_points):
    points = set()
    while len(points) < num_points:
        x = random.uniform(0, 10000)
        y = random.uniform(0, 10000)
        points.add((round(x, 6), round(y, 6)))
    
    with open(filename, 'w') as f:
        for x, y in sorted(points):
            f.write(f"{x:.6f} {y:.6f}\n")

generate_dataset('dataset-20points.txt', 20)
generate_dataset('dataset-100points.txt', 100)
generate_dataset('dataset-500points.txt', 500)
generate_dataset('dataset-1000points.txt', 1000)
generate_dataset('dataset-10000points.txt', 10000)
generate_dataset('dataset-100000points.txt', 100000)
generate_dataset('dataset-1000000points.txt', 1000000)

print("All datasets generated successfully!")
