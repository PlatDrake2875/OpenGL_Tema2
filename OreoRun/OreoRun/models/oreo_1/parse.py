maxZ = -float("inf")
minX = float("inf")
minY = float("inf")
maxX = -float("inf")
maxY = -float("inf")

with open("oreo.obj", "r") as f:
    for line in f:
        literals = line.split()
        if len(literals) > 0 and literals[0] == "v":
            maxZ = max(maxZ, float(literals[3]))
            minX = min(minX, float(literals[1]))
            minY = min(minY, float(literals[2]))
            maxX = max(maxX, float(literals[1]))
            maxY = max(maxY, float(literals[2]))

print(f"maxZ: {maxZ} minX: {minX} minY: {minY} maxX: {maxX} maxY: {maxY}")