def f1(H):
    if H <= 0:
        return 0
    elif H == 1:
        return 1
    else:
        return f1(H - 1) * 2

def tower_count(H):
    if H <= 0:
        return 0
    elif H == 1:
        return 1
    else:
        count = 0
        for h in range(H):
            for k in range(1, H - h + 1):
                count += f1(h) * tower_count(H - h - k)
        return count

# Example usage:
H = 6
print("Number of possibilities for tower of width 2 and height", H, "is", tower_count(H))
