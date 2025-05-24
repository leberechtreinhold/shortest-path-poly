import matplotlib.pyplot as plt

# Your list of segments as coordinate tuples
points = [
    (6, 2), (7.36, 7.44), (8.24, 9.7), (11.36, 12.4), (14.24, 14.24),
    (20.24, 15.74), (23.84, 15.28), (31.042, 4.116), (30, 2)
]

segments = [
    [(5, 3), (9.68, 3.82)],
    [(2.8, 6.4), (7.36, 7.44)],
    [(4.06, 11.84), (8.24, 9.7)],
    [(6.82, 14.04), (11.36, 12.4)],
    [(4.88, 15.36), (14.24, 14.24)],
    [(12.58, 18), (17.02, 10.48)],
    [(20.24, 15.74), (18.38, 11.64)],
    [(21.58, 13.92), (22.22, 7.24)],
    [(23.84, 15.28), (25.7, 10.76)],
    [(30.1, 11.76), (25.82, 8.52)],
    [(29.282, 6.866), (25.938, 6.91)],
    [(31.042, 4.116), (28, 4)]
]

plt.figure(figsize=(10, 6))

# Separate into X and Y for plotting
x_vals, y_vals = zip(*points)

# Plot the path as connected segments
plt.plot(x_vals, y_vals, marker=None, linestyle='-', color='blue', label='Path Segments')
for i in range(len(points) - 1):
    x0, y0 = points[i]
    x1, y1 = points[i + 1]
    plt.annotate(
        '', xy=(x1, y1), xytext=(x0, y0),
        arrowprops=dict(arrowstyle='->', color='blue', lw=1.5),
    )

# Optionally annotate each point with its coordinates
for x, y in points:
    plt.text(x, y + 0.5, f"({x}, {y})", fontsize=8, ha='center')

# Plot each segment
for i, segment in enumerate(segments):
    (x1, y1), (x2, y2) = segment
    plt.plot([x1, x2], [y1, y2], marker=None, color='red', label=f"Segment {i + 1}")
    plt.text((x1 + x2) / 2, (y1 + y2) / 2 + 0.3,
             f"{i + 1}", fontsize=8, ha='center', color='gray')
    
# Customize the plot
plt.title('Segment Path Plot')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.axis('equal')  # Maintain aspect ratio
plt.tight_layout()

# Show the plot
plt.show()