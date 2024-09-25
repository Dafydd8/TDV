class Grafo:
    def __init__(self):
        self.aristas = set()
        self.nodos = set()

    def agregar_nodo(self, nodo):
        self.nodos.add(nodo)

    def agregar_arista(self, inicio, fin):
        if not self.tiene_nodo(inicio) or not self.tiene_nodo(fin):
            raise ValueError("Arista con nodo invalido")

        self.aristas.add((inicio, fin))

    def eliminar_nodo(self, nodo):
        self.aristas = filter(lambda arista: nodo not in arista, self.aristas)
        self.nodos.remove(nodo)
        
    def eliminar_nodo2(self, nodo):
        aux = set()
        for arista in self.aristas:
            if nodo not in arista:
                aux.add(arista)
        self.aristas = aux
        self.nodos.remove(nodo)

    def eliminar_arista(self, inicio, fin):
        self.aristas.remove((inicio, fin))

    def tiene_nodo(self, nodo):
        return nodo in self.nodos

    def in_degree(self, nodo):
        count = 0
        for arista in self.aristas:
            if nodo == arista[1]:
                count += 1
        return count

    def out_degree(self, nodo):
        count = 0
        for arista in self.aristas:
            if nodo == arista[0]:
                count += 1
        return count
    
    def tamanio(self):
        return len(self.nodos)
