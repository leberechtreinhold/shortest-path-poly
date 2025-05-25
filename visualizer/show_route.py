import matplotlib.pyplot as plt
import argparse
import json

def parse_json(input_file):
    file_content = ''
    with open(input_file, "r", encoding="utf-8") as f:
        file_content = f.read()
    
    data = json.loads(file_content)
    points = [tuple(pair) for pair in data["path"]]
    points.insert(0, data["start"])
    points.append(data["end"])
    
    segments = [ [tuple(p1), tuple(p2)] for p1, p2 in data["segments"] ]
    
    return points, segments
    
def main():
    parser = argparse.ArgumentParser(description="Process a result path with a route taken.")
    parser.add_argument('--input', type=str, required=True, help='Path to the input file')
    
    args = parser.parse_args()
    
    print(f"Using file: {args.input}")
    
    points, segments = parse_json(args.input)
    plt.figure(figsize=(10, 6))

    x_vals, y_vals = zip(*points)

    plt.plot(x_vals, y_vals, marker=None, linestyle='-', color='blue', label='Path Segments')
    for i in range(len(points) - 1):
        x0, y0 = points[i]
        x1, y1 = points[i + 1]
        plt.annotate(
            '', xy=(x1, y1), xytext=(x0, y0),
            arrowprops=dict(arrowstyle='->', color='blue', lw=1.5),
        )

    for x, y in points:
        plt.text(x, y + 0.5, f"({x}, {y})", fontsize=8, ha='center')

    for i, segment in enumerate(segments):
        (x1, y1), (x2, y2) = segment
        plt.plot([x1, x2], [y1, y2], marker=None, color='red', label=f"Segment {i + 1}")
        plt.text((x1 + x2) / 2, (y1 + y2) / 2 + 0.3,
                f"{i + 1}", fontsize=8, ha='center', color='gray')
        
    plt.title('Segment Path Plot')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.grid(True)
    plt.axis('equal')  # Maintain aspect ratio
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    
if __name__ == "__main__":
    main()