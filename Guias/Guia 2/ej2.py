def coloreable(nodo, aristas, color):
    global coloreo
    for v in aristas[nodo]:
        if coloreo[v] == color:
            return False

def coloreo(nodo, aristas, colores, coloreo):
    if nodo == len(aristas):
        if len(coloreo) > 0:
            coloreo[-1] = colores[0]
        return coloreo
    

    a = coloreo(nodo+1, aristas, colores, coloreo)
    for color in colores:
        if coloreable(nodo, aristas, color, coloreo):
            coloreo[nodo] = color
        return coloreo
    return False

colores = [0,1,2]
aristas = [[1,2], [0,2], [0,1]]
coloreo = [-1,-1,-1]
print(coloreo_posible(0, aristas, colores, coloreo))