## Genera instancias de un grafo pesado completo de N nodos

import numpy as np
import random
import math
from matplotlib import pyplot as plt
random.seed(123)
MAX_COORD = 100

class Point:
    def __init__(self, x :int, y:int):
        self.x = x
        self.y = y

    def distancia(self, p):
        z = self - p
        return math.hypot(z.x, z.y)
    
    def __sub__(self, p):
        return Point(self.x - p.x, self.y - p.y)
    def __add__(self, p):
        return Point(self.x + p.x, self.y + p.y)

def generar_puntos_random(n:int = 10):
    puntos = []
    for _ in range(n):
        x = random.randint(0, MAX_COORD)  
        y = random.randint(0, MAX_COORD)  
        puntos.append(Point(x, y))
    
    return puntos

def transformar_en_grafo(puntos:list[Point]) -> list[list[float]]:
    return [[p.distancia(q) for q in puntos] for p in puntos]


def graficar(puntos: list[Point], solucion : list[int], resultado : float) -> None:
    plt.clf()
    puntos = [puntos[x] for x in solucion]
    points_x = list(map(lambda p: p.x, puntos))
    points_y = list(map(lambda p: p.y, puntos))
    points_x.append(points_x[0])
    points_y.append(points_y[0])
    plt.plot(points_x, points_y, 'mo', linestyle = '-')
    plt.title(str(resultado))
    plt.show()