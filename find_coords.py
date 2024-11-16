filename = "mob.obj"

f = open(filename, 'r')

vertices = []
vertex_norms = []
tex_coords = []

vertex_attribs = []
for line in f:
    # skip comments
    if line[0] == '#':
        continue

    # process vertex attribues
    if line[0] == 'v':
   
        if line[1] == 'n':  # normals
            coords = line[3:].split(' ')
            coords = map(float, coords)
            vertex_norms += coords
        elif line[1] == 't':  # texture coordinates
            coords = line[3:].split(' ')
            coords = map(float, coords)
            tex_coords += coords
        else:  # vertices
            coords = line[2:].split(' ')
            coords = map(float, coords)
            vertices += coords

    elif line[0] == 'f':  # build full vertex attribs array
        face = line[2:].split(' ')
        face = list(map(lambda s: s.strip('\n').split('/'), face))
        # first triangle
        for i in range(3):
            vi, vti, vni = map(int, face[i])
            vertex_attribs += [vertices[vi], vertices[vi + 1], vertices[vi + 2],
                               tex_coords[vti], tex_coords[vti + 1]]
        # second triangle
        for i in range(3):
            index = (i + 2) % 4
            vi, vti, vni = map(int, face[index])
            vertex_attribs += [vertices[vi], vertices[vi + 1], vertices[vi + 2],
                               tex_coords[vti], tex_coords[vti + 1]]



counter = 0

for val in vertex_attribs:
    if counter == 4:
        print(str(round(val, 3)) + ',')
        counter = 0
    else:
        print(round(val, 3), end=', ')
        counter += 1


